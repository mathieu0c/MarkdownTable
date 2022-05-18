// #define ENABLE_LOG
#include "MarkdownIndex.hpp"

#include "Slugger.hpp"

namespace md{

Title parseMdLine(const std::string_view& line){
    if(empty(line))//empty line
        return {.level=-1};
    
    if(line[0] != '#')
    {
        return {.level=-1};
    }

    Title out{.level = 0,.text={}};
    // 0 -> Level tracking
    // 1 -> space between # and the actual text
    // 2 -> text
    int parsingStage{0};
    for(size_t i{}; i < size(line);++i)
    {
        if (line[i] == '\n' || line[i] == '\n')
        {
            break;
        }
        
        if(line[i] == '#' && parsingStage == 0)
        {
            ++out.level;
        }
        else if((line[i] == ' ' || line[i] == '\t') && parsingStage != 2)
        {
            continue;//whitspace between "#" and the actual title
        }
        else
        {
            out.text.reserve(size(line));
            parsingStage = 2;
            //manual copy mandatory because of windaube end line char
            for(size_t j{i}; j < size(line);++j)
            {
                const auto& c{line[j]};
                //thanks to windaube, we have to check for this
                if(c == '\n' || c == '\r')
                    break;
                out.text += c;
            }
            // out.text = line.substr(i);
            break;
        }
    }

    if(empty(out.text))//if it's an empty title
        return {.level=-1};

    return out;
}

auto getTagsIndexes(const std::string_view& mdContent,const MdIndexTags& tags){
    auto start{mdContent.find(tags.start)};
    if(start == std::string::npos)
    {
        LOGEL("\tSTART NOT FOUND <\""<<tags.start<<"\">");
        return std::pair{std::string::npos,std::string::npos};
    }
    auto end{mdContent.find(tags.end,start+size(tags.start))};
    if(end == std::string::npos)
    {
        LOGEL("\tSTART NOT FOUND <\""<<tags.end<<"\">");
        return std::pair{std::string::npos,std::string::npos};
    }

    if(start >= end)//if the starting point is after the ending point
    {
        LOGEL("\tSTART<"<<start<<"> AFTER END<"<<end<<">");
        return std::pair{std::string::npos,std::string::npos};
    }

    return std::pair{start,end};
}

std::string generateTable(const TitleList& titles,const std::string& tableTitle, const std::string& tabChar){
    std::string out{"# "+tableTitle+"\n\n"};

    //tabChar = 3*hard-space by default : AltGr+Space with Linux

    for(const auto& title : titles)
    {
        std::string line{};
        auto realLevel{title.level-1};//start at 0 instead of 1
        for(decltype(Title::level) i{};i < realLevel; ++i)
        {
            line += tabChar;
        }
        auto formattedTitle{empty(title.slug)?title.text : "["+title.text+"](#"+title.slug+")"};
        if(realLevel == 0)
        {
            formattedTitle = "**"+formattedTitle+"**";
        }
        else if(realLevel == 1)
        {
            formattedTitle = "*"+formattedTitle+"*";
        }

        line += ""+formattedTitle+"<br/>\n";
        out += line;
    }

    return out;
}

// TitleList parseMd(const std::string& filePath,const MdIndexTags& tags){
//     std::ifstream f{filePath};
//     if(!f.is_open())
//     {
//         LOGE("Error : Cannot open <"<<filePath<<">\n");
//     }

//     TitleList out{};

//     std::string line{};
//     bool checkIndex{true};
//     bool isInIndexTable{false};
//     while(std::getline(f,line))
//     {
//         if(checkIndex)//if we haven't encountered the index yet
//         {
//             if(!isInIndexTable)//if we are not yet in the index
//             {
//                 if(line.find(tags.start) != std::string::npos)//Here we go, entering the index
//                 {
//                     isInIndexTable = true;
//                     //index line, just skip it boi
//                     continue;
//                 }
//             }
//             else
//             {
//                 if(line.find(tags.end) != std::string::npos)//if we find the end table tag
//                 {
//                     isInIndexTable = false;
//                     checkIndex = false;
//                 }
//                 //index line, just skip it boi
//                 continue;
//             }
//         }

//         Title tmp{parseMdLine(line)};
//         if(tmp.level < 0)
//         {
//             continue;
//         }

//         out.emplace_back(std::move(tmp));
//     }

//     return out;
// }

namespace ram{

TitleList titlesFromContent(const std::string& mdString,const MdIndexTags& tags){
    std::stringstream ss(mdString.data());
    std::string line;

    TitleList out{};

    bool checkIndex{true};
    bool isInIndexTable{false};
    if(mdString.data() != NULL)
    {
        while(std::getline(ss, line))
        {
            if(checkIndex)//if we haven't encountered the index yet
            {
                if(!isInIndexTable)//if we are not yet in the index
                {
                    if(line.find(tags.start) != std::string::npos)//Here we go, entering the index
                    {
                        isInIndexTable = true;
                        //index line, just skip it boi
                        continue;
                    }
                }
                else
                {
                    if(line.find(tags.end) != std::string::npos)//if we find the end table tag
                    {
                        isInIndexTable = false;
                        checkIndex = false;
                    }
                    //index line, just skip it boi
                    continue;
                }
            }

        Title tmp{parseMdLine(line)};
        if(tmp.level < 0)
        {
            continue;
        }

        out.emplace_back(std::move(tmp));
        }
    }
    return out;
}

std::string insertTableInStr(const std::string& mdText,const std::string& rawTable,const MdIndexTags& tags){
    auto [tagStartPos,tagEndPos]{getTagsIndexes(mdText,tags)};
    if(tagStartPos == tagEndPos)//this should never happen and correspond to an error
    {
        LOGEL(  "Error occurred when searching for StartingTag<\""<<tags.start<<
                "\">"<<" and EndingTag<\""<<tags.end<<"\">\n"<<
                "Possible causes :\n"
                "\t- Cannot find either the start or end tag\n"<<
                "\t- End tag found before start tag");
        return mdText;
    }
    tagStartPos += size(tags.start)+1;  //set starting index to the end of the tag
                                        //let's add one for a beautiful new line
    auto finalSize{size(mdText)+size(rawTable)-(tagEndPos-tagStartPos)};
    std::string out{};
    out.resize(finalSize);



    //copy md content from start to the end of first (starting) tag
    std::copy(  cbegin(mdText),cbegin(mdText)+tagStartPos,begin(out));

    out[tagStartPos] = '\n';//do not forget to add the newline char

    //copy rawTableContent, from the end of the first (starting) tag to the output
    //after the first md content part
    std::copy(  cbegin(rawTable),cend(rawTable),begin(out)+tagStartPos);

    //copy md content from the second (ending) tag to the end to the output
    //after the first md part + the raw table content + the ending tag
    std::copy(  cbegin(mdText)+tagEndPos,cend(mdText),
                begin(out)+tagStartPos+size(rawTable));

    return out;
}

bool insertTableInFile( const std::string& inFilePath, const std::string& outFilePath,
                        const std::string& tableTitle,
                        const std::string& tabChar,
                        const MdIndexTags& tags){
    auto fContentOpt{readAll(inFilePath)};
    if(!fContentOpt)
    {
        LOGE("Error : Cannot read <"<<inFilePath<<">\n");
        return false;
    }

    std::string fContent{std::move(fContentOpt.value())};
    auto titles{titlesFromContent(fContent,tags)};
    slugify(titles,md::slugify_github);
    auto rawTable{generateTable(titles,tableTitle,tabChar)};

    // auto newContent{insertTableInStr(fContent,rawTable,tags)};

    return writeFile(outFilePath,insertTableInStr(fContent,rawTable,tags));
}

bool insertTableInFile( const std::string& inFilePath, const std::string& outFilePath,
                        const TableSettings& settings)
{
    auto fContentOpt{readAll(inFilePath)};
    if(!fContentOpt)
    {
        LOGE("Error : Cannot read <"<<inFilePath<<">\n");
        return false;
    }

    std::string fContent{std::move(fContentOpt.value())};
    auto titles{titlesFromContent(fContent,settings.tags)};
    auto rawTable{generateTable(titles,settings.title,settings.tabChar)};

    // auto newContent{insertTableInStr(fContent,rawTable,tags)};

    return writeFile(outFilePath,insertTableInStr(fContent,rawTable,settings.tags));
}

}//namespace ram
}//namespace md
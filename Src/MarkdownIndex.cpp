// #define ENABLE_LOG
#include "MarkdownIndex.hpp"

namespace md{

std::string to_string(const Title& title){
    using std::to_string;
    std::string out{"Title{.level="};
    out += to_string(title.level);
    out += ",.text=\"";
    out += title.text;
    out += "\"}";
    return out;
}

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

TitleList titlesFromStr(const std::string& mdString){
    std::stringstream ss(mdString.data());
    std::string line;

    LOGP(mdString << "\n");

    TitleList out{};

    if(mdString.data() != NULL)
    {
        while(std::getline(ss, line))
        {
            Title tmp{parseMdLine(line)};
            if(tmp.level < 0)
            {
                continue;
            }
            LOGP("Parsed and found on LINE = "<<line << "\n");

            out.emplace_back(std::move(tmp));
        }
    }
    return out;
}

std::string generateTable(const TitleList& titles,const std::string& tableTitle, const std::string& tabChar){
    std::string out{"# "+tableTitle+"\n"};

    //tabChar = 3*hard-space by default : AltGr+Space with Linux

    for(const auto& title : titles)
    {
        std::string line{};
        auto realLevel{title.level-1};//start at 0 instead of 1
        for(decltype(Title::level) i{};i < realLevel; ++i)
        {
            line += tabChar;
        }
        line += ""+title.text+"<br/>\n";
        out += line;
    }

    return out;
}

std::string insertTableInStr(const std::string& mdText,const std::string& rawTable,const MdIndexTags& tags){
    const auto regexTxt{"("+tags.start+")(.*)("+tags.end+")"};
    std::regex rx{regexTxt,std::regex::extended};

    return std::regex_replace(mdText, rx, tags.start+"\n"+rawTable+tags.end);
}

bool insertTable(const std::string& filePath,const std::string& rawTable,const MdIndexTags& tags){
    auto fContentOpt{readAll(filePath)};
    if(!fContentOpt)
    {
        LOGE("Error : Cannot read <"<<filePath<<">\n");
        return false;
    }

    std::string fContent{std::move(fContentOpt.value())};

    auto newContent{insertTableInStr(fContent,rawTable,tags)};

    writeFile(filePath,newContent);

    return true;
}

}//namespace md
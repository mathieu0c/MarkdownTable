#include <iostream>
#include <string>

#define ENABLE_LOG

#include "../Src/Log.hpp"
#include "../Src/MarkdownIndex.hpp"

void logList(const md::TitleList& list){
    LOGE("md::TitleList{\n");
    for(const auto& e : list)
    {
        LOGE("\t"<<e<<"\n");
    }
    LOGE("}\n");
}

int main(int argc,char* argv[]){
    md::MdIndexTags tags{};
    std::string mdLine{"## This is a level 2 title\nEt du texte\n"+tags.start+"\n# Index (ignoré)\nEt texte ignoré\n"+tags.end+"\n# Et un level 1\nDe nouveau du texte\nEncore\n###Et un dernier titre 3\n"
    "```\n"
    "# Et un commentaire bash qui ne devrait pas être un titre\n"
    "Avec un peu de code\n"
    "```\n"
    "# Et un nouveau titre\n"};

    auto titleList{md::ram::titlesFromContent(mdLine)};
    md::TitleList expected{{2,"This is a level 2 title"},{1,"Et un level 1"},{3,"Et un dernier titre 3"},{1,"Et un nouveau titre"}};

    if(titleList != expected)
    {
        LOGE(" -- EXPECTED --\n");
        logList(expected);
        LOGE(" -- GOT --\n");
        logList(titleList);

        return 1;
    }
    
    return 0;
}

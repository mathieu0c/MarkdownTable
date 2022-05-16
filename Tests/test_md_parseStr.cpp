#include <iostream>
#include <string>

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
    
    auto constexpr mdLine{"## This is a level 2 title\nEt du texte\n# Et un level 1\nDe nouveau du texte\nEncore\n###Et un dernier titre 3\n"};

    auto titleList{md::titlesFromStr(mdLine)};
    md::TitleList expected{{2,"This is a level 2 title"},{1,"Et un level 1"},{3,"Et un dernier titre 3"}};

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

#include <iostream>
#include <string>

#include "../Src/MarkdownIndex.hpp"


int main(int argc,char* argv[]){
    auto constexpr mdLine{"## This is a level 2 title\n\r"};
    md::Title expectedTitle{.level=2,.text="This is a level 2 title"};

    auto got{md::parseMdLine(mdLine)};
    if(got != expectedTitle)
    {
        LOGE("Expected :<" << expectedTitle << "> but got <"<<got<<">\n");
        return 1;
    }

    auto constexpr mdLine2{"### This is a level 3 title\rNotInSTR"};
    expectedTitle = {.level=3,.text="This is a level 3 title"};
    got = md::parseMdLine(mdLine2);
    if(got != expectedTitle)
    {
        LOGE("Expected :<" << expectedTitle << "> but got <"<<got<<">\n");
        return 1;
    }
    
    return 0;
}

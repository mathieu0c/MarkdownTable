#include <iostream>
#include <string>
#include <vector>


#define ENABLE_LOG

#include "Src/MarkdownIndex.hpp"

int main(int argc,char* argv[]){

    auto constexpr file{"../Tests/Inputs/Test_complex.md"};
    auto titles = md::TitleList{};
    for(int i{}; i < 100000;++i)
    {
        auto content = md::readRaw(file);
        if(!content)
        {
            LOGEL("Cannot open file " << file);
        }
        titles = md::ram::titlesFromContent(content.value());
    }

    return 0;
}

/*
<!--MARKDOWN_INDEX_BEGIN-->
<!--MARKDOWN_INDEX_END-->
*/
#include <iostream>
#include <string>
#include <vector>

#include <unordered_map>

#define ENABLE_LOG

#include "Src/MarkdownIndex.hpp"

#include "Src/PerfTools/ScopeTimer.h"

void test_setIndex(){
    // perfTools::ScopeTimer _t{__func__};

    // auto constexpr file{"../Tests/Inputs/Test.md"};
    // auto constexpr file{"C:\\Users\\Mathieu\\Documents\\MyFiles\\Programmation\\TEMP\\s7a_stm32_vscode\\README.md"};
    auto constexpr file{"../Tests/Inputs/Test_complex.md"};
    auto content{md::readRaw(file)};
    if(!content)
    {
        LOGE("Cannot open file <"<<file<<">\n");
        return;
    }
    auto titles = md::titlesFromStr(content.value());
    LOGP("----" << size(titles) << "\n");
    for(const auto& e : titles)
    {
        LOG("\t" << e << "\n";);
    }
    // auto titles = md::parseMd(file);
    auto index{md::generateTable(titles)};

    LOG("INDEX=\n"<<index<<"\n");

    // LOGP(index);
    
    // md::insertTable(file,index);
}

int main(int argc,char* argv[]){

    std::vector<std::string> argList{argv+1,argv+argc};

    for(const auto& arg : argList){
        LOG("\t Given as arg : "<<arg<<"\n");
    }

    LOG('\n');

    for(int i{}; i < 1;++i)
        test_setIndex();

    return 0;
}

/*
<!--MARKDOWN_INDEX_BEGIN-->
<!--MARKDOWN_INDEX_END-->
*/
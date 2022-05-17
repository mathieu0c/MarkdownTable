#include <iostream>
#include <string>
#include <vector>


#define ENABLE_LOG

#include "Src/MarkdownIndex.hpp"

#include "Src/PerfTools/ScopeTimer.h"

void test_setIndex(){
    // perfTools::ScopeTimer _t{__func__};

    // auto constexpr file{"../Tests/Inputs/Test.md"};
    // auto constexpr file{"C:\\Users\\Mathieu\\Documents\\MyFiles\\Programmation\\TEMP\\s7a_stm32_vscode\\README.md"};
    auto constexpr file{"../Tests/Inputs/Test_complex.md"};
    auto success{md::ram::insertTableInFile(file,file)};
    if(!success)
    {
        LOGE("Cannot add index table to <"<<file<<">");
    }
    
    LOGPL("Success : "<<success);
}

int main(int argc,char* argv[]){

    std::vector<std::string> argList{argv+1,argv+argc};

    LOGL(argv[0]);
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
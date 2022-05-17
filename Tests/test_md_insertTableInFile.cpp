#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "../Src/MarkdownIndex.hpp"

bool compareFiles(const std::string &p1, const std::string &p2)
{
    std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        LOGEL("File fail");
        return false; //file problem
    }

    if (f1.tellg() != f2.tellg())
    {
        LOGEL("Different size files 1=<"<<f1.tellg()<<"> 2=<"<<f2.tellg()<<">");
        return false; //size mismatch
    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

int main(int argc,char* argv[]){
    auto constexpr testFile_target{"../../Tests/Inputs/Test_complex_0.md"};
    auto constexpr testFile_ref{"../../Tests/Inputs/Test_complex_ref.md"};
    auto constexpr testFile_output{"result.md"};
    
    md::ram::insertTableInFile(testFile_target,testFile_output,"\\* INDEX \\*","&emsp;",{.start="<!--MARKDOWN_INDEX_BEGIN-->",.end="<!--MARKDOWN_INDEX_END-->"});
    
    return !compareFiles(testFile_ref,testFile_output);
}

#pragma once

#include "Log.hpp"

#include "MdTypes.hpp"

#include <cstdint>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <optional>

#include <regex>

namespace{

#define WINSHIT_SLOW

#ifndef WINSHIT_SLOW
std::optional<std::string> readAll(const std::string& filePath){
    std::ifstream f{filePath,std::ios::ate};//open at the end
    if(!f.is_open())
    {
        // LOGE("Error : Cannot open <"<<filePath<<">\n");
        return {};
    }
    std::string contents{};
    // std::filesystem::path p{filePath};
    
    // f.seekg(0, std::ios_base::end);
    //current position is the size because we're at the end
    contents.resize(f.tellg());//allocate memory once
    // contents.resize(file_size(p));
    f.seekg(0, std::ios_base::beg);//back to the beginning
    f.read(&contents[0], contents.size());//readAll
    return contents;
}

#else

std::optional<std::string> readAll(const std::string& filePath){
    std::ifstream ifs(filePath);
    if(!ifs.is_open())
    {
        // LOGE("Error : Cannot open <"<<filePath<<">\n");
        return {};
    }
    std::string content(std::istreambuf_iterator<char>{ifs}, {});
    return content;
}

#endif

bool writeFile(const std::string& filePath, const std::string_view& content){
    std::ofstream f(filePath,std::ios::trunc);
    if(!f.is_open())
    {
        // LOGE("Error : Cannot open <"<<filePath<<">\n");
        return false;
    }
    f.seekp(0, std::ios::beg);
    f.write(content.data(), content.size());
    f.close();
    return true;
}

} // namespace



namespace md
{
inline
auto readRaw(const std::string& filePath){ return ::readAll(filePath);}
inline
auto saveRaw(const std::string& filePath, const std::string_view& content){return ::writeFile(filePath,content);}

//---------------------------------------------------------------


Title parseMdLine(const std::string_view& line);

auto getTagsIndexes(const std::string_view& mdContent,const MdIndexTags& tags);

std::string generateTable(const TitleList& titles,const std::string& tableTitle = std::string{"\\* Index \\*"},
                          const std::string& tabChar = std::string{"&emsp;"});




namespace ram
{
// TitleList parseMd(const std::string& filePath,const MdIndexTags& tags = MdIndexTags{});
TitleList titlesFromContent(const std::string& mdString,const MdIndexTags& tags = {});



std::string insertTableInStr(const std::string& mdText,const std::string& rawTable,const MdIndexTags& tags = MdIndexTags{});

//in file
bool insertTableInFile( const std::string& inFilePath, const std::string& outFilePath,
                        const std::string& tableTitle = std::string{"\\* Index \\*"},
                        const std::string& tabChar = std::string{"&emsp;"},
                        const MdIndexTags& tags = MdIndexTags{});

bool insertTableInFile( const std::string& inFilePath, const std::string& outFilePath,
                        const TableSettings& settings);
// inline
// bool insertTableInFile( const std::string& inFilePath,
//                         const std::string& tableTitle = std::string{"\\* Index \\*"},
//                         const std::string& tabChar = std::string{"&emsp;"},
//                         const MdIndexTags& tags = MdIndexTags{})
// {
//     return insertTableInFile(inFilePath,inFilePath,tabChar,tags);
// }
} // namespace ram
} // namespace md

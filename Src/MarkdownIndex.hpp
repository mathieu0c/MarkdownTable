#pragma once

#include "Log.hpp"
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
    f.close();
    return contents;
}

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

//tags used to marks index beginning and ending
//in the md document
struct MdIndexTags{
    std::string start{"<!--MARKDOWN_INDEX_BEGIN-->"};
    std::string end{"<!--MARKDOWN_INDEX_END-->"};
};

struct TableSettings{
    std::string title{};
    std::string tabChar{};
    MdIndexTags tags{};
};

struct Title{
    int32_t level{-1};
    std::string text{};
};

using TitleList = std::vector<Title>;


std::string to_string(const Title& title);
inline
std::ostream& operator<<(std::ostream& os,const Title& title){
    return os << md::to_string(title);
}
inline
bool operator==(const Title& l, const Title& r){
    return l.level == r.level && l.text == r.text;
}

inline
std::ostream& operator<<(std::ostream& os,const TitleList list){
    os << "{";
    for(size_t i{}; i < size(list);++i){
        os << list[i];if(i != size(list)-1) os << ",";
    }
    return os << "}";
}

//---------------------------------------------------------------


Title parseMdLine(const std::string_view& line);

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

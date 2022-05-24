#pragma once

#include <cstdint>
#include <vector>
#include <ostream>

namespace md
{
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
    std::string slug{};
};


// struct InsertionResult
// {
//     bool successful;
// };


using TitleList = std::vector<Title>;


std::string to_string(const Title& title);
inline
std::ostream& operator<<(std::ostream& os,const Title& title){
    return os << md::to_string(title);
}
inline
bool operator==(const Title& l, const Title& r){
    return l.level == r.level && l.text == r.text && l.slug == r.slug;
}
inline
bool operator!=(const Title& l, const Title& r){
    return !(l == r);
}

std::ostream& operator<<(std::ostream& os,const TitleList& list);

} // namespace md

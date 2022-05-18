#include "MdTypes.hpp"

namespace md
{

std::string to_string(const Title& title){
    using std::to_string;
    std::string out{"Title{.level="};
    out += to_string(title.level);
    out += ",.text=\"";
    out += title.text;
    out += "\",.slug=\"";
    out += title.slug;
    out += "\"}";
    return out;
}

std::ostream& operator<<(std::ostream& os,const TitleList list){
    os << "{";
    for(size_t i{}; i < size(list);++i){
        os << list[i];if(i != size(list)-1) os << ",";
    }
    return os << "}";
}

} // namespace md

#pragma once

#include <string>
#include <algorithm>

namespace utils
{

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(begin(s), std::find_if(begin(s), end(s), [&](auto ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(rbegin(s), rend(s), [&](auto ch) {
        return !std::isspace(ch);
    }).base(), end(s));
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

} // namespace utils
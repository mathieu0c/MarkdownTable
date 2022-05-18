#include "Slugger.hpp"
#include "Utils.hpp"

#include <regex>
#include <algorithm>
#include <functional>


namespace md
{

std::string slugify_github(const std::string& str)
{
    // auto constexpr regexStr{"[^[:lower:][:upper:][:space:]]"};
    auto constexpr regexStr{"[^A-Za-zÀ-ÿ0-9[:space:]\\-\\\"]"};
    static std::regex re{regexStr,std::regex_constants::optimize};

    auto data{std::regex_replace(str,re,"")};
    utils::rtrim(data);

    std::transform(data.begin(), data.end(), data.begin(),[&](unsigned char c){
        return (c == ' ')?'-':std::tolower(c);
    });
    return data;
}

int32_t slugify(TitleList& titles,std::function<std::string(const std::string&)> slugFunc)
{
    int32_t count{};
    for(auto& e : titles)
    {
        auto slug{slugFunc(e.text)};
        if(!empty(slug))//we have a slug !
        {
            ++count;
            e.slug = slug;
        }
    }
    return count;
}

} // namespace md

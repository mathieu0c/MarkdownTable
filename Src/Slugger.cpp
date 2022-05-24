#include "Slugger.hpp"
#include "Utils.hpp"

#include <regex>
#include <algorithm>
#include <functional>
#include <unordered_map>

#include <iostream>


namespace md
{

std::string slugify_github(std::string str)
{
    // auto constexpr regexStr{"[^[:lower:][:upper:][:space:]]"};
    auto constexpr regexStr{"[^A-Za-zÀ-ÿ0-9[:space:]\\-\\\"]"};
    static std::regex re{regexStr,std::regex_constants::optimize};

    utils::rtrim(str);
    std::transform(str.begin(), str.end(), str.begin(),[&](unsigned char c){
        std::cout << c << "   " << char((c == ' ')?'-':std::tolower(c))<<"\n";
        return (c == ' ')?'-':std::tolower(c);
    });

    auto data{std::regex_replace(str,re,"")};
    std::cout << data << "\n";
    
    return data;
}

int32_t slugify(TitleList& titles,std::function<std::string(const std::string&)> slugFunc)
{
    int32_t count{};
    std::unordered_map<std::string,int32_t> eachSlugCount{};
    using std::to_string;
    for(auto& e : titles)
    {
        auto slug{slugFunc(e.text)};
        if(!empty(slug))//we have a slug !
        {
            ++count;
            ++eachSlugCount[slug];
            auto curCount{eachSlugCount.at(slug)};
            e.slug = ((curCount == 1)?std::move(slug):slug+"-"+to_string(curCount-1));
        }
    }
    return count;
}

} // namespace md

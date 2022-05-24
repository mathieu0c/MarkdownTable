#pragma once

#include <string>
#include <functional>

#include "MdTypes.hpp"

namespace md
{

std::string slugify_github(std::string str);

//return the number of slugs done
int32_t slugify(TitleList& titles,std::function<std::string(const std::string&)> slugFunc);

} // namespace md

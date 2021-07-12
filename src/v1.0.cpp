#include <vector>
#include <string>
#include <string_view>
#include <variant>

namespace Html {

template<const char* TagName_v, bool IsLeaf_v = false>
struct TagTree_t;

static inline constexpr char div[] { "div" };
static inline constexpr char p[] { "p" };

template<const char* TagName_v>
struct TagTree_t<TagName_v, false>
{
    std::vector< std::variant< TagTree_t<div>, TagTree_t<div, true>, TagTree_t<p>, TagTree_t<p, true> > > mLeafs {  };
};

template<const char* TagName_v>
struct TagTree_t<TagName_v, true>
{
    std::string inner { };
};

template<bool IsLeaf_v = false>
using Div_t = TagTree_t<div, IsLeaf_v>;

template<bool IsLeaf_v = false>
using P_t = TagTree_t<p, IsLeaf_v>;

template<template<const char*, bool> class Tag_t,
         const char* TagName_v,
         bool IsLeaf_v>
std::string TagToString(const Tag_t<TagName_v, IsLeaf_v>& tag)
{
    std::string result {  };
    if constexpr (IsLeaf_v) {
        result = result + "<" + TagName_v + ">" +  tag.inner + "</" + TagName_v + ">";
    } else {
        result = result + "<" + TagName_v + ">" ;
        for (auto&& t : tag.mLeafs) {
            result += std::visit([](auto&& tg){return TagToString(tg);}, t);
        }
        result = result + "</" + TagName_v + ">";
    }

    return result;
}

};

decltype(auto) div_username(std::string name)
{
    auto div { Html::Div_t<>{ } } ;
    for (std::size_t i {  }; i < 10; ++i)
    {
        div.mLeafs.push_back(Html::P_t<true>{ name });
    }
    return div;
}

#include <iostream>
int main()
{
    std::string name {  };
    std::cin >> name;
    auto treetag = Html::Div_t<>
    {
        {
            Html::P_t<true>{ "P tag"  },
            Html::Div_t<true> { "Div tag"  },
            div_username(name)
        }
    };
    std::cout << TagToString(treetag);
    return 0;
}

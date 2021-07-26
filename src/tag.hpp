#pragma once

#include <string>
#include <type_traits>
#include <valarray>
#include <variant>
#include <vector>

namespace Tag
{

template<const char* Str_v>
struct string_constant
{
    inline static constexpr auto const value { Str_v };
};

template<const char* Str_v>
inline static constexpr auto const string_constant_v =
    string_constant<Str_v>::value;

template<const char* TagName_v, class TagAttributes_t>
struct leaf_tag
{
    static inline constexpr auto value { TagName_v };
    std::string inner {  };
    TagAttributes_t attr {  };
};

template<template<const char*, class, const char*...>class TagTree_t,
         template<const char*, class>class TagLeaf_t,
         class TagAttributes_t,
         const char*... TagNames>
using TaggedUnionContainer_t =
    std::vector<std::variant<TagTree_t<TagNames,
                                       TagAttributes_t,
                                       TagNames...>...,
                             TagLeaf_t<TagNames,
                                       TagAttributes_t>...>>;

template<const char* TagName_v, class TagAttributes_t, const char*... TagNames>
struct tree_tag
{
    using VecVariant_t = TaggedUnionContainer_t<tree_tag,
                                                leaf_tag,
                                                TagAttributes_t,
                                                TagNames...>;

    static inline constexpr auto value { TagName_v };

    VecVariant_t childs {  };
};

template<const char* TgName_v, class TgAttr>
inline std::string tag_to_string(const leaf_tag<TgName_v, TgAttr>& leaf)
{
    return std::string{} + "<" + TgName_v + ">"
                         + leaf.inner
                         + "</" + TgName_v + ">";
}

template<class TgTree>
inline std::string tag_to_string(const TgTree& tree)
{
    std::string result {  };
    result = result + "<" + TgTree::value + ">";
    for (auto&& t : tree.childs) {
        result += std::visit([](auto&& tg){return tag_to_string(tg);}, t);
    }
    result = result + "</" + TgTree::value + ">";

    return result;
}

} // namespace html

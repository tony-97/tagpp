#pragma once

#include "tag_names.hpp"
#include "tag_container.hpp"

#include <string>
#include <type_traits>

namespace Html
{

struct TagAttributes
{
    //here goes the common tag attributes
};

template<class TagName>
struct leaf_tag
{
    std::string inner {  };
    TagAttributes attr {  };
};

template<class TagName>
struct tree_tag
{
    HtmlTags_t<tree_tag, leaf_tag> childs {  };
    TagAttributes attr {  };
};

template<class TgName>
inline std::string tag_to_string(const leaf_tag<TgName>& leaf)
{
    return std::string{} + TgName::open + leaf.inner + TgName::close;
}

template<class TgName>
inline std::string tag_to_string(const tree_tag<TgName>& tree)
{
    std::string result {  };
    result = result + TgName::open;
    for (auto&& t : tree.childs) {
        result += std::visit([](auto&& tg){return tag_to_string(tg);}, t);
    }
    result = result + TgName::close;

    return result;
}

} // namespace html

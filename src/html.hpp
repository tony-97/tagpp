#pragma once

#include "tag.hpp"
#include "html_tags.hpp"

namespace Html
{
    struct CommonAttributes
    {
        
    };

    template<const char* TagName_v>
    using Leaf = Tag::leaf_tag<TagName_v, CommonAttributes>;

    template<const char* TagName_v, const char*... TagNames_v>
    using Tree = Tag::tree_tag<TagName_v, CommonAttributes, TagNames_v...>;
} // namespace Html

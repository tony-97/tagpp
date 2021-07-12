#include "html.hpp"
#include <iostream>
using namespace Html;
using namespace Html::TagNames;

int main()
{
    using mycontainer = HtmlTags_t<tree_tag, leaf_tag>;
    mycontainer cont { tree_tag<struct Html> {  }, leaf_tag<Div>{} };
    tree_tag<struct Html> root_html
    {
        {
            tree_tag<P>
            {
                {
                    leaf_tag<Div> { "Hello" }
                }
            },
            leaf_tag<Div>{ "From" },
            leaf_tag<Div>{ "CPP HTML" },
            leaf_tag<Div>{ "World" }
        }
    };
    auto str { tag_to_string(root_html) };
    std::cout << str << std::endl;
    return 0;
}

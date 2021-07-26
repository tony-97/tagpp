#include "html.hpp"

#include <iostream>
#include <string>
#include <vector>

template<const char* TagName_v>
using TagTree_t = Html::Tree<TagName_v, Html::Html,
                                        Html::Body,
                                        Html::Div,
                                        Html::P>;

template<const char* TagName_v>
using TagLeaf_t = Html::Leaf<TagName_v>;

struct User_t
{
    int id {  };
    std::string name {  };
};

auto user_tag(const User_t& usr)
{
    return
    TagTree_t<Html::Div> {
        {
            TagLeaf_t<Html::P> {
                std::to_string(usr.id)
            },
            TagLeaf_t<Html::P> {
                usr.name
            }
        }
    };
}

int main()
{
    TagTree_t<Html::Div> tag_users {  };
    std::vector<User_t> vec_user { 10, User_t{1, "name"} };

    for (auto usr : vec_user) {
        tag_users.childs.push_back(user_tag(usr));
    }

    auto str { tag_to_string(tag_users) };
    std::cout << str << std::endl;

    return 0;
}

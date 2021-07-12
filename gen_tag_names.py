def make_cpp_tag_struct(tag_name, tag_open, tag_close):
    tag_struct  = "struct %s \n" % (tag_name);
    tag_struct += "{\n";
    tag_struct += "static constexpr char open[]  { \"%s\" };\n" % (tag_open)
    tag_struct += "static constexpr char close[] { \"%s\" };\n" % (tag_close)
    tag_struct += "};\n\n";
    return tag_struct;

tags = {}

with open("./tag_names.txt") as tag_names:
    for line in tag_names:
        tag_name  = line.strip().removeprefix("<") \
                                .removesuffix(">") \
                                .capitalize()
        tag_open  = line.strip();
        tag_close = tag_open.replace("<", "</")
        tags[tag_name] = (tag_open, tag_close)

f_tags = open("./generated_tag_structs.txt", "w")
f_tags_parameter_list = open("./tag_list.txt", "w")

for tag_name, [tag_open, tag_close] in tags.items():
    cpp_struct = make_cpp_tag_struct(tag_name, tag_open, tag_close)
    f_tags.write(cpp_struct)

for tag_name in tags:
    f_tags_parameter_list.write("TagNames::%s,\n" % tag_name)


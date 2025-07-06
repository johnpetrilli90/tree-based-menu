import yaml

id_counter = 0
function_set = set()

def generate_node_code(node, parent_name=None):
    global id_counter, function_set
    name = f"node_{id_counter}"
    id_counter += 1

    enter_cb = node.get("on_enter", "NULL")
    exit_cb = node.get("on_exit", "NULL")
    action_cb = node.get("on_action", "NULL")

    if enter_cb != "NULL":
        function_set.add(enter_cb)
    if exit_cb != "NULL":
        function_set.add(exit_cb)
    if action_cb != "NULL":
        function_set.add(action_cb)

    lines = []
    lines.append(f'MenuNode* {name} = CreateMenuNode("{node["name"]}", {enter_cb}, {exit_cb}, {action_cb});')
    if parent_name:
        lines.append(f'AddChild({parent_name}, {name});')

    if "children" in node:
        for child in node["children"]:
            lines += generate_node_code(child, name)

    return lines

def generate_menu_c(yaml_file, output_file, header_file="menu_callbacks.h"):
    with open(yaml_file, "r") as f:
        menu_tree = yaml.safe_load(f)

    lines = [f'#include "{header_file}"', '#include "menu.h"', '#include <stdlib.h>\n',
             'MenuSystem* BuildMenuTree() {\n',
             '    MenuSystem* system = (MenuSystem*)malloc(sizeof(MenuSystem));']
    node_lines = generate_node_code(menu_tree)
    lines += ['    ' + line for line in node_lines]
    lines += ['    system->root = node_0;', '    system->current = node_0;', '    return system;', '}']

    with open(output_file, "w") as f:
        f.write("\n".join(lines))

    with open(header_file, "w") as f:
        f.write("#pragma once\n\n// Auto-generated callback declarations\n")
        for fn in sorted(function_set):
            f.write(f"void {fn}();\n")

if __name__ == "__main__":
    generate_menu_c("menu.yaml", "menu_generated.c")

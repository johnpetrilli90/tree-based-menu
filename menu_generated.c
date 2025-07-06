#include "menu_callbacks.h"
#include "menu.h"
#include <stdlib.h>

MenuSystem* BuildMenuTree() {

    MenuSystem* system = (MenuSystem*)malloc(sizeof(MenuSystem));
    MenuNode* node_0 = CreateMenuNode("Main Menu", main_menu_enter, main_menu_exit, NULL);
    MenuNode* node_1 = CreateMenuNode("Sub Menu 1", submenu1_enter, NULL, NULL);
    AddChild(node_0, node_1);
    MenuNode* node_2 = CreateMenuNode("Option 1.1", NULL, NULL, option_1_1_action);
    AddChild(node_1, node_2);
    MenuNode* node_3 = CreateMenuNode("Option 1.2", NULL, NULL, option_1_2_action);
    AddChild(node_1, node_3);
    MenuNode* node_4 = CreateMenuNode("Sub-Sub Menu 1.3", NULL, NULL, NULL);
    AddChild(node_1, node_4);
    MenuNode* node_5 = CreateMenuNode("Option 1.3.1", NULL, NULL, option_1_3_1_action);
    AddChild(node_4, node_5);
    MenuNode* node_6 = CreateMenuNode("Sub Menu 2", submenu2_enter, NULL, NULL);
    AddChild(node_0, node_6);
    MenuNode* node_7 = CreateMenuNode("Option 2.1", NULL, NULL, option_2_1_action);
    AddChild(node_6, node_7);
    MenuNode* node_8 = CreateMenuNode("Option 2.2", NULL, NULL, option_2_2_action);
    AddChild(node_6, node_8);
    MenuNode* node_9 = CreateMenuNode("Sub Menu 3", submenu3_enter, NULL, NULL);
    AddChild(node_0, node_9);
    MenuNode* node_10 = CreateMenuNode("Option 3.1", NULL, NULL, option_3_1_action);
    AddChild(node_9, node_10);
    MenuNode* node_11 = CreateMenuNode("Option 3.2", NULL, NULL, option_3_2_action);
    AddChild(node_9, node_11);
    MenuNode* node_12 = CreateMenuNode("Option 3.3", NULL, NULL, option_3_3_action);
    AddChild(node_9, node_12);
    MenuNode* node_13 = CreateMenuNode("Sub-Sub Menu 3.4", NULL, NULL, NULL);
    AddChild(node_9, node_13);
    MenuNode* node_14 = CreateMenuNode("Option 3.4.1", NULL, NULL, option_3_4_1_action);
    AddChild(node_13, node_14);
    MenuNode* node_15 = CreateMenuNode("Option 3.4.2", NULL, NULL, option_3_4_2_action);
    AddChild(node_13, node_15);
    system->root = node_0;
    system->current = node_0;
    return system;
}
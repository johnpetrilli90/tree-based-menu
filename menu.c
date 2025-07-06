/**
 * @file menu.c
 * @brief Console-based hierarchical menu system implementation.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <conio.h>  // For _getch() on Windows
 
 #include "menu.h"
 
 /**
  * @brief Default callback for OnEnter.
  */
 void DefaultOnEnter() {
     printf("[INFO] Entered a menu.\n");
 }
 
 /**
  * @brief Default callback for OnExit.
  */
 void DefaultOnExit() {
     printf("[INFO] Exited a menu.\n");
 }
 
 /**
  * @brief Default callback for OnAction.
  */
 void DefaultOnAction() {
     printf("[ACTION] Default action executed.\n");
 }
 
 /**
  * @brief Create and initialize a new menu node.
  *
  * @param name Display name of the menu item.
  * @param onEnter Callback function for entering this menu.
  * @param onExit Callback function for exiting this menu.
  * @param onAction Callback function for taking action on this menu.
  * @return Pointer to the created MenuNode.
  */
 MenuNode* CreateMenuNode(const char* name, Callback onEnter, Callback onExit, Callback onAction) {
     MenuNode* node = (MenuNode*)malloc(sizeof(MenuNode));
     if (!node) {
         perror("Failed to allocate MenuNode");
         exit(EXIT_FAILURE);
     }
 
     node->name = name;
     node->parent = NULL;
     node->children = NULL;
     node->child_count = 0;
     node->selected_index = 0;
     node->OnEnter = onEnter ? onEnter : DefaultOnEnter;
     node->OnExit = onExit ? onExit : DefaultOnExit;
     node->OnAction = onAction ? onAction : DefaultOnAction;
     return node;
 }
 
 /**
  * @brief Adds a child menu node to a parent.
  *
  * @param parent Pointer to the parent node.
  * @param child Pointer to the child node to add.
  */
 void AddChild(MenuNode* parent, MenuNode* child) {
     parent->children = (MenuNode**)realloc(parent->children, sizeof(MenuNode*) * (parent->child_count + 1));
     if (!parent->children) {
         perror("Failed to realloc children");
         exit(EXIT_FAILURE);
     }
 
     parent->children[parent->child_count] = child;
     child->parent = parent;
     parent->child_count++;
 }
 
 /**
  * @brief Draws the current menu on the console.
  *
  * @param node The current menu node.
  */
 void DrawMenu(MenuNode* node) {
     system("cls");  // Windows-only clear screen. For Linux, use "clear"
     printf("\n=== %s ===\n", node->name);
 
     for (int i = 0; i < node->child_count; i++) {
         if (i == node->selected_index)
             printf(" > %s\n", node->children[i]->name);
         else
             printf("   %s\n", node->children[i]->name);
     }
 
     printf("\n[Use arrow keys: ↑ ↓ → Enter  ← Back]\n");
 }
 
 /**
  * @brief Handles user input and navigates the menu.
  *
  * Uses arrow keys:
  * - Up/Down to move between menu options
  * - Right (Enter) to enter a submenu or execute an action
  * - Left (Back) to return to the previous menu
  *
  * @param menuSystem Pointer to the menu system context.
  */
 void Navigate(MenuSystem* menuSystem) {
     int running = 1;
 
     while (running) {
         DrawMenu(menuSystem->current);
 
         int ch = _getch();
         if (ch == 0 || ch == 224) ch = _getch();  // Handle extended keys
 
         switch (ch) {
             case 72: // Up Arrow
                 menuSystem->current->selected_index =
                     (menuSystem->current->selected_index - 1 + menuSystem->current->child_count) %
                     menuSystem->current->child_count;
                 break;
 
             case 80: // Down Arrow
                 menuSystem->current->selected_index =
                     (menuSystem->current->selected_index + 1) % menuSystem->current->child_count;
                 break;
 
             case 75: // Left Arrow (Exit / Back)
                 menuSystem->current->OnExit();
                 if (menuSystem->current->parent) {
                     menuSystem->current = menuSystem->current->parent;
                 } else {
                     running = 0;  // Exit at root
                 }
                 break;
 
             case 77: // Right Arrow (Enter / Select)
                 if (menuSystem->current->child_count > 0) {
                     menuSystem->current = menuSystem->current->children[menuSystem->current->selected_index];
                     menuSystem->current->OnEnter();
                     menuSystem->current->selected_index = 0;
                 } else {
                     menuSystem->current->OnAction();
                     // Return to root after action
                     while (menuSystem->current->parent)
                         menuSystem->current = menuSystem->current->parent;
                 }
                 break;
 
             default:
                 break;
         }
     }
 
     system("cls");
     printf("\nExited the menu system.\n");
 }
 
#pragma once

/**
 * @file menu.h
 * @brief Core menu system API and data structures.
 */

#include <stddef.h>

/**
 * @brief Callback function type for menu actions.
 */
typedef void (*Callback)();

/**
 * @brief A node in the hierarchical menu tree.
 */
typedef struct MenuNode {
    const char* name;              /**< Display name */
    struct MenuNode* parent;       /**< Parent node pointer */
    struct MenuNode** children;    /**< Array of child node pointers */
    int child_count;               /**< Number of child nodes */
    int selected_index;            /**< Currently selected index */
    Callback OnEnter;              /**< Enter callback */
    Callback OnExit;               /**< Exit callback */
    Callback OnAction;             /**< Action callback */
} MenuNode;

/**
 * @brief A handle for navigating the menu tree.
 */
typedef struct {
    MenuNode* root;     /**< Root menu node */
    MenuNode* current;  /**< Current selected menu node */
} MenuSystem;

/**
 * @brief Create and initialize a new menu node.
 *
 * @param name Display name
 * @param onEnter Callback for entering node
 * @param onExit Callback for exiting node
 * @param onAction Callback for selecting node
 * @return Pointer to the created MenuNode
 */
MenuNode* CreateMenuNode(const char* name, Callback onEnter, Callback onExit, Callback onAction);

/**
 * @brief Add a child node to a parent menu node.
 *
 * @param parent Parent node
 * @param child Child node to be added
 */
void AddChild(MenuNode* parent, MenuNode* child);

/**
 * @brief Run the menu system interactively using arrow key input.
 *
 * @param menuSystem Pointer to the menu system instance
 */
void Navigate(MenuSystem* menuSystem);



/**
 * @file main.c
 * @brief Entry point for the menu simulation application.
 */

 #include <stdio.h>
 #include "menu.h"             // Menu system core
 #include "menu_generated.h"  // Auto-generated menu structure
 #include "menu_callbacks.h"   // Declarations of callback functions
 #include "oled_sim.h"         // OLED display simulation
 
 /**
  * @brief Application entry point.
  */
 int main(void) {
     // Build menu tree from auto-generated file
     MenuSystem* menuSystem = BuildMenuTree();
 
     // Start menu navigation loop
     Navigate(menuSystem);
 
     // Cleanup and exit
     printf("Exited menu system.\n");
     return 0;
 }
 
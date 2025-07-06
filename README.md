# Embedded Hierarchical Menu System (Console & Embedded Compatible)

This project implements a **hierarchical, recursive menu system** in C for use in **embedded systems** or **PC simulation**. It supports flexible navigation, dynamic menu generation from YAML files, and simulated OLED or console-based rendering.

---

## 🚀 Features

- Recursive tree-based menu structure (arbitrary depth)
- Navigation via arrow keys:
  - `↑ / ↓` → Navigate menu options
  - `→` → Enter submenu or trigger action
  - `←` → Go back to previous menu
- `OnEnter`, `OnExit`, and `OnAction` callback support
- Circular navigation (wrap-around at ends)
- Dynamic generation from a `YAML` configuration file
- Console-based and simulated-OLED-based rendering
- Designed to run on:
  - Embedded targets (e.g., STM32, AVR, etc.)
  - PC simulation (Windows/Linux)

---

## 📁 File System Structure

```text
project/
├── main.c                 # Entry point
├── menu.c                 # Core menu logic
├── menu.h                 # Menu structure and API
├── menu.yaml              # YAML menu definition (user editable)
├── generate_menu.py       # Python script to generate C code
├── menu_generated.c       # GENERATED: menu tree from YAML
├── menu_callbacks.h       # GENERATED: callback declarations
├── your_callbacks.c       # User-implemented callback functions
├── oled_sim.c / oled_sim.h# OPTIONAL: OLED 96x32 bitmap simulator
├── Makefile               # Build system
├── oled.bmp               # OUTPUT: simulated OLED screen image (if used)
```

---

## ⚙️ MenuNode Structure

```c
typedef struct MenuNode {
    const char* name;              // Display name
    struct MenuNode* parent;       // Pointer to parent node
    struct MenuNode** children;    // Dynamic array of child nodes
    int child_count;               // Number of child nodes
    int selected_index;            // Current selection index
    Callback OnEnter;              // Called on entering this node
    Callback OnExit;               // Called on exiting this node
    Callback OnAction;             // Called if node is selected (leaf)
} MenuNode;
```

---

## ✍️ Configuring the Menu in YAML

Your menu structure is defined in `menu.yaml`:

```yaml
name: Main Menu
on_enter: main_menu_enter
on_exit: main_menu_exit
children:
  - name: Sub Menu 1
    on_enter: submenu1_enter
    children:
      - name: Option 1.1
        on_action: option_1_1_action
      - name: Sub-Sub Menu
        children:
          - name: Option 1.2.1
            on_action: option_1_2_1_action
  - name: Sub Menu 2
    children:
      - name: Option 2.1
        on_action: option_2_1_action
```

### 🔧 Callback Fields:
- `on_enter`: Called when menu is selected
- `on_exit`: Called when leaving this menu
- `on_action`: Called if the node has no children and is selected

Each callback must be implemented by you in `your_callbacks.c`.

---

## 🐍 Python Generator

### Usage:
```bash
python generate_menu.py
```

### What It Does:
- Parses `menu.yaml`
- Generates:
  - `menu_generated.c`: Full C source with tree structure
  - `menu_callbacks.h`: Declares all referenced callbacks

These files are **regenerated every time** — do not edit them manually.

---

## 🧑‍💻 Implementing Callbacks

```c
#include <stdio.h>

void main_menu_enter()  { printf("Entered Main Menu\n"); }
void main_menu_exit()   { printf("Exited Main Menu\n"); }
void submenu1_enter()   { printf("Entered Sub Menu 1\n"); }
void option_1_1_action(){ printf("Option 1.1 Selected!\n"); }
void option_1_2_1_action() { printf("Deep option selected!\n"); }
void option_2_1_action(){ printf("Option 2.1 Selected!\n"); }
```

---

## 🛠️ Makefile & Compilation

### 💡 Makefile Targets:
```makefile
CC = gcc
CFLAGS = -Wall -std=c99

SRC = main.c menu.c menu_generated.c your_callbacks.c oled_sim.c
OBJ = $(SRC:.c=.o)

TARGET = menu_sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET) *.bmp

.PHONY: all clean
```

### 🔨 Build and Run:
```bash
make             # Build the project
./menu_sim       # Run it in the terminal
```

If using Windows: run `menu_sim.exe`.

### 🧹 Clean:
```bash
make clean
```

---

## 🧪 Simulated OLED Output (Optional)

If you include `oled_sim.c`:
- The screen is rendered to a file called `oled.bmp`
- You can open it to view the 96×32 monochrome output

This is useful for visually testing how the menu will appear on embedded OLEDs.

---

## 🤖 Tips for Embedded Integration

- Replace `_getch()` and `printf()` with:
  - Hardware input (buttons, encoders, touchscreen)
  - Display drivers (e.g., SSD1306 or SH1106 for I2C/SPI OLEDs)
- Replace `system("cls")` with display clear calls
- Consider allocating menu nodes statically (preallocated array)
- `menu_generated.c` can be included directly in your embedded project
- Use function pointers to route to tasks, state transitions, or UI views

---

## 🧠 Troubleshooting

| Problem                        | Solution                                      |
|-------------------------------|-----------------------------------------------|
| Arrow keys don't work         | Make sure you're on a terminal that supports them. Try Windows CMD or run in raw mode on Linux. |
| `menu_generated.c` not found  | Run `python3 generate_menu.py`                |
| Missing callbacks             | Implement the function in `your_callbacks.c`  |
| Menu not updating             | Are you calling `Navigate(menuSystem)` in `main()`? |

---

## 📌 Future Features (Suggestions)

- Paging support for long menus
- Search/filtering
- EEPROM save/load of last selected item
- Multiple menu root contexts (tabs/views)
- Real-time input hooks for encoder/button handling

---

## 📷 Screenshot (Console Example)

```
=== Main Menu ===
 > Sub Menu 1
   Sub Menu 2

[Use arrow keys: ↑ ↓ → Enter  ← Back]
```

---

## 🧾 License

MIT License (feel free to use and modify in commercial/embedded products)

---


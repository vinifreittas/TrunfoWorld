# 🌍 TrunfoWorld

**TrunfoWorld** is a recreation of the classic **Super Trunfo – Countries** card game, built entirely in **C** and played directly in the **terminal**.  

Challenge the machine in duels of geographic, economic, and demographic attributes and find out who truly dominates the world map! 🃏

---

## ✨ Features

- 📊 **Real Attributes:** Compare Population, Area, GDP, Tourist Attractions, and Population Density (where the lowest wins!).
- 🖥️ **Rich Interface:** Retro-modern visual experience in the terminal using colors (ANSI escape codes) and ASCII art.
- ⚙️ **Dynamic Management (CRUD):** Complete system to add, remove, and update country cards directly in code or in save files.
- 🎲 **Authentic Mechanics:** Robust shuffle algorithm (*Fisher-Yates*) and fair deck partitioning.
- 💾 **Data Persistence:** Automatic deck saving and loading via binary files (`.bin`).

---

## 🛠️ Technologies and Concepts Used

- **Language:** C (C17 Standard)
- **Build Tool:** CMake (version 3.10 or newer)
- **Data Structures:** Dynamic lists (dynamically allocated arrays with `realloc`)
- **File Handling:** Binary I/O (`fread`, `fwrite`) for progress persistence
- **Modularization:** Clear separation of responsibilities (`engine.h/c`, `utilitarios.h/c`, `main.c`)

---

## 🚀 How to Build and Play

### Prerequisites
Before you start, make sure you have the following installed:
- A C compiler (such as `gcc` or `clang`)
- [CMake](https://cmake.org) (version 3.10 or newer)

### 1. Clone the Repository
```bash
git clone https://github.com
cd TrunfoWorld
```

### 2. Configure and Build with CMake
Create a folder to keep build artifacts organized:
```bash
cmake -S . -B build
cmake --build build
```

### 3. Run the Game
The executable will be generated inside the build directory:
```bash
./build/TrunfoWorld
```
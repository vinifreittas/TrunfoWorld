# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(TrunfoWorld LANGUAGES C)

# C language standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Header files directory
include_directories(include)

# Source files list (.c)
set(SOURCES
    src/main.c
    src/engine.c
    src/utilitarios.c
)

# Final executable target and required sources
add_executable(TrunfoWorld ${SOURCES})
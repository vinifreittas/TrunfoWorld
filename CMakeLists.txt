# Versão mínima do CMake necessária
cmake_minimum_required(VERSION 3.10)

# Nome do projeto e linguagem utilizada
project(TrunfoWorld LANGUAGES C)

# Padrão do C utilizado 
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Pasta dos cabeçalhos
include_directories(include)

# Lista dos arquivos de código fonte (.c)
set(SOURCES
    src/main.c
    src/engine.c
    src/utilitarios.c
)

# Nome do executável final e os arquivos necessários para gerá-lo
add_executable(TrunfoWorld ${SOURCES})
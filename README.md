# 🌍 TrunfoWorld

**TrunfoWorld** é uma recriação do clássico jogo de cartas **Super Trunfo – Países**, desenvolvida inteiramente em **C** e jogada diretamente no **terminal**.  

Desafie a máquina em duelos de atributos geográficos, econômicos e demográficos e descubra quem realmente domina o mapa-múndi! 🃏

---

## ✨ Funcionalidades

- 📊 **Atributos Reais:** Compare População, Área, PIB, Pontos Turísticos e Densidade Populacional (onde a menor vence!).
- 🖥️ **Interface Rica:** Experiência visual retro-moderna no terminal utilizando cores (ANSI escape codes) e ASCII art.
- ⚙️ **Gerenciamento Dinâmico (CRUD):** Sistema completo para adicionar, remover e atualizar cartas de países diretamente no código ou em arquivos de registro.
- 🎲 **Mecânica Autêntica:** Algoritmo de embaralhamento robusto (*Fisher-Yates*) e distribuição justa de porções do baralho.
- 💾 **Persistência de Dados:** Salvamento e leitura automática do baralho via arquivos binários (`.bin`).

---

## 🛠️ Tecnologias e Conceitos Utilizados

- **Linguagem:** C (Padrão C17)
- **Ferramenta de Build:** CMake (versão 3.10 ou superior)
- **Estruturas de Dados:** Listas Dinâmicas (Vetores Alocados Dinamicamente com `realloc`)
- **Manipulação de Arquivos:** I/O Binário (`fread`, `fwrite`) para persistência do progresso
- **Modularização:** Divisão limpa de responsabilidades (`engine.h/c`, `utilitarios.h/c`, `main.c`)

---

## 🚀 Como Compilar e Jogar

### Pré-requisitos
Antes de começar, você precisará ter instalado em sua máquina:
- Um compilador C (como `gcc` ou `clang`)
- [CMake](https://cmake.org) (versão 3.10 ou superior)

### 1. Clonar o Repositório
```bash
git clone https://github.com
cd TrunfoWorld
```

### 2. Configurar e Compilar com CMake
Crie uma pasta para organizar os arquivos gerados pela compilação:
```bash
cmake -S . -B build
cmake --build build
```

### 3. Executar o Jogo
O executável será gerado dentro do diretório de build:
```bash
./build/TrunfoWorld
```
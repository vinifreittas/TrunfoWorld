#ifndef ENGINE_H
#define ENGINE_H

#include <stddef.h>   // Required for size_t
#include <stdbool.h>  // Required for bool type

#define ARQUIVO_REGISTRO "registro.bin"

/* ========================== Structures ========================== */

typedef struct {
    char codigo[10];
    char estado;                // Example: 'A', 'B'
    int cidade;                 // Example: 1, 2, 3...
    unsigned int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Carta;

typedef struct {
    Carta* cartas;
    size_t tamanho;
    size_t capacidade;
} Lista_de_cartas;

/* ========================== Enumerations ========================== */

// Attribute index
typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    PONTOS_TURISTICOS,
    DENSIDADE_POPULACIONAL,
    PIB_PER_CAPITA
} Atributo;

// Competition result
typedef enum { 
    ERRO, 
    VITORIA_JOGADOR_1, 
    VITORIA_JOGADOR_2, 
    EMPATE 
} Resultado_competicao;

/* ========================== Prototypes ========================== */

// List management
Lista_de_cartas inicializar_lista();
bool alocar_espaco(Lista_de_cartas *lista, size_t quantidade);
void finalizar_lista(Lista_de_cartas *lista);
Lista_de_cartas copiar_lista(const Lista_de_cartas *origem);

// Registry (File persistence)
Lista_de_cartas ler_registro();
bool atualizar_registro(const Lista_de_cartas *lista);

// Card CRUD
bool adicionar_carta_lista(Lista_de_cartas *lista, Carta nova);
bool remover_carta_lista(Lista_de_cartas *lista, const char *codigo);
bool atualizar_carta_lista(Lista_de_cartas *lista, const char *codigo, Carta nova);

// Handling and gameplay
bool embaralhar_lista(Lista_de_cartas *lista);
Lista_de_cartas porcionar_lista(Lista_de_cartas lista, int numero_de_porcoes, int porcao);

// Game logic
bool distribuir_cartas(const Lista_de_cartas *lista, Lista_de_cartas *jogadores[], int qtd_jogadores);
Resultado_competicao competir_atributo(Atributo atr, const Carta *c1, const Carta *c2);
bool transferir_carta_topo(Lista_de_cartas *perdedor, Lista_de_cartas *vencedor);

#endif
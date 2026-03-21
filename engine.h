#ifndef ENGINE_H
#define ENGINE_H

#include <stddef.h>   // Necessário para size_t
#include <stdbool.h>  // Necessário para o tipo bool

#define ARQUIVO_REGISTRO "registro.bin"

/* ========================== Estruturas ========================== */

typedef struct {
    char codigo[10];
    char estado;                // Ex: 'A', 'B'
    int cidade;                 // Ex: 1, 2, 3...
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

/* ========================== Enumerações ========================== */

// Index dos atributos
typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    PONTOS_TURISTICOS,
    DENSIDADE_POPULACIONAL,
    PIB_PER_CAPITA
} Atributo;

// Resultado da competição
typedef enum { 
    ERRO, 
    VITORIA_JOGADOR_1, 
    VITORIA_JOGADOR_2, 
    EMPATE 
} Resultado_competicao;

/* ========================== Protótipos ========================== */

// Utilitários
bool showError(const char* error_msg);

// Gerenciamento de Lista
Lista_de_cartas inicializar_lista();
bool alocar_espaco(Lista_de_cartas *lista, size_t quantidade);
void finalizar_lista(Lista_de_cartas *lista);
Lista_de_cartas copiar_lista(const Lista_de_cartas *origem);

// Registro (Persistência em Arquivo)
Lista_de_cartas ler_registro();
bool atualizar_registro(const Lista_de_cartas *lista);

// CRUD de Cartas
bool adicionar_carta_lista(Lista_de_cartas *lista, Carta nova);
bool remover_carta_lista(Lista_de_cartas *lista, const char *codigo);
bool atualizar_carta_lista(Lista_de_cartas *lista, const char *codigo, Carta nova);

// Manipulação e Gameplay
bool embaralhar_lista(Lista_de_cartas *lista);
Lista_de_cartas porcionar_lista(Lista_de_cartas lista, int numero_de_porcoes, int porcao);

// Lógica do jogo
bool distribuir_cartas(const Lista_de_cartas *lista, Lista_de_cartas *jogadores[], int qtd_jogadores);
Resultado_competicao competir_atributo(Atributo atr, const Carta *c1, const Carta *c2);
bool transferir_carta_topo(Lista_de_cartas *perdedor, Lista_de_cartas *vencedor);

#endif

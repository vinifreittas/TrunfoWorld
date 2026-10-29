#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utilitarios.h"
#include "engine.h"


/* ========================== Card List  ========================== */

Lista_de_cartas inicializar_lista() {
    return (Lista_de_cartas) {NULL, 0, 0};
}

bool alocar_espaco(Lista_de_cartas *lista, size_t quantidade) {
    size_t nova_capacidade = lista->capacidade + quantidade;
    
    Carta *novo = realloc(lista->cartas, sizeof(Carta) * nova_capacidade);
    if (!novo && nova_capacidade > 0)
        return showError("Realocação de memória falhou!");
    
    lista->cartas = novo;
    lista->capacidade = nova_capacidade;
    return true;
}

void finalizar_lista(Lista_de_cartas *lista) {
    free(lista->cartas);
    *lista = (Lista_de_cartas) {NULL, 0, 0};
}

Lista_de_cartas copiar_lista(const Lista_de_cartas *origem) {
    Lista_de_cartas copia = inicializar_lista();
    alocar_espaco(&copia, origem->tamanho);

    memcpy(copia.cartas, origem->cartas, sizeof(Carta) * origem->tamanho);
    copia.tamanho = origem->tamanho;

    return copia;
}


/* ========================== Registry ========================== */

Lista_de_cartas ler_registro() {
    Lista_de_cartas lista = inicializar_lista();
    FILE *registro = fopen(ARQUIVO_REGISTRO, "rb");
    if (!registro) return lista;

    Carta temp;
    while (fread(&temp, sizeof(Carta), 1, registro)) {
        if (!alocar_espaco(&lista, 1)) break;
        lista.cartas[lista.tamanho++] = temp;
    }
    fclose(registro);
    return lista;
}

bool atualizar_registro(const Lista_de_cartas *lista) {
    if (!lista || !lista->cartas)
        return showError("Erro ao ler lista (lista vazia)");

    FILE *registro = fopen(ARQUIVO_REGISTRO, "wb");
    if (!registro) 
        return showError("Erro ao abrir arquivo para atualização");

    size_t escritos = fwrite(lista->cartas, sizeof(Carta), lista->tamanho, registro);
    fclose(registro);

    return (escritos == lista->tamanho);
}

/* ========================== CRUD (card list) ========================== */

long long buscar_carta_por_codigo(const Lista_de_cartas *lista, const char *codigo) {
    if (!lista || !lista->cartas) return -1;
    for (size_t i = 0; i < lista->tamanho; i++) {
        if (strcmp(lista->cartas[i].codigo, codigo) == 0) {
            return (long long)i;
        }
    }
    return -1;
}

bool adicionar_carta_lista(Lista_de_cartas *lista, Carta nova) {
    if (!lista) return false;
    
    if (buscar_carta_por_codigo(lista, nova.codigo) != -1)
        return showError("Codigo de carta já existente!");
    
    if (!alocar_espaco(lista, 1)) return false;
    
    lista->cartas[lista->tamanho++] = nova;
    return true;
}

bool remover_carta_lista(Lista_de_cartas *lista, const char *codigo) {
    if (!lista || !lista->cartas) 
        return showError("Lista de cartas zerada!");

    long long indice = buscar_carta_por_codigo(lista, codigo);
    if (indice == -1) return showError("Carta não encontrada!");

    for (size_t j = indice; j < lista->tamanho - 1; j++) {
        lista->cartas[j] = lista->cartas[j + 1];
    }
    lista->tamanho--;

    return true;
}

bool atualizar_carta_lista(Lista_de_cartas *lista, const char *codigo, Carta nova) {
    long long indice = buscar_carta_por_codigo(lista, codigo);
    if (indice == -1) return showError("Carta não encontrada!");

    lista->cartas[indice] = nova;
    return true;
}


/* ========================== Handling ========================== */

// Fisher-Yates algorithm for shuffling
bool embaralhar_lista(Lista_de_cartas *lista) {
    if (!lista || lista->tamanho <= 1) 
        return showError("Não é possível realizar o embaralhamento! (cartas insuficientes)");

    for (size_t i = lista->tamanho - 1; i > 0; i--) {
        size_t j = (size_t) rand() % (i + 1);
        Carta temp = lista->cartas[i];  
        lista->cartas[i] = lista->cartas[j];
        lista->cartas[j] = temp;
    }
    return true;
}

Lista_de_cartas porcionar_lista(Lista_de_cartas lista, int numero_de_porcoes, int porcao) {
    Lista_de_cartas mao = inicializar_lista();
    if (numero_de_porcoes <= 0 || porcao < 0 || porcao >= numero_de_porcoes) return mao;

    size_t tamanho_ajustado = lista.tamanho - (lista.tamanho % numero_de_porcoes);
    size_t cartas_por_porcao = (size_t) tamanho_ajustado / numero_de_porcoes;

    alocar_espaco(&mao, cartas_por_porcao);
    
    size_t indice_inicial = (cartas_por_porcao) * (porcao);
    memcpy(mao.cartas, lista.cartas + indice_inicial, sizeof(Carta) * cartas_por_porcao); // Copies the card block to the hand.
    mao.tamanho = cartas_por_porcao;

    return mao;
}

/* ========================== Game Logic ========================== */

bool distribuir_cartas(const Lista_de_cartas *lista, Lista_de_cartas *jogadores[], int qtd_jogadores) {
    if (lista->tamanho < qtd_jogadores) 
        return showError("Cartas insuficientes!");
    if (qtd_jogadores < 2)
        return showError("Jogadores insuficientes!");

    // Creates a list copy
    Lista_de_cartas copia = copiar_lista(lista);

    embaralhar_lista(&copia);

    for (int i = 0; i < qtd_jogadores; i++) {
        Lista_de_cartas *jogador = jogadores[i];
        *jogador = porcionar_lista(copia, qtd_jogadores, i);
    }
    finalizar_lista(&copia);
    return true;
}

Resultado_competicao competir_atributo(Atributo atr, const Carta *c1, const Carta *c2) {
    double v1, v2;
    bool menor_vence = false;

    // Maps the enum to the struct's actual values
    switch (atr) {
        case POPULACAO:
            v1 = (double)c1->populacao;
            v2 = (double)c2->populacao;
            break;
        case AREA:
            v1 = c1->area;
            v2 = c2->area;
            break;
        case PIB:
            v1 = c1->pib;
            v2 = c2->pib;
            break;
        case PONTOS_TURISTICOS:
            v1 = (double)c1->pontos_turisticos;
            v2 = (double)c2->pontos_turisticos;
            break;
        case DENSIDADE_POPULACIONAL:
            v1 = c1->densidade_populacional;
            v2 = c2->densidade_populacional;
            menor_vence = true; // Special rule: lower density wins
            break;
        case PIB_PER_CAPITA:
            v1 = c1->pib_per_capita;
            v2 = c2->pib_per_capita;
            break;
        default:
            return ERRO;
    }

    if (v1 == v2) return EMPATE;

    if (menor_vence) {
        return (v1 < v2) ? VITORIA_JOGADOR_1 : VITORIA_JOGADOR_2;
    } else {
        return (v1 > v2) ? VITORIA_JOGADOR_1 : VITORIA_JOGADOR_2;
    }
}

bool transferir_carta_topo(Lista_de_cartas *perdedor, Lista_de_cartas *vencedor) {
    if (!perdedor || perdedor->tamanho == 0 || !vencedor) return false;

    Carta carta = perdedor->cartas[0];

    if (!adicionar_carta_lista(vencedor, carta)) return false;

    for (size_t i = 0; i < perdedor->tamanho - 1; i++) {
        perdedor->cartas[i] = perdedor->cartas[i + 1];
    }
    perdedor->tamanho--;

    return true;
}
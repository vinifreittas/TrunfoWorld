#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include "utilitarios.h"

#define RESET "\033[0m"


/* ========================== Impressão ========================== */

void limpar_tela(void) {
    printf("\033[H\033[J");
}

bool showError(const char *error_msg) {
    printf("Erro: %s\n", error_msg);
    return false;
}

void imprimir_mensagem(char *msg, char *formatacao) {
    printf("\n %s%s%s \n", formatacao, msg, RESET); 
    sleep(2);
}


/* ========================== Validação ========================== */

// Limpa o buffer e retorna 1 se houver lixo
int limpar_buffer() {
    int c;
    int lixo = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isspace(c)) lixo = 1;
    }
    return lixo;
}

int ler_inteiro(const char *mensagem, int min, int max) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%i", &valor) != 1) {
            printf("Erro: Digite apenas números inteiros.\n");
            limpar_buffer();
            continue;
        }
        
        if (limpar_buffer()) {
            printf("Erro: Entrada inválida. Não digite letras junto com os números.\n");
            continue;
        }
        
        if (valor < min || valor > max) {
            printf("Erro: O valor deve estar entre %i e %i.\n", min, max);
            continue;
        }
        return valor;
    }
}

float ler_float(const char *mensagem, float min, float max) {
    float valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) != 1) {
            printf("Erro: Digite um número decimal válido.\n");
            limpar_buffer();
            continue;
        }
        
        if (limpar_buffer()) {
            printf("Erro: Entrada inválida. Não digite letras junto com os números.\n");
            continue;
        }
        
        if (valor < min || valor > max) {
            printf("Erro: O valor deve estar entre %.2f e %.2f.\n", min, max);
            continue;
        }
        return valor;
    }
}

char ler_char(const char *mensagem, char min, char max) {
    char valor;
    char min_up = toupper((unsigned char)min);
    char max_up = toupper((unsigned char)max);
    
    while (1) {
        printf("%s", mensagem);
        if (scanf(" %c", &valor) != 1) {
            limpar_buffer();
            continue;
        }
        
        if (limpar_buffer()) {
            printf("Erro: Digite apenas um único caractere.\n");
            continue;
        }
        
        valor = toupper((unsigned char)valor);
        if (valor < min_up || valor > max_up) {
            printf("Erro: Digite uma letra entre %c e %c.\n", min_up, max_up);
            continue;
        }
        return valor;
    }
}

unsigned int ler_unsigned(const char *mensagem, unsigned int min, unsigned int max) {
    unsigned int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%u", &valor) != 1) {
            printf("Erro: Digite apenas números inteiros positivos.\n");
            limpar_buffer();
            continue;
        }
        
        if (limpar_buffer()) {
            printf("Erro: Entrada inválida. Não digite letras junto com os números.\n");
            continue;
        }
        
        if (valor < min || valor > max) {
            printf("Erro: O valor deve estar entre %u e %u.\n", min, max);
            continue;
        }
        return valor;
    }
}

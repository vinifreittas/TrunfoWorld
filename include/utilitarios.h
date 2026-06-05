#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define RESET "\033[0m"

/* ========================== Impressão ========================== */

void limpar_tela(void);

bool showError(const char *error_msg);

void imprimir_mensagem(char *msg, char *formatacao);


/* ========================== Validação ========================== */

int limpar_buffer(void);

int ler_inteiro(const char *mensagem, int min, int max);

float ler_float(const char *mensagem, float min, float max);

char ler_char(const char *mensagem, char min, char max);

unsigned int ler_unsigned(const char *mensagem, unsigned int min, unsigned int max);

#endif /* UTILS_H */

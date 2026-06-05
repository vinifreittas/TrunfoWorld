// ==================================================================
// Super Trunfo - Países
// Versão 7.5 - Modularização ++
// Objetivo: modularizar o código e deixar ele mais escalável e profissional
// ==================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>
#include "engine.h"
#include "utilitarios.h"

// Estilos de texto (ANSI)
#define NEGRITO "\033[1m"
#define ITALICO "\033[3m"
#define AZUL "\033[1;34m"
#define VERDE "\033[1;32m"
#define VERMELHO "\033[1;31m"
#define RESET "\033[0m"

// Codificação pro tipo de exibição
typedef enum { COMPLETO, SIMPLIFICADO } Modo_exibicao;


/* ========================== Funcionalidades ========================== */

void cadastrar_carta(Lista_de_cartas *registro) {
    Carta dados;
    limpar_tela();

    printf("Bem-vindo ao sistema de cadastro de cartas!\n");
    printf("Para o cadastro de sua carta, preencha os dados solicitados a seguir...\n");

    dados.estado = ler_char("\n Letra do Estado (A a H): ", 'A', 'H');

    dados.cidade = ler_inteiro("\n Número da cidade (01 a 04): ", 1, 4);

    dados.populacao = ler_unsigned("\n População: ", 1, 4000000000U);   

    dados.area = ler_float("\n Área territorial (em km²): ", 0.01f, 10000000.0f);

    dados.pib = ler_float("\n PIB (em bilhões): ", 0.0f, 100000.0f);

    dados.pontos_turisticos = ler_inteiro("\n N° de pontos turísticos: ", 0, 10000);

    // Cálculos automáticos
    dados.densidade_populacional = (float) dados.populacao / dados.area;
    dados.pib_per_capita = (float) (dados.pib * 1000000000) / dados.populacao;
    snprintf(dados.codigo, sizeof(dados.codigo), "%c%02i", dados.estado, dados.cidade);

    if (!adicionar_carta_lista(registro, dados)) return;
    if (!atualizar_registro(registro)) return;

    imprimir_mensagem("Carta registrada com sucesso!", VERDE);
}

void remover_carta(Lista_de_cartas *registro) {
    char codigo[10];
    printf("\nQual o código da carta? (Ex: A01) -> ");
    scanf("%9s", codigo);

    if (!remover_carta_lista(registro, codigo)) return;
    if (!atualizar_registro(registro)) return;

    imprimir_mensagem("Carta excluida com sucesso!", VERDE);
}

void exibir_carta(const Carta dados, Modo_exibicao modo) {
    switch (modo) {
        case COMPLETO:
            printf("Cidade %s[%s]%s \n\n", AZUL, dados.codigo, RESET);

            printf("População: %u hab. \n", dados.populacao);
            printf("Área territorial: %.2f km² \n", dados.area);
            printf("PIB: %.2f bilhões \n", dados.pib);
            printf("N° de pontos turisticos: %i \n\n", dados.pontos_turisticos);

            printf("Densidade populacional: %.2f hab. por km² \n", dados.densidade_populacional);
            printf("PIB per capita: %.2f reais \n\n", dados.pib_per_capita);
            break;
        
        case SIMPLIFICADO:
            char codigo[40];
            snprintf(codigo, sizeof(codigo), "%s[%s]%s", AZUL, dados.codigo, RESET);

            printf("%-15s População: %u hab.\n", codigo, dados.populacao);
            printf("%-5s Área: %.2f km²\n", "", dados.area);
            printf("%-5s PIB: %.2f bi.\n", "", dados.pib);
            printf("%-5s Pontos turísticos: %i\n", "", dados.pontos_turisticos);
            break;
    }
}

Resultado_competicao competir_atributo_UI(Atributo atr, Carta carta, Carta oponente) {
    limpar_tela();
    
    switch (atr) {
            case POPULACAO: 
                printf("População: %u  VS  %u", carta.populacao, oponente.populacao);
                break;

            case AREA: 
                printf("Área: %.2f  VS  %.2f", carta.area, oponente.area);
                break;

            case PIB: 
                printf("PIB: %.2f  VS  %.2f", carta.pib, oponente.pib);
                break;

            case PONTOS_TURISTICOS: 
                printf("Pontos turisticos: %i  VS  %i", carta.pontos_turisticos, oponente.pontos_turisticos);
                break;

            case DENSIDADE_POPULACIONAL: 
                printf("Densidade populacional: %.2f  VS  %.2f", carta.densidade_populacional, oponente.densidade_populacional);
                break;

            case PIB_PER_CAPITA: 
                printf("PIB per capita: %.2f  VS  %.2f", carta.pib_per_capita, oponente.pib_per_capita);
                break;

            default:
                imprimir_mensagem("\nAtributo inválido!", NEGRITO);
    }

    Resultado_competicao resultado = competir_atributo(atr, &carta, &oponente);

    switch (resultado) {
        case VITORIA_JOGADOR_1:
            imprimir_mensagem("\nVocê ganhou a partida!", VERDE); break;
        case VITORIA_JOGADOR_2:
            imprimir_mensagem("\nO oponente ganhou a partida!", VERMELHO); break;
        case EMPATE:
            imprimir_mensagem("\nHouve empate!", NEGRITO); break;
        case ERRO:
            imprimir_mensagem("\nErro ao calcular o atributo!", VERMELHO); break;
    }
    return resultado;
}


/* ========================== Menus ========================== */

void iniciar_partida() {

    // Distribuição das cartas
    Lista_de_cartas player1 = inicializar_lista();
    Lista_de_cartas player2 = inicializar_lista();

    Lista_de_cartas* jogadores[] = { &player1, &player2 };
    Lista_de_cartas lista = ler_registro();

    if (distribuir_cartas(&lista, jogadores, 2)) {
        limpar_tela();
        imprimir_mensagem("Cartas distribuídas!", NEGRITO);
        printf("Cada jogador recebeu %lu cartas", player1.tamanho);
    } else {
        finalizar_lista(&lista);
        return;
    }
    
    // Rodada
    int atributo, rodada = 1;
    while (player1.tamanho && player2.tamanho) {
        Carta atual = player1.cartas[(rodada - 1) % player1.tamanho];
        Carta atual_inimigo = player2.cartas[(rodada - 1) % player2.tamanho];

        limpar_tela();
        printf("%s Rodada %i (Placar P1 %lu x P2 %lu) %s\n\n", NEGRITO, rodada, player1.tamanho, player2.tamanho, RESET);

        exibir_carta(atual, COMPLETO);

        printf("\n 1 - População");
        printf("\n 2 - Área");
        printf("\n 3 - PIB");
        printf("\n 4 - Pontos turisticos");
        printf("\n 5 - Densidade populacional");
        printf("\n 6 - PIB per capita");

        printf("\n\nEscolha uma atributo para competir -> ");
        scanf("%i", &atributo);
        
        // Competição
        Resultado_competicao resultado = competir_atributo_UI((Atributo)atributo, atual, atual_inimigo);
        if (resultado == ERRO) { continue; }
        if (resultado == EMPATE) { rodada++; continue; }

        (resultado == VITORIA_JOGADOR_1) ? transferir_carta_topo(&player2, &player1) : transferir_carta_topo(&player1, &player2);
        rodada++;
    }

    finalizar_lista(&lista);
    finalizar_lista(&player1); 
    finalizar_lista(&player2);
}

void gerenciar_cartas() {
    int escolha, rodando = 1;
    while(rodando) {
        Lista_de_cartas lista = ler_registro();

        limpar_tela();
        printf("%sSistema de Gerenciamento de Cartas%s\n", NEGRITO, RESET);

        printf("\nTotal de cartas: %zu\n\n\n", lista.tamanho);

        if (!lista.tamanho) {
            printf("Nenhuma carta cadastrada!\n\n\n");
        } else {
            for (size_t i = 0; i < lista.tamanho; i++) {
                exibir_carta(lista.cartas[i], SIMPLIFICADO);
                printf("\n\n");
            }
        }

        printf("\n 1 - Cadastrar carta");
        printf("\n 2 - Remover carta");
        printf("\n 3 - Voltar ao Menu principal");

        printf("\n\nEscolha sua opção -> ");
        scanf("%i", &escolha);

        switch (escolha) {
            case 1: cadastrar_carta(&lista); break;
            case 2: remover_carta(&lista); break;
            case 3: rodando = 0; break;
        }
        finalizar_lista(&lista);    
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand((unsigned) time(NULL));

    int escolha, rodando = 1;
    while(rodando) {
        limpar_tela();

        printf("%s #### #   # ##### #### #####    ##### ##### #   # #     # #### ##### %s\n", NEGRITO, RESET);
        printf("%s #    #   # #   # #    #   #      #   #   # #   # # #   # #    #   # %s\n", NEGRITO, RESET);
        printf("%s #### #   # ##### #### #####      #   ##### #   # #  #  # #### #   # %s\n", NEGRITO, RESET);
        printf("%s    # #   # #     #    #  #       #   #  #  #   # #   # # #    #   # %s\n", NEGRITO, RESET);
        printf("%s #### ##### #     #### #   #      #   #   # ##### #    ## #    ##### %s\n", NEGRITO, RESET);

        printf("\n%s%s=== MENU PRINCIPAL ===%s\n", AZUL, ITALICO, RESET);

        printf("\n 1 - Jogar (PvP)"); 
        printf("\n 2 - Gerenciar cartas");
        printf("\n 3 - Sair");

        printf("\n\nEscolha sua opção -> ");
        scanf("%i", &escolha);

        switch (escolha) {
            case 1: iniciar_partida(); break;
            case 2: gerenciar_cartas(); break;
            case 3: rodando = 0; break;
        }
    }
    imprimir_mensagem("Fechando o programa...\n", VERMELHO);
    return 0;
}
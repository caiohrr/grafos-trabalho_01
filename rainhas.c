#include "rainhas.h"
#include <stdio.h>
#include <stdlib.h>

#define VAZIO 0
#define RAINHA 1
#define PROIBIDO 2
//------------------------------------------------------------------------------
// computa uma resposta para a instância (n,c) do problema das n rainhas 
// com casas proibidas usando backtracking
//
//    n é o tamanho (número de linhas/colunas) do tabuleiro
//
//    c é um vetor de k 'struct casa' indicando as casas proibidas
//
//    r é um vetor de n posições (já alocado) a ser preenchido com a resposta:
//      r[i] = j > 0 indica que a rainha da linha i+1 fica na coluna j;
//      r[i] = 0     indica que não há rainha nenhuma na linha i+1
//
// devolve r
//

unsigned int *vetor_uint_alocar(unsigned int n) {

        unsigned int *tabuleiro = malloc(sizeof(unsigned int) * n);
        if (!tabuleiro)
                return NULL;

        return tabuleiro;
}

void tabuleiro_zerar(unsigned int n, unsigned int *tabuleiro) {
        for (unsigned int i = 0; i < n * n; i++) {
                tabuleiro[i] = 0;
        }
}

void tabuleiro_imprimir(unsigned int n, unsigned int *tabuleiro) {

        //printf("n = %u\n", n);
        for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) {
                        //printf("i = %u, j = %u\n", i, j);
                        printf("%u ", tabuleiro[i * n + j]);
                }
                printf("\n");
        }
}

// UTILIZANDO UM VETOR UNIDIMENSIONAL COMO O TABULEIRO, E FAZENDO ARITMETICA PARA AS
// POSICOES
// Verifica se a posição "pos" é valida no tabuleiro, ou seja, se a rainha que
// for colocada nessa posição nao ataca nehuma outra

// Retorna 0 se for invalida, e 1 caso contrario.
unsigned int tabuleiro_posicao_valida(unsigned int *tabuleiro, unsigned int n, unsigned int linha, unsigned int coluna) {
        // Verifica a coluna
        for (unsigned int i = coluna; i < n*n; i += n) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }

        // Verifica a linha
        for (unsigned int i = linha * n; i < (linha + 1) * n; i++) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }

        // Verifica a diagonal superior esquerda
        for (int i = (int)linha, j = (int)coluna; i >= 0 && j >= 0; i--, j--) {
                if (tabuleiro[i * (int)n + j] != VAZIO)
                        return 0;
        }

        // Verifica a diagonal superior direita 
        for (int i = (int)linha, j = (int)coluna; i >= 0 && j <(int)n; i--, j++) {
                if (tabuleiro[i * (int)n + j] != VAZIO)
                        return 0;
        }

        // Verifica a diagonal inferior esquerda
        for (int i = (int)linha, j = (int)coluna; i < (int)n && j >= 0; i++, j--) {
                if (tabuleiro[i * (int)n + j] != VAZIO)
                        return 0;
        }

        // Verifica a diagonal inferior direita 
        for (int i = (int)linha, j = (int)coluna; i < (int)n && j < (int)n; i++, j++) {
                if (tabuleiro[i * (int)n + j] != VAZIO)
                        return 0;
        }

        return 1;
}

unsigned int posicao_proibida(unsigned int *proibido, unsigned int n, unsigned int linha, unsigned int coluna ) {
        if (proibido[linha * n + coluna] == PROIBIDO)
                return 1;

        return 0;
}

void gera_tabuleiro_proibido(casa *casas_proibidas, unsigned int k, unsigned int *proibido, unsigned int n) {
        for (unsigned int i = 0; i < k; i++) {
                casa casa_proibida = casas_proibidas[i];
                printf("l=%u, c=%u\n", casa_proibida.linha, casa_proibida.coluna);
                proibido[(casa_proibida.linha - 1) * n + (casa_proibida.coluna - 1)] = PROIBIDO;
        }
}

void preencher_vetor_resposta(unsigned int *r, unsigned int *tabuleiro, unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
                for(unsigned int j = 0; j < n; j++) {
                        if (tabuleiro[i * n + j] == RAINHA) {
                                r[i] = j + 1;
                        }
                }
        }
}


unsigned int rainhas_bt_recursivo(unsigned int n, unsigned int k, unsigned int *proibido, unsigned int *r, unsigned int *tabuleiro, unsigned int coluna) {

        if (coluna >= n) {
                printf("Resposta encontrada: \n");
                tabuleiro_imprimir(n, tabuleiro); 
                preencher_vetor_resposta(r, tabuleiro, n);
                return 1;
        }

        unsigned int solucao_encontrada = 0;
        
        for (unsigned int i = 0; i < n; i++) {
                if (tabuleiro_posicao_valida(tabuleiro, n, i, coluna) && !posicao_proibida(proibido, n, i, coluna)) {
                        tabuleiro[i * n + coluna] = RAINHA;
                        solucao_encontrada = rainhas_bt_recursivo(n, k, proibido, r, tabuleiro, coluna + 1) || solucao_encontrada;
                        tabuleiro[i * n + coluna] = VAZIO;
                }
        }
        return solucao_encontrada;
}

unsigned int *rainhas_bt(unsigned int n, unsigned int k, casa *c, unsigned int *r) {

        unsigned int *tabuleiro = vetor_uint_alocar(n*n);
        unsigned int *proibido = vetor_uint_alocar(n*n);

        tabuleiro_zerar(n, tabuleiro);
        tabuleiro_zerar(n, proibido);

        gera_tabuleiro_proibido(c, k, proibido, n);

        tabuleiro_imprimir(n, proibido);


        rainhas_bt_recursivo(n, k, proibido, r, tabuleiro, 0);

        n = n;
        k = k;
        c = c;

        free(tabuleiro);

        return r;
}
//------------------------------------------------------------------------------
// computa uma resposta para a instância (n,c) do problema das n
// rainhas com casas proibidas usando a modelagem do problema como
// conjunto independente de um grafo
//
// n, c e r são como em rainhas_bt()

unsigned int *rainhas_ci(unsigned int n, unsigned int k, casa *c, unsigned int *r) {

        n = n;
        k = k;
        c = c;

        return r;
}

#include "rainhas.h"
#include <stdio.h>
#include <stdlib.h>

#define VAZIO 0
#define RAINHA 1
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

unsigned int *tabuleiro_alocar(unsigned int n) {

        unsigned int *tabuleiro = malloc(sizeof(unsigned int) * n * n);
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
unsigned int tabuleiro_posicao_valida(unsigned int *tabuleiro, unsigned int n, unsigned int pos) {
        unsigned int linha_atual, modulo;
        linha_atual = pos / n; 
        modulo = pos % n;

        // Verifica a coluna
        for (unsigned int i = modulo; i < n*n; i += n) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }

        // Verifica a linha
        for (unsigned int i = linha_atual * n; i < n * (linha_atual + 1); i++) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }
        // Verifica a diagonal superior esquerda
        for (unsigned int i = pos; i > 0; i -= (n+1)) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }

        // Verifica a diagonal superior direita 
        for (unsigned int i = pos; i > 0; i -= (n-1)) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }

        // Verifica a diagonal inferior esquerda
        for (unsigned int i = pos; i < 0; i += (n-1)) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }

        // Verifica a diagonal inferior direita 
        for (unsigned int i = pos; i < 0; i += (n+1)) {
                if (tabuleiro[i] != VAZIO)
                        return 0;
        }

        return 1;
}

unsigned int rainhas_bt_recursivo(unsigned int n, unsigned int k, casa *c, unsigned int *r, unsigned int *tabuleiro, unsigned int pos) {
        if (pos >= n*n) {
                printf("RETORNADO\n");
                return 1;
        }

        for (unsigned int i = 0; i < n*n; i += n) {
                printf("FOR LOOP\n");
                if (tabuleiro_posicao_valida(tabuleiro, n, pos)) {
                        printf("VALIDA\n");
                        tabuleiro[pos] = RAINHA;
                        tabuleiro_imprimir(n, tabuleiro);
                        if (rainhas_bt_recursivo(n, k, c, r, tabuleiro, pos + 1))
                                return 1;
                        tabuleiro[pos] = VAZIO;
                }
        }
        return 0;
}

unsigned int *rainhas_bt(unsigned int n, unsigned int k, casa *c, unsigned int *r) {

        unsigned int *tabuleiro = tabuleiro_alocar(n*n);

        tabuleiro_zerar(n, tabuleiro);
        tabuleiro_imprimir(n, tabuleiro);

        
        printf("RECURSAO\n");
        rainhas_bt_recursivo(n, k, c, r, tabuleiro, 0);
        
        for (unsigned int i = 0; i < n; i++) {
                r[i] = 0;
        }

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

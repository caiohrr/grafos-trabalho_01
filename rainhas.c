#include "rainhas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAZIO 0
#define RAINHA 1
#define PROIBIDO 2

// Estrutura de conjunto específica para o problema em questão;
// se vetor[i] == 1 é porque o valor i está no conjunto, caso
// contrário i não está, e vetor[i] = 0
typedef struct conjunto {
        unsigned int tam;
        unsigned int n;
        unsigned int *vetor;
} conjunto;


// -- Vetores
unsigned int *vetor_uint_alocar(unsigned int n);
void vetor_uint_imprimir(unsigned int *vetor, unsigned int n);
void preencher_vetor_resposta(unsigned int *r, unsigned int *tabuleiro, unsigned int n);

// -- Conjuntos
conjunto *conjunto_criar(unsigned int n);
void conjunto_destruir(conjunto *conj);
void conjunto_remover(conjunto *conj, unsigned int i);
unsigned int conjunto_remover_proximo(conjunto *conj);
void conjunto_inserir(conjunto *conj, unsigned int i);

// -- Tabuleiro
void tabuleiro_zerar(unsigned int n, unsigned int *tabuleiro);
void tabuleiro_imprimir(unsigned int n, unsigned int *tabuleiro);
unsigned int tabuleiro_posicao_valida(unsigned int *tabuleiro, unsigned int n, unsigned int linha, unsigned int coluna);
unsigned int posicao_proibida(unsigned int *proibido, unsigned int n, unsigned int linha, unsigned int coluna );
void gera_tabuleiro_proibido(casa *casas_proibidas, unsigned int k, unsigned int *proibido, unsigned int n);

// -- Grafos
void grafo_inserir_rainha(unsigned int *grafo, unsigned int n, unsigned int n_tab, unsigned int linha, unsigned int coluna);
void remover_vizinhos(unsigned int *grafo, unsigned int n, conjunto *conj, unsigned int vertice);
unsigned int conjunto_independente(unsigned int *grafo, unsigned int n, unsigned int tam, conjunto *independente, conjunto *candidatos);

// -- Backtracking
unsigned int rainhas_bt_recursivo(unsigned int n, unsigned int *proibido, unsigned int *r, unsigned int *tabuleiro, unsigned int coluna, unsigned int **respostas);


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
        for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) {
                        printf("%u ", tabuleiro[i * n + j]);
                }
                printf("\n");
        }
}

// Retorna 1 se for possível colocar uma rainha na casa linha x coluna do tabuleiro
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

// Retorna 1 se a casa linha x coluna foi proibida
unsigned int posicao_proibida(unsigned int *proibido, unsigned int n, unsigned int linha, unsigned int coluna ) {
        if (proibido[linha * n + coluna] == PROIBIDO)
                return 1;
        return 0;
}

// Gera um tabuleiro n*n para indicar as casas proibidas
void gera_tabuleiro_proibido(casa *casas_proibidas, unsigned int k, unsigned int *proibido, unsigned int n) {
        for (unsigned int i = 0; i < k; i++) {
                casa casa_proibida = casas_proibidas[i];
                proibido[(casa_proibida.linha - 1) * n + (casa_proibida.coluna - 1)] = PROIBIDO;
        }
}

// Preenche o vetor resposta baseado em um tabuleiro preenchido com as rainhas
void preencher_vetor_resposta(unsigned int *r, unsigned int *tabuleiro, unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) {
                        if (tabuleiro[i * n + j] == RAINHA) {
                                r[i] = j + 1;
                        }
                }
        }
}

 Função recursiva para resolver o problema das n-rainhas com casas proibidas por backtracking
unsigned int rainhas_bt_recursivo(unsigned int n, unsigned int *proibido, unsigned int *r, unsigned int *tabuleiro, unsigned int linha, unsigned int **respostas) {
        if (linha >= n) {
                return 1;
        }

        unsigned int linha_proibida = 1;
        //unsigned int linha_invalida = 1;
        for (unsigned int i = 0; i < n; i++) {
                if (!posicao_proibida(proibido, n, linha, i)) {
                        linha_proibida = 0;
                        if (tabuleiro_posicao_valida(tabuleiro, n, linha, i)) {

                                // Coloca uma rainha no tabuleiro, e preenche uma matriz de respostas
                                // para salvar ao menos uma resposta de cada tamanho que for possível
                                unsigned int *ptr = respostas[linha ] + 1;

                                tabuleiro[linha * n + i] = RAINHA;
                                //tabuleiro[i * n + linha ] = RAINHA;

                                if (respostas[linha][0] == 0) {
                                        respostas[linha][0] = 1;
                                        preencher_vetor_resposta(ptr, tabuleiro, n);
                                }

                                if (rainhas_bt_recursivo(n, proibido, r, tabuleiro, linha + 1, respostas)) {
                                        return 1;
                                }
                                tabuleiro[linha * n + i] = VAZIO;
                        }
                }
        }
        if (linha_proibida == 1) {
                rainhas_bt_recursivo(n, proibido, r, tabuleiro, linha + 1, respostas);
        }
        return 0;
}

unsigned int *rainhas_bt(unsigned int n, unsigned int k, casa *c, unsigned int *r) {

        unsigned int **respostas = malloc(sizeof(unsigned int *) * n);
        if (!respostas) {
                return NULL;
        }

        for (unsigned int i = 0; i < n; i++) {
                respostas[i] = vetor_uint_alocar(n + 1);
                for (unsigned int j = 0; j < n + 1; j++) {
                        respostas[i][j] = 0;
                }
        }

        unsigned int *tabuleiro = vetor_uint_alocar(n*n);
        unsigned int *proibido = vetor_uint_alocar(n*n);

        // Zera o vetor resposta inicial
        for (unsigned int i = 0; i < n; i++) {
                r[i] = 0;
        }

        tabuleiro_zerar(n, tabuleiro);
        tabuleiro_zerar(n, proibido);

        gera_tabuleiro_proibido(c, k, proibido, n);

        rainhas_bt_recursivo(n, proibido, r, tabuleiro, 0, respostas);

        for (int i = (int)n - 1; i >= 0; i--) {
                if (respostas[i][0] == 1) {
                        for (unsigned int j = 1; j < n + 1; j++) {
                                r[j-1] = respostas[i][j];
                        }
                        break;
                }
        }

        for (unsigned int i = 0; i < n; i++) {
                free(respostas[i]);
        }

        free(tabuleiro);
        free(proibido);
        free(respostas);

        return r;
}

// n é a quantidade de arestas do grafo (se o tabuleiro for 4x4, n = 16)
// insere uma rainha na posicao linha x coluna no grafo, completando
// as devidas arestas na matriz de adjacência
void grafo_inserir_rainha(unsigned int *grafo, unsigned int n, unsigned int n_tab, unsigned int linha, unsigned int coluna) {

        int offset = (int) ((linha * n_tab + coluna) * n);

        // Preenche a linha do tabuleiro 
        for (unsigned int i = linha * n_tab; i < (linha + 1) * n_tab; i++) {
                grafo[(unsigned int)offset + i] = 1;
        }

        // Preenche a coluna do tabuleiro
        for (unsigned int i = coluna; i < n; i += n_tab) {
                grafo[(unsigned int)offset + i] = 1;
        }

        // Verifica a diagonal superior esquerda
        for (int i = (int)linha, j = (int)coluna; i >= 0 && j >= 0; i--, j--) {
                grafo[offset + (i * (int)n_tab + j)] = 1;
        }

        // Verifica a diagonal superior direita 
        for (int i = (int)linha, j = (int)coluna; i >= 0 && j <(int)n_tab; i--, j++) {
                grafo[offset + (i * (int)n_tab + j)] = 1;
        }

        // Verifica a diagonal inferior esquerda
        for (int i = (int)linha, j = (int)coluna; i < (int)n_tab && j >= 0; i++, j--) {
                grafo[offset + (i * (int)n_tab + j)] = 1;
        }

        // Verifica a diagonal inferior direita 
        for (int i = (int)linha, j = (int)coluna; i < (int)n_tab && j < (int)n_tab; i++, j++) {
                grafo[offset + (i * (int)n_tab + j)] = 1;
        }

        grafo[(unsigned int)offset + (linha * n_tab + coluna)] = 0;
}

// Aloca memória e inicializa os valores iniciais para um conjunto
conjunto *conjunto_criar(unsigned int n) {
        conjunto *conj = malloc(sizeof(conjunto));
        conj->vetor = vetor_uint_alocar(n);
        conj->tam = 0;
        conj->n = n;
        for (unsigned int i = 0; i < n; i++) {
                conj->vetor[i] = 0;
        }
        if (conj == NULL || conj->vetor == NULL) {
                return NULL;
        }
        return conj;
}

void conjunto_destruir(conjunto *conj) {
        free(conj->vetor);
        free(conj);
}

void conjunto_remover(conjunto *conj, unsigned int i) {
        if (conj->vetor[i] == 0)
                return;
        conj->vetor[i] = 0;
        conj->tam--;

}

unsigned int conjunto_remover_proximo(conjunto *conj) {
        for (unsigned int i = 0; i < conj->n; i++) {
                if (conj->vetor[i] != 0) {
                        conj->vetor[i] = 0;
                        conj->tam--;
                        return i;
                }
        }
        return 0;
}

void conjunto_inserir(conjunto *conj, unsigned int i) {
        conj->vetor[i] = 1; 
        conj->tam++;
}

void remover_vizinhos(unsigned int *grafo, unsigned int n, conjunto *conj, unsigned int vertice) {

        for (unsigned int i = vertice * n; i < (vertice + 1) * n; i++) {
                if (grafo[i] == 1) {
                        conjunto_remover(conj, i % n);
                }
        }
}

void vetor_uint_imprimir(unsigned int *vetor, unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
                printf("%u ", vetor[i]);
        }
        printf("\n");
}

// independente e candidatos sao vetores que representam os conjuntos de vertices
// I e C do algoritmo demonstrado na especificacao do trabalho
//
unsigned int conjunto_independente(unsigned int *grafo, unsigned int n, unsigned int tam, conjunto *independente, conjunto *candidatos) {
        unsigned int *aux_vetor_candidatos = vetor_uint_alocar(n);
        unsigned int *aux_vetor_independente = vetor_uint_alocar(n);
        unsigned int tam_vetor_independente = independente->tam;

        memcpy(aux_vetor_independente, independente->vetor, n * sizeof(unsigned int));

        if (independente->tam == tam) {
                free(aux_vetor_candidatos);
                free(aux_vetor_independente);
                return 1;
        }
        if (independente->tam + candidatos->tam < tam) {
                free(aux_vetor_candidatos);
                free(aux_vetor_independente);
                return 0;
        }
        unsigned int v = conjunto_remover_proximo(candidatos);

        unsigned int tam_vetor_candidatos = candidatos->tam;
        memcpy(aux_vetor_candidatos, candidatos->vetor, n * sizeof(unsigned int));
        conjunto_inserir(independente, v);
        remover_vizinhos(grafo, n, candidatos, v);

        unsigned int r = conjunto_independente(grafo, n, tam, independente, candidatos);
        if (r != 0) {
                free(aux_vetor_candidatos);
                free(aux_vetor_independente);
                return 2;
        }

        memcpy(candidatos->vetor, aux_vetor_candidatos, n * sizeof(unsigned int));
        memcpy(independente->vetor, aux_vetor_independente, n * sizeof(unsigned int));
        candidatos->tam = tam_vetor_candidatos;
        independente->tam = tam_vetor_independente;

        free(aux_vetor_candidatos);
        free(aux_vetor_independente);

        return conjunto_independente(grafo, n, tam, independente, candidatos);
}

//------------------------------------------------------------------------------
// computa uma resposta para a instância (n,c) do problema das n
// rainhas com casas proibidas usando a modelagem do problema como
// conjunto independente de um grafo
//
// n, c e r são como em rainhas_bt()

unsigned int *rainhas_ci(unsigned int n, unsigned int k, casa *c, unsigned int *r) {
        unsigned int n_4 = n*n*n*n;
        unsigned int *grafo = vetor_uint_alocar(n_4);
        unsigned int *proibido = vetor_uint_alocar(n*n);
        unsigned int res;
        // Zera o vetor resposta
        for (unsigned int i = 0; i < n; i++) {
                r[i] = 0;
        }

        tabuleiro_zerar(n, proibido);
        gera_tabuleiro_proibido(c, k, proibido, n);

        tabuleiro_zerar(n*n, grafo);
        for (unsigned int i = 0; i < n; i++) {
                for (unsigned int j = 0; j < n; j++) {
                        grafo_inserir_rainha(grafo, n*n, n, i, j);
                }
        }

        conjunto *independente, *candidatos;
        independente = conjunto_criar(n*n);
        candidatos = conjunto_criar(n*n);

        for (unsigned int i = 0; i < n*n; i++) {
                if (proibido[i] != PROIBIDO) {
                        conjunto_inserir(candidatos, i);
                } 
        }

        unsigned int *copia_candidatos, copia_tam_candidatos;
        copia_candidatos = vetor_uint_alocar(candidatos->n);
        memcpy(copia_candidatos, candidatos->vetor, sizeof(unsigned int) * candidatos->n);
        copia_tam_candidatos = candidatos->tam;

        for (unsigned int i = n; i > 0; i--) {
                memcpy(candidatos->vetor, copia_candidatos, sizeof(unsigned int) * candidatos->n); 
                candidatos->tam = copia_tam_candidatos;

                res = conjunto_independente(grafo, n*n, i, independente, candidatos);
                if (res != 0) {
                        for (unsigned int j = 0; j < n*n; j++) {
                                if (independente->vetor[j] == 1) {
                                        r[j/n] = j % n + 1;
                                }
                        }
                        free(grafo);
                        free(proibido);
                        free(copia_candidatos);

                        conjunto_destruir(independente);
                        conjunto_destruir(candidatos);
                        return r;
                }
        }
        // Chegou ao final sem encontrar um conjunto independente valido
        for (unsigned int i = 0; i < n; i++) {
                r[i] = 0;
        }

        free(grafo);
        free(proibido);
        free(copia_candidatos);

        conjunto_destruir(independente);
        conjunto_destruir(candidatos);

        return r;
}

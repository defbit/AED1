/*
    Aluna: Giulia Salles
    Matricula: 2215310010
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINHAS 10
#define MAX_COLUNAS 10

typedef struct {
    int linha;
    int coluna;
} Posicao;

typedef struct {
    Posicao itens[MAX_LINHAS * MAX_COLUNAS];
    int topo;
} Pilha;

void inicializar_pilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilha_vazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void empilhar(Pilha *pilha, Posicao posicao) {
    if (pilha->topo < MAX_LINHAS * MAX_COLUNAS - 1) {
        pilha->topo++;
        pilha->itens[pilha->topo] = posicao;
    }
}

Posicao desempilhar(Pilha *pilha) {
    Posicao posicao_vazia = {-1, -1};
    if (pilha_vazia(pilha)) {
        return posicao_vazia;
    }
    Posicao posicao = pilha->itens[pilha->topo];
    pilha->topo--;
    return posicao;
}

void resolver_labirinto(int labirinto[MAX_LINHAS][MAX_COLUNAS], int linha_inicio, int coluna_inicio, int linha_fim, int coluna_fim) {
    Pilha pilha;
    inicializar_pilha(&pilha);

    Posicao posicao_inicio = {linha_inicio, coluna_inicio};
    empilhar(&pilha, posicao_inicio);

    while (!pilha_vazia(&pilha)) {
        Posicao posicao_atual = desempilhar(&pilha);

        int linha = posicao_atual.linha;
        int coluna = posicao_atual.coluna;

        if (linha < 0 || linha >= MAX_LINHAS || coluna < 0 || coluna >= MAX_COLUNAS || labirinto[linha][coluna] != 0) {
            continue;
        }

        labirinto[linha][coluna] = 2;  // Marcar como caminho percorrido

        if (linha == linha_fim && coluna == coluna_fim) {
            break;  // Labirinto resolvido
        }

        Posicao proxima_pos[4] = {
            {linha + 1, coluna},
            {linha - 1, coluna},
            {linha, coluna + 1},
            {linha, coluna - 1}
        };

        for (int i = 0; i < 4; i++) {
            empilhar(&pilha, proxima_pos[i]);
        }
    }
}

int main(int argc, char** argv) {
    FILE *arquivo = fopen("labirinto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo do labirinto.\n");
        return 1;
    }

    int labirinto[MAX_LINHAS][MAX_COLUNAS];
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            fscanf(arquivo, "%d", &labirinto[i][j]);
        }
    }

    fclose(arquivo);

    int linha_inicio = 0, coluna_inicio = 0;
    int linha_fim = MAX_LINHAS - 1, coluna_fim = MAX_COLUNAS - 1;

    resolver_labirinto(labirinto, linha_inicio, coluna_inicio, linha_fim, coluna_fim);

    printf("Labirinto resolvido:\n");
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            printf("%d ", labirinto[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/*
    Aluna: Giulia Salles
    Matricula: 2215310010
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 10
#define TAMANHO_NOME_TAREFA 50

typedef struct {
    char nome[TAMANHO_NOME_TAREFA];
} Tarefa;

typedef struct {
    Tarefa itens[MAX_TAREFAS];
    int frente, tras, tamanho;
} Fila;

void inicializar_fila(Fila *fila) {
    fila->frente = fila->tras = fila->tamanho = 0;
}

int esta_cheia(Fila *fila) {
    return fila->tamanho == MAX_TAREFAS;
}

int esta_vazia(Fila *fila) {
    return fila->tamanho == 0;
}

void enfileirar(Fila *fila, Tarefa tarefa) {
    if (esta_cheia(fila)) {
        printf("A fila está cheia. Não é possível adicionar mais tarefas.\n");
        return;
    }
    fila->itens[fila->tras] = tarefa;
    fila->tras = (fila->tras + 1) % MAX_TAREFAS;
    fila->tamanho++;
}

Tarefa desenfileirar(Fila *fila) {
    if (esta_vazia(fila)) {
        Tarefa tarefa_vazia = {"Nenhuma tarefa"};
        printf("A fila está vazia. Retornando tarefa vazia.\n");
        return tarefa_vazia;
    }
    Tarefa tarefa = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_TAREFAS;
    fila->tamanho--;
    return tarefa;
}

void exibir_tarefas(Fila *fila) {
    if (esta_vazia(fila)) {
        printf("Não há tarefas na lista.\n");
        return;
    }
    printf("Tarefas na lista:\n");
    int atual = fila->frente;
    for (int i = 0; i < fila->tamanho; i++) {
        printf("%d. %s\n", i + 1, fila->itens[atual].nome);
        atual = (atual + 1) % MAX_TAREFAS;
    }
}

int main(int argc, char** argv) {
    Fila fila_de_tarefas;
    inicializar_fila(&fila_de_tarefas);

    int opcao;
    Tarefa nova_tarefa;

    do {
        printf("\n Escolha uma opção a baixo\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Concluir Tarefa\n");
        printf("3. Exibir Tarefas\n");
        printf("4. Sair\n");
        printf("Digite a opção escolhida: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome da tarefa: ");
                scanf(" %[^\n]", nova_tarefa.nome);
                enfileirar(&fila_de_tarefas, nova_tarefa);
                break;
            case 2:
                if (!esta_vazia(&fila_de_tarefas)) {
                    Tarefa tarefa_concluida = desenfileirar(&fila_de_tarefas);
                    printf("Tarefa concluída: %s\n", tarefa_concluida.nome);
                } else {
                    printf("Não há tarefas para concluir.\n");
                }
                break;
            case 3:
                exibir_tarefas(&fila_de_tarefas);
                break;
            case 4:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Por favor, digite uma opção válida.\n");
        }
    } while (opcao != 4);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

/*Definição da estrutura do nó da lista*/
struct No {
    int data;
    struct No* prev;
    struct No* next;
};

/*Definição do tipo de dado para a lista*/
typedef struct No No;

/*Função para criar um novo nó*/
No* criarNo(int value) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    novoNo->data = value;
    novoNo->prev = NULL;
    novoNo->next = NULL;
    return novoNo;
}

/*Função para inserir um nó no início da lista*/
void inserir_no_inicio(No** head, int value) {
    No* novoNo = criarNo(value);

    if (*head == NULL) {
        *head = novoNo;
    } else {
        novoNo->next = *head;
        (*head)->prev = novoNo;
        *head = novoNo;
    }
}

/*Função para inserir um nó no fim da lista*/
void inserir_no_fim(No** head, int value) {
    No* novoNo = criarNo(value);

    if (*head == NULL) {
        *head = novoNo;
    } else {
        No* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNo;
        novoNo->prev = temp;
    }
}

/*Função para excluir o nó do início da lista*/
void excluir_do_inicio(No** head) {
    if (*head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    No* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    free(temp);
}

/*Função para excluir o nó do fim da lista*/
void excluir_do_fim(No** head) {
    if (*head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    No* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        /*Caso especial: o nó a ser removido é o único nó da lista*/
        *head = NULL;
    }

    free(temp);
}

/*Função para imprimir a lista*/
void imprimir(No* head) {
    No* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/*Função para buscar um valor na lista*/
No* buscar(No* head, int value) {
    No* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; /*Retornar NULL se o valor não for encontrado*/
}

/*Função para liberar a memória alocada pela lista*/
void liberar_lista(No* head) {
    while (head != NULL) {
        No* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char** argv) {
    No* head = NULL;

    inserir_no_inicio(&head, 3);
    inserir_no_inicio(&head, 2);
    inserir_no_inicio(&head, 1);

    inserir_no_fim(&head, 4);
    inserir_no_fim(&head, 5);

    printf("Lista: ");
    imprimir(head);

    No* busca = buscar(head, 3);
    if (busca != NULL) {
        printf("Valor 3 encontrado na lista.\n");
    } else {
        printf("Valor 3 não encontrado na lista.\n");
    }

    excluir_do_inicio(&head);
    excluir_do_fim(&head);

    printf("Lista após exclusões: ");
    imprimir(head);

    liberar_lista(head);
    return 0;
}

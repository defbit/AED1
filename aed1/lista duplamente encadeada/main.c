#include <stdio.h>
#include <stdlib.h>

/*Defini��o da estrutura do n� da lista*/
struct No {
    int data;
    struct No* prev;
    struct No* next;
};

/*Defini��o do tipo de dado para a lista*/
typedef struct No No;

/*Fun��o para criar um novo n�*/
No* criarNo(int value) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de aloca��o de mem�ria.\n");
        exit(EXIT_FAILURE);
    }

    novoNo->data = value;
    novoNo->prev = NULL;
    novoNo->next = NULL;
    return novoNo;
}

/*Fun��o para inserir um n� no in�cio da lista*/
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

/*Fun��o para inserir um n� no fim da lista*/
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

/*Fun��o para excluir o n� do in�cio da lista*/
void excluir_do_inicio(No** head) {
    if (*head == NULL) {
        printf("A lista est� vazia.\n");
        return;
    }

    No* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    free(temp);
}

/*Fun��o para excluir o n� do fim da lista*/
void excluir_do_fim(No** head) {
    if (*head == NULL) {
        printf("A lista est� vazia.\n");
        return;
    }

    No* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        /*Caso especial: o n� a ser removido � o �nico n� da lista*/
        *head = NULL;
    }

    free(temp);
}

/*Fun��o para imprimir a lista*/
void imprimir(No* head) {
    No* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/*Fun��o para buscar um valor na lista*/
No* buscar(No* head, int value) {
    No* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; /*Retornar NULL se o valor n�o for encontrado*/
}

/*Fun��o para liberar a mem�ria alocada pela lista*/
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
        printf("Valor 3 n�o encontrado na lista.\n");
    }

    excluir_do_inicio(&head);
    excluir_do_fim(&head);

    printf("Lista ap�s exclus�es: ");
    imprimir(head);

    liberar_lista(head);
    return 0;
}

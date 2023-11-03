#include <stdio.h>
#include <stdlib.h>

/*Defini��o da estrutura do n� da lista*/
struct No {
    int data;
    struct No* prev;
    struct No* next;
};

/*Defini��o do tipo de dado para o n� da lista*/
typedef struct No No;

/*Defini��o da estrutura do descritor da lista*/
struct Descritor {
    int qtde;
    No* primeiro;
    No* ultimo;
};

/*Defini��o do tipo de dado para o descritor da lista*/
typedef struct Descritor Descritor;

/*Fun��o para criar um novo n�*/
No* criar_No(int value) {
    No* novo_No = (No*)malloc(sizeof(No));
    if (novo_No == NULL) {
        printf("Erro na aloca��o de mem�ria.\n");
        exit(EXIT_FAILURE);
    }

    novo_No->data = value;
    novo_No->prev = NULL;
    novo_No->next = NULL;
    return novo_No;
}

/*Fun��o para inicializar o descritor da lista*/
void inic_descritor(Descritor* descritor) {
    descritor->qtde = 0;
    descritor->primeiro = NULL;
    descritor->ultimo = NULL;
}

/*Fun��o para inserir um n� no in�cio da lista*/
void inserir_no_inicio(Descritor* descritor, int value) {
    No* novo_No = criar_No(value);

    if (descritor->qtde == 0) {
        descritor->primeiro = novo_No;
        descritor->ultimo = novo_No;
    } else {
        novo_No->next = descritor->primeiro;
        descritor->primeiro->prev = novo_No;
        descritor->primeiro = novo_No;
    }

    descritor->qtde++;
}

/*Fun��o para inserir um n� no fim da lista*/
void inserir_no_fim(Descritor* descritor, int value) {
    No* novo_No = criar_No(value);

    if (descritor->qtde == 0) {
        descritor->primeiro = novo_No;
        descritor->ultimo = novo_No;
    } else {
        novo_No->prev = descritor->ultimo;
        descritor->ultimo->next = novo_No;
        descritor->ultimo = novo_No;
    }

    descritor->qtde++;
}

/*Fun��o para excluir o n� do in�cio da lista*/
void excluir_do_inicio(Descritor* descritor) {
    if (descritor->qtde == 0) {
        printf("A lista est� vazia.\n");
        return;
    }

    No* temp = descritor->primeiro;
    descritor->primeiro = descritor->primeiro->next;

    if (descritor->primeiro != NULL) {
        descritor->primeiro->prev = NULL;
    } else {
        /*Quando a lista fica vazia*/
        descritor->ultimo = NULL;
    }

    free(temp);
    descritor->qtde--;
}

/*Fun��o para excluir o n� do fim da lista*/
void excluir_do_fim(Descritor* descritor) {
    if (descritor->qtde == 0) {
        printf("A lista vazia.\n");
        return;
    }

    No* temp = descritor->ultimo;
    descritor->ultimo = descritor->ultimo->prev;

    if (descritor->ultimo != NULL) {
        descritor->ultimo->next = NULL;
    } else {
        /*Quando a lista fica vazia*/
        descritor->primeiro = NULL;
    }

    free(temp);
    descritor->qtde--;
}

/*Fun��o para imprimir a lista*/
void imprimir(Descritor* descritor) {
    No* temp = descritor->primeiro;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/*Fun��o para buscar um valor na lista*/
No* buscar(Descritor* descritor, int value) {
    No* temp = descritor->primeiro;
    while (temp != NULL) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; /*Retorna NULL se o valor n�o for encontrado*/
}

/*Fun��o para liberar a mem�ria alocada pela lista*/
void liberar_lista(Descritor* descritor) {
    while (descritor->primeiro != NULL) {
        No* temp = descritor->primeiro;
        descritor->primeiro = descritor->primeiro->next;
        free(temp);
    }
    descritor->ultimo = NULL;
    descritor->qtde = 0;
}

int main(int argc, char** argv) {
    Descritor descritor;
    inic_descritor(&descritor);

    inserir_no_inicio(&descritor, 3);
    inserir_no_inicio(&descritor, 2);
    inserir_no_inicio(&descritor, 1);

    inserir_no_fim(&descritor, 4);
    inserir_no_fim(&descritor, 5);

    printf("Lista: ");
    imprimir(&descritor);

    No* busca = buscar(&descritor, 4);
    if (busca != NULL) {
        printf("achou.\n");
    } else {
        printf("n�o achou.\n");
    }

    excluir_do_inicio(&descritor);
    excluir_do_fim(&descritor);

    printf("Lista ap�s exclus�es: ");
    imprimir(&descritor);

    liberar_lista(&descritor);
    return 0;
}

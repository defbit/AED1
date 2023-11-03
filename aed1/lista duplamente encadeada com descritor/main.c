#include <stdio.h>
#include <stdlib.h>

/*Definição da estrutura do nó da lista*/
struct No {
    int data;
    struct No* prev;
    struct No* next;
};

/*Definição do tipo de dado para o nó da lista*/
typedef struct No No;

/*Definição da estrutura do descritor da lista*/
struct Descritor {
    int qtde;
    No* primeiro;
    No* ultimo;
};

/*Definição do tipo de dado para o descritor da lista*/
typedef struct Descritor Descritor;

/*Função para criar um novo nó*/
No* criar_No(int value) {
    No* novo_No = (No*)malloc(sizeof(No));
    if (novo_No == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    novo_No->data = value;
    novo_No->prev = NULL;
    novo_No->next = NULL;
    return novo_No;
}

/*Função para inicializar o descritor da lista*/
void inic_descritor(Descritor* descritor) {
    descritor->qtde = 0;
    descritor->primeiro = NULL;
    descritor->ultimo = NULL;
}

/*Função para inserir um nó no início da lista*/
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

/*Função para inserir um nó no fim da lista*/
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

/*Função para excluir o nó do início da lista*/
void excluir_do_inicio(Descritor* descritor) {
    if (descritor->qtde == 0) {
        printf("A lista está vazia.\n");
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

/*Função para excluir o nó do fim da lista*/
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

/*Função para imprimir a lista*/
void imprimir(Descritor* descritor) {
    No* temp = descritor->primeiro;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/*Função para buscar um valor na lista*/
No* buscar(Descritor* descritor, int value) {
    No* temp = descritor->primeiro;
    while (temp != NULL) {
        if (temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; /*Retorna NULL se o valor não for encontrado*/
}

/*Função para liberar a memória alocada pela lista*/
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
        printf("não achou.\n");
    }

    excluir_do_inicio(&descritor);
    excluir_do_fim(&descritor);

    printf("Lista após exclusões: ");
    imprimir(&descritor);

    liberar_lista(&descritor);
    return 0;
}

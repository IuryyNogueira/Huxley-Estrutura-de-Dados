#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 20000

typedef struct _node{
    char lista_int[TAM];
    struct _node* next;
} Node;

Node* create_linked_list(){
    return NULL;
}

Node* add(Node* head, char item[]){
    Node *newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->lista_int, item); // Copia item para newNode->lista_int
    newNode->next = head;
    return newNode;
}

Node* POP(Node* head){
    if (head == NULL) {
        printf("EMPTY STACK\n");
        return NULL;
    }
    
    printf("%s\n", head->lista_int); // Imprime o item do nó que está sendo removido
    Node* temp = head;
    head = head->next;
    free(temp); // Libera a memória do nó removido
    return head;
}

int main(){
    Node* pilha = create_linked_list();
    char comando[TAM];
    char item[TAM]; // Array para armazenar o item a ser lido

    while(scanf(" %s", comando) != EOF) { // Lê os comandos até o final do arquivo
        if(strcmp(comando,"PUSH") == 0){
            scanf(" %[^\n]", item); // Lê toda a linha até encontrar uma nova linha
            pilha = add(pilha, item);
        }
        else if(strcmp(comando,"POP") == 0){
            pilha = POP(pilha);
        }

    }
    return 0;
}

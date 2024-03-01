#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _node{
    int item;
    struct _node* next;
} Node;

Node* create_linked_list(){
    return NULL;
}

Node* add(Node* head, int item){
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = head;
    return newNode;
}

Node* POP(Node* head){
    
    head = head->next;
    return head;

}

int top(Node* pilha){
    int cont = 0;
    while(pilha){
        cont++;
        pilha = pilha->next;
    }
    return cont;
}

int main(){
    Node* Back = create_linked_list();
    Node* Forward = create_linked_list();
    
    char comando[100];
    
    int cont = 0;
    

    while(scanf("%s", comando) != EOF){
        if(strcmp(comando,"ENTER") == 0){
            if(!cont == 0) Back = add(Back, 1);
            Forward = create_linked_list();
            cont++;   
        }
        if(strcmp(comando,"BACK") == 0){
            Forward = add(Forward,1);
            Back = POP(Back);
            cont--;
        }
        if(strcmp(comando,"FORWARD") == 0){
            Forward = POP(Forward);
            Back = add(Back,1);
            cont++;
        }
        
    }
    //NUM DE CADA
    printf("BACK: %d\nFORWARD: %d", top(Back), top(Forward));
    return 0;
}
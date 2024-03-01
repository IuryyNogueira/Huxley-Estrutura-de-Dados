#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct pilha {
    ITEM vet[TAM];
    int topo;
} TPilha;

void create(TPilha *p) {
    p->topo = -1;
}

void destroy(TPilha *p) {
    p->topo = -1;
}

int isfull(TPilha *p) {
    return p->topo == TAM;
}

int isempty(TPilha *p) {
    return p->topo == -1;
}

void push(TPilha *p, ITEM x) {
    if( isfull(p) ) {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

ITEM pop(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    ITEM x = p->vet[p->topo];
    p->topo--;
    return x;
}

ITEM top(TPilha *p) {
    if( isempty(p) ) {
        puts("underflow");
        abort();
    }
    return p->vet[p->topo];
} 

int palindromo(char s[]) {
	
    TPilha p;
    create(&p);
    
    int i = 0, cont = 0;

    // Empilha a palavra
    while(s[i] != '\0') {
        push(&p, s[i]);
        i++;
    }
    
    // Verifica se a palavra é um palíndromo
    for(int teste_paralelo = 0; teste_paralelo < i; teste_paralelo++){
        
        if(pop(&p) == s[teste_paralelo]) cont++;
    }
    
    // Retorna 1 se a palavra for um palíndromo(se cada letra for igual a sua correspondente na pilha)
    return cont == i;
}

int main(void) {
    char palavra[TAM];

    scanf("%s", palavra);
    printf(palindromo(palavra) ? "sim" : "nao");

    return 0;
}

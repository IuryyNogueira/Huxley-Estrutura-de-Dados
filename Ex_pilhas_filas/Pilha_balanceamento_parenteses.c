#include <stdio.h>
#include <stdlib.h>

#define MAX 255

typedef struct Pilha{
    char arr[MAX];
    int top;
} Pilha;

void push(Pilha *s, char c) {
    if (s->top != 254) {
        s->top++;
        s->arr[s->top] = c;
    }
}

char pop(Pilha *s) {
    if (s->top != -1) {
        char c = s->arr[s->top];
        s->top--;
        return c;
    }
    return '\0';
}

int isBalanced(char *expressao) {
    Pilha p;
    
    //inicializar
    p.top = -1;

    for (int i = 0; expressao[i] != '\0'; i++) {
        //empilha aberturas
        if (expressao[i] == '(' || expressao[i] == '[') push(&p, expressao[i]);
        
        //desempilha fechamentos
        else if (expressao[i] == ')' || expressao[i] == ']') {
            
            //verifica caso comece com fechamento 
            if (p.top == -1) return 0;
                
            char c = pop(&p);
            if ((c == '(' && expressao[i] != ')') || (c == '[' && expressao[i] != ']')) {
                return 0;
            }
        }
    }

    //se a pilha zerar a expressão está balanceada (não sobrou aberturas sem fechamento)
    return p.top == -1;
}

int main() {
    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; i++) {
        char expressao[MAX];
        fgets(expressao, MAX, stdin);

        if (isBalanced(expressao)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
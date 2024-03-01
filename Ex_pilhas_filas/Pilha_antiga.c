#include <stdio.h>
#include <stdlib.h>

typedef struct pilha
{
    int vet[10];
    int topo;
} Pilha;

void create(Pilha *p)
{
    p->topo = -1;
}

int isfull(Pilha *p) {
    return p->topo == 9;
}

int isempty(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, int x)
{
    if (isfull(p))
    {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

int pop(Pilha *p)
{
    if (isempty(p))
    {
        puts("underflow");
        abort();
    }
    int x = p->vet[p->topo];
    p->topo--;
    return x;
}

void print_pilha(Pilha *p)
{
    for (int i = p->topo; i >= 0; i--)
    {
        printf("%d", p->vet[i]);
        if (i != 0)printf(" ");
    }
    printf("\n");
}

void what_do(Pilha *p)
{
    while (1)
    {
        int item;
        char pedido[15];
        scanf("%s", pedido);

        switch (pedido[0])
        {
        case 'E':
            // Empilhar
            scanf("%d", &item);
            push(p, item);
            print_pilha(p);
            break;
        case 'D':
            // Desempilhar
            pop(p);
            print_pilha(p);
            break;
        case 'F':
            // Finalizar
            return;
            break;
        }
    }
}

int main()
{
    Pilha p;
    create(&p);

    what_do(&p);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 100

typedef struct pilha
{
    ITEM vet[TAM];
    int topo;
} TPilha;

void create(TPilha *p)
{
    p->topo = -1;
}

void destroy(TPilha *p)
{
    p->topo = -1;
}

int isfull(TPilha *p)
{
    return p->topo == TAM;
}

int isempty(TPilha *p)
{
    return p->topo == -1;
}

void push(TPilha *p, ITEM x)
{
    if (isfull(p))
    {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

ITEM pop(TPilha *p)
{
    if (isempty(p))
    {
        puts("underflow");
        abort();
    }
    ITEM x = p->vet[p->topo];
    p->topo--;
    return x;
}

ITEM top(TPilha *p)
{
    if (isempty(p))
    {
        puts("underflow");
        abort();
    }
    return p->vet[p->topo];
}

void inverte_palavras_frase(char frase[])
{

    TPilha p;
    create(&p);

    int i = 0, inverter = 0;

    while (frase[i] != '\0' ) 
    {
        //empilha
        if (frase[i] != ' ') push(&p, frase[i]);

        //achou ' ' ou fim da frase
        else
        {
            while (!isempty(&p))
            {
                frase[inverter] = pop(&p);
                inverter++;
            }

            // manter o ' ' no lugar
            inverter = i + 1;
            destroy(&p);
        }
        i++;
    }
    // para a ultima palavra
    while(inverter < i)
    {
        frase[inverter] = pop(&p);
        inverter++;
    }

    destroy(&p);
}

int main(void)
{
    char frase[TAM];

    gets(frase);
    printf("original = %s\n", frase);
    inverte_palavras_frase(frase);
    printf("invertida = %s\n", frase);

    return 0;
}

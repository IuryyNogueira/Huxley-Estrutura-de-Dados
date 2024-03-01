#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct deque {
    ITEM vet[TAM];
    int front, rear;
} TDeque;

void create(TDeque *d) {
    d->front = 0;
    d->rear = -1;
}

void destroy(TDeque *d) {
    d->front = 0;
    d->rear = -1;
}

int isfull(TDeque *d) {
    return d->rear == TAM - 1;
}

int isempty(TDeque *d) {
    return d->rear < d->front;
}

void store(TDeque *d, int extremidade, ITEM x) {
    if (!isfull(d)) {
        if (extremidade == 1) {
            for (int i = d->rear; i >= d->front; i--) {
                d->vet[i+1] = d->vet[i];
            }
            d->vet[d->front] = x;
            d->rear++;
        } else {
            d->vet[++d->rear] = x;
        }
    }
}

ITEM retrieve(TDeque *d, int extremidade) {
    ITEM x = '\0';
    if (!isempty(d)) {
        if (extremidade == 1) {
            x = d->vet[d->front];
            for (int i = d->front; i < d->rear; i++) {
                d->vet[i] = d->vet[i+1];
            }
            d->rear--;
        } else {
            x = d->vet[d->rear];
            d->rear--;
        }
    }
    return x;
}

void preenche(TDeque *d) {
    ITEM x;
    int qtd, extremidade, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &extremidade);
        store(d, extremidade, x);
    }
}

void exibe(TDeque *d) {
    int extremidade;

    while( scanf("%d", &extremidade) != EOF ) {
		if( extremidade==1 )
        	printf("INICIO = %c\n", retrieve(d, extremidade));
		else
			printf("FIM = %c\n", retrieve(d, extremidade));
	}
}

int main(void) {
    TDeque d;

    create(&d);
    preenche(&d);
    exibe(&d);
    destroy(&d);

    return 0;
}

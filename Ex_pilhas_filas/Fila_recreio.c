#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 1000

typedef struct {
    int nota;
    int posicao;
} Aluno;

typedef struct {
    int current_size;
    Aluno items[MAX_QUEUE_SIZE];
} Fila;

Fila* criar_fila() {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->current_size = 0;
    return fila;
}
// Inserir ordenado
void inserir(Fila* fila, int nota, int posicao) {
    // ultimo indice elemnto fila
    int i = fila->current_size - 1;
    // Deslocar os elementos menores que a nota para a direita
    // abrindo espaço pra inserir a nota
    while (i >= 0 && fila->items[i].nota < nota) {
        fila->items[i+1] = fila->items[i];
        i--;
    }
    // Inserir a nota na posição correta
    fila->items[i+1].nota = nota;
    fila->items[i+1].posicao = posicao;
    fila->current_size++;
}

int main() {
    int N, M, nota, contagem;
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%d", &M);
        Fila* fila = criar_fila();

        for(int j = 0; j < M; j++) {
            scanf("%d", &nota);
            inserir(fila, nota, j);
        }

        contagem = 0;
        for(int j = 0; j < M; j++) {
            // Se a posição do aluno for igual a j, ele trocou de posição
            if (fila->items[j].posicao == j) {
                contagem++;
            }
        }

        printf("%d\n", contagem);
        free(fila);
    }

    return 0;
}
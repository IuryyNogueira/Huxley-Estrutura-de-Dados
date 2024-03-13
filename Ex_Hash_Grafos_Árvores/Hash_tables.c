#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct no
{
	int chave;
	struct no *prox;
} no;

typedef struct
{
	int tamanho;
	// Vetor de ponteiros para nós, eu usei um ponteiro de ponteiro para no, porque cada posição da tabela é um ponteiro para o primeiro nó da lista encadeada
	no **tabela;
} tabela_hash;

// Função hash que retorna o resto da divisão da chave pelo tamanho da tabela, pra saber em qual posição da tabela a chave será inserida
int funcao_hash(int chave, int tamanho_tabela)
{
	return chave % tamanho_tabela;
}
// Função que cria a tabela hash
tabela_hash criar_tabela_hash(int tamanho)
{
	tabela_hash th;
	th.tamanho = tamanho;
	th.tabela = (no **)malloc(tamanho * sizeof(no *));
	// Inicializa a tabela com NULL
	for (int i = 0; i < tamanho; i++)
	{
		th.tabela[i] = NULL;
	}
	return th;
}

void inserir_na_tabela(tabela_hash *th, int chave)
{
	int indice = funcao_hash(chave, th->tamanho);
	no *novo_no = (no *)malloc(sizeof(no));
	novo_no->chave = chave;
	novo_no->prox = NULL;
	// Se a posição da tabela estiver vazia, insere o novo nó
	if (th->tabela[indice] == NULL)
	{
		th->tabela[indice] = novo_no;
	}
	// Se não, percorre a lista encadeada até o final e insere o novo nó
	else
	{
		no *atual = th->tabela[indice];
		while (atual->prox != NULL)
		{
			atual = atual->prox;
		}
		atual->prox = novo_no;
	}
}
// Função que imprime a tabela hash, ela imprime o índice da tabela e as chaves que estão na lista encadeada daquela posição
void imprimir_tabela(const tabela_hash *th)
{
	for (int i = 0; i < th->tamanho; i++)
	{
		printf("%d -> ", i);
		no *atual = th->tabela[i];
		while (atual != NULL)
		{
			printf("%d -> ", atual->chave);
			atual = atual->prox;
		}
		printf("\\\n");
	}
}
// 
void liberar_tabela(tabela_hash *th)
{
	for (int i = 0; i < th->tamanho; i++)
	{
		no *atual = th->tabela[i];
		while (atual != NULL)
		{
			no *prox = atual->prox;
			free(atual);
			atual = prox;
		}
	}
	free(th->tabela);
}

int main()
{
	int num_casos_teste;
	scanf("%d", &num_casos_teste);

	// Para cada caso de teste, lê o tamanho da tabela e o número de chaves, cria a tabela hash, insere as chaves e imprime a tabela
	while (num_casos_teste--)
	{
		int tamanho_tabela, num_chaves;
		scanf("%d %d", &tamanho_tabela, &num_chaves);

		tabela_hash th = criar_tabela_hash(tamanho_tabela);

		for (int i = 0; i < num_chaves; i++)
		{
			int chave;
			scanf("%d", &chave);
			inserir_na_tabela(&th, chave);
		}

		imprimir_tabela(&th);
		printf("\n");

		liberar_tabela(&th);
	}

	return 0;
}

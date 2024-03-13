
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct _btree
{
    int item;
    struct _btree *left;
    struct _btree *right;
} btree;

btree *criarArvore(int item, btree *esquerda, btree *direita)
{
    btree *novaArvore = (btree *)calloc(1, sizeof(btree));

    novaArvore->item = item;

    novaArvore->left = esquerda;

    novaArvore->right = direita;

    return novaArvore;
}

btree *construirArvore(char tree[], int *i)
{
    if (tree[*i] == '(' && tree[*i + 1] == ')')
    {
        *i += 2;
        return NULL;
    }

    else if (tree[*i] == '(')
        *i += 1;

    char quaseNumeros[100];

    int j = 0;
    while (tree[*i] != '(' && tree[*i] != ')')
    {
        if (tree[*i] == ' ')
        {
            (*i) += 1;
        }
        else
        {
            quaseNumeros[j] = tree[*i];
            (*i) += 1;
            j++;
        }
    }

    quaseNumeros[j] = '\0';

    int numerosFinalmente = atoi(quaseNumeros);

    btree *raizReggae = criarArvore(numerosFinalmente, NULL, NULL);

    raizReggae->left = construirArvore(tree, i);
    raizReggae->right = construirArvore(tree, i);

    if (tree[*i] == ')')
        *i += 1;

    return raizReggae;
}

int e_btree_valida(btree *raiz, int min, int max)
{
    if (raiz == NULL)  return 1;

    if (raiz->item < min || raiz->item > max) return 0;
    
    // recursivamente chama a função para a subárvore esquerda e direita
    return e_btree_valida(raiz->left, min, raiz->item) && e_btree_valida(raiz->right, raiz->item, max);
}

int main(){

    char tree[1000];
    fgets(tree, 1000, stdin);

    int n = strlen(tree);

    char niceTree[1000];

    int j = 0;
    // remove os espaços da string
    for (int i = 0; i < n; i++)
    {
        if (tree[i] != ' ')
        {
            niceTree[j] = tree[i];
            j++;
        }
    }
    
    int i = 0;
    btree *raiz = construirArvore(niceTree, &i);

    if (e_btree_valida(raiz, INT_MIN, INT_MAX)) printf("VERDADEIRO\n");
    else printf("FALSO\n");
       
    return 0;
}
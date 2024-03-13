#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _btree
{
    int item;
    int height;
    struct _btree *left;
    struct _btree *right;

} btree;

btree *criar_arvore(int item, btree *left, btree *right, int height)
{
    btree *new_tree = (btree *)calloc(1, sizeof(btree));

    new_tree->item = item;

    new_tree->left = left;

    new_tree->right = right;

    new_tree->height = height;

    return new_tree;
}

int esta_aqui(btree *arvore, int criminoso, btree **aux)
{
    *aux = arvore;

    if (arvore == NULL)
        return 0;

    if (arvore->item == criminoso)
        return 1;

    esta_aqui(arvore->left, criminoso, aux);
    esta_aqui(arvore->right, criminoso, aux);

    return esta_aqui(arvore->left, criminoso, aux) || esta_aqui(arvore->right, criminoso, aux);
}

btree *encontrar(btree *arvore, int criminoso, btree **aux)
{
    return esta_aqui(arvore, criminoso, aux) == 1 ? arvore : NULL;
}

btree *construir_arvore_bin(char tree[], int *i, int height)
{
    // Se a árvore estiver vazia
    if (tree[*i] == '(' && tree[*i + 1] == ')')
    {
        *i += 2;
        return NULL;
    }
    // Se a árvore não estiver vazia
    else if (tree[*i] == '(')
        *i += 1;

    // aloca espaço para os números
    char numbers[100];

    int j = 0;
    while (tree[*i] != '(' && tree[*i] != ')')
    {
        // Pega os números da string
        numbers[j] = tree[*i];
        (*i) += 1;
        j++;
    }

    numbers[j] = '\0';

    // Converte os "números" para inteiros
    int verdadeiros_num = atoi(numbers);

    btree *no_raiz = criar_arvore(verdadeiros_num, NULL, NULL, height);

    no_raiz->left = construir_arvore_bin(tree, i, height + 1);
    no_raiz->right = construir_arvore_bin(tree, i, height + 1);

    // fecha o no
    if(tree[*i] == ')') *i += 1;

    return no_raiz;
}

int main()
{
    char tree[1000];
    fgets(tree, 1000, stdin);

    int n = strlen(tree);
    char check_tree[1000];

    int j = 0;
    // Remove os espaços da string
    for (int i = 0; i < n; i++)
    {
        if (tree[i] != ' ')
        {
            check_tree[j] = tree[i];
            j++;
        }
    }

    int i = 0, altura = 0;

    btree *root = construir_arvore_bin(check_tree, &i, altura);

    int procurado;
    scanf("%d", &procurado);

    btree *aux = NULL;
    btree *esse_cara = encontrar(root, procurado, &aux);

    if (esse_cara == NULL)
    {
        puts("NAO ESTA NA ARVORE\n-1");
        return 0;
    }

    printf("ESTA NA ARVORE\n%d\n", aux->height);

    return 0;
}
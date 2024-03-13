#include <stdio.h>
#include <stdlib.h>

typedef struct _tree
{
    int item;
    struct _tree *left;
    struct _tree *right;
} tree;

tree *criar_arvore_null()
{
    tree *new_tree = (tree *) calloc(1 , sizeof(tree));

    new_tree = NULL;
    return new_tree;
}

tree *criar_no_arvore(int item)
{
    tree *new_tree_node = (tree *) calloc(1 , sizeof(tree));

    new_tree_node->item = item;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;

    return new_tree_node;
}

void print_arvore(tree *raiz)
{
    if(raiz == NULL)
    {
        printf("  ()");
    }
    else
    {
        printf("  ( %d", raiz->item);
        print_arvore(raiz->left);
        print_arvore(raiz->right);
        printf(" )");
    }
}

tree *inserir_arvore(tree *raiz, int item)
{
    if(raiz == NULL) return criar_no_arvore(item);

    if (item < raiz->item) raiz->left = inserir_arvore(raiz->left, item);
    
    else raiz->right = inserir_arvore(raiz->right, item);

    return raiz;
}

int main()
{
    int item;
    tree *raiz = criar_arvore_null();

    puts("----");
    while(scanf("%d", &item) == 1)
    {
        printf("Adicionando %d\n ", item);
        raiz = inserir_arvore(raiz, item);
        print_arvore(raiz);
        puts(" \n----");
    }

    return 0;
}
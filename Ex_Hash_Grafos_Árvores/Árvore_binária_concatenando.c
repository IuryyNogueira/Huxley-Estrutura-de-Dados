#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct binary_tree
{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} btree;

btree *criar_arvore_vazia(int item)
{
    btree *no = (btree *)malloc(sizeof(btree));
    no->item = item;
    no->left = no->right = NULL;
    return no;
}

btree *criar_arvore(int item, btree *left, btree *right)
{
    btree *nova_arvore = (btree *)malloc(sizeof(btree));
    nova_arvore->item = item;
    nova_arvore->left = left;
    nova_arvore->right = right;
    return nova_arvore;
}

int arvore_binaria_vazia(btree *arvore)
{
    return (arvore == NULL);
}

int item_presente_na_arvore(btree *arvore, int item)
{
    if (arvore == NULL) return 0;
    if (arvore->item == item) return 1;
    
    item_presente_na_arvore(arvore->left, item);
    item_presente_na_arvore(arvore->right, item);

    return item_presente_na_arvore(arvore->left, item) || item_presente_na_arvore(arvore->right, item);
}

btree *buscar_item_na_arvore(btree *arvore, int item)
{
    if (arvore == NULL) return NULL;
    
    if (arvore->item == item && arvore->left == NULL && arvore->right == NULL)
    {
        return arvore;
    }

    btree *left = buscar_item_na_arvore(arvore->left, item);
    btree *right = buscar_item_na_arvore(arvore->right, item);

    if (left != NULL) return left;
   
    if (right != NULL) return right;
   
    return NULL;
}

btree *concatenar_arvores(btree *arvore1, btree *arvore2)
{
    if (arvore1 == NULL) return arvore2;
   
    if (arvore2 == NULL) return arvore1;
    

    if (item_presente_na_arvore(arvore1, arvore2->item))
    {
        btree *no = buscar_item_na_arvore(arvore1, arvore2->item);
        
        no->left = arvore2->left;
        no->right = arvore2->right;
        
        return arvore1;
    }

    if (arvore1->left == NULL && arvore1->right == NULL)
    {
        return arvore2;
    }

    if (arvore2->left == NULL && arvore2->right == NULL)
    {
        return arvore1;
    }

    return arvore1;
}

int encontrar_indice(char *str, int inicio, int fim)
{
    if (inicio > fim)
    {
        return -1;
    }

    char pilha[fim - inicio + 1];
    int topo = -1;
    for (int i = inicio; i <= fim; i++)
    {
        if (str[i] == '(')
        {
            pilha[++topo] = str[i];
        }
        else if (str[i] == ')')
        {
            if (pilha[topo] == '(')
            {
                topo--;
                if (topo == -1)
                {
                    return i;
                }
            }
        }
    }
    return -1;
}

btree *tradutor_string_btree(char *str, int inicio, int fim)
{
    if (inicio > fim)return NULL;

    if (str[inicio] == '(')inicio++;

    if (str[inicio] == ')') return NULL;
  
    int i = inicio;
    int sinal = 1;

    if (str[i] == '-')
    {
        sinal = -1;
        i++;
    }

    if (str[i] == '(' || str[i] == ')')return NULL;
  
    while (str[i] != '(' && str[i] != ')')
    {
        i++;
    }

    int item = 0;
    for (int j = inicio; j < i; j++)
    {
        if (str[j] != '-')
        {
            item = item * 10 + (str[j] - '0');
        }
    }

    item *= sinal;

    btree *raiz = criar_arvore_vazia(item);

    int indice = encontrar_indice(str, inicio, fim);

    if (indice != -1)
    {
        raiz->left = tradutor_string_btree(str, i, indice);
        raiz->right = tradutor_string_btree(str, indice + 1, fim - 1);
    }

    return raiz;
}

char *tradutor_btree_string(btree *arvore)
{
    if (arvore == NULL) return "()";
   
    char *left = tradutor_btree_string(arvore->left);
    char *right = tradutor_btree_string(arvore->right);

    char *arvore_str = (char *)malloc(1000 * sizeof(char));
    
    // sprintf armazena no buffer a string para arvore_str.
    sprintf(arvore_str, "(%d%s%s)", arvore->item, left, right);
    
    return arvore_str;
}

void imprimir_pre_ordem(btree *arvore)
{
    if (!arvore_binaria_vazia(arvore))
    {
        printf("%d ", arvore->item);
        imprimir_pre_ordem(arvore->left);
        imprimir_pre_ordem(arvore->right);
    }
}

void imprimir_arvore(btree *raiz, int nivel, char direcao)
{
    if (raiz == NULL)
    {
        return;
    }

    imprimir_arvore(raiz->right, nivel + 1, '/');

    for (int i = 0; i < nivel; i++)
    {
        printf("    ");
    }

    printf("%c~%d\n", direcao, raiz->item);

    imprimir_arvore(raiz->left, nivel + 1, '\\');
}

int main()
{
    char arvore[1000];
    fgets(arvore, 1000, stdin);
    //inicial
    btree *raiz = tradutor_string_btree(arvore, 0, strlen(arvore) - 1);

    //contrucao concatenada
    while (1)
    {
        char arvore[1000];
        fgets(arvore, 1000, stdin);

        if (arvore[0] == '(' && arvore[1] == ')')
        {
            break;
        }
        btree *nova_arvore = tradutor_string_btree(arvore, 0, strlen(arvore) - 1);

        raiz = concatenar_arvores(raiz, nova_arvore);
    }

    char *resultado = tradutor_btree_string(raiz);
    printf("%s\n", resultado);
}

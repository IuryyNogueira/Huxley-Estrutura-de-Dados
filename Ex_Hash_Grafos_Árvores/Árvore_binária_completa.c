#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct binary_tree
{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

binary_tree *create_empty_binary_tree(int item)
{
    binary_tree *node = (binary_tree *)malloc(sizeof(binary_tree));
    
    node->item = item;
    node->left = node->right = NULL;
    
    return node;
}

binary_tree *criar_btree(int item, binary_tree *left, binary_tree *right)
{
    binary_tree *new_binary_tree = (binary_tree *)malloc(sizeof(binary_tree));
    
    new_binary_tree->item = item;
    new_binary_tree->left = left;
    new_binary_tree->right = right;
    
    return new_binary_tree;
}

int encontrar_index_na_string(char *str, int start, int end)
{
    if (start > end) return -1;

    char pilha[end - start + 1];
    int top = -1;
    // Percorre a string do início ao fim procurando por parênteses de abertura e fechamento e os empilhando e desempilhando 
    for (int i = start; i <= end; i++)
    {
        if (str[i] == '(')
        {
            pilha[++top] = '(';
        }
        else if (str[i] == ')')
        {
            if (top >= 0)
            {
                top--;
                if (top == -1)
                {
                    // Retorna o índice do parêntese de fechamento do nó atual
                    return i;
                }
            }
        }
    }
    return -1;
}

binary_tree *tradutor_string_btree(char *str, int start, int end)
{
    if (start > end) return NULL;

    // Se nos depararmos com um parêntese de abertura, o próximo caractere será o valor do nó
    if (str[start] == '(') start++;

    // Se nos depararmos com um parêntese de fechamento, retornamos NULL
    if (str[start] == ')') return NULL;

    // Encontramos o valor do nó
    int i = start;
    int sign = 1;

    // Verifica se o número é negativo
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }

    // Verifica se há um número após o parêntese de abertura, se não houver, retorna NULL
    if (str[i] == '(' || str[i] == ')') return NULL;

    while (str[i] != '(' && str[i] != ')')
    {
        i++;
    }

    int item = 0;
    for (int j = start; j < i; j++)
    {
        // Ignora o sinal negativo na conversão para inteiro
        if (str[j] != '-')
        {
            // Multiplica o valor por 10 e soma o valor do caractere convertido para inteiro
            item = item * 10 + (str[j] - '0');
        }
    }

    // Multiplica o valor por -1 se o número for negativo
    item *= sign;

    binary_tree *root = create_empty_binary_tree(item);

    // Encontramos o índice do parêntese de fechamento do nó atual
    int index = encontrar_index_na_string(str, start, end);

    // Se o índice for -1, significa que não encontramos o parêntese de fechamento
    if (index != -1)
    {
        root->left = tradutor_string_btree(str, i, index);
        // Chamamos a função recursivamente para encontrar o nó da direita
        root->right = tradutor_string_btree(str, index + 1, end - 1);
    }

    return root;
}

int get_total_tree_nodes_amount(binary_tree *bt)
{
    if (bt == NULL) return 0;
    else
    {
        return (1 + get_total_tree_nodes_amount(bt->left) + get_total_tree_nodes_amount(bt->right));
    }
}

int is_tree_complete(binary_tree *bt, int *total_nodes_amount)
{
    if (bt == NULL) return 1;
   
    *total_nodes_amount = get_total_tree_nodes_amount(bt);
    return check_complete(bt, 0, *total_nodes_amount);
}

int check_complete(binary_tree *bt, int index, int total_nodes)
{
    if (bt == NULL) return 1;
    
    if (index >= total_nodes)
    {
        return 0;
    }

    return check_complete(bt->left, 2 * index + 1, total_nodes) && check_complete(bt->right, 2 * index + 2, total_nodes);
}

void print_nos_unitarios(binary_tree *bt)
{
    if (bt != NULL)
    {
        print_nos_unitarios(bt->left);
        // Se o nó não for binário, imprime o valor do nó
        if (bt->left == NULL && bt->right != NULL || bt->left != NULL && bt->right == NULL)
        {
            printf("%d ", bt->item);
        }

        print_nos_unitarios(bt->right);
    }
}

int main()
{
    char input[1000];

    while (scanf("%s", input) != EOF)
    {
        binary_tree *bt = tradutor_string_btree(input, 0, strlen(input) - 1);

        int total_nodes_amount;
        int is_complete = is_tree_complete(bt, &total_nodes_amount);

        if (is_complete)
        {
            printf("completa\n");
            printf("total de nos: %d\n", total_nodes_amount);
        }
        else
        {
            printf("nao completa\n");
            printf("nos com um filho: ");
            print_nos_unitarios(bt);
            printf("\n");
        }
    }

    return 0;
}
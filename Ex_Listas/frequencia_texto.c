#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da lista encadeada
typedef struct _node {
    char index;             // Armazena o caractere
    int freq;               // Armazena a frequência do caractere
    struct _node* next;    // Ponteiro para o próximo nó na lista
} node;

// Função para adicionar um novo nó ao final da lista encadeada
node *add_node_no_final(node *head, int frequencia, int index)
{
    // Aloca memória para o novo nó
    node *new_node = (node*) calloc(1, sizeof(node));
    
    // Define a frequência e o caractere do novo nó
    new_node->freq = frequencia;
    new_node->index = index;
    
    // Inicializa o próximo nó como NULL
    new_node->next = NULL;

    // Verifica se a lista está vazia
    if(head == NULL)
    {
        return new_node; // Se estiver vazia, o novo nó se torna a cabeça da lista
    }
    else
    {
        // Caso contrário, percorre a lista até o último nó
        node *aux = head;
        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        // Adiciona o novo nó ao final da lista
        aux->next = new_node;

        return head;
    }
}

// Função para incrementar a frequência de um caractere na lista
void frequencia_geral(node *head, int letra_num)
{
    // Percorre a lista até encontrar o nó correspondente ao caractere
    node *aux = head;
    while(aux->index != letra_num)
    {
        aux = aux->next;
    }

    // Incrementa a frequência do caractere encontrado
    aux->freq += 1;
}

// Função para imprimir a lista de caracteres e suas frequências
void print_lista_freq(node *head)
{
    // Percorre a lista e imprime cada nó
    node *aux = head;
    while(aux != NULL)
    {
        // Imprime apenas os nós cuja frequência é diferente de zero
        if(aux->freq != 0)
            printf("%c %d\n", aux->index, aux->freq);
        
        aux = aux->next;
    }
}

int main(){
    // Inicialização da lista encadeada
    node *lista = NULL;

    // Adiciona nós para todos os caracteres ASCII possíveis (de 0 a 255)
    for (int i = 255; i >= 0; i--) 
    {
        lista = add_node_no_final(lista, 0, i);
    }

    // Declaração de uma string para armazenar o texto inserido pelo usuário
    char texto[1000];

    // Solicita ao usuário que insira um texto
    fgets(texto, 1000, stdin);

    // Calcula o tamanho do texto inserido
    int tam = strlen(texto);

    // Itera sobre cada caractere do texto
    for(int i = 0; i < tam; i++)
    {
        // Incrementa a frequência do caractere na lista
        frequencia_geral(lista, texto[i]);
    }

    // Imprime a lista de caracteres e suas frequências
    print_lista_freq(lista);
    
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack();

//Recebe um elemento e cria e retorna um novo node
// com o elemento passado
NODE* create_node(int element);

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack);

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack);

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element);

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char elementos);

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size);

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));

}

STACK* Create_stack()
{
    STACK* new_stack = (STACK*)malloc(sizeof(STACK));
    new_stack->head = NULL;
    return new_stack;
}

NODE* create_node(int element)
{
    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    new_node->element = element;
    new_node->next = NULL;
   
    return new_node;
}

int IS_EMPTY(STACK* stack)
{
    return stack->head == NULL;
    
}

int POP(STACK* stack){
    if(IS_EMPTY(stack))  return -1;
    
    NODE* aux = stack->head;
    stack->head = stack->head->next;
    
    int element = aux->element;
    
    free(aux);
    
    return element;
}

void PUSH(STACK* stack, int element)
{
        NODE *new_node = create_node(element);
        new_node->next = stack->head;
        stack->head = new_node;
}

// "51 13 12 * + "
void result(STACK* stack, char elementos){
    
    int num1, num2;
    
    switch(elementos){
        case '+' :
            num1 = POP(stack);
            num2 = POP(stack);
            PUSH(stack, num1 + num2);
            break;
        case '-' :
            num1 = POP(stack);
            num2 = POP(stack);
            PUSH(stack, num2 - num1);
            break;
        case '*' :
            num1 = POP(stack);
            num2 = POP(stack);
            PUSH(stack, num1 * num2);
            break;
        case '/' :
            num1 = POP(stack);
            num2 = POP(stack);
            PUSH(stack, num2 / num1);
            break;
    }
}
/*  51 
    13 
    12 
    * 
    +  */
void Calculadora(STACK* calculadora, int size){
    
    for(int i = 0; i < size; i++){
        char elemento[100];

        scanf("%s", elemento);

        if(elemento[0] == '+' || elemento[0] == '-' || elemento[0] == '/' || elemento[0] == '*')
        {
            result(calculadora,elemento[0]);
        }
        else
        {
            int item = atoi(elemento);
            PUSH(calculadora,item);
        }
    }
}
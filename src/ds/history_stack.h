#ifndef HISTORY_STACK_H
#define HISTORY_STACK_H

#include <stddef.h>  /* size_t */
#include "model/history.h"

/*
  Pilha LIFO de HistoryRecord para "desfazer" o último atendimento.
*/

/*
    Struct que representa o nó da pilha de histórico
*/
typedef struct HistoryNode{
    HistoryRecord data; // Struct contendo dados da auditoria
    struct HistoryNode* next; // ponteiro para proximo da lista
} HistoryNode;


/*
    Pilha de atendimentos (histórico)
    Struct contendo dados do node e o seu tamanho 
*/
typedef struct {
    HistoryNode* top; // representação do topo da pilha
    size_t size; //Numero de nós na pilha
} HistoryStack;


/* Funções públicas da pilha de histórico */
void init_history_stack(HistoryStack* stack);
HistoryRecord make_history_record(const Patient* patient);
void push_history(HistoryStack* stack, HistoryRecord record);
int pop_history(HistoryStack* stack, HistoryRecord* out_record);
void print_history(const HistoryStack* stack);
void free_history(HistoryStack* stack);



#endif
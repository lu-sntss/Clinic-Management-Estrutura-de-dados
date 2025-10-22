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



#endif
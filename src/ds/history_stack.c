#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ds/history_stack.h"

static void now_timestamp(char out_timestamp[20]){
    time_t current_time = time(NULL);
    struct tm local_time;
#if defined(_POSIX_THREAD_SAFE_FUNCTIONS)
    localtime_r(&current_time, &local_time);
#else  
    struct tm* tm_ptr = localtime(&current_time);
    if (tm_ptr) local_time = *tm_ptr;
#endif
    strftime(out_timestamp, 20, "%Y-%m-%d %H:%M", &local_time);
}

/*
 Inicializa a pilha de histórico.

 Args:
   stack: Ponteiro para a pilha a ser inicializada.

 Efeito:
   - Define stack->top = NULL e stack->size = 0.
*/
void init_history_stack(HistoryStack* stack){
    if (stack == NULL)      // Se o ponteiro for nulo, significa que ele não está apontando 
        return;             // para lugar nenhum válido na memória.
        // Finaliza método por aqui mesmo

    stack->top = NULL;  // Define o top como nulo, espaço vazio
    stack->size = 0; // Define 0 para o tamanho da pilha
}

/*
 Cria um HistoryRecord do tipo QUEUE_OUT com timestamp atual e snapshot do paciente.

 Args:
   patient: Ponteiro para o paciente atendido (pode ser NULL).

 Returns:
   HistoryRecord preenchido.
*/
HistoryRecord make_history_record(const Patient* patient){
    HistoryRecord record;
    now_timestamp(record.timestamp); // Atribuindo timestamp ao atributo timestamp da struct
    record.action = QUEUE_OUT; // Ação realizada é a saída da lista de espera

    if (patient) { // Se existir o paciente...
        record.patient = *patient; // Atribui o endereço do paciente ao atributo da struct
    } else {
        // Função padrão do C para "setar memória" (memory set). Ela preenche um bloco de memória com um valor específico.
        // &record.patient: endereço de onde começar a preencher.
        // 0: com qual valor preencher (nesse caso, tudo com zeros).
        // sizeof(record.patient): quantos bytes devem ser preenchidos (o tamanho exato da estrutura de um paciente).
        memset(&record.patient, 0, sizeof(record.patient));
    }
    return record; // Devolve o objeto record com os dados manipulados
}

/*
 Empilha um registro de histórico na pilha.

 Args:
   stack: Ponteiro para a pilha global.
   record: Registro de histórico (snapshot do paciente).
*/
void push_history(HistoryStack* stack, HistoryRecord record) {
    if (!stack) return;

    HistoryNode* newNode = malloc(sizeof(HistoryNode));
    if (!newNode) {
        puts("Erro: falha ao alocar memória para histórico.");
        return;
    }

    newNode->data = record;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

/*
 Desempilha o último registro (desfazer último atendimento).
 Retorna 1 se removeu com sucesso, 0 se pilha vazia.
*/
int pop_history(HistoryStack* stack, HistoryRecord* out_record) {
    if (!stack || !stack->top) return 0;

    HistoryNode* temp = stack->top;
    if (out_record) *out_record = temp->data;

    stack->top = temp->next;
    free(temp);
    stack->size--;
    return 1;
}

/*
 Exibe todo o histórico (topo → base)
*/
void print_history(const HistoryStack* stack) {
    if (!stack || !stack->top) {
        puts("\nNenhum atendimento realizado ainda.\n");
        return;
    }

    printf("\n========== HISTÓRICO DE ATENDIMENTOS ==========\n");
    HistoryNode* curr = stack->top;
    int index = 1;
    while (curr) {
        const HistoryRecord* rec = &curr->data;
        printf("%d) [%s] %s (CPF: %s, prioridade %d)\n",
               index++, rec->timestamp,
               rec->patient.name,
               rec->patient.cpf,
               rec->patient.priority);
        curr = curr->next;
    }
    printf("===============================================\n");
}

/*
 Libera toda a memória da pilha de histórico.
*/
void free_history(HistoryStack* stack) {
    HistoryNode* curr = stack->top;
    while (curr) {
        HistoryNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
    stack->top = NULL;
    stack->size = 0;
}
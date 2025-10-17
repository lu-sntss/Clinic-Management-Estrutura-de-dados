#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_queue.h"

// Inicializa a fila
void init_queue(PatientQueue *q) {
    q->front = q->rear = NULL;
}

// Adiciona paciente na fila (FIFO, cópia independente)
void enqueue(PatientQueue *q, Patient *p) {
    printf("\nDEBUG: EXECUTANDO A FUNCAO ENQUEUE COM LOGICA DE PRIORIDADE PARA: '%s'\n", p->name);
    QueueNode *newNode = malloc(sizeof(QueueNode));
    if (!newNode) {
        puts("Erro: Falha ao alocar memória para o novo nó da fila.");
        return;
    }
    newNode->patient = p;
    newNode->next = NULL;

    // --- LÓGICA DE PRIORIDADE CORRIGIDA ---

    // Caso 1: A fila está vazia OU o novo paciente tem a maior prioridade e deve ser o novo 'front'.
    if (is_queue_empty(q) || p->priority < q->front->patient->priority) {
        newNode->next = q->front;
        q->front = newNode;
    } else {
        // Caso 2: Percorre a fila para encontrar a posição correta.
        QueueNode *current = q->front;
        // # O loop agora avança 'current' até encontrar o nó ANTES do qual devemos inserir.
        while (current->next != NULL && current->next->patient->priority <= p->priority) {
            current = current->next;
        }
        // Insere o novo nó depois de 'current'.
        newNode->next = current->next;
        current->next = newNode;
    }

    // --- GERENCIAMENTO DO PONTEIRO 'rear' ---
    // # A lógica para atualizar o 'rear'.
    // Se o 'rear' original era o nó onde inserimos depois, ou se o novo nó é o último, atualizamos 'rear'.
    if (newNode->next == NULL) {
        q->rear = newNode;
    }
    // Se a fila estava vazia, o 'rear' precisa ser inicializado.
    if (is_queue_empty(q)) {
        q->rear = q->front;
    }
}

// Remove paciente da fila e retorna ponteiro (lembre-se de liberar depois)
Patient* dequeue(PatientQueue *q) {
    if (q->front == NULL) return NULL;

    QueueNode *temp = q->front;
    Patient *p = temp->patient;

    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;

    free(temp);
    return p;
}

// Verifica se a fila está vazia
int is_queue_empty(const PatientQueue *q) {
    return q->front == NULL;
}

// Libera toda a fila (útil ao encerrar)
void free_queue(PatientQueue *q) {
    while (!is_queue_empty(q)) {
        Patient *p = dequeue(q);
        free(p); // libera cada paciente copiado
    }
}


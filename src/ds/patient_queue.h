#ifndef PATIENT_QUEUE_H
#define PATIENT_QUEUE_H

#include "../model/patient.h"
#include <stdlib.h> // Para NULL

// Estrutura do Nó da Fila (QueueNode)
// Cada "caixinha" da fila que guarda um paciente.
typedef struct QueueNode {
    Patient *patient;           // Ponteiro para os dados do paciente (a cópia alocada)
    struct QueueNode *next;     // Ponteiro para o próximo nó na fila
} QueueNode;

// Estrutura principal da Fila (PatientQueue)
// Controla o início e o fim da fila.
typedef struct {
    QueueNode *front; // Ponteiro para o primeiro paciente da fila
    QueueNode *rear;  // Ponteiro para o último paciente da fila
} PatientQueue;

// --- Protótipos das Funções ---

// Inicializa uma fila vazia
void init_queue(PatientQueue *q);

// Verifica se a fila está vazia
int is_queue_empty(const PatientQueue *q);

// Adiciona um paciente ao FIM da fila
void enqueue(PatientQueue *q, Patient *p);

// Remove e retorna o paciente do INÍCIO da fila
Patient* dequeue(PatientQueue *q);

// Libera toda a memória usada pela fila
void free_queue(PatientQueue *q);

#endif // PATIENT_QUEUE_H
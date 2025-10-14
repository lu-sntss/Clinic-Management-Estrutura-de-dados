// src.ds.patient_list.h

#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

#include "../model/patient.h"

// Estrutura do "nó" ou "elo" da lista.
// Cada nó contém os dados de um paciente e um ponteiro para o próximo nó.
typedef struct node {
    Patient data;          // Os dados do paciente.
    struct node* next;     // Ponteiro para o próximo nó na lista, ou NULL se for o último.
} Node;

// Estrutura principal da lista.
// Contém apenas um ponteiro para o primeiro nó (a "cabeça" da lista).
typedef struct {
    Node* head;            // Ponteiro para o nó inicial da lista.
} PatientList;


// --- Protótipos das Funções Públicas ---

/* Inicializa uma lista para um estado seguro (vazia). */
void init_patient_list(PatientList* list);

/* Insere um novo paciente no início da lista. */
void insert_patient(PatientList* list, Patient patient);

/* Exibe todos os pacientes da lista no console. */
void print_all_patient(PatientList* list);

/* Busca um paciente pelo CPF. Retorna ponteiro para o paciente ou NULL se não encontrar. */
Patient* search_patient_by_CPF(PatientList* list, const char* cpf);

/* Libera toda a memória alocada pelos nós da lista, evitando memory leaks. */
void free_list(PatientList* list);

#endif /* PATIENT_LIST_H */
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
int insert_patient(PatientList *list, const Patient *p);

/* Exibe todos os pacientes da lista no console. */
void print_all_patient(PatientList* list);

/* Busca por CPF; retorna ponteiro constante para o Patient na lista, ou NULL.*/
const Patient* search_patient_by_CPF(const PatientList *list, const char *cpf);

/* Libera toda a memória alocada pelos nós da lista, evitando memory leaks. */
void free_list(PatientList* list);

/* 
    Verifica se lsita de pacientes está vazia

    Args:
    list: Ponteiro para a lista a ser verificada.

  Returns:
    int: 1 se vazia (ou não inicializada), 0 caso contrário.
*/
int is_patient_list_empty(const PatientList *list);

#endif /* PATIENT_LIST_H */
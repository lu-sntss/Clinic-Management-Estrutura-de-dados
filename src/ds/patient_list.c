// src.ds.patient_list.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_list.h"

void initList(PatientList* list) {
    list->head = NULL;
}

void insertPatient(PatientList* list, Patient patient) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    newNode->data = patient;
    newNode->next = list->head;
    list->head = newNode;
}

void printPatients(PatientList* list) {
    if (list->head == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    Node* current = list->head;
    printf("\n=== Lista de Pacientes ===\n");
    while (current != NULL) {
        Patient p = current->data;
        printf("ID: %d | Nome: %s | CPF: %s | Idade: %d | Prioridade: %d\n",
               p.id, p.name, p.cpf, p.age, p.priority);
        current = current->next;
    }
}

Patient* searchPatientByCPF(PatientList* list, const char* cpf) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.cpf, cpf) == 0) {
            return &current->data;
        }
        current = current->next;
    }
    return NULL;
}

void freeList(PatientList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

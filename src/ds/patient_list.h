#ifndef PATIENT_LIST_H
#define PATIENT_LIST_H

#include "../model/patient.h"

typedef struct node {
    Patient data;
    struct node* next;
} Node;

typedef struct {
    Node* head;
} PatientList;

void initList(PatientList* list);
void insertPatient(PatientList* list, Patient patient);
void printPatients(PatientList* list);
Patient* searchPatientByCPF(PatientList* list, const char* cpf);
void freeList(PatientList* list);

#endif

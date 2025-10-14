#ifndef PATIENT_H
#define PATIENT_H

#include <stddef.h>  /* size_t */

typedef struct {
    int id;
    char name[100];
    char cpf[15];
    int age;
    char gender;           /* 'M' ou 'F' */
    char condition[200];
    int priority;          /* 1=Alta, 2=Média, 3=Baixa */
} Patient;

/* Valida regras de domínio (sem I/O).
   Returns: 1 se válido, 0 se inválido. Se errbuf != NULL, escreve mensagem. */
int patient_validate(const Patient* p, char* errbuf, size_t errcap);

/* Normaliza campos simples (ex.: uppercase do gender). */
void patient_normalize(Patient* p);

#endif

#ifndef PATIENT_H
#define PATIENT_H

typedef struct {
    int id;
    char name[100];
    char cpf[15];
    int age;
    char gender;
    char condition[200];
    int priority;  // 1=Alta, 2=Média, 3=Baixa
} Patient;

#endif
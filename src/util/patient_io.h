#ifndef PATIENT_IO_H
#define PATIENT_IO_H

#include <stddef.h>
#include "model/patient.h"

/* Lê um Patient do console (stdin). Retorna 1 se OK, 0 se erro/cancelado. */
int read_patient_from_console(Patient* p);

/* Lê um CPF do console (stdin). Retorna 1 se OK, 0 se erro. */
int read_cpf_from_console(char* cpf, size_t cap);

/* Imprime uma linha resumida do paciente. */
void print_patient_line(const Patient* p);

#endif

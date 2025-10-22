#ifndef HISTORY_H
#define HISTORY_H

#include "model/patient.h" // Import da struct de pacientes

/*
  Define o tipo de ação e o registro do histórico.
  Snapshot por valor para permitir "desfazer" mesmo após liberar a cópia da fila.
*/

typedef enum{
    QUEUE_OUT = 1 // atendimento (pop da fila)
} HistoryAction;

typedef struct {
    char timestamp[20]; // YYYY-MM-DD HH:MM
    HistoryAction action; // Tipo de ação
    Patient patient;    // Paciente
} HistoryRecord;

#endif
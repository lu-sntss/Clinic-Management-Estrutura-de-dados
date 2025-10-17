#include <stdio.h>
#include <string.h>
#include "patient_queue.h"

int main() {
    // Inicializa a fila
    PatientQueue queue;
    init_queue(&queue);

    // Criação dos pacientes
    Patient p1, p2, p3;

    p1.id = 1;
    strcpy(p1.name, "Alice");
    strcpy(p1.cpf, "111.111.111-11");
    p1.age = 30;
    p1.gender = 'F';
    strcpy(p1.condition, "Normal");
    p1.priority = 3;

    p2.id = 2;
    strcpy(p2.name, "Bob");
    strcpy(p2.cpf, "222.222.222-22");
    p2.age = 25;
    p2.gender = 'M';
    strcpy(p2.condition, "Urgente");
    p2.priority = 1;

    p3.id = 3;
    strcpy(p3.name, "Carol");
    strcpy(p3.cpf, "333.333.333-33");
    p3.age = 40;
    p3.gender = 'F';
    strcpy(p3.condition, "Média");
    p3.priority = 2;

    // Enfileira os pacientes
    enqueue(&queue, &p1);
    enqueue(&queue, &p2);
    enqueue(&queue, &p3);

    printf("Fila inicializada e pacientes enfileirados.\n");

    // Desenfileira e mostra os pacientes
    Patient *p;
    while (!is_queue_empty(&queue)) {
        p = dequeue(&queue);
        printf("Atendendo paciente: %s (ID: %d, Prioridade: %d)\n", p->name, p->id, p->priority);
    }

    printf("Todos os pacientes foram atendidos.\n");

    return 0;
}

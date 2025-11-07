/*
===============================================================================
 Módulo: main_controller.c
 Papel:  Orquestra o fluxo de navegação dos menus (Controller da aplicação).

 Sobre os #includes: (Importação de módulos/arquivos)
   - <stdio.h>:
        Fornece funções de E/S padrão, aqui usamos puts() para imprimir linhas.
        Biblioteca Essencial, dentro do escopo pedido pelo professor
   - "main_controller.h":
        Header do próprio módulo. Expõe a interface pública (ex.: run_main_menu()) 
        para que outros módulos possam chamar o menu principal.
   - "view/menu_view.h":
        Declara as funções de exibição de menus (show_*).
   - "util/input.h":
        Declara utilitários de entrada (ex.: read_int_in_range(), press_enter()).
   - "util/patient_io.h":
        Funções de leitura/escrita de pacientes.
   - "ds/patient_list.h":
        PatientList, insert/print/search/free.
   - "ds/patient_queue.h":
        Fila de pacientes.
   - "model/patient.h":
        Struct Patient.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_controller.h"
#include "view/menu_view.h"
#include "util/input.h"
#include "util/patient_io.h"
#include "ds/patient_list.h"
#include "ds/patient_queue.h"
#include "model/patient.h"

/* ------------------------------
   Submenus internos (helpers)
------------------------------ */
static void run_patient_menu(void);
static void run_queue_menu(void);
static void run_history_menu(void);

/* Lista global de pacientes */
static PatientList global_patient_list;
static int g_inited = 0;

/* Fila global de pacientes */
static PatientQueue global_patient_queue;

/* =========================
   Função de teste rápido
   ========================= */
static void quick_test_patients(void) {
    if (g_inited) return; // Se já foi inicializado, não faz nada.

    // Se não foi, agora sim inicializa tudo aqui dentro
    init_patient_list(&global_patient_list);
    init_queue(&global_patient_queue);

    Patient test_data[] = {
        {1, "Alice", "111", 30, 'F', "Normal", 3},
        {2, "Bob", "222", 25, 'M', "Urgente", 1},
        {3, "Carol", "333", 40, 'F', "Média", 2}
    };
    int num_patients = sizeof(test_data) / sizeof(Patient);

    puts("-> Carregando pacientes de teste na lista e na fila...");
    for (int i = 0; i < num_patients; i++) {
        // 1. Adiciona à lista geral
        insert_patient(&global_patient_list, &test_data[i]);

        // 2. Cria uma cópia para a fila
        Patient *copy = malloc(sizeof(Patient));
        if (copy) {
            *copy = test_data[i];
            // 3. Adiciona a cópia na fila de atendimento
            enqueue(&global_patient_queue, copy);
        }
    }
    puts("-> Pacientes de teste carregados!\n");

    // Define a flag APENAS NO FINAL de tudo.
    g_inited = 1;
}

/* =========================
   Inicialização leve (sem dados de teste)
   ========================= */
static void ensure_initialized(void) {
    if (g_inited) return;
    init_patient_list(&global_patient_list);
    init_queue(&global_patient_queue);
    g_inited = 1;
}

/* =========================
   Loop do menu principal
   ========================= */
void run_main_menu(void) {
    // Apenas chama a função de inicialização.
    // Ela mesma vai garantir que só roda uma vez, na ordem certa.
    
    ensure_initialized(); // Chama se sem teste
    // quick_test_patients(); // Chama se com teste

    for (;;) {
        show_main_menu();
        int option = read_int_in_range("Escolha uma opção [1-3,9]: ", 1, 9);

        switch (option) {
            case 1: 
                run_patient_menu();
                break;
            case 2:     
                run_queue_menu();
                break;
            case 3:     
                run_history_menu();
                break;
            case 9:
                puts("Encerrando o sistema. Até mais!");
                // Adicionando a liberação de memória para evitar vazamentos
                free_list(&global_patient_list);
                free_queue(&global_patient_queue);
                return;
            default:
                puts("Opção inválida.");
        }
    }
}

/* =========================
   Submenu: Pacientes (Lista)
========================= */
static void run_patient_menu(void) {
    for (;;) {
        show_patient_menu();
        int option = read_int_in_range("Escolha uma opção [1-3,9]: ", 1, 9);
        if (option == 9) break;

        switch (option) {
            case 1: {  // Inserir paciente
                Patient p;
                printf("\nCadastrando paciente -\n");
                printf("\nInsira as informações solicitadas abaixo:\n");
                if (read_patient_from_console(&p)) {
                    
                    if (insert_patient(&global_patient_list, &p)) {
                        puts("\nPaciente cadastrado com sucesso.");
                        print_patient_line(&p);
                        puts(""); // Pulo de linha simples
                    } else {
                        puts("\nFalha ao cadastrar (CPF/ID já existente ou erro de memória).");
                    }
                } else {
                    puts("\nEntrada cancelada ou dados inválidos.");
                }
                break;
            }
            case 2:
                // INTERTRAVAMENTO: bloqueia se a lista de pacientes estiver vazia 
                if (is_patient_list_empty(&global_patient_list)) {
                    puts("\nNenhum paciente cadastrado. Use a opção de cadastro para incluir pacientes.\n");
                    break;
                }

                print_all_patient(&global_patient_list);
                puts(""); // Pulo de linha simples
                break;
            case 3: {
                char cpf[15];
                if (read_cpf_from_console(cpf, sizeof cpf)) {
                    const Patient *found = search_patient_by_CPF(&global_patient_list, cpf);
                    if (found) print_patient_line(found);
                    else puts("\nCPF não encontrado.\n");
                }
                break;
            }
            // case 4:
            //     puts("[TODO] Remover paciente da fila por CPF");
            //     break;
            default:
                puts("Opção inválida.");
        }
        press_enter(NULL);
    }
}

/*
  Imprime a FIFO de atendimento

  Args:
    *queue: Ponteiro para a lista de atendimento

  Returns:
    os dados dos pacientes contidos na lista de atendimento.
*/
static void print_queue(PatientQueue *queue) {
    if (is_queue_empty(queue)) {
        puts("\nFila de atendimento está vazia.\n");
        return;
    }

    printf("\n========== FILA DE ATENDIMENTO ==========\n");
    QueueNode *curr = queue->front;
    int pos = 1;
    while (curr) {
        printf("%d) ", pos++);
        print_patient_line(curr->patient); // Usando a função de impressão padrão
        curr = curr->next;
    }
    printf("=========================================\n");
}

/* =========================
   Submenu: Fila de Atendimento (Queue)
========================= */
static void run_queue_menu(void) {
    for (;;) {
        show_queue_menu();
        int option = read_int_in_range("Escolha uma opção [1-3,9]: ", 1, 9);
        if (option == 9) break;

        switch (option) {
            case 1: { // Adicionar paciente à fila

                // INTERTRAVAMENTO: bloqueia se a lista estiver vazia
                if (is_patient_list_empty(&global_patient_list)) {
                    puts("\nNenhum paciente cadastrado. Use o menu 1 (Cadastro) para incluir pacientes.\n");
                    break;
                }

                puts("=== Pacientes disponíveis na lista ===");
                print_all_patient(&global_patient_list);

                char cpf[15];
                if (read_cpf_from_console(cpf, sizeof cpf)) {
                    const Patient *p = search_patient_by_CPF(&global_patient_list, cpf);
                    if (p) {
                        Patient *copy = malloc(sizeof(Patient));
                        if (!copy) {
                            puts("Erro de memória!");
                            break;
                        }
                        *copy = *p;
                        // Chama a nova função corrigida
                        enqueue(&global_patient_queue, copy);
                        printf(" Paciente '%s' adicionado à fila (prioridade %d).\n", copy->name, copy->priority);
                    } else {
                        puts("CPF não encontrado.");
                    }
                }
                break;
            }
            case 2: { // Chamar próximo paciente
                // USA A FUNÇÃO DEQUEUE SEGURA, QUE JÁ EXISTE NO SEU patient_queue.c
                Patient *p = dequeue(&global_patient_queue);

                if (p) {
                    printf("\n Chamando próximo paciente:\n");
                    print_patient_line(p);
                    free(p); // Libera a memória da CÓPIA do paciente
                } else {
                    puts("\nFila vazia.\n");
                }
                break;
            }
            case 3:
                print_queue(&global_patient_queue);
                break;
            // case 4:
            //     puts("[TODO] Remover paciente da fila por CPF");
            //     break;
            default:
                puts("Opção inválida.");
        }
        press_enter(NULL);
    }
}

/* =========================
   Submenu: Histórico (Pilha/Stack)
========================= */
static void run_history_menu(void) {
    for (;;) {
        show_history_menu();
        int option = read_int_in_range("Escolha uma opção [1-2,9]: ", 1, 9);
        if (option == 9) break;

        switch (option) {
            case 1: 
                puts("[TODO] Visualizar últimos atendimentos"); 
                break;
            case 2: 
                puts("[TODO] Desfazer último atendimento"); 
                break;
            default: 
                puts("Opção inválida.");
        }
        press_enter(NULL);
    }
}

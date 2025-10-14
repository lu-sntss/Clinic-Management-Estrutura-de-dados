/*
===============================================================================
 Módulo: main_controller.c
 Papel:  Orquestra o fluxo de navegação dos menus (Controller da aplicação).

 Sobre os #includes: (Improtação de modulos/arquivos)
   - <stdio.h>:
        Fornece funções de E/S padrão, aqui usamos puts() para imprimir linhas.
        Biblioteca Essencial, dentro do escopo pedido pelo professor
   - "main_controller.h":
        Header do próprio módulo. Expõe a interface pública (ex.: run_main_menu()) 
        para que outros módulos possam chamar o menu principal.
   - "view/menu_view.h":
        Apenas DECLARA as funções de exibição de menus (show_*). As DEFINIÇÕES 
        reais moram em menu_view.c. Incluir o header permite ao compilador checar 
        tipos/assinaturas ao chamar show_*.
   - "util/input.h":
        Declara utilitários de entrada (ex.: read_int_in_range(), press_enter()) 
        implementados em outro .c. O header nos dá os prototypes corretos.

 Observação importante sobre headers em C:
   #include "arquivo.h" traz DECLARAÇÕES para este .c; o código de fato 
   (DEFINIÇÕES) fica nos .c correspondentes e é “costurado” pelo linker(interno do compilador) 
   ao final.

 Convenções deste projeto:
   - Nomes de funções e identificadores em inglês.
   - Comentários em português (explicam o "porquê" e o "que" está acontecendo).
===============================================================================
*/

#include <stdio.h>
#include <string.h>            // strcspn, fgets
#include "main_controller.h"
#include "view/menu_view.h"
#include "util/input.h"
#include "ds/patient_list.h"   // PatientList, insert/print/search/free
#include "model/patient.h"     // Patient

/*
-------------------------------------------------------------------------------
 Submenus internos (helpers)
 
 - 'static' restringe a VISIBILIDADE à unidade de tradução (este arquivo .c).
   Ou seja, essas funções NÃO ficam “exportadas” para outros .c.
   Elas são detalhes de implementação do controller.
   Pode se chamar de métodos privados do controller
-------------------------------------------------------------------------------
*/
static void run_patient_menu(void);
static void run_queue_menu(void);
static void run_history_menu(void);

/* =========================
   Loop do menu principal
   ========================= */
/*
 Função: run_main_menu
 Responsabilidade:
   - Exibir o menu principal e despachar para os submenus conforme a opção.
   - Permanecer em loop até o usuário escolher sair.
 
 Nota sobre 'for (;;)':
   - É um laço infinito idiomático em C (equivalente a 'while (1)').
   - Saímos dele com 'return' (caso 9) encerrando o programa/menu.
   - Podemos simplificar se de acordo com o time
*/
void run_main_menu(void) {
    for (;;) { // Basicamente um "while rodando para sempre" até sair explicitamente
        show_main_menu();  // Apenas imprime o menu principal (camada de VIEW)
        int option = read_int_in_range("Escolha uma opção [1-3,9]: ", 1, 9);
        // read_int_in_range: garante um inteiro dentro do intervalo informado.
        // Aqui aceitamos 1..9; as opções não usadas caem no 'default'.

        switch (option) {
            case 1: 
                run_patient_menu();   // Submenu de Pacientes (Lista)
                break;
            case 2:    
                run_queue_menu();     // Submenu de Fila (Queue)
                break;
            case 3:    
                run_history_menu();   // Submenu de Histórico (Pilha/Stack)
                break;
            case 9:
                puts("Encerrando o sistema. Até mais!");
                return;               // Sai do laço e encerra o controller
            default:
                // Pode ocorrer se o usuário digitar algo "válido" (1..9) que não mapeamos
                puts("Opção inválida.");
        }
    }
}

/* =========================
   Loops dos submenus
   ========================= */

/*
 Submenu: Pacientes (Lista)
 Papel:
   - Exibe as opções relacionadas ao cadastro/consulta de pacientes.
   - Mantém o usuário no submenu até escolher '9' (Voltar).
 Observações:
   - Neste estágio, as ações estão como [TODO]; apenas mensagens de stub.
   - press_enter(NULL) aguarda ENTER para dar tempo de leitura ao usuário.
*/
static void run_patient_menu(void) {
    static PatientList list;        // Lista persistente enquanto o programa roda
    static int initialized = 0;
    if (!initialized) {
        initList(&list);
        initialized = 1;
    }

    for (;;) {
        show_patient_menu();
        int option = read_int_in_range("Escolha uma opção [1-3,9]: ", 1, 9);
        if (option == 9) break;

        switch (option) {
            case 1: {
                Patient p;
                printf("ID: ");
                scanf("%d", &p.id);
                printf("Nome: ");
                getchar(); // consome '\n'
                fgets(p.name, sizeof(p.name), stdin);
                p.name[strcspn(p.name, "\n")] = '\0';

                printf("CPF: ");
                fgets(p.cpf, sizeof(p.cpf), stdin);
                p.cpf[strcspn(p.cpf, "\n")] = '\0';

                printf("Idade: ");
                scanf("%d", &p.age);

                printf("Sexo (M/F): ");
                getchar();
                scanf("%c", &p.gender);

                printf("Condição: ");
                getchar();
                fgets(p.condition, sizeof(p.condition), stdin);
                p.condition[strcspn(p.condition, "\n")] = '\0';

                printf("Prioridade [1-Alta / 2-Média / 3-Baixa]: ");
                scanf("%d", &p.priority);

                insertPatient(&list, p);
                printf("Paciente inserido com sucesso!\n");
                break;
            }
            case 2:
                printPatients(&list);
                break;
            case 3: {
                char cpf[15];
                printf("Digite o CPF: ");
                getchar();
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0';

                Patient* found = searchPatientByCPF(&list, cpf);
                if (found)
                    printf("Paciente encontrado: %s (%d anos)\n", found->name, found->age);
                else
                    printf("Paciente não encontrado.\n");
                break;
            }
            default:
                puts("Opção inválida.");
        }

        press_enter(NULL); // Pausa para o usuário ler a saída antes de redesenhar o menu
    }

    freeList(&list);  // Limpa memória ao sair do submenu (opcional)
}

/*
 Submenu: Fila de Atendimento (Queue)
 Papel:
   - Operações de enfileiramento/atendimento.
   - Permanece até '9' (Voltar).
*/
static void run_queue_menu(void) {
    for (;;) {
        show_queue_menu();  // VIEW: apenas imprime o submenu
        int option = read_int_in_range("Escolha uma opção [1-3,9]: ", 1, 9);
        if (option == 9) break;

        switch (option) {
            case 1: 
                puts("[TODO] Adicionar paciente à fila"); 
                break;
            case 2: 
                puts("[TODO] Chamar próximo paciente"); 
                break;
            case 3: 
                puts("[TODO] Ver quem está na fila"); 
                break;
            default: 
                puts("Opção inválida.");
        }
        press_enter(NULL); // Pausa para leitura
    }
}

/*
 Submenu: Histórico (Pilha/Stack)
 Papel:
   - Visualização e operações relacionadas ao histórico de atendimentos.
   - Permanece até '9' (Voltar).
*/
static void run_history_menu(void) {
    for (;;) {
        show_history_menu();  // VIEW: apenas imprime o submenu
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
        press_enter(NULL); // Pausa para leitura
    }
}


/*
===============================================================================
 Módulo: menu_view.c
 Papel:  Responsável APENAS por exibir (imprimir) os menus na tela.
        Não lê entrada do usuário, não controla fluxo de navegação.
        (Separação clara de responsabilidades: VIEW vs CONTROLLER)

 Dependências:
   - <stdio.h>: puts() para imprimir linhas. (Dentro do solicitado pelo professor)
   - "menu_view.h": garante que as assinaturas aqui definidas batem com o header.
===============================================================================
*/

#include <stdio.h>
#include "menu_view.h"

/* =========================
   Menus (exibição)
   ========================= */

void show_main_menu(void) {
    puts("\n================= CLÍNICA — MENU PRINCIPAL =================");
    puts("1) Cadastro de Pacientes (Lista)");
    puts("2) Fila de Atendimento   (Fila)");
    puts("3) Histórico             (Pilha)");
    puts("9) Sair");
    puts("============================================================");
}

void show_patient_menu(void) {
    puts("\n=========== CADASTRO DE PACIENTES (LISTA) ===========");
    puts("1) Inserir novo paciente");
    puts("2) Listar todos os pacientes");
    puts("3) Buscar paciente por CPF");
    puts("9) Voltar");
    puts("=====================================================");
}

void show_queue_menu(void) {
    puts("\n============ FILA DE ATENDIMENTO (FILA) ============");
    puts("1) Adicionar paciente à fila");
    puts("2) Chamar próximo paciente");
    puts("3) Ver quem está na fila");
    puts("9) Voltar");
    puts("====================================================");
}

void show_history_menu(void) {
    puts("\n=============== HISTÓRICO (PILHA) ==================");
    puts("1) Visualizar últimos atendimentos");
    puts("2) Desfazer último atendimento");
    puts("9) Voltar");
    puts("====================================================");
}

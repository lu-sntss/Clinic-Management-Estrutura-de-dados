#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------
// Estrutura do Paciente
// ------------------------
typedef struct Paciente {
    char nome[50];
    int idade;
    char cpf[15];
    char prioridade[10]; // "normal" ou "urgente"
    struct Paciente *prox;
} Paciente;

// Lista encadeada (cadastro)
Paciente *lista = NULL;

// Fila de atendimento
Paciente *inicioFila = NULL;
Paciente *fimFila = NULL;

// Pilha do histórico
Paciente *topoHistorico = NULL;

// ------------------------
// Funções da Lista Encadeada
// ------------------------
void cadastrarPaciente() {
    Paciente *novo = (Paciente*)malloc(sizeof(Paciente));

    printf("\nNome: ");
    scanf(" %[^\n]", novo->nome);
    printf("Idade: ");
    scanf("%d", &novo->idade);
    printf("CPF: ");
    scanf(" %[^\n]", novo->cpf);
    printf("Prioridade (normal/urgente): ");
    scanf(" %[^\n]", novo->prioridade);

    novo->prox = lista;
    lista = novo;

    printf("\nPaciente cadastrado com sucesso!\n");
}

void listarPacientes() {
    Paciente *aux = lista;
    if (aux == NULL) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Pacientes ---\n");
    while (aux != NULL) {
        printf("Nome: %s | Idade: %d | CPF: %s | Prioridade: %s\n",
               aux->nome, aux->idade, aux->cpf, aux->prioridade);
        aux = aux->prox;
    }
}

void buscarPaciente() {
    char cpfBuscado[15];
    printf("\nDigite o CPF do paciente: ");
    scanf(" %[^\n]", cpfBuscado);

    Paciente *aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->cpf, cpfBuscado) == 0) {
            printf("\nPaciente encontrado:\n");
            printf("Nome: %s | Idade: %d | CPF: %s | Prioridade: %s\n",
                   aux->nome, aux->idade, aux->cpf, aux->prioridade);
            return;
        }
        aux = aux->prox;
    }
    printf("\nPaciente não encontrado.\n");
}

// ------------------------
// Funções da Fila
// ------------------------
void adicionarNaFila() {
    char cpfBuscado[15];
    printf("\nDigite o CPF do paciente para colocar na fila: ");
    scanf(" %[^\n]", cpfBuscado);

    Paciente *aux = lista;

    while (aux != NULL) {
        if (strcmp(aux->cpf, cpfBuscado) == 0) {
            Paciente *novo = (Paciente*)malloc(sizeof(Paciente));
            *novo = *aux;
            novo->prox = NULL;

            if (fimFila == NULL) {
                inicioFila = fimFila = novo;
            } else {
                fimFila->prox = novo;
                fimFila = novo;
            }

            printf("\nPaciente colocado na fila!\n");
            return;
        }
        aux = aux->prox;
    }
    printf("\nPaciente não encontrado no cadastro.\n");
}

void chamarPaciente() {
    if (inicioFila == NULL) {
        printf("\nFila vazia.\n");
        return;
    }

    Paciente *atendido = inicioFila;
    inicioFila = inicioFila->prox;

    if (inicioFila == NULL) fimFila = NULL;

    // empilha no histórico
    atendido->prox = topoHistorico;
    topoHistorico = atendido;

    printf("\nPaciente atendido e movido ao histórico!\n");
}

void verFila() {
    Paciente *aux = inicioFila;
    if (aux == NULL) {
        printf("\nNenhum paciente na fila.\n");
        return;
    }
    printf("\n--- Fila de Atendimento ---\n");
    while (aux != NULL) {
        printf("CPF: %s | Nome: %s\n", aux->cpf, aux->nome);
        aux = aux->prox;
    }
}

// ------------------------
// Funções da Pilha (histórico)
// ------------------------
void verHistorico() {
    Paciente *aux = topoHistorico;
    if (aux == NULL) {
        printf("\nHistórico vazio.\n");
        return;
    }
    printf("\n--- Histórico de Atendimentos ---\n");
    while (aux != NULL) {
        printf("CPF: %s | Nome: %s\n", aux->cpf, aux->nome);
        aux = aux->prox;
    }
}

void desfazerUltimoAtendimento() {
    if (topoHistorico == NULL) {
        printf("\nHistórico vazio, nada a desfazer.\n");
        return;
    }
    Paciente *removido = topoHistorico;
    topoHistorico = topoHistorico->prox;
    free(removido);
    printf("\nÚltimo atendimento desfeito.\n");
}

// ------------------------
// Programa Principal
// ------------------------
int main() {
    int opcao;

    do {
        printf("\n--- Sistema da Clínica ---\n");
        printf("1 - Cadastrar Paciente\n");
        printf("2 - Listar Pacientes\n");
        printf("3 - Buscar Paciente\n");
        printf("4 - Adicionar na Fila\n");
        printf("5 - Chamar próximo paciente\n");
        printf("6 - Ver Fila\n");
        printf("7 - Ver Histórico\n");
        printf("8 - Desfazer último atendimento\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarPaciente(); break;
            case 2: listarPacientes(); break;
            case 3: buscarPaciente(); break;
            case 4: adicionarNaFila(); break;
            case 5: chamarPaciente(); break;
            case 6: verFila(); break;
            case 7: verHistorico(); break;
            case 8: desfazerUltimoAtendimento(); break;
        }
    } while(opcao != 0);

    return 0;
}

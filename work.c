#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------
// Estrutura do Paciente
// ------------------------
typedef struct Paciente{
    char nome[50];
    int idade;
    char cpf[15];
    char prioridade[10]; // normal ou urgente
    struct Paciente *prox; // auto-referência para proximo paciente
} Paciente; // Alias amigavel da struct para código mais limpo

// lista encadeada (cadastro)
Paciente *lista = NULL;

// fila de atendimento
Paciente *inicio_fila = NULL;
Paciente *fim_fila = NULL;

// pilha do historico
Paciente *topo_historico = NULL;

// ========= Funções Lista encadeada =========
void cadastrar_paciente(){
    Paciente *novo = (Paciente*)malloc(sizeof(Paciente)); // Alocação de memoria dinamica para criar um novo paciente

    printf("\nNome: ");
    // Utilizo uma forma de ler nomes compostos
    // []   --> leia um conjunto de caracteres
    // ^    --> que não seja
    // \n   --> o enter
    scanf(" %[^\n]", novo->nome); // o espaço na frente impede o buffer de ler o \n acidental e finalizar leitura antes de receber o dado
    printf("\nIdade: ");
    scanf("%d", &novo->idade);
    printf("\nCPF: ");
    scanf(" %[^\n]", novo->cpf);
    printf("\n Prioridade (normal/urgente): ");
    scanf(" %[^\n]", novo->prioridade);

    novo->prox = lista; // vá ATÉ o endereço novo e acesse a variável prox e atribua o novo paciente a lista
    lista=novo; // define o novo paciente como inicio da lista encadeada

    printf("\nPaciente cadastrado com sucesso!\n");
}

void imprimir_lista_paciente(){
    Paciente *aux = lista;

    if (aux == NULL){
        printf("\nNenhum paciente cadastrado.\n");
        return;
    };

    printf("\n--- Lista de pacientes ---\n");
    while (aux != NULL) {
        printf("Nome: %s | Idade: %d | CPF: %s | Prioridade: %s\n",
            aux->nome, aux->idade, aux->cpf, aux->prioridade);
        aux = aux->prox;
    };
};

int main(){
    int opcao;
        
    do{
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

        switch (opcao){
            case 1:
                cadastrar_paciente();
                break;
            case 2:
                imprimir_lista_paciente();
                break;
            case 3:
                printf("HELLO WORLD\n");
                break;
            case 4:
                printf("HELLO WORLD\n");
                break;
            case 5:
                printf("HELLO WORLD\n");
                break;
            case 6:
                printf("HELLO WORLD\n");
                break;
            case 7:
                printf("HELLO WORLD\n");
                break;
            case 8:
                printf("HELLO WORLD\n");
                break;
            default:
            break;
        }
    } while (opcao != 0);

    
};








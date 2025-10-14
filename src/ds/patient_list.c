/*
 Módulo: patient_list.c
 Papel:  Implementa a estrutura de dados de lista encadeada para gerenciar
         os pacientes. Este módulo contém a DEFINIÇÃO (a lógica interna)
         de como os pacientes são armazenados, inseridos, buscados e liberados
         da memória.

 Sobre os #includes: (Importação de módulos/arquivos)
   - <stdio.h>:
        Fornece funções de E/S, como printf() para exibir a lista e
        mensagens de erro/status.
   - <stdlib.h>:
        Essencial para o gerenciamento de memória dinâmica. Usamos malloc()
        para alocar espaço para novos nós (Node) e free() para liberá-los.
   - <string.h>:
        Fornece a função strcmp() para comparar os CPFs durante a busca.
   - "patient_list.h":
        Header do próprio módulo. Traz as DECLARAÇÕES das estruturas (Patient,
        Node, PatientList) e os protótipos das funções públicas, formando o
        "contrato" que outros módulos (como o controller) usarão.

 Observação importante sobre o Módulo:
   Este arquivo é o "coração" do armazenamento de dados. Ele abstrai a
   complexidade de ponteiros e alocação de memória. Outras partes do
   sistema (como main_controller.c) não precisam saber COMO a lista funciona,
   apenas precisam chamar as funções declaradas no header
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_list.h"

/*
 Função: init_patient_list
 Responsabilidade:
   - Inicializar uma lista, garantindo que ela comece em um estado válido
     e seguro, ou seja, vazia.
 Parâmetros:
   - list: Um ponteiro para a estrutura PatientList que será inicializada.
           É um ponteiro para que a função possa modificar a variável original
           passada por quem a chamou.
 Lógica:
   - Uma lista vazia é representada por um ponteiro 'head' (cabeça) que
     aponta para NULL.
*/
void init_patient_list(PatientList* list) {
    list->head = NULL;
}

/*
 Função: insert_patient
 Responsabilidade:
   - Adicionar um novo paciente ao início da lista. Esta é a forma mais
     simples e eficiente (complexidade O(1)) de inserção em lista encadeada.
 Parâmetros:
   - list: Ponteiro para a lista onde o paciente será inserido.
   - patient: Os dados do paciente a serem adicionados (copiados para a lista).
 Lógica de Implementação:
   1. Aloca memória dinamicamente para um novo 'Node' (o contêiner).
   2. Verifica se a alocação de memória foi bem-sucedida. É uma boa prática
      de programação defensiva para evitar que o programa quebre.
   3. Copia os dados do paciente para dentro do novo nó.
   4. O 'next' do novo nó aponta para o que era o antigo início da lista.
   5. A cabeça ('head') da lista passa a ser o novo nó que acabamos de criar.
*/
void insert_patient(PatientList* list, Patient patient) {
    // 1. Aloca um "contêiner" (Node) para guardar os dados do paciente
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) { // 2. Se malloc falhar (faltar memória), ele retorna NULL
        printf("Erro de alocação de memória!\n");
        return;
    }

    newNode->data = patient;          // 3. Coloca os dados do paciente no contêiner
    newNode->next = list->head;       // 4. O novo nó agora "aponta" para o antigo primeiro
    list->head = newNode;             // 5. A lista oficialmente começa neste novo nó
}

/*
 Função: print_all_patient
 Responsabilidade:
   - Percorrer e exibir todos os pacientes cadastrados na lista, do primeiro
     ao último.
 Parâmetros:
   - list: A lista de pacientes a ser exibida.
 Lógica:
   - Primeiro, trata o caso de a lista estar vazia.
   - Cria um ponteiro temporário 'current' que começa na cabeça da lista.
   - Em um loop, enquanto 'current' não for NULL (fim da lista):
     a. Imprime os dados do paciente no nó atual.
     b. Avança 'current' para o próximo nó da sequência (current = current->next).
*/
void print_all_patient(PatientList* list) {
    if (list->head == NULL) { // Caso especial: lista vazia
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    Node* current = list->head; // Ponteiro para percorrer a lista sem perder a referência da cabeça
    printf("\n=== Lista de Pacientes ===\n");
    while (current != NULL) {
        Patient p = current->data;
        printf("ID: %d | Nome: %s | CPF: %s | Idade: %d | Prioridade: %d\n",
               p.id, p.name, p.cpf, p.age, p.priority);
        current = current->next; // Move para o próximo nó
    }
}

/*
 Função: search_patient_by_CPF
 Responsabilidade:
   - Buscar um paciente na lista usando o CPF como chave única de identificação.
 Parâmetros:
   - list: A lista onde a busca será realizada.
   - cpf: A string de CPF a ser procurada. É 'const' para garantir que a
          função não altere o valor que está sendo buscado.
 Retorno:
   - Retorna um PONTEIRO para os dados do paciente (Patient) se encontrado.
   - Retorna NULL se nenhum paciente com o CPF informado for encontrado.
 Lógica:
   - Percorre a lista de forma similar à função print_all_patient.
   - Em cada nó, usa strcmp() para comparar o CPF do nó atual com o CPF buscado.
   - Se strcmp() retornar 0 (strings são iguais), a função retorna o endereço
     dos dados do paciente (&current->data) e para a busca.
   - Se chegar ao final da lista sem encontrar, retorna NULL.
*/
Patient* search_patient_by_CPF(PatientList* list, const char* cpf) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.cpf, cpf) == 0) { // Compara os CPFs
            return &current->data; // Encontrado! Retorna o endereço dos dados.
        }
        current = current->next; // Não é este, vamos para o próximo.
    }
    return NULL; // Percorreu tudo e não achou.
}

/*
 Função: free_list
 Responsabilidade:
   - Liberar toda a memória alocada dinamicamente pelos nós da lista,
     evitando vazamentos de memória (memory leaks).
 Parâmetros:
   - list: A lista a ser "destruída".
 Lógica de Implementação (CRUCIAL):
   - Percorre a lista, mas com um cuidado especial:
   1. Um ponteiro 'current' aponta para o nó atual que será liberado.
   2. ANTES de liberar 'current', é preciso guardar uma referência para o
      próximo nó, senão perderíamos o resto da lista. Um ponteiro 'temp'
      guarda 'current'.
   3. 'current' avança para o próximo nó.
   4. AGORA sim, com o caminho para o resto da lista salvo, podemos liberar
      a memória do nó anterior (apontado por 'temp').
   - Ao final, o 'head' da lista é setado para NULL para indicar que ela está
     vazia e segura para ser usada novamente.
*/
void free_list(PatientList* list) {
    Node* current = list->head;
    Node* temp;

    while (current != NULL) {
        temp = current;             // 1. Guarda o nó atual para liberar depois
        current = current->next;    // 2. AVANÇA para o próximo ANTES de apagar o atual
        free(temp);                 // 3. Libera a memória do nó que ficou para trás
    }
    list->head = NULL; // Deixa a lista em um estado limpo e seguro
}
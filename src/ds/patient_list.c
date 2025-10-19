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
   0. (NOVO) Verifica se já existe um paciente com o mesmo CPF; se existir,
      não insere para manter unicidade de CPF.
   1. Aloca memória dinamicamente para um novo 'Node' (o contêiner).
   2. Verifica se a alocação de memória foi bem-sucedida. É uma boa prática
      de programação defensiva para evitar que o programa quebre.
   3. Copia os dados do paciente para dentro do novo nó.
   4. O 'next' do novo nó aponta para o que era o antigo início da lista.
   5. A cabeça ('head') da lista passa a ser o novo nó que acabamos de criar.
*/
int insert_patient(PatientList *list, const Patient *p) {
    if (!list || !p) return 0;

    /* Unicidade de CPF */
    const Patient *dup = search_patient_by_CPF(list, p->cpf);
    if (dup) return 0;

    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return 0;

    newNode->data = *p;          /* copia por valor a partir do ponteiro */
    newNode->next = list->head;  /* insere no início (O(1)) */
    list->head    = newNode;

    return 1;
}


/*
 Função: search_patient_by_CPF
 Responsabilidade:
   - Buscar um paciente na lista usando o CPF como chave única de identificação.
 Parâmetros:
   - list: A lista onde a busca será realizada.
   - cpf:  A string de CPF a ser procurada (não é modificada pela função).
 Retorno:
   - Retorna um PONTEIRO para os dados do paciente (Patient) se encontrado.
   - Retorna NULL se nenhum paciente com o CPF informado for encontrado.
 Lógica:
   1. Verifica argumentos básicos (list e cpf). Se inválidos, retorna NULL.
   2. Percorre a lista a partir de 'head' até o fim (cur = cur->next).
   3. Em cada nó, compara o CPF armazenado com o CPF buscado via strcmp().
   4. Se strcmp() retornar 0 (strings iguais), retorna &cur->data imediatamente.
   5. Se chegar ao final sem encontrar, retorna NULL.
 Observações:
   - Complexidade de tempo: O(n), onde n é o número de nós da lista.
   - Pressupõe que o CPF já foi normalizado no momento da entrada
     (ex.: sem '\n' e sem espaços nas pontas). A comparação é exata:
     "111.222.333-44" é diferente de "11122233344".
*/
const Patient* search_patient_by_CPF(const PatientList *list, const char *cpf) {
    if (!list || !cpf) return NULL;
    for (Node *cur = list->head; cur; cur = cur->next) {
        if (strcmp(cur->data.cpf, cpf) == 0) return &cur->data;
    }
    return NULL;
}

// /*
//  Função: id_exists  (opcional, auxiliar)
//  Responsabilidade:
//    - Verificar se já existe um paciente com o ID informado na lista.
//  Parâmetros:
//    - list: Lista onde a verificação será feita.
//    - id:   Identificador numérico do paciente a verificar.
//  Retorno:
//    - Retorna 1 se existir ao menos um nó com 'data.id == id'.
//    - Retorna 0 se não encontrar nenhum ID igual.
//  Lógica:
//    - Percorre a lista do 'head' ao fim comparando 'cur->data.id == id'.
//    - Se encontrar, retorna 1 imediatamente; senão, ao final retorna 0.
//    - Complexidade O(n).
// */
// static int id_exists(const PatientList *list, int id) {
//     for (Node *cur = list->head; cur; cur = cur->next) {
//         if (cur->data.id == id) return 1;
//     }
//     return 0;
// }


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

/*
 Função: print_all_patient
 Responsabilidade:
   - Percorrer e exibir todos os pacientes cadastrados na lista, do primeiro
     ao último.
 Parâmetros:
   - list: A lista de pacientes a ser exibida.
 Lógica:
   - Cria um ponteiro temporário 'current' que começa na cabeça da lista.
   - Em um loop, enquanto 'current' não for NULL (fim da lista):
     a. Imprime os dados do paciente no nó atual.
     b. Avança 'current' para o próximo nó da sequência (current = current->next).
*/
void print_all_patient(PatientList* list) {

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
  Verifica se a lista de pacientes está vazia.

  Args:
    list: Ponteiro para a lista a ser verificada.

  Returns:
    int: 1 se vazia (ou se list == NULL), 0 caso contrário.
*/
int is_patient_list_empty(const PatientList *list) {
    if (list == NULL) return 1;
    /* Ajuste o nome do campo se necessário (ex.: list->first). */
    return (list->head == NULL) ? 1 : 0;
}
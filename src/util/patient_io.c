#include "patient_io.h"
#include <stdio.h>
#include <string.h>

/* Remove o '\n' final de uma string lida por fgets (se existir). */
static void trim_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}

/*
 * Descarta o restante da linha corrente em stdin.
 * Útil ao misturar scanf (numérico) com fgets (string), evitando que
 * o '\n' pendente seja capturado pela próxima leitura de linha.
 */
static void flush_stdin_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/*
 * Lê todos os campos do Patient via console.
 * - Retorna 0 imediatamente se qualquer leitura falhar (inclui EOF/Ctrl+D).
 * - Normaliza e valida o struct antes de retornar sucesso.
 * - Em caso de dados inválidos, imprime a mensagem de erro de domínio.
 */
int read_patient_from_console(Patient* p) {
    if (!p) return 0;

    printf("ID: ");
    if (scanf("%d", &p->id) != 1) return 0;
    flush_stdin_line();  /* limpa '\n' após scanf */

    printf("Nome: ");
    if (!fgets(p->name, sizeof(p->name), stdin)) return 0;
    trim_newline(p->name);

    printf("CPF: ");
    if (!fgets(p->cpf, sizeof(p->cpf), stdin)) return 0;
    trim_newline(p->cpf);

    printf("Idade: ");
    if (scanf("%d", &p->age) != 1) return 0;

    /* Espaço antes de %c faz scanf ignorar whitespace pendente */
    printf("Sexo (M/F): ");
    if (scanf(" %c", &p->gender) != 1) return 0;
    flush_stdin_line();

    printf("Condição: ");
    if (!fgets(p->condition, sizeof(p->condition), stdin)) return 0;
    trim_newline(p->condition);

    printf("Prioridade [1-Alta / 2-Média / 3-Baixa]: ");
    if (scanf("%d", &p->priority) != 1) return 0;
    flush_stdin_line();

    /* Normalização de campos (ex.: gênero para maiúsculo) */
    patient_normalize(p);

    /* Validação de domínio (mensagem amigável em caso de erro) */
    char err[64];
    if (!patient_validate(p, err, sizeof err)) {
        printf("Dados inválidos: %s\n", err);
        return 0;
    }
    return 1;
}

/*
 * Captura um CPF como string (sem validação de formato).
 * Útil para buscas por CPF.
 */
int read_cpf_from_console(char* cpf, size_t cap) {
    if (!cpf || cap == 0) return 0;
    printf("Digite o CPF: ");
    if (!fgets(cpf, cap, stdin)) return 0;
    trim_newline(cpf);
    return 1;
}

/*
 * Impressão compacta de um Patient (debug/listagens).
 * Evita acesso nulo verificando ponteiro antes.
 */
void print_patient_line(const Patient* p) {
    if (!p) { puts("(Patient=NULL)"); return; }
    printf("ID: %d | Nome: %s | CPF: %s | Idade: %d | Prioridade: %d\n",
           p->id, p->name, p->cpf, p->age, p->priority);
}

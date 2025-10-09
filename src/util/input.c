#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Lê uma linha do stdin (sem incluir o '\n') garantindo terminação em '\0'.

Args:
    buffer: Buffer de destino.
    capacity: Tamanho total do buffer (bytes).

Returns:
    int: 1 em sucesso, 0 em erro/EOF.
*/
int read_line(char *buffer, size_t capacity) {
    if (!fgets(buffer, (int)capacity, stdin)) return 0;
    size_t n = strlen(buffer);
    if (n > 0 && buffer[n - 1] == '\n') buffer[n - 1] = '\0';
    return 1;
}

/*
Lê um inteiro dentro de um intervalo, repetindo até ser válido.

Args:
    prompt: Texto a exibir ao usuário.
    min: Valor mínimo aceito.
    max: Valor máximo aceito.

Returns:
    int: Valor válido dentro de [min, max].
*/
int read_int_in_range(const char *prompt, int min, int max) {
    char line[64];
    for (;;) {
        printf("%s", prompt);
        if (!read_line(line, sizeof(line))) {
            puts("\nEntrada encerrada. Saindo...");
            exit(0);
        }
        char *endptr = NULL;
        long val = strtol(line, &endptr, 10);
        while (endptr && *endptr && isspace((unsigned char)*endptr)) endptr++;
        if (endptr && *endptr == '\0' && val >= min && val <= max) {
            return (int)val;
        }
        printf("Opção inválida. Digite um número entre %d e %d.\n", min, max);
    }
}

/*
Aguarda ENTER para continuar.

Args:
    message: Mensagem opcional antes da pausa (pode ser NULL).
*/
void press_enter(const char *message) {
    if (message && *message) printf("%s", message);
    printf("Pressione ENTER para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}

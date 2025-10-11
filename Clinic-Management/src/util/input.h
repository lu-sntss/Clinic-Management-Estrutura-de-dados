#ifndef INPUT_H
#define INPUT_H
#include <stddef.h>

/* Lê linha do stdin e remove '\n'. Retorna 1 em sucesso, 0 em erro/EOF. */
int read_line(char *buffer, size_t capacity);

/* Lê inteiro no intervalo [min, max], repetindo até ser válido. */
int read_int_in_range(const char *prompt, int min, int max);

/* Pausa aguardando ENTER (mensagem opcional). */
void press_enter(const char *message);

#endif /* INPUT_H */

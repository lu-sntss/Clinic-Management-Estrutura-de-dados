#include "patient.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/*
 * Retorna 1 se a string for NULL, vazia ou apenas espaços; caso contrário 0.
 * Útil para validações de obrigatoriedade sem impor formato.
 */
static int is_blank(const char* s) {
    if (!s || !*s) return 1;
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

/*
 * Normalização de campos do Patient.
 * Objetivo: padronizar valores para reduzir falhas de validação/negócio.
 *
 * Exemplo atual:
 *   - Converte gender para maiúsculo (permite entrada 'm'/'f').
 * Futuras normalizações possíveis:
 *   - Trim em name/condition, remoção de espaços duplos, etc.
 */
void patient_normalize(Patient* p) {
    if (!p) return;
    if (p->gender >= 'a' && p->gender <= 'z')
        p->gender = (char)toupper((unsigned char)p->gender);
}

/*
 * Validação de domínio do Patient.
 *
 * Args:
 *   p:      Ponteiro para validação.
 *   errbuf: Buffer opcional para mensagem de erro (pode ser NULL).
 *   errcap: Capacidade de errbuf (ignorada se errbuf for NULL ou 0).
 *
 * Returns:
 *   1 se válido, 0 caso inválido (errbuf recebe motivo quando possível).
 *
 * Regras atuais:
 *   - id > 0
 *   - name não vazio/branco
 *   - age no intervalo [0..130]
 *   - gender ∈ {'M','F'}
 *   - priority ∈ {1,2,3}
 *   - cpf não vazio/branco (não valida dígitos/algoritmo ainda)
 *
 * Observações:
 *   - errbuf é “melhor esforço”: mensagem curta e objetiva.
 *   - Validação completa de CPF (dígitos/algoritmo) pode ser adicionada
 *     futuramente sem alterar a assinatura.
 */
int patient_validate(const Patient* p, char* errbuf, size_t errcap) {
    if (!p) {
        if (errbuf && errcap) snprintf(errbuf, errcap, "Paciente NULL.");
        return 0;
    }
    if (p->id <= 0) {
        if (errbuf && errcap) snprintf(errbuf, errcap, "id deve ser > 0.");
        return 0;
    }
    if (is_blank(p->name)) {
        if (errbuf && errcap) snprintf(errbuf, errcap, "name vazio.");
        return 0;
    }
    if (p->age < 0 || p->age > 130) {
        if (errbuf && errcap) snprintf(errbuf, errcap, "age fora de faixa [0..130].");
        return 0;
    }
    if (!(p->gender == 'M' || p->gender == 'F')) {
        if (errbuf && errcap) snprintf(errbuf, errcap, "gender deve ser 'M' ou 'F'.");
        return 0;
    }
    if (p->priority < 1 || p->priority > 3) {
        if (errbuf && errcap) snprintf(errbuf, errcap, "priority deve ser 1..3.");
        return 0;
    }
    /* CPF: apenas obriga não-vazio por enquanto */
    if (is_blank(p->cpf)) {
        if (errbuf && errcap) snprintf(errbuf, errcap, "cpf vazio.");
        return 0;
    }
    return 1;
}

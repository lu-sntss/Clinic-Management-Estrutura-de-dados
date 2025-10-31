# Makefile 
# ------------------
# Este arquivo automatiza a compilação do projeto.
# Comentarios de guia para desenvolvimento do projeto em colaboração com a equipe

# --- Variáveis de Compilação ---

# Define o compilador C que será utilizado. 'gcc' é o padrão na maioria dos sistemas.
CC      := gcc

# Define as flags (opções) para o compilador.
# -std=c11      : Usa o padrão C11 da linguagem C.
# -Wall -Wextra : Ativa um conjunto extenso de avisos (warnings) para ajudar a encontrar possíveis erros.
# -Wpedantic    : Garante que o código segue estritamente o padrão ISO C.
# -g            : # BOA PRÁTICA: Adiciona informações de debug ao executável. Essencial para usar um debugger como o GDB.
# -I./src       : Informa ao compilador para procurar arquivos de cabeçalho (.h) também no diretório 'src'.
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -g -I./src

# # MUDANÇA: LDFLAGS para opções que precisam estar também no link (ex.: sanitizers).
LDFLAGS :=

# # MUDANÇA: Toggle de perfil de build (debug por padrão).
# DEBUG=1 -> compila com -g (manter linha acima)
# DEBUG=0 -> compila otimizado (-O2) sem debug
DEBUG ?= 1
ifeq ($(DEBUG),0)
  CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -O2 -I./src
endif

# Lista de todos os arquivos de código-fonte (.c) do projeto.
# Se você adicionar um novo arquivo .c ao projeto, adicione o caminho para ele nesta lista.
# Use uma barra invertida (\) no final da linha para continuar a lista na linha seguinte.
SRC := src/main.c \
       src/controller/main_controller.c \
       src/view/menu_view.c \
       src/util/input.c \
       src/util/patient_io.c \
       src/ds/patient_list.c \
       src/ds/patient_queue.c \
	   src/history_stack.c \
       src/model/patient.c


# BOA PRÁTICA: Gera uma lista de arquivos objeto (.o) a partir da lista de fontes (.c).
# Isso permite compilar apenas os arquivos que foram modificados, tornando o processo muito mais rápido.
OBJ := $(SRC:.c=.o)
       
# Define o nome do arquivo executável que será gerado.
BIN := clinic


# --- Regras de Execução ---

# # MUDANÇA: Declarar alvos "fakes" para evitar conflito com arquivos de mesmo nome.
.PHONY: all run clean veryclean debug release

# A regra 'all' é a regra padrão. Se você executar 'make' sem argumentos, esta regra será chamada.
# Ela depende da regra $(BIN), o que significa que o executável será construído.
all: $(BIN)

# Esta é a regra principal que compila o projeto.
# # MUDANÇA: Agora, ela junta (linka) os arquivos objeto (.o) pré-compilados para criar o executável.
# É mais eficiente do que recompilar todos os .c toda vez.
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

# # MUDANÇA: Esta nova regra ensina ao 'make' como transformar qualquer arquivo .c em um arquivo .o.
# O '-c' diz ao compilador para "compilar, mas não linkar ainda".
# # MUDANÇA: Geração de dependências automáticas (-MMD -MP) para recompilar ao alterar .h
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# # MUDANÇA: Inclusão dos arquivos de dependência (.d) gerados com -MMD
-include $(OBJ:.o=.d)

# A regra 'run' é um atalho para compilar (se necessário) e executar o programa.
# Primeiro ela garante que '$(BIN)' existe e está atualizado, depois o executa.
run: all
	./$(BIN)

# A regra 'clean' serve para limpar os arquivos gerados pela compilação.
# # MUDANÇA: Agora ela remove também os arquivos objeto (.o) para garantir uma limpeza completa.
# Útil para forçar uma recompilação total do zero.
clean:
	rm -f $(BIN) $(OBJ) $(OBJ:.o=.d)
# make clean no terminal

# # MUDANÇA: Limpeza "pesada" para cenários de troca de SO (Windows/Linux) ou artefatos perdidos.
# Remove .o/.d dentro de src/ e possíveis binários .exe.
# Executa o clean e faz uma varredura em src/ removendo qualquer *.o e *.d que tenham ficado 
# para trás (inclusive artefatos do outro SO) e apaga clinic.exe.
veryclean: clean
	find src -name '*.o' -o -name '*.d' -delete
	rm -f clinic.exe
# make veryclean (e opcional) && make no terminal

# # MUDANÇA: Atalhos para alternar perfis rapidamente
debug:
	@$(MAKE) --no-print-directory DEBUG=1 all

release:
	@$(MAKE) --no-print-directory DEBUG=0 all

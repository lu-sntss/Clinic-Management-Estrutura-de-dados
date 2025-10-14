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
# -I./src       : Informa ao compilador para procurar arquivos de cabeçalho (.h) também no diretório 'src'.
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -I./src

# Lista de todos os arquivos de código-fonte (.c) do projeto.
# Se você adicionar um novo arquivo .c ao projeto, adicione o caminho para ele nesta lista.
# Use uma barra invertida (\) no final da linha para continuar a lista na linha seguinte.
SRC := src/main.c \
       src/controller/main_controller.c \
       src/view/menu_view.c \
       src/util/input.c \
       src/util/patient_io.c \
       src/ds/patient_list.c\
       src/model/patient.c \
                                    
# Define o nome do arquivo executável que será gerado.
BIN := clinic


# --- Regras de Execução ---

# A regra 'all' é a regra padrão. Se você executar 'make' sem argumentos, esta regra será chamada.
# Ela depende da regra $(BIN), o que significa que o executável será construído.
all: $(BIN)

# Esta é a regra principal que compila o projeto.
# Ela diz que para criar o arquivo '$(BIN)' (o executável 'clinic'),
# é necessário ter todos os arquivos da lista '$(SRC)'.
# Se qualquer um dos arquivos .c for alterado, o comando abaixo será executado para recompilar.
$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

# A regra 'run' é um atalho para compilar (se necessário) e executar o programa.
# Primeiro ela garante que '$(BIN)' existe e está atualizado, depois o executa.
run: $(BIN)
	./$(BIN)

# A regra 'clean' serve para limpar os arquivos gerados pela compilação.
# Ela remove o arquivo executável. Útil para forçar uma recompilação completa do zero.
clean:
	rm -f $(BIN)
# make clean no terminal
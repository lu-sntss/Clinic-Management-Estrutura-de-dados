# Makefile
CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -I./src

SRC := src/main.c \
       src/controller/main_controller.c \
       src/view/menu_view.c \
       src/util/input.c \
       src/ds/patient_list.c   # <-- patient_list adicionado 

BIN := clinic

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)

# Clinic-Management-Estrutura-de-dados
Projeto final da disciplina Estrutura de dados da turma 2025.2  

Sobre o projeto:
    

    Estrutura de pastas.
        Estado Preliminar.
        Arquitetura de organização: MVC

        clinic_management/
        ├─ Makefile
        └─ src/
            ├─ main.c
            ├─ controller/
            │  └─ main_controller.c
            │     main_controller.h
            ├─ view/
            │  └─ menu_view.c
            │     menu_view.h
            ├─ util/
            │  └─ input.c
            │     input.h
            ├─ model/
            │  ├─ patient.h          // (tipos: paciente/prioridade) 
            │  └─ priority.h
            └─ ds/           // data structures (estruturas de dados).
                ├─ patient_list.h     
                ├─ patient_list.c     // lista encadeada de paciente 
                ├─ patient_queue.h   
                ├─ patient_queue.c    // fila de paciente 
                ├─ patient_stack.h    
                └─ patient_stack.c    // pilha de paciente, ainda discutindo necessidade


Executando o projeto:
    Como executar o Makefile

        O Makefile basicamente é o menu de instrução para o compilador montar o sistema da maneira correta

        Linux -
            # na raiz do projeto
            make        # compila
            make run    # executa o binário gerado
            Observação: o alvo run do Makefile deve rodar o executável gerado (ex.: ./clinic).
            make clean  # remove artefatos de compilação

        Windows -
            Usar MSYS2 (robusto)
                Baixe e instale: msys2
                Abra MSYS2 MinGW 64-bit (não o MSYS “puro”).
                Atualize e instale toolchain:
                    pacman -Syu
                    pacman -S --needed base-devel mingw-w64-x86_64-gcc make
                No terminal do projeto: vá até a pasta do projeto 
                    make ./clinic.exe
                Se o make não estiver disponível, tente mingw32-make.

        Sem makefile
            Windows PowerShell - // Vai ter q compilar arquivo por arquivo
                gcc -std=c11 -Wall -Wextra -Wpedantic -Isrc `
                src\main.c `
                src\controller\main_controller.c `
                src\view\menu_view.c `
                src\util\input.c `
                -o clinic.exe

                .\clinic.exe
            Linux - 
                gcc -std=c11 -Wall -Wextra -Wpedantic -Isrc \
                src/main.c \
                src/controller/main_controller.c \
                src/view/menu_view.c \
                src/util/input.c \
                -o clinic

                ./clinic

Convenções de código

    Identificadores em inglês; 
    comentários em português explicando o porquê.


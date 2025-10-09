#ifndef MENU_VIEW_H
#define MENU_VIEW_H

/*
===============================================================================
 Header: menu_view.h
 Papel:  Expor as DECLARAÇÕES (prototypes) das funções de exibição de menus.

 Por que um header?
   - Permite que outros módulos (.c) chamem show_* com checagem de tipos.
   - Mantém baixo acoplamento: a VIEW só imprime; não lê entrada nem decide fluxo.

 Notas:
   - As DEFINIÇÕES dessas funções estão em menu_view.c.
   - Este header NÃO deve ter estado global nem lógica — somente declarações.
   - É oq seria uma """"""""""Classe""""""""""""" puramente estatica com chamadas
=============================================================================== 
*/

/* Exibe os menus (somente impressão; sem ler entrada do usuário). */
void show_main_menu(void);
void show_patient_menu(void);
void show_queue_menu(void);
void show_history_menu(void);

#endif /* MENU_VIEW_H */

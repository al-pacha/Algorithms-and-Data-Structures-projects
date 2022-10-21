#ifndef __tab_int_h
#define __tab_int_h

#include <stdio.h>
#include <stdlib.h>

typedef struct _tab_int tab_int;
struct _tab_int
{
  int *V;
  int dim;
  int n;
};

/* Crea la tabella T di dim elementi */
void crea_tab_int (tab_int *pT, int dim);

/* Distrugge la tabella T */
void distrugge_tab_int (tab_int *pT);

/* Restituisce la cardinalita' corrente della tabella T */
int card_tab_int (tab_int *pT);

/* Inserisce in fondo alla tabella T l'elemento u */
void ins_tab_int (tab_int *pT, int u);

/*Restituisce il valore intero della tabella nell'indice indice*/
int RestituisceInteroTabInt (tab_int *pT, int indice);

/* Cancella dalla tabella T l'elemento di indice i */
void canc_tab_int (tab_int *pT, int i);

/* Stampa la tabella T */
void print_tab_int (tab_int *pT);

#endif

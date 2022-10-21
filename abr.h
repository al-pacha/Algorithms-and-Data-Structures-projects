#ifndef __abr_h
#define __abr_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tablivelli.h"

#define ROW_LENGTH 256

#define boolean int
#define TRUE  1
#define FALSE 0


#define NO_TREE   NULL
#define NO_NODE   NULL

typedef struct _nodo nodo;
struct _nodo
{
  /*argomento del nodo*/
  char val[ROW_LENGTH];
  tablivelli livelli;
  /*puntatori a nodi padre, figlio sinistro e figlio destro*/
  nodo *padre;
  nodo *Ts;
  nodo *Td;
};

typedef nodo *ABR;

/* Crea un albero binario vuoto */
ABR creaABR ();

/* Distrugge un albero */
void distruggeABR (ABR *pT);

/* Dato un ABR indica se è vuoto */
boolean ABRvuoto (ABR T);

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABR (char *elem, ABR T);

/*Inserisce livello nel nodo che ha per elemento quello indicato
  Serve anche sapere se dobbiamo aggiungere il livello di un impiegato
  o di un progetto.
  Restituisce FALSE se l'elemento indicato non è nell'albero*/
boolean inslivello(char *elem, ABR T, int n, boolean impiegato);

/*Restituisce l'ABR che ha come radice l'elemento inserito*/
ABR nodoABR(char *elem, ABR T);

ABR costruisceABR (char *elem, ABR Ts, ABR Td);

/* Dato un elemento e un ABR, inserisce l'elemento nell'ABR */
ABR insertABR (char *elem, ABR T);

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABR deleteABR (char *elem, ABR T);

char minABR (ABR T);

char maxABR (ABR T);

void stampaABR (ABR T);

void sstampaABR (ABR T, char *s);

void stampaABRInOrdine (ABR T);

int numeroNodi(ABR T);

/*Stampa i nodi dell'albero in ordine con anche i livelli nel formato
  livello i: on-dm
  dove n è il numero di impiegati con quel livello e m il numero di 
  progetti con quel livello*/
void stampaABRLivelli(ABR T);

#endif
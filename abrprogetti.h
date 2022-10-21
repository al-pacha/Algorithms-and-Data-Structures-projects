#ifndef __abrprogetti_h
#define __abrprogetti_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ROW_LENGTH 256

#define boolean int
#define TRUE  1
#define FALSE 0


#define NO_TREE   NULL
#define NO_NODE   NULL

typedef struct _nodoprogetto nodoprogetto;
struct _nodoprogetto
{
  /*argomento del nodo*/
  char val[ROW_LENGTH];
  int scadenza;
  int inizio;
  /*puntatori a nodi padre, figlio sinistro e figlio destro*/
  nodoprogetto *padre;
  nodoprogetto *Ts;
  nodoprogetto *Td;
};

typedef nodoprogetto *ABRprogetti;

/* Crea un albero binario vuoto */
ABRprogetti creaABRprogetti ();

/* Distrugge un albero */
void distruggeABRprogetti (ABRprogetti *pT);

/* Dato un ABR indica se è vuoto */
boolean ABRprogettivuoto (ABRprogetti T);

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABRprogetti (char *elem, ABRprogetti T);

/*Costruisce un ABR con nodo elem, figlio sinistro Ts, figlio sinistro Td*/
ABRprogetti costruisceABRprogetti (char *elem, ABRprogetti Ts, ABRprogetti Td, int s, int i);

/* Dato un elemento e un ABR, inserisce l'elemento nell'ABR */
ABRprogetti insertABRprogetti (char *elem, ABRprogetti T, int s, int i);

ABRprogetti toglienodoABRprogetti (nodoprogetto *n, ABRprogetti T);

nodoprogetto *argmaxABRprogetti (ABRprogetti T);

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABRprogetti deleteABRprogetti (char *elem, ABRprogetti T);

/*Conta quanti progetti sono attivi nel giorno i*/
int contaProgettiNelGiorno(ABRprogetti T, int i);

int contaProgettiNelGiornoBis(ABRprogetti T, int i, int counter);
/*Stampa i progetti che hanno inizio pari a i*/
void stampaProgettiInizio (ABRprogetti T, int i);

/*Stampa i progetti che hanno scadenza pari a i*/
void stampaProgettiScadenza (ABRprogetti T, int i);

int restituisceScadenza (ABRprogetti T, char *elem);

/*Restituisce il valore massimo della scadenza fra i nodi dell'ABR progetti T*/
/*TODO: trova un modo migliore, il fatto che in argomento si debba inserire un numero è problematico*/
// int scadenzaMassima (ABRprogetti T);

// char minABR (ABRprogetti T);

// char maxABR (ABRprogetti T);

// void stampaABR (ABRprogetti T);

// void sstampaABR (ABRprogetti T, char *s);

void stampaABRprogettiInOrdine (ABRprogetti T);

// int numeroNodi(ABRprogetti T);

#endif
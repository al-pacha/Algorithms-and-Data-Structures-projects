#ifndef __abrStr_h
#define __abrStr_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tabStr.h"

#define ROW_LENGTH 256
// typedef char Str[ROW_LENGTH];

#define boolean int
#define TRUE 1
#define FALSE 0

#define NO_TREE NULL
#define NO_NODE NULL

typedef struct _nodoStr nodoStr;
struct _nodoStr
{
    /*argomento del nodo*/
    char val[ROW_LENGTH];
    /*puntatori a nodi padre, figlio sinistro e figlio destro*/
    nodoStr *padre;
    nodoStr *Ts;
    nodoStr *Td;
};

typedef nodoStr *ABRStr;

/* Crea un albero binario vuoto */
ABRStr creaABRStr();

/* Distrugge un albero */
void distruggeABRStr(ABRStr *pT);

/* Dato un ABR indica se è vuoto */
boolean ABRStrvuoto(ABRStr T);

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABRStr(char *elem, ABRStr T);

/* Dato un elemento e un ABR, inserisce l'elemento nell'ABR */
ABRStr insertABRStr(char *elem, ABRStr T);

ABRStr toglienodoABRStr(nodoStr *n, ABRStr T);

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABRStr deleteABRStr(char *elem, ABRStr T);

/*Restituisce il numero di elementi contenuti nell'albero*/
int quantiElementi (ABRStr T);

/*Inserisce l'albero T in una tabella*/
void insABRStrInTabS (ABRStr T, tabS *Tab);

/*Restituisce il valore massimo della scadenza fra i nodi dell'ABR progetti T*/
/*TODO: trova un modo migliore, il fatto che in argomento si debba inserire un numero è problematico*/
// int scadenzaMassima (ABRprogetti T);

// char minABR (ABRprogetti T);

// char maxABR (ABRprogetti T);

void stampaABRStr(ABRStr T);

// void sstampaABR (ABRprogetti T, char *s);

// void stampaABRprogettiInOrdine (ABRStr T);

// int numeroNodi(ABRprogetti T);

#endif
#ifndef __abrStrInt_h
#define __abrStrInt_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tabint.h"

#define ROW_LENGTH 256
// typedef char Str[ROW_LENGTH];

#define boolean int
#define TRUE 1
#define FALSE 0

typedef int * vint;

#define NO_TREE NULL
#define NO_NODE NULL

typedef struct _nodoStrInt nodoStrInt;
struct _nodoStrInt
{
    /*argomento del nodo*/
    char Stringa[ROW_LENGTH];
    int  val;
    /*puntatori a nodi padre, figlio sinistro e figlio destro*/
    nodoStrInt *padre;
    nodoStrInt *Ts;
    nodoStrInt *Td;
};

typedef nodoStrInt *ABRStrInt;

/* Crea un albero binario vuoto */
ABRStrInt creaABRStrInt();

/* Distrugge un albero */
void distruggeABRStrInt(ABRStrInt *pT);

/* Dato un ABR indica se è vuoto */
// boolean ABRStrvuoto(ABRStrInt T);

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABRStrInt(char *elem, ABRStrInt T);

/* Dato un elemento e un ABR, inserisce l'elemento elem e val nell'ABR */
ABRStrInt insertABRStrInt(char *elem, int val, ABRStrInt T);

ABRStrInt toglienodoABRStrInt(nodoStrInt *n, ABRStrInt T);

/*Inserisce i valori numerici dell'albero in una tabella ordinata*/
void insABRStrIntInTabInt (ABRStrInt T, tab_int *Tab);

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
// ABRStrInt deleteABRStrInt(char *elem, ABRStrInt T);

/*Restituisce il numero di elementi contenuti nell'albero*/
// int quantiElementi (ABRStrInt T);

/*Restituisce il valore massimo della scadenza fra i nodi dell'ABR progetti T*/
/*TODO: trova un modo migliore, il fatto che in argomento si debba inserire un numero è problematico*/
// int scadenzaMassima (ABRprogetti T);

// char minABR (ABRprogetti T);

// char maxABR (ABRprogetti T);

void stampaABRStrInt(ABRStrInt T);

// void sstampaABR (ABRprogetti T, char *s);

// void stampaABRprogettiInOrdine (ABRStrInt T);

// int numeroNodi(ABRprogetti T);

#endif
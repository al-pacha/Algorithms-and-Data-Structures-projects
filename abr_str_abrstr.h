#ifndef __abr_str_abrstr_h
#define __abr_str_abrstr_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "abrStr.h"
#include "tabStr.h"
#include "tabint.h"

#define ROW_LENGTH 256
// typedef char Str[ROW_LENGTH];

#define boolean int
#define TRUE 1
#define FALSE 0

#define NO_TREE NULL
#define NO_NODE NULL

typedef struct _nodoStrNodoStr nodoStrNodoStr;
struct _nodoStrNodoStr
{
    /*argomento del nodo*/
    char        val[ROW_LENGTH];
    /*Elenco ordinato*/
    ABRStr      ElencoOrd; 

    /*puntatori a nodi padre, figlio sinistro e figlio destro*/
    nodoStrNodoStr *padre;
    nodoStrNodoStr *Ts;
    nodoStrNodoStr *Td;
};

typedef nodoStrNodoStr *ABRStrABRStr;

/* Crea un albero binario vuoto */
ABRStrABRStr creaABR_str_ABRStr();

/* Distrugge un albero */
void distruggeABR_str_ABRStr(ABRStrABRStr *pT);

/* Dato un ABR indica se è vuoto */
boolean ABR_str_ABRStr_vuoto(ABRStrABRStr T);

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABR_str_ABRStr(char *elem, ABRStrABRStr T, ABRStr TStr);

/* Dato un elemento e un ABR, inserisce l'elemento nell'ABR */
ABRStrABRStr insertABR_str_ABRStr(char *elem, ABRStrABRStr T);

/*Inserisce una Stringa nell'Elenco Ordinato*/
boolean insInElenco(char *elem, ABRStrABRStr T, char *Str);

ABRStrABRStr toglienodoABR_str_ABRStr(nodoStrNodoStr *n, ABRStrABRStr T);

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABRStrABRStr deleteABR_str_ABRStr(char *elem, ABRStrABRStr T);

/*Restituisce il numero di elementi contenuti nell'albero*/
int numeroElementi (ABRStrABRStr T);

void inserisceInTabS ( ABRStrABRStr T, tabS *Tab);

void inserisceElencoInTabS (ABRStrABRStr T, char *val, tabS *Tab);

void StampaABR_str_ABRStr (ABRStrABRStr T);

/*Restituisce TRUE se Cerca appartiene all'elenco di val */
boolean appartieneAdElenco (ABRStrABRStr T, char *val, char *Cerca);

/*Inserisce le altezze dell'albero in una tabella di interi*/
void insInTabIntAltezzeABR (ABRStrABRStr T, tab_int *Tab);

/*Restituisce il valore massimo della scadenza fra i nodi dell'ABR progetti T*/
/*TODO: trova un modo migliore, il fatto che in argomento si debba inserire un numero è problematico*/
// int scadenzaMassima (ABRprogetti T);

// char minABR (ABRprogetti T);

// char maxABR (ABRprogetti T);

// void stampaABRStr (ABRStrABRStr T);

// void sstampaABR (ABRprogetti T, char *s);

// void stampaABRprogettiInOrdine (ABRStr T);

// int numeroNodi(ABRprogetti T);

#endif
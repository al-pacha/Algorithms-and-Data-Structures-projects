/*Tabella che in argomento ha due stringhe e un intero*/
#ifndef __tabStrStrInt_h
#define __tabStrStrInt_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERO_LIVELLI 50
#define ROW_LENGTH 256

typedef char Str[ROW_LENGTH];

#define boolean int
#define TRUE  1
#define FALSE 0

typedef struct colonnetab colonnetab;
struct colonnetab
{
    /*Colonne della tabella*/
    Str     *StrUno;
    Str     *StrDue;
    int     *val;
};


typedef struct tabSSI tabSSI;
struct tabSSI
{
    colonnetab C;

    /*Contatori di dimensione della tabella*/
    int     n;

    /*dimensione della tabella*/
    int     dim;
};

/* Crea la tabella T di dim elementi */
tabSSI creatabSSI(int dim);

/* Distrugge la tabella T */
void distruggetabSSI(tabSSI *pT);

/* Restituisce la cardinalita' corrente della tabella T */
// int cardtabint(tabSSI *pT);

/*Inserisce in fondo alla tabella l'elemento dato da 
    -StrUno
    -StrDue
    -n */
void instabSSI(tabSSI *pT, Str StrUno, Str StrDue, int val);

/*Restituisce la cardinalità della tabSSI T*/
int cardtabSSI (tabSSI *pT);

/*Restituisce la StrUno nella posizione indice*/
void restituisceStrUno(tabSSI *pT, int indice, char *risultato);

/*Restituisce la StrDue nella posizione indice*/
void restituisceStrDue(tabSSI *pT, int indice, char *risultato);

/*Restituisce val nella posizione indice*/
int restituisceVal(tabSSI *pT, int indice);

/* Cancella dalla tabella T l'elemento di indice i */
// void canctabint(tabSSI *pT, int i);

/* Cancella dalla tabella T l'ultimo elemento */
void canctabint(tabSSI *pT);

/* Stampa la tabella T */
void stampatabSSI(tabSSI *pT);



#endif

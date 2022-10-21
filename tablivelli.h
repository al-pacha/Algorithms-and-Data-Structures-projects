#ifndef __tablivelli_h
#define __tablivelli_h

#include <stdio.h>
#include <stdlib.h>

#define NUMERO_LIVELLI 50

#define boolean int
#define TRUE  1
#define FALSE 0

typedef struct tablivelli tablivelli;
struct tablivelli
{
    /*Livelli impiegati*/
    int *LI;
    /*numero livelli impiegati*/
    int nLI;
    /*Livelli progetti*/
    int *LP;
    /*numero livelli progetti*/
    int nLP;

    int dim;
};

/* Crea la tabella T di dim elementi */
void creatablivelli(tablivelli *pT, int dim);

/* Distrugge la tabella T */
void distruggetablivelli(tablivelli *pT);

/* Restituisce la cardinalita' corrente della tabella T */
// int cardtabint(tablivelli *pT);

/* Inserisce in fondo alla tabella T l'elemento u */
// void instabint(tablivelli *pT, int u);

/*Aumenta di una unità tutti i livelli precenti al livello l inserito*/
void instabpos(tablivelli *pT, int l, boolean impiegato);

/* Cancella dalla tabella T l'elemento di indice i */
// void canctabint(tablivelli *pT, int i);

/* Stampa la tabella T */
// void stampatabint(tablivelli *pT);

/*Stampa i livelli e i valori di ogni livello*/
void stampatablivelli2(tablivelli *pT);

/*Calcola il massimo fra a e b*/
int massimo(int a, int b);

#endif

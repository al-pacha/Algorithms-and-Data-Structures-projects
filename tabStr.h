/*Tabella che in argomento ha due stringhe e un intero*/
#ifndef __tabStr_h
#define __tabStr_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERO_LIVELLI 50
#define ROW_LENGTH 256

typedef char Str[ROW_LENGTH];

#define boolean int
#define TRUE  1
#define FALSE 0


typedef struct tabS tabS;
struct tabS
{
    /*Colonne tabella*/
    Str     *Stringa;

    /*Contatori di dimensione della tabella*/
    int     n;

    /*dimensione della tabella*/
    int     dim;
};

/* Crea la tabella T di dim elementi */
tabS creatabS(int dim);

/* Distrugge la tabella T */
void distruggetabS(tabS *pT);

/* Restituisce la cardinalita' corrente della tabella T */
// int cardtabint(tabS *pT);

/*Inserisce in fondo alla tabella una Stringa*/
void instabS(tabS *pT, Str S);

/*Restituisce la cardinalità della tabS T*/
int cardtabS (tabS *pT);

/*Restituisce la Stringa nella posizione indice*/
void restituisceStringa(tabS *pT, int indice, char *risultato);

/* Cancella dalla tabella T l'elemento di indice i */
// void canctabint(tabS *pT, int i);

/*Restituisce la posizione dell'elemento elem nella tabella pT*/
int posizioneElem (tabS *pT, char *elem);

/* Stampa la tabella T */
void stampatabS(tabS *pT);



#endif

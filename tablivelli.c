#include "tablivelli.h"
#include <stdio.h>

/* Crea la tabella T di dim elementi */
void creatablivelli(tablivelli *pT, int dim)
{
    pT->LI = (int *)calloc(dim + 1, sizeof(int));
    if (pT->LI == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione della tabella!\n");
        exit(EXIT_FAILURE);
    }

    pT->nLI = 0;

    pT->LP = (int *)calloc(dim + 1, sizeof(int));
    if (pT->LP == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione della tabella!\n");
        exit(EXIT_FAILURE);
    }

    pT->nLP = 0;

    pT->dim = dim;
}

/* Distrugge la tabella T */
void distruggetablivelli(tablivelli *pT)
{
    /*libero la memoria occupata dagli impiegati*/
    free(pT->LI);
    pT->LI = NULL;   
    /*libero la memoria occupata dai progetti*/
    free(pT->LP);
    pT->LP = NULL;

    pT->dim = 0;
    pT->nLI = 0;
    pT->nLP = 0;
}

/* Restituisce la cardinalita' corrente della tabella T */
// int cardtabint(tablivelli *pT)
// {
//     return pT->nLI;
// }

/* Inserisce in fondo alla tabella T l'elemento u */
// void instabint(tablivelli *pT, int u)
// {
//     if (pT->nLI >= pT->dim)
//     {
//         fprintf(stderr, "Tabella piena (%d elementi)!\n", pT->dim);
//         exit(EXIT_FAILURE);
//     }

//     pT->nLI++;
//     pT->LI[pT->nLI] = u;
// }

/*Aumenta di una unità tutti i livelli precenti al livello l inserito*/
void instabpos(tablivelli *pT, int l, boolean impiegato)
{
    /*Parte dichiarativa*/
    int i;

    /*Controllo d'errore sul livello inserito*/
    if ((l <= 0))
    {
        fprintf(stderr, "L'indice %d e' esterno alla tabella!\n", l);
        exit(EXIT_FAILURE);
    }
    
    if (l >= pT->dim)
    {
        pT->LI = (int *)realloc(pT->LI, sizeof(int)*(pT->nLI+2));
        if (pT->LI == NULL)
        {
            fprintf(stderr, "Errore nell'allocazione della tabella!\n");
            exit(EXIT_FAILURE);
        }
    }

    if (l >= pT->dim)
    {
        pT->LP = (int *)realloc(pT->LP, sizeof(int)*(pT->nLP+2));
        if (pT->LP == NULL)
        {
            fprintf(stderr, "Errore nell'allocazione della tabella!\n");
            exit(EXIT_FAILURE);
        }  
    }
    pT->dim++;
    
    /*Parte esecutiva*/

    /*Se impiegato è VERO (1)*/
    if (impiegato == TRUE){
        for (i = 1; i < l + 1; i++)
        {
            if (pT->LI[i] == 0)
                (pT->nLI)++;
            (pT->LI[i])++;
        }
    }
    else{
        for (i = 1; i < l + 1; i++)
        {
            if (pT->LP[i] == 0)
                (pT->nLP)++;
            (pT->LP[i])++;
        }
    }
}

/* Cancella dalla tabella T l'elemento di indice i */
// void canctabint(tablivelli *pT, int i)
// {
//     if ((i <= 0) || (i > pT->nLI))
//     {
//         fprintf(stderr, "L'indice %d e' esterno alla tabella!\n", i);
//         exit(EXIT_FAILURE);
//     }
//     pT->LI[i] = pT->LI[pT->nLI];
//     (pT->nLI)--;
// }

/* Stampa la tabella T */
// void stampatabint(tablivelli *pT)
// {
//     int i;

//     for (i = 1; i <= pT->nLI; i++)
//         printf("%d ", pT->LI[i]);
//     printf("\n");
// }

/*Stampa i livelli e i valori di ogni livello*/
void stampatablivelli2 (tablivelli *pT)
{
    int i;

    for (i = 1; i <= massimo(pT->nLI,pT->nLP); i++){
        printf("livello %d:\to%d-d%d\n", i, pT->LI[i], pT->LP[i]);
    }
    // printf("\n");
}

/*Calcola il massimo fra a e b*/
int massimo(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
    
}
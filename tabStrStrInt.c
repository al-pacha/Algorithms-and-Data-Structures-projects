#include "tabStrStrInt.h"

/* Crea la tabella T di dim elementi */
tabSSI creatabSSI(int dim)
{
    tabSSI T;

    /*Alloco la memoria necessaria a contenere dim+1 colonne*/
    T.C.StrUno = (Str *)calloc(dim + 1, sizeof(Str));
    if (T.C.StrUno == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione della tabella!\n");
        exit(EXIT_FAILURE);
    }
    

    T.C.StrDue = (Str *)calloc(dim + 1, sizeof(Str));
    if (T.C.StrDue == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione della tabella!\n");
        exit(EXIT_FAILURE);
    }

    T.C.val = (int *)calloc(dim + 1, sizeof(int));
    if (T.C.val == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione della tabella!\n");
        exit(EXIT_FAILURE);
    }

    /*Imposto la dimensione effettiva (n) a zero e 
        e la dimensione massima al valore inserito in ingresso (dim)*/

    T.n = 0;

    T.dim = dim;

    return T;
}

/* Distrugge la tabella T */
void distruggetabSSI(tabSSI *pT)
{
    /*libero la memoria occupata dalle colonne*/
    free(pT->C.StrUno);
    pT->C.StrUno = NULL;   
    
    free(pT->C.StrDue);
    pT->C.StrDue = NULL;   

    free(pT->C.val);
    pT->C.val = NULL;



    /*Imposto la dimensione della tabella a zero*/
    pT->n = 0;
    pT->dim = 0;
}

/* Restituisce la cardinalita' corrente della tabella T */
// int cardtabint(tabSSI *pT)
// {
//     return pT->nLI;
// }

/*Inserisce in fondo alla tabella l'elemento dato da 
    -StrUno
    -StrDue
    -n */
void instabSSI(tabSSI *pT, Str StrUno, Str StrDue, int val)
{

    /*se la tabella è piena aggiungo una riga*/
    if (pT->n >= pT->dim)
    {
        
        /*Rialloco la memoria della tabella in modo da aggiungere una riga*/

        pT->C.StrUno = (Str *)realloc(pT->C.StrUno, sizeof(Str)*(pT->n+2));
        if (pT->C.StrUno == NULL)
        {
            fprintf(stderr, "Errore nell'allocazione della tabella!\n");
            exit(EXIT_FAILURE);
        }

        pT->C.StrDue = (Str *)realloc(pT->C.StrDue, sizeof(Str)*(pT->n+2));
        if (pT->C.StrDue == NULL)
        {
            fprintf(stderr, "Errore nell'allocazione della tabella!\n");
            exit(EXIT_FAILURE);
        }

        pT->C.val = (int *)realloc(pT->C.val, sizeof(Str)*(pT->n+2));
        if (pT->C.val == NULL)
        {
            fprintf(stderr, "Errore nell'allocazione della tabella!\n");
            exit(EXIT_FAILURE);
        }
        pT->dim++;
    }


    pT->n++;
    strcpy (pT->C.StrUno[pT->n], StrUno);
    strcpy (pT->C.StrDue[pT->n], StrDue);
    pT->C.val[pT->n] = val;

}


/* Cancella dalla tabella T l'elemento di indice i */
// void canctabint(tabSSI *pT, int i)
// {
//     if ((i <= 0) || (i > pT->nLI))
//     {
//         fprintf(stderr, "L'indice %d e' esterno alla tabella!\n", i);
//         exit(EXIT_FAILURE);
//     }
//     pT->LI[i] = pT->LI[pT->nLI];
//     (pT->nLI)--;
// }

/* Cancella dalla tabella T l'ultimo elemento */
void canctabint(tabSSI *pT)
{

    // free(pT->C.StrUno[pT->n]);
    // free(pT->C.StrDue[pT->n]);
    // pT->C.val = 0;
    (pT->n)--;

}

/*Restituisce la cardinalità della tabSSI T*/
int cardtabSSI (tabSSI *pT)
{
    return pT->n;
}

/*Restituisce la StrUno nella posizione indice*/
void restituisceStrUno(tabSSI *pT, int indice, char *risultato)
{
    strcpy(risultato, pT->C.StrUno[indice]);
}

/*Restituisce la StrDue nella posizione indice*/
void restituisceStrDue(tabSSI *pT, int indice, char *risultato)
{
    strcpy(risultato, pT->C.StrDue[indice]);
}

/*Restituisce val nella posizione indice*/
int restituisceVal(tabSSI *pT, int indice)
{
    return pT->C.val[indice];
}

/* Stampa la tabella T */
void stampatabSSI(tabSSI *pT)
{
    int i;

    for (i = 1; i <= pT->n; i++)
        printf("%s %s %d\n", pT->C.StrUno[i], pT->C.StrDue[i], pT->C.val[i]);
    printf("\n");
}



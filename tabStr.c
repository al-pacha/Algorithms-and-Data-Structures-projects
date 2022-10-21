#include "tabStr.h"

/* Crea la tabella T di dim elementi */
tabS creatabS(int dim)
{
    tabS T;

    /*Alloco la memoria necessaria a contenere dim+1 colonne*/
    T.Stringa = (Str *)calloc(dim + 1, sizeof(Str));
    if (T.Stringa == NULL)
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
void distruggetabS(tabS *pT)
{
    /*libero la memoria occupata dalle colonne*/
    free(pT->Stringa);
    pT->Stringa = NULL;   

    /*Imposto la dimensione della tabella a zero*/
    pT->n = 0;
    pT->dim = 0;
}

/* Restituisce la cardinalita' corrente della tabella T */
// int cardtabint(tabS *pT)
// {
//     return pT->nLI;
// }

/*Inserisce in fondo alla tabella la Stringa S*/
void instabS(tabS *pT, Str S)
{

    /*se la tabella è piena aggiungo una riga*/
    if (pT->n >= pT->dim)
    {
        
        /*Rialloco la memoria della tabella in modo da aggiungere una riga*/

        pT->Stringa = (Str *)realloc(pT->Stringa, sizeof(Str)*(pT->n+2));
        if (pT->Stringa == NULL)
        {
            fprintf(stderr, "Errore nell'allocazione della tabella!\n");
            exit(EXIT_FAILURE);
        }

        pT->dim++;
    }


    pT->n++;
    strcpy (pT->Stringa[pT->n], S);

}


/* Cancella dalla tabella T l'elemento di indice i */
// void canctabint(tabS *pT, int i)
// {
//     if ((i <= 0) || (i > pT->nLI))
//     {
//         fprintf(stderr, "L'indice %d e' esterno alla tabella!\n", i);
//         exit(EXIT_FAILURE);
//     }
//     pT->LI[i] = pT->LI[pT->nLI];
//     (pT->nLI)--;
// }

/*Restituisce la cardinalità della tabS T*/
int cardtabS (tabS *pT)
{
    return pT->n;
}

/*Restituisce la StrUno nella posizione indice*/
void restituisceStringa(tabS *pT, int indice, char *risultato)
{
    strcpy(risultato, pT->Stringa[indice]);
}

/*Restituisce la posizione dell'elemento elem nella tabella pT*/
int posizioneElem (tabS *pT, char *elem)
{
    int i;

    for (i = 1; strcmp(pT->Stringa[i], elem) != FALSE; i++);

    return i;
}

/* Stampa la tabella T */
void stampatabS(tabS *pT)
{
    int i;

   for (i = 1; i <= pT->n; i++)
        printf("%s\n", pT->Stringa[i]);
    printf("\n");
}



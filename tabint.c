#include "tabint.h"

/* Crea la tabella T di dim elementi */
void crea_tab_int (tab_int *pT, int dim)
{
  pT->V = (int *) calloc(dim+1,sizeof(int));
  if (pT->V == NULL)
  {
    fprintf(stderr,"Errore nell'allocazione della tabella!\n");
    exit(EXIT_FAILURE);
  }

  pT->dim = dim;
  pT->n = 0;
}

/* Distrugge la tabella T */
void distrugge_tab_int (tab_int *pT)
{
  free(pT->V);
  pT->V = NULL;
  pT->dim = 0;
  pT->n = 0;
}

/* Restituisce la cardinalita' corrente della tabella T */
int card_tab_int (tab_int *pT)
{
  return pT->n;
}

/* Inserisce in fondo alla tabella T l'elemento u */
void ins_tab_int (tab_int *pT, int u)
{
  /*Rialloco la memoria della tabella in modo da aggiungere una riga*/
    if (pT->n >= pT->dim)
    {
        pT->V = (int *)realloc(pT->V, sizeof(int)*(pT->n+2));
        if (pT->V == NULL)
        {
            fprintf(stderr, "Errore nell'allocazione della tabella!\n");
            exit(EXIT_FAILURE);
        }

        pT->dim++;
    }

  pT->n++;
  pT->V[pT->n] = u;
}

/*Restituisce il valore intero della tabella nell'indice indice*/
int RestituisceInteroTabInt (tab_int *pT, int indice)
{
    if(indice <=0 || indice > pT->n)
    {
        fprintf(stderr, "Indice fuori dalla tabella!\n");
        exit(EXIT_FAILURE);
    }
    return pT->V[indice];
}

/* Cancella dalla tabella T l'elemento di indice i */
void canc_tab_int (tab_int *pT, int i)
{
  if ( (i <= 0) || (i > pT->n) ) exit(EXIT_FAILURE);
  pT->V[i] = pT->V[pT->n];
  (pT->n)--;
}

/* Stampa la tabella T */
void print_tab_int (tab_int *pT)
{
  int i;

  for (i = 1; i <= pT->n; i++)
    printf("%d ",pT->V[i]);
  printf("\n");
}

#include <limits.h>
#include "abrprogetti.h"

/* Crea un albero binario vuoto */
ABRprogetti creaABRprogetti()
{
    // ABR T;

    // T = (ABR) malloc(sizeof(nodo));
    // if (T == NO_TREE)
    // {
    //   fprintf(stderr,"Errore nell'allocazione di una lista!\n");
    //   exit(EXIT_FAILURE);
    // }

    // T->val = NULL;
    // T->padre = NO_NODE;
    // T->Ts = NO_NODE;
    // T->Td = NO_NODE;

    // return T;
    return NO_TREE;
}

/* Distrugge un albero */
void distruggeABRprogetti(ABRprogetti *pT)
{
    if (*pT != NO_TREE)
    {
        distruggeABRprogetti(&(*pT)->Ts);
        distruggeABRprogetti(&(*pT)->Td);
        free(*pT);
        *pT = NO_TREE;
    }
}

/* Dato un ABR, indica se è vuoto */
boolean ABRprogettivuoto(ABRprogetti T)
{
    return (T == NO_TREE);
}

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABRprogetti(char *elem, ABRprogetti T)
{
#ifdef RICORSIVA
    /* Implementazione ricorsiva */
    if (T == NO_TREE)
        return FALSE;
    else if (strcmp(elem, T->val) == 0)
        return TRUE;
    else if (strcmp(elem, T->val) < 0)
        return memberABRprogetti(elem, T->Ts);
    else /* if ( i > T->val) */
        return memberABRprogetti(elem, T->Td);
#else
    /* Implementazione iterativa */
    while ((T != NO_TREE) && (strcmp(elem, T->val) != 0))
    {
        if (strcmp(elem, T->val) < 0)
            T = T->Ts;
        else /* if ( i > T->val) */
            T = T->Td;
    }

    return (T != NO_TREE);

#endif
}

ABRprogetti costruisceABRprogetti(char *elem, ABRprogetti Ts, ABRprogetti Td, int s, int i)
{
    ABRprogetti T;

    /* Alloca l'elemento radice */
    T = (ABRprogetti)malloc(sizeof(nodoprogetto));
    if (T == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione di un ABR!\n");
        exit(EXIT_FAILURE);
    }

    // printf("ok\n");
    strcpy(T->val, elem);
    T->scadenza = s;
    T->inizio = i;
    T->padre = NULL;
    T->Ts = Ts;
    if (Ts != NULL) 
        Ts->padre = T;
    T->Td = Td;
    if (Td != NULL)
        Td->padre = T;

    return T;
}

/* Dato un elemento e un ABR, inserisce l'elemento elem nell'ABR T*/
ABRprogetti insertABRprogetti(char *elem, ABRprogetti T, int s, int i)
{
    if (T == NO_TREE)
        T = costruisceABRprogetti(elem, NO_TREE, NO_TREE, s, i);
    else if (strcmp(elem, T->val) < 0)
    {
        T->Ts = insertABRprogetti(elem, T->Ts, s, i);
        T->Ts->padre = T;
    }
    else if (strcmp(elem, T->val) > 0)
    {
        T->Td = insertABRprogetti(elem, T->Td, s, i);
        T->Td->padre = T;
    }

    return T;
}

/* Appende direttamente l'unico sottoalbero al nodo padre della radice e dealloca la radice stessa */
ABRprogetti toglienodoABRprogetti(nodoprogetto *n, ABRprogetti T)
{
    ABRprogetti Tf;
    /* Determina l'unico sottoalbero non vuoto del nodo n (eventualmente NO_TREE) */
    Tf = n->Ts;
    if (Tf == NO_TREE)
        Tf = n->Td;

    /* Se esiste un sottoalbero, lo appende al nodo padre (se questo esiste) */
    if (Tf != NO_TREE)
        Tf->padre = n->padre;

    /* Se n è la radice, cambia l'albero T (punta il sottoalbero) */
    if (n == T)
        T = Tf;
    /* Sostituire il sottoalbero all'albero corrente nelle informazioni del nodo padre */
    else if (n == n->padre->Ts)
        n->padre->Ts = Tf;
    else
        n->padre->Td = Tf;

    /* Dealloca il nodo n */
    free(n);

    return T;
}

/* Determina il nodo che corrisponde al valore massimo nell'albero T */
nodoprogetto *argmaxABRprogetti(ABRprogetti T)
{
    if (T == NO_TREE)
        return NULL;
    while (T->Td != NO_TREE)
        T = T->Td;

    return T;
}

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABRprogetti deleteABRprogetti(char *elem, ABRprogetti T)
{
    nodoprogetto *n;

    /* Se l'albero T è vuoto, non si fa nulla */
    if (T != NO_TREE)
    {
        /* Se i precede la radice dell'albero T */
        if (strcmp(elem, T->val) < 0)
            T->Ts = deleteABRprogetti(elem, T->Ts);
        /* Se i segue la radice dell'albero T */
        else if (strcmp(elem, T->val) > 0)
            T->Td = deleteABRprogetti(elem, T->Td);
        /* Se i è la radice dell'albero T e ha un solo figlio */
        else if ((T->Ts == NO_TREE) || (T->Td == NO_TREE))
        {
            /* Appende direttamente l'unico sottoalbero al nodo padre della radice
               e dealloca la radice */
            T = toglienodoABRprogetti(T, T);
        }
        /* Se i è la radice dell'albero T e ha due figli */
        else
        {
            n = argmaxABRprogetti(T->Ts);
            strcpy(T->val, n->val);
            T = toglienodoABRprogetti(n, T);
        }
    }

    return T;
}

/*Conta quanti progetti sono attivi nel giorno i*/
int contaProgettiNelGiorno(ABRprogetti T, int i)
{
    int counter = 0;
    return contaProgettiNelGiornoBis(T, i, counter);
}

/*Conta quanti progetti sono attivi nel giorno i
    ATTENZIONE: è una funzione privata per la libreria
    può essere utilizzata solo all'interno della funzione ContaProgettiNelGiorno
    La funzione contaProgettiNelGiorno è stata creata solo per evitare che 
    l'utente possa utilizzare questa funzione inserendo un valore di counter diverso da zero
    il che avrebbe fornito risultati assurdi*/
int contaProgettiNelGiornoBis(ABRprogetti T, int i, int counter)
{

    if(T != NO_TREE){
        if((i >= T->inizio) && (i <= T->scadenza)){
            counter++;
        }
        counter = contaProgettiNelGiornoBis(T->Ts, i, counter);
        counter = contaProgettiNelGiornoBis(T->Td, i, counter);
        return counter;
    }
    return counter;
}

void stampaProgettiInizio (ABRprogetti T, int i)
{
    if(T != NO_TREE){
        if(T->scadenza == i)
            printf("%s>", T->val);
            
        stampaProgettiInizio(T->Ts, i);
        stampaProgettiInizio(T->Td, i);
    }
}

void stampaProgettiScadenza (ABRprogetti T, int i)
{
    if(T != NO_TREE){
        if(T->inizio == i)
            printf("<%s", T->val);
            
        stampaProgettiScadenza(T->Ts, i);
        stampaProgettiScadenza(T->Td, i);
    }
}

/*Restituisce il valore massimo della scadenza fra i nodi dell'ABR progetti T*/
/*TODO: trova un modo migliore, il fatto che in argomento si debba inserire un numero è problematico*/
// int scadenzaMassima (ABRprogetti T, int smax)
// {   

//     printf("scandenza: %d\n", T->scadenza);

//     if(T != NULL){
//         if(smax < T->scadenza)
//             smax = T->scadenza;

//         smax = scadenzaMassima(T->Ts, smax);
//         smax = scadenzaMassima(T->Td, smax);
//     }

//     printf("scadenza massima interna: %d\n", smax);
//     return smax;
// }



/* Dato un ABR, ne restituisce l'elemento minimo. Se l'ABR è vuoto, restituisce un valore fittizio +inf */
// char minABR (ABRprogetti T)
// {
//   return 'a';
// }

// /* Dato un ABR, ne restituisce l'elemento massimo. Se l'ABR è vuoto, restituisce un valore fittizio -inf */
// char maxABR (ABRprogetti T)
// {
//   return 'a';
// }

// /* Stampa in ordine crescente */
// void stampaABR (ABRprogetti T)
// {
//   if (T != NO_TREE)
//   {
//     stampaABR(T->Ts);
//     printf("%s ", T->val);
//     stampaABR(T->Td);
//   }
// }

// void sstampaABR (ABRprogetti T, char *s)
// {
//   if (T != NO_TREE)
//   {
//     sstampaABR(T->Ts, s);
//     s = strcat(s, T->val);
//     s = strcat(s, " ");
//     sstampaABR(T->Td, s);
//   }
// }

int restituisceScadenza (ABRprogetti T, char *elem)
{
    while ((T != NO_TREE) && (strcmp(elem, T->val) != 0))
    {
        if (strcmp(elem, T->val) < 0)
            T = T->Ts;
        else /* if ( i > T->val) */
            T = T->Td;
    }
    return T->scadenza;
}

/*Stampa un a capo dopo ogni singola parola dell'albero*/
void stampaABRprogettiInOrdine (ABRprogetti T)
{
  if (T != NO_TREE)
  {
    stampaABRprogettiInOrdine(T->Ts);
    printf("valore:%s inizio: %d scadenza: %d \n", T->val, T->inizio, T->scadenza);
    stampaABRprogettiInOrdine(T->Td);
  }
}

// /*Conta il numero di nodi di un ABR*/
// int numeroNodi(ABRprogetti T)
// {
//   if (T != NO_TREE)
//     return (numeroNodi (T->Ts) + numeroNodi (T->Td) + 1); // Conto +1 per il nodo radice
//   else
//     return 0;
// }

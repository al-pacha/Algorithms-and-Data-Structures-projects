#include <limits.h>
#include "abrStr.h"


/* Crea un albero binario vuoto */
ABRStr creaABRStr()
{
    return NO_TREE;
}

/* Distrugge un albero */
void distruggeABRStr(ABRStr *pT)
{
    if (*pT != NO_TREE)
    {
        distruggeABRStr(&(*pT)->Ts);
        distruggeABRStr(&(*pT)->Td);
        free(*pT);
        *pT = NO_TREE;
    }
}

/* Dato un ABR, indica se è vuoto */
boolean ABRStrvuoto(ABRStr T)
{
    return (T == NO_TREE);
}

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABRStr(char *elem, ABRStr T)
{
#ifdef RICORSIVA
    /* Implementazione ricorsiva */
    if (T == NO_TREE)
        return FALSE;
    else if (strcmp(elem, T->val) == 0)
        return TRUE;
    else if (strcmp(elem, T->val) < 0)
        return memberABRStr(elem, T->Ts);
    else /* if ( i > T->val) */
        return memberABRStr(elem, T->Td);
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

/*Costruisce un ABR con nodo elem, figlio sinistro Ts, figlio sinistro Td*/
ABRStr costruisceABRStr(char *elem, ABRStr Ts, ABRStr Td)
{
    ABRStr T;

    /* Alloca l'elemento radice */
    T = (ABRStr)malloc(sizeof(nodoStr));
    if (T == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione di un ABR!\n");
        exit(EXIT_FAILURE);
    }

    // printf("ok\n");
    strcpy(T->val, elem);
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
ABRStr insertABRStr(char *elem, ABRStr T)
{
    if (T == NO_TREE)
        T = costruisceABRStr(elem, NO_TREE, NO_TREE);
    else if (strcmp(elem, T->val) < 0)
    {
        T->Ts = insertABRStr(elem, T->Ts);
        T->Ts->padre = T;
    }
    else if (strcmp(elem, T->val) > 0)
    {
        T->Td = insertABRStr(elem, T->Td);
        T->Td->padre = T;
    }

    return T;
}

/* Appende direttamente l'unico sottoalbero al nodo padre della radice e dealloca la radice stessa */
ABRStr toglienodoABRStr(nodoStr *n, ABRStr T)
{
    ABRStr Tf;
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
nodoStr *argmaxABRStr(ABRStr T)
{
    if (T == NO_TREE)
        return NULL;
    while (T->Td != NO_TREE)
        T = T->Td;

    return T;
}

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABRStr deleteABRStr(char *elem, ABRStr T)
{
    nodoStr *n;

    /* Se l'albero T è vuoto, non si fa nulla */
    if (T != NO_TREE)
    {
        /* Se i precede la radice dell'albero T */
        if (strcmp(elem, T->val) < 0)
            T->Ts = deleteABRStr(elem, T->Ts);
        /* Se i segue la radice dell'albero T */
        else if (strcmp(elem, T->val) > 0)
            T->Td = deleteABRStr(elem, T->Td);
        /* Se i è la radice dell'albero T e ha un solo figlio */
        else if ((T->Ts == NO_TREE) || (T->Td == NO_TREE))
        {
            /* Appende direttamente l'unico sottoalbero al nodo padre della radice
               e dealloca la radice */
            T = toglienodoABRStr(T, T);
        }
        /* Se i è la radice dell'albero T e ha due figli */
        else
        {
            n = argmaxABRStr(T->Ts);
            strcpy(T->val, n->val);
            T = toglienodoABRStr(n, T);
        }
    }

    return T;
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

/*Restituisce il numero di elementi contenuti nell'albero
    ATTENZIONE: è una funzione di libreria che va utilizzata solo all'interno
    di quantiElementi, perchè il counter deve essere settato a zero per funzionare correttamente*/
int quantiElementiBis(ABRStr T, int counter)
{
    if (T != NO_TREE)
    {
        counter++;
        counter = quantiElementiBis(T->Ts, counter);
        counter = quantiElementiBis(T->Td, counter);
        return counter;
    }
    return counter;
}

/*Restituisce il numero di elementi contenuti nell'albero*/
int quantiElementi(ABRStr T)
{
    int counter = 0;
    return quantiElementiBis(T, counter);
}

/*Inserisce l'albero T in una tabella*/
void insABRStrInTabS(ABRStr T, tabS *Tab)
{
    if (T != NO_TREE)
    {
        insABRStrInTabS(T->Ts, Tab);
        instabS (Tab, T->val);
        insABRStrInTabS(T->Td, Tab);
    }
}

/* Stampa in ordine crescente */
void stampaABRStr(ABRStr T)
{
    if (T != NO_TREE)
    {
        stampaABRStr(T->Ts);
        printf("%s ", T->val);
        stampaABRStr(T->Td);
    }
}

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

/*Stampa un a capo dopo ogni singola parola dell'albero*/
// void stampaABRprogettiInOrdine (ABRStr T)
// {
//   if (T != NO_TREE)
//   {
//     stampaABRprogettiInOrdine(T->Ts);
//     printf("valore:%s inizio: %d scadenza: %d \n", T->val, T->inizio, T->scadenza);
//     stampaABRprogettiInOrdine(T->Td);
//   }
// }

// /*Conta il numero di nodi di un ABR*/
// int numeroNodi(ABRprogetti T)
// {
//   if (T != NO_TREE)
//     return (numeroNodi (T->Ts) + numeroNodi (T->Td) + 1); // Conto +1 per il nodo radice
//   else
//     return 0;
// }

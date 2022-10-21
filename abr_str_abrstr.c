#include <limits.h>
#include "abr_str_abrstr.h"
#include "tabStr.h"

/* Crea un albero binario vuoto */
ABRStrABRStr creaABR_str_ABRStr()
{
    return NO_TREE;
}

/* Distrugge un albero */
void distruggeABR_str_ABRStr(ABRStrABRStr *pT)
{
    if (*pT != NO_TREE)
    {
        distruggeABR_str_ABRStr(&(*pT)->Ts);
        distruggeABR_str_ABRStr(&(*pT)->Td);
        free(*pT);
        *pT = NO_TREE;
    }
}

/* Dato un ABR, indica se è vuoto */
boolean ABR_str_ABRStr_vuoto(ABRStrABRStr T)
{
    return (T == NO_TREE);
}

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABR_str_ABRStr(char *elem, ABRStrABRStr T, ABRStr TStr)
{
#ifdef RICORSIVA
    /* Implementazione ricorsiva */
    if (T == NO_TREE)
        return FALSE;
    else if (strcmp(elem, T->val) == 0)
        return TRUE;
    else if (strcmp(elem, T->val) < 0)
        return memberABR_str_ABRStr(elem, T->Ts);
    else /* if ( i > T->val) */
        return memberABR_str_ABRStr(elem, T->Td);
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
ABRStrABRStr costruisceABR_str_ABRStr(char *elem, ABRStrABRStr Ts, ABRStrABRStr Td)
{
    ABRStrABRStr T;

    /* Alloca l'elemento radice */
    T = (ABRStrABRStr)malloc(sizeof(nodoStrNodoStr));
    if (T == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione di un ABR!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(T->val, elem);
    T->ElencoOrd = creaABRStr();
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
ABRStrABRStr insertABR_str_ABRStr(char *elem, ABRStrABRStr T)
{
    if (T == NO_TREE)
        T = costruisceABR_str_ABRStr(elem, NO_TREE, NO_TREE);
    else if (strcmp(elem, T->val) < 0)
    {
        T->Ts = insertABR_str_ABRStr(elem, T->Ts);
        T->Ts->padre = T;
    }
    else if (strcmp(elem, T->val) > 0)
    {
        T->Td = insertABR_str_ABRStr(elem, T->Td);
        T->Td->padre = T;
    }

    return T;
}

/*Inserisce una Stringa nell'Elenco Ordinato*/
boolean insInElenco(char *elem, ABRStrABRStr T, char *Str)
{
#ifdef RICORSIVA
    /* Implementazione ricorsiva */
    if (T == NO_TREE)
        return FALSE;
    else if (strcmp(elem, T->val) == 0)
        return TRUE;
    else if (strcmp(elem, T->val) < 0)
        return memberABR(elem, T->Ts);
    else /* if ( i > T->val) */
        return memberABR(elem, T->Td);
#else
    /* Implementazione iterativa */
    while ((T != NO_TREE) && (strcmp(elem, T->val) != 0))
    {
        if (strcmp(elem, T->val) < 0)
            T = T->Ts;
        else /* if ( i > T->val) */
            T = T->Td;
    }
    // printf("ok\n");
    T->ElencoOrd = insertABRStr(Str, T->ElencoOrd);
    // printf("ook\n");

    return (T != NO_TREE);

#endif
}

/* Appende direttamente l'unico sottoalbero al nodo padre della radice e dealloca la radice stessa */
ABRStrABRStr toglienodoABR_str_ABRStr(nodoStrNodoStr *n, ABRStrABRStr T)
{
    ABRStrABRStr Tf;
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
nodoStrNodoStr *argmaxABR_str_ABRStr(ABRStrABRStr T)
{
    if (T == NO_TREE)
        return NULL;
    while (T->Td != NO_TREE)
        T = T->Td;

    return T;
}

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABRStrABRStr deleteABR_str_ABRStr(char *elem, ABRStrABRStr T)
{
    nodoStrNodoStr *n;

    /* Se l'albero T è vuoto, non si fa nulla */
    if (T != NO_TREE)
    {
        /* Se i precede la radice dell'albero T */
        if (strcmp(elem, T->val) < 0)
            T->Ts = deleteABR_str_ABRStr(elem, T->Ts);
        /* Se i segue la radice dell'albero T */
        else if (strcmp(elem, T->val) > 0)
            T->Td = deleteABR_str_ABRStr(elem, T->Td);
        /* Se i è la radice dell'albero T e ha un solo figlio */
        else if ((T->Ts == NO_TREE) || (T->Td == NO_TREE))
        {
            /* Appende direttamente l'unico sottoalbero al nodo padre della radice
               e dealloca la radice */
            T = toglienodoABR_str_ABRStr(T, T);
        }
        /* Se i è la radice dell'albero T e ha due figli */
        else
        {
            n = argmaxABR_str_ABRStr(T->Ts);
            strcpy(T->val, n->val);
            T = toglienodoABR_str_ABRStr(n, T);
        }
    }

    return T;
}

/*Restituisce il numero di elementi contenuti nell'albero
    ATTENZIONE: è una funzione di libreria che va utilizzata solo all'interno
    di numeroElementi, perchè il counter deve essere settato a zero per funzionare correttamente*/
int numeroElementiBis (ABRStrABRStr T, int counter)
{
    if (T != NO_TREE)
    {
        counter++;
        counter = numeroElementiBis(T->Ts, counter);
        counter = numeroElementiBis(T->Td, counter);
        return counter;
    }
    return counter;
}

/*Restituisce il numero di elementi contenuti nell'albero*/
int numeroElementi (ABRStrABRStr T)
{
    int counter = 0;
    return numeroElementiBis(T, counter);
}

/*Restituisce TRUE se Cerca appartiene all'elenco di val */
boolean appartieneAdElenco (ABRStrABRStr T, char *val, char *Cerca)
{

    while ((T != NO_TREE) && (strcmp(val, T->val) != 0))
    {
        if (strcmp(val, T->val) < 0)
            T = T->Ts;
        // else if(strcmp(val,T->val) == 0){
        //     memberABRStr(Cerca, T->ElencoOrd);
        // }
        else /* if ( i > T->val) */
            T = T->Td;
    }

    if( T == NO_TREE )
        return FALSE;
    else if (memberABRStr(Cerca, T->ElencoOrd) == TRUE)
        return TRUE;

    // return (memberABRStr(Cerca, T->ElencoOrd));

    //     if (T != NO_TREE)
    // {
    //     appartieneAdElenco(T->Ts, val, Cerca);
    //     if (strcmp(T->val, val) == 0){

    //     }
    //     appartieneAdElenco(T->Td, val, Cerca);
    // }

}


void inserisceInTabS ( ABRStrABRStr T, tabS *Tab)
{
    if (T != NO_TREE)
    {
        inserisceInTabS(T->Ts, Tab);
        instabS(Tab, T->val);
        inserisceInTabS(T->Td, Tab);
    }
}

/*Inserisce gli elementi dell'elenco relativi al nodo di nome val nella tabella Tab*/
void inserisceElencoInTabS (ABRStrABRStr T, char *val, tabS *Tab)
{

    while ((T != NO_TREE) && (strcmp(val, T->val) != 0))
    {
        if (strcmp(val, T->val) < 0)
            T = T->Ts;
        else /* if ( i > T->val) */
            T = T->Td;
    }
    insABRStrInTabS (T->ElencoOrd, Tab);
}

void StampaABR_str_ABRStr (ABRStrABRStr T)
{

    if (T != NO_TREE)
    {
        StampaABR_str_ABRStr(T->Ts);
        printf("%s\n", T->val);
        printf("%d ", quantiElementi(T->ElencoOrd));
        stampaABRStr(T->ElencoOrd);
        printf("\n");
        StampaABR_str_ABRStr(T->Td);
    }
}

/*Inserisce le altezze dell'albero in una tabella di interi*/
void insInTabIntAltezzeABR (ABRStrABRStr T, tab_int *Tab)
{
    if (T != NO_TREE)
    {
        insInTabIntAltezzeABR(T->Ts, Tab);
        ins_tab_int (Tab, quantiElementi(T->ElencoOrd));
        insInTabIntAltezzeABR(T->Td, Tab);
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

/* Stampa in ordine crescente */
// void stampaABRStr (ABR_str_ABRStr T)
// {
//   if (T != NO_TREE)
//   {
//     stampaABRStr(T->Ts);
//     printf("%s ", T->val);
//     stampaABRStr(T->Td);
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

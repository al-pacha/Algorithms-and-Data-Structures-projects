#include <limits.h>
#include "abrStrInt.h"


/* Crea un albero binario vuoto */
ABRStrInt creaABRStrInt()
{
    return NO_TREE;
}

/* Distrugge un albero */
void distruggeABRStrInt(ABRStrInt *pT)
{
    if (*pT != NO_TREE)
    {
        distruggeABRStrInt(&(*pT)->Ts);
        distruggeABRStrInt(&(*pT)->Td);
        free(*pT);
        *pT = NO_TREE;
    }
}

/* Dato un ABR, indica se è vuoto */
// boolean ABRStrvuoto(ABRStrInt T)
// {
//     return (T == NO_TREE);
// }

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABRStrInt(char *elem, ABRStrInt T)
{
#ifdef RICORSIVA
    /* Implementazione ricorsiva */
    if (T == NO_TREE)
        return FALSE;
    else if (strcmp(elem, T->val) == 0)
        return TRUE;
    else if (strcmp(elem, T->val) < 0)
        return memberABRStrInt(elem, T->Ts);
    else /* if ( i > T->val) */
        return memberABRStrInt(elem, T->Td);
#else
    /* Implementazione iterativa */
    while ((T != NO_TREE) && (strcmp(elem, T->Stringa) != 0))
    {
        if (strcmp(elem, T->Stringa) < 0)
            T = T->Ts;
        else /* if ( i > T->val) */
            T = T->Td;
    }

    return (T != NO_TREE);

#endif
}

/*Costruisce un ABR con nodo elem, figlio sinistro Ts, figlio sinistro Td*/
ABRStrInt costruisceABRStrInt(char *elem, int val, ABRStrInt Ts, ABRStrInt Td)
{
    ABRStrInt T;

    /* Alloca l'elemento radice */
    T = (ABRStrInt)malloc(sizeof(nodoStrInt));
    if (T == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione di un ABR!\n");
        exit(EXIT_FAILURE);
    }

    // printf("ok\n");
    strcpy(T->Stringa, elem);
    T->val = val;
    T->padre = NULL;
    T->Ts = Ts;
    if (Ts != NULL)
        Ts->padre = T;
    T->Td = Td;
    if (Td != NULL)
        Td->padre = T;

    return T;
}

/* Dato un elemento e un ABR, inserisce l'elemento elem e val nell'ABR */
ABRStrInt insertABRStrInt(char *elem, int val, ABRStrInt T)
{
    if (T == NO_TREE)
        T = costruisceABRStrInt(elem, val, NO_TREE, NO_TREE);
    else if (strcmp(elem, T->Stringa) < 0)
    {
        T->Ts = insertABRStrInt(elem, val, T->Ts);
        T->Ts->padre = T;
    }
    else if (strcmp(elem, T->Stringa) > 0)
    {
        T->Td = insertABRStrInt(elem, val, T->Td);
        T->Td->padre = T;
    }

    return T;
}

/* Appende direttamente l'unico sottoalbero al nodo padre della radice e dealloca la radice stessa */
ABRStrInt toglienodoABRStrInt(nodoStrInt *n, ABRStrInt T)
{
    ABRStrInt Tf;
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
nodoStrInt *argmaxABRStrInt(ABRStrInt T)
{
    if (T == NO_TREE)
        return NULL;
    while (T->Td != NO_TREE)
        T = T->Td;

    return T;
}

/*Inserisce i valori numerici dell'albero in una tabella ordinata*/
void insABRStrIntInTabInt (ABRStrInt T, tab_int *Tab)
{
    if (T != NO_TREE)
    {
        insABRStrIntInTabInt(T->Ts, Tab);
        ins_tab_int (Tab, T->val);
        insABRStrIntInTabInt(T->Td, Tab);
    }
}

/* Stampa in ordine crescente */
void stampaABRStrInt(ABRStrInt T)
{
    if (T != NO_TREE)
    {
        stampaABRStrInt(T->Ts);
        printf("%s %d\n", T->Stringa, T->val);
        stampaABRStrInt(T->Td);
    }
}


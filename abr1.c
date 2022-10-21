#include <limits.h>
#include "abr.h"

/* Crea un albero binario vuoto */
ABR creaABR ()
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
void distruggeABR (ABR *pT)
{
  if (*pT != NO_TREE){
    distruggeABR(&(*pT)->Ts);
    distruggeABR(&(*pT)->Td);
    free (*pT);
    *pT = NO_TREE;
  }
}

/* Dato un ABR, indica se è vuoto */
boolean ABRvuoto (ABR T)
{
  return (T == NO_TREE);
}

/* Dato un elemento e un ABR, indica se l'elemento fa parte dell'ABR */
boolean memberABR (char *elem, ABR T)
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
    while ( (T != NO_TREE) && (strcmp(elem, T->val) != 0) ){
      if (strcmp(elem, T->val) < 0)
        T = T->Ts;
      else /* if ( i > T->val) */
        T = T->Td;
    }

    return (T != NO_TREE);

  #endif
}

ABR costruisceABR (char *elem, ABR Ts, ABR Td)
{
  ABR T;

  /* Alloca l'elemento radice */
  T = (ABR) malloc (sizeof(nodo));
  if (T == NULL) 
  {
    fprintf(stderr,"Errore nell'allocazione di un ABR!\n");
    exit(EXIT_FAILURE);
  }

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

/* Dato un elemento e un ABR, inserisce l'elemento elem nell'ABR */
ABR insertABR (char *elem, ABR T)
{
  if (T == NO_TREE)
    T = costruisceABR(elem, NO_TREE, NO_TREE);
  else if (strcmp(elem, T->val) < 0) {
    T->Ts = insertABR(elem, T->Ts);
    T->Ts->padre = T;
  }
  else if (strcmp(elem, T->val) > 0) {
    T->Td = insertABR(elem, T->Td);
    T->Td->padre = T;
  }

  return T;
}

/* Appende direttamente l'unico sottoalbero al nodo padre della radice e dealloca la radice stessa */
ABR toglienodoABR (nodo *n, ABR T)
{
  ABR Tf;
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
  free (n);


  return T;
}

/* Determina il nodo che corrisponde al valore massimo nell'albero T */
nodo *argmaxABR (ABR T){
  if (T == NO_TREE)
    return NULL;
  while (T->Td != NO_TREE)
    T = T->Td;

  return T;
}

/* Dato un elemento e un ABR, cancella l'elemento dall'ABR */
ABR deleteABR (char *elem, ABR T)
{
  nodo *n;

  /* Se l'albero T è vuoto, non si fa nulla */
  if (T != NO_TREE){
    /* Se i precede la radice dell'albero T */
    if (strcmp (elem, T->val) < 0)
      T->Ts = deleteABR(elem, T->Ts);
    /* Se i segue la radice dell'albero T */
    else if (strcmp (elem, T->val) > 0)
      T->Td = deleteABR(elem, T->Td);
    /* Se i è la radice dell'albero T e ha un solo figlio */
    else if ( (T->Ts == NO_TREE) || (T->Td == NO_TREE) ){
      /* Appende direttamente l'unico sottoalbero al nodo padre della radice
         e dealloca la radice */
      T = toglienodoABR (T, T);
    }
    /* Se i è la radice dell'albero T e ha due figli */
    else {
      n = argmaxABR(T->Ts);
      strcpy(T->val, n->val);
      T = toglienodoABR(n, T);
    }
  }

  return T;
}

/* Dato un ABR, ne restituisce l'elemento minimo. Se l'ABR è vuoto, restituisce un valore fittizio +inf */
char minABR (ABR T)
{
  return 'a';
}

/* Dato un ABR, ne restituisce l'elemento massimo. Se l'ABR è vuoto, restituisce un valore fittizio -inf */
char maxABR (ABR T)
{
  return 'a';
}

/* Stampa in ordine crescente */
void stampaABR (ABR T)
{
  if (T != NO_TREE)
  {
    stampaABR(T->Ts);
    printf("%s ", T->val);
    stampaABR(T->Td);
  }
}

void sstampaABR (ABR T, char *s)
{
  if (T != NO_TREE)
  {
    sstampaABR(T->Ts, s);
    s = strcat(s, T->val);
    s = strcat(s, " ");
    sstampaABR(T->Td, s);
  }
}

/*Stampa un a capo dopo ogni singola parola dell'albero*/
void stampaABRInOrdine (ABR T)
{
  if (T != NO_TREE)
  {
    stampaABRInOrdine(T->Ts);
    printf("%s \n", T->val);
    stampaABRInOrdine(T->Td);
  }
}

/*Conta il numero di nodi di un ABR*/
int numeroNodi(ABR T)
{
  if (T != NO_TREE)
    return (numeroNodi (T->Ts) + numeroNodi (T->Td) + 1); // Conto +1 per il nodo radice
  else
    return 0;
}



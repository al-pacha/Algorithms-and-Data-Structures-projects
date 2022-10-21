#include <limits.h>
#include "abrint.h"

ABRint creaABRint ()
{
  return EMPTY_TREE;
}


void distruggeABRint (ABRint *pT)
{
  if (*pT != EMPTY_TREE)
  {
    distruggeABRint(&(*pT)->Ts);
    distruggeABRint(&(*pT)->Td);
    free(*pT);
    *pT = EMPTY_TREE;
  }
}


boolean ABRintvuoto (ABRint T)
{
  return (T == EMPTY_TREE);
}


boolean memberABRint (int i, ABRint T)
{
#ifdef RICORSIVA
  /* Implementazione ricorsiva */
  if (T == EMPTY_TREE)
    return FALSE;
  else if (i == T->val)
    return TRUE;
  else if (i < T->val)
    return memberABRint(i,T->Ts);
  else /* if (i > T->val) */
    return memberABRint(i,T->Td);
#else
  /* Implementazione iterativa */
  while ( (T != EMPTY_TREE) && (i != T->val) )
    if (i < T->val)
      T = T->Ts;
    else /* if (i > T->val) */
      T = T->Td;

  return (T != EMPTY_TREE);
#endif
}


ABRint creanodoABRint (int i, ABRint Ts, ABRint Td)
{
  ABRint T;

  /* Alloca l'elemento radice */
  T = (nodoint *) malloc(sizeof(nodoint));
  if (T == NULL)
  {
    fprintf(stderr,"Errore nell'allocazione di un nodoint!\n");
    exit(EXIT_FAILURE);
  }

  T->val = i;
  T->padre = NULL;
  T->Ts = Ts;
  if (Ts != NULL) Ts->padre = T;
  T->Td = Td;
  if (Td != NULL) Td->padre = T;

  return T;
}


ABRint insertABRint (int i, ABRint T)
{
  if (T == EMPTY_TREE)
    T = creanodoABRint(i,EMPTY_TREE,EMPTY_TREE);
  else if (i < T->val)
  {
    T->Ts = insertABRint(i,T->Ts);
    T->Ts->padre = T;
  }
  else if (i > T->val)
  {
    T->Td = insertABRint(i,T->Td);
    T->Td->padre = T;
  }

  return T;
}


/* Appende direttamente l'unico sottoalbero del nodoint n dell'ABRint T
   al nodoint padre e dealloca il nodoint n */
ABRint toglienodoABRint (nodoint *n, ABRint T)
{
  ABRint Tf;


  /* Determina l'unico sottoalbero non vuoto del nodoint n (eventualmente EMPTY_TREE) */
  Tf = ( (n->Ts == EMPTY_TREE) ? n->Td : n->Ts );

  /* Se esiste un sottoalbero, lo appende al padre (eventualmente NULL) */
  if (Tf != EMPTY_TREE) Tf->padre = n->padre;

  /* Se n e' la radice, sostituisce l'albero T con il sottoalbero */
  if (n == T)
    T = Tf;
  else /* Se n ha un padre, determina in quale sottoalbero del padre stava
          e sostituisce il sottoalbero a se stesso */
  {
    if (n == n->padre->Ts)
      n->padre->Ts = Tf;
    else if (n == n->padre->Td)
      n->padre->Td = Tf;
  }

  /* Dealloca il nodoint */
  free(n);

  return T;
}


/* Determina il nodoint che corrisponde al valore massimo dell'ABRint T */
nodoint *argmaxABRint (ABRint T)
{
  if (T == EMPTY_TREE) return EMPTY_TREE;
  while (T->Td != EMPTY_TREE)
    T = T->Td;
  return T;
}


ABRint deleteABRint (int i, ABRint T)
{
  nodoint *n;

  /* Se l'albero e' vuoto, non fa nulla (se i non appartiene all'albero, si finisce qui) */
  if (T != EMPTY_TREE)
  {
    if (i < T->val)
      T->Ts = deleteABRint(i,T->Ts);
    else if (i > T->val)
      T->Td = deleteABRint(i,T->Td);
    /* Se i e' la radice e ha al massimo un figlio */
    else if ( (T->Ts == EMPTY_TREE) || (T->Td == EMPTY_TREE) )
      /* Appende il sottoalbero al padre e cancella la radice */
      T = toglienodoABRint(T,T);
    /* Se i e' la radice e ha due figli */
    else
    {
      /* Sovrascrive la radice con l'elemento massimo del sottoalbero sinistro
         e cancella quest'ultimo */
      n = argmaxABRint(T->Ts);
      T->val = n->val;
      T = toglienodoABRint(n,T);
    }
  }

  return T;
}


int minABRint (ABRint T)
{
#ifdef RICORSIVA
  /* Implementazione ricorsiva */
  if (T == EMPTY_TREE)
    return INT_MAX;
  else if (T->Ts == EMPTY_TREE)
    return T->val;
  else
    return minABRint(T->Ts);
#else
  /* Implementazione iterativa */
  if (T == EMPTY_TREE) return INT_MAX;
  while (T->Ts != EMPTY_TREE)
    T = T->Ts;

  return T->val;
#endif
}


int maxABRint (ABRint T)
{
#ifdef RICORSIVA
  /* Implementazione ricorsiva */
  if (T == EMPTY_TREE)
    return INT_MIN;
  else if (T->Td == EMPTY_TREE)
    return T->val;
  else
    return maxABRint(T->Td);
#else
  /* Implementazione iterativa */
  if (T == EMPTY_TREE) return INT_MIN;
  while (T->Td != EMPTY_TREE)
    T = T->Td;

  return T->val;
#endif
}


void stampaABRint (ABRint T)
{
  if (T != EMPTY_TREE)
  {
    stampaABRint(T->Ts);
    printf(" %d",T->val);
    stampaABRint(T->Td);
  }
}

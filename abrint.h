#ifndef __abrint_h
#define __abrint_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ROW_LENGTH 256

#define boolean int
#define TRUE  1
#define FALSE 0


#define EMPTY_TREE  NULL

typedef struct _nodoint nodoint;
struct _nodoint
{
  int val;
  nodoint *padre;
  nodoint *Ts;
  nodoint *Td;
};

typedef nodoint *ABRint;


ABRint creaABRint ();

void distruggeABRint (ABRint *pT);

boolean ABRintvuoto (ABRint T);

boolean memberABRint (int i, ABRint T);

ABRint insertABRint (int i, ABRint T);

ABRint deleteABRint (int i, ABRint T);

int minABRint (ABRint T);

int maxABRint (ABRint T);

void stampaABRint (ABRint T);

#endif

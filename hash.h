/* MARDALE Andrei-Iulian - 311CB */
#include "list.h"

#ifndef _HASH_
#define _HASH_

typedef int (*hashf) (void *); //dispersion function

typedef struct {
	TList *buckets; //list vector (buckets)
	int n; //number of elements
} THash;

//allocates memory for structure and buckets vector
THash * initHash (int n);

//adds element to hash 1/0 success/fail
int add (THash *H, void *inf, int index, TFcmp cmp);

//finds element in hash 
void *findEL (THash *H, void *target, int index, TFcmp cmp);

//deletes element from hash returns 1/0 success/fail
int removeEL (THash *H, void *target, int index, TFcmp cmp, TFwork freeInf);

//destroys all elements in hash (frees memory)
void destroyHash (THash **H, TFwork freeInf);

#endif


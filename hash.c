/* MARDALE Andrei-Iulian - 311CB */
#include "hash.h"

THash * initHash (int n) {
	THash *h = malloc(sizeof(THash));
	if (!h) return NULL;
	
	h->buckets = calloc(n, sizeof(AList));
	if (!(h->buckets)) {
		free(h);
		return NULL;
	}
	
	h->n = n;
	
	return h;
}	

int add (THash *H, void *inf, int index, TFcmp cmp) {	
	return addOrdered(&H->buckets[index], inf, cmp);
}

void * findEL (THash *H, void *target, int index, TFcmp cmp) {
	return findCell(H->buckets[index], target, cmp);
}

int removeEL (THash *H, void *target, int index, TFcmp cmp, TFwork freeInf) {
	return removeCell(&H->buckets[index], target, cmp, freeInf);
}

void destroyHash (THash **H, TFwork freeInf) {
	for (int i = 0; i < (*H)->n; ++i) {
		destroyList(&(*H)->buckets[i], freeInf);
	}
	
	free((*H)->buckets);
	free(*H);
	
	*H = NULL;
}
	
	
	

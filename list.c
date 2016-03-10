/* MARDALE Andrei-Iulian - 311CB */
#include "list.h"

TList createCell (void *inf) {
	TList r = malloc(sizeof(TCell));
	if (!r) return NULL;
	
	r->inf = inf;
	r->next = NULL;
	
	return r;
}

//advance until next element is greater
//then insert new element before it
//insertion is made only if element is not already in list
/* exit codes:
	0 - not added because it's already there
	-1 not added because could not allocate memory for new cell
	1 - added
*/
int addOrdered (AList aL, void *inf, TFcmp cmp) {
	int diff = -1;
	while (*aL && (diff = cmp(inf, (*aL)->inf)) > 0) {
		aL = &(*aL)->next;
	}
	
	if (diff != 0) {
		TList r = createCell(inf);
		if (!r) return -1;
		
		r->next = *aL;
		*aL = r;	
		return 1;
	}
	
	return 0;
}

void * findCell (TList L, void *target, TFcmp cmp) {
	while (L) {
		int diff = cmp(target, L->inf);
		
		if (diff > 0) {
			L = L->next;
		} else if (diff == 0) {
			return L->inf;
		} else {
			return NULL;
		}
	}
	
	return NULL;
}
	

/*searches for inf in ordered list pointed to by aL;
if found then deletes it =>output 1
if passed max position (reached higher elements than inf exits function; element will not be found =>output 0;
*/
int removeCell (AList aL, void *inf, TFcmp cmp, TFwork freeInf) {
	while (*aL) {
		int diff = cmp(inf, (*aL)->inf);
		
		if (diff > 0) {
			aL = &(*aL)->next;
		} else if (diff == 0) {
			TList aux = *aL;
			*aL = (*aL)->next;
			
			freeInf(aux->inf);
			free(aux);
			
			return 1;
		} else {
			return 0;
		}
	}
	
	return 0;
}

void work (TList L, TFwork F) {
	for (; L; L = L->next) {
		F(L->inf);
	}
}
			
void work2 (TList L, TFcmp F, void *p) {
	for (; L; L = L->next) {
		F(L->inf, p);
	}
}

void destroyList (AList aL, TFwork freeInf) {
	TList L = *aL, aux = NULL;
	
	while (L) {
		aux = L;
		L = L->next;
		freeInf(aux->inf);
		free(aux);
	}
	
	*aL = NULL;
}
		
 		

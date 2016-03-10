/* MARDALE Andrei-Iulian - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _LIST_
#define _LIST_

#define IS_VOID(L) ((L) == NULL)

typedef int (*TFcmp) (void *, void *); //performs action on 2 elements
typedef int (*TFwork) (void *); //performs action on 1 element

typedef struct TCell {
	struct TCell *next;
	void *inf;
} TCell, *TList, **AList;

//create new cell; asumes information for inf has been allocated application-side
TList createCell (void *inf);

//creates new cell with inf and adds it to ordered list pointed to by aL
//will not add duplicates
int addOrdered (AList aL, void *inf, TFcmp cmp);

//returns inf for searched element (assumes list is ordered)
void * findCell (TList L, void *target, TFcmp cmp);

//remove element from list (assumes list is ordered)
int removeCell (AList aL, void *inf, TFcmp cmp, TFwork freeInf);

//performs simple action on all elements in list; action is defined by work
void work (TList L, TFwork F);

//performs action on all elements in list; action is defined by work
//this is a print function
void work2 (TList L, TFcmp F, void *p);

//destroys list aL, deallocate information too with function freeInf
//using freeInf in case information is a complex type which also need to be freed
//if freeInf is NULL then just call free() directly
void destroyList (AList aL, TFwork freeInf); 

#endif

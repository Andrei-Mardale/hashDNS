/* MARDALE Andrei-Iulian - 311CB */
#include "hash.h"

#ifndef _DNS_
#define _DNS_

#define MAX_WORDS 3
#define INSTR 0 //intruction
#define ARG1 1 //argument 1 of instruction
#define ARG2 2 //argument 2 of instruction (may sometimes be absent)

typedef struct {
	char *key;
	char *value;
} TEL, *AEL;


AEL createElement (char *key, char *value); //allocates memory for element and copies data from key and value
//parses commands; calls other functions accordingly will return -1 if something goes wrong
int parse (THash *H, char *input, FILE *out); 
int put (THash *H, char *key, char *value); //adds element to hash (1 added, 0 already there, -1 could not allocate)
char * get (THash *H, char *key); //gets value for key from hash (null if nothing)
int removeEntry (THash *H, char *key); //deletes value from hash (1 removed, 0 not)
int find (THash *H, char *key); //checks if key is in hash (1 it is, 0 is not)
void print(THash *H, FILE *out); //prints whole data
void print_bucket (THash *H, int index, FILE *out); //prints data for specified bucket

int freeInf (void *p); //elementwise free function, will be passed to other functions

#endif

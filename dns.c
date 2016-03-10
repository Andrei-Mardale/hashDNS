/* MARDALE Andrei-Iulian - 311CB */
#include "dns.h"

//definition of dispersion function
int disp (void *p) {
	char *s = (char *) p;
	
	int sum = 0, lim = strlen(s);
	for (int i = 0; i < lim; ++i) {
		sum += s[i];
	}
	
	return sum;
}

//definition of elementwise print to file function
int printElement (void *p1, void *p2) {
	AEL ae = (AEL) p1;
	FILE *out = (FILE *) p2; 
	fprintf(out, "%s ", ae->value);
	return 0;
}

//definition of comparation function
//this one takes two AELs
int cmp (void *p1, void *p2) {
	AEL ae1 = (AEL) p1;
	AEL ae2 = (AEL) p2;
	
	return strcmp(ae1->key, ae2->key);
}

//another definition of comparation function
//this one takes an AEL and a char *
//more efficient when the objective is to find instead of adding
int cmp2 (void *p1, void *p2) {
	AEL ae = (AEL) p2;
	char *s = (char *) p1;
	
	return strcmp(s, ae->key);
}

//definition of elementwise free function
int freeInf (void *p) {
	AEL ae = (AEL) p;
	free(ae->key);
	free(ae->value);
	free(ae);
	return 0;
}

AEL createElement (char *key, char *value) {
	AEL ae = malloc(sizeof(TEL));
	if(!ae) return NULL;
	
	char *k = NULL, *v = NULL;
	
	int l = strlen(key) + 1; //get length
	k = malloc(l * sizeof(char)); //allocate
	if (!k) { //check
		free(ae);
		return NULL;
	}	
	memcpy(k, key, l); //copy data
	
	//same steps for value
	l = strlen(value) + 1;
	v = malloc(l* sizeof(char));
	if (!v) {
		free(k);
		free(ae);
		return NULL;
	}
	memcpy(v, value, l);
	
	ae->value = v;
	ae->key = k;
	
	return ae;
}

/* exit codes:
	-1 somewhere memory could not be allocated
	1 everything ok
*/
int parse (THash *H, char *input, FILE *out) {
	//tokenize
	int i = 0;
	char *p[MAX_WORDS], *temp = strtok(input, " ");
	while (temp != NULL) {
		p[i] = temp;
		++i;
		temp = strtok(NULL, " ");
	}
	
	//check which instruction is given and call function accordingly
	if (!strcmp(p[INSTR], "put")) {
		int r = put(H, p[ARG1], p[ARG2]);
		if (r == -1) {
			return r;
		}
	} else if (!strcmp(p[INSTR], "get")) {
		AEL ae = (AEL) get(H, p[ARG1]);
		if (!ae) {
			fprintf(out, "NULL\n");
		} else {
			fprintf(out, "%s\n", ae->value);
		}
	} else if (!strcmp(p[INSTR], "remove")) {
		removeEntry(H, p[ARG1]);
	} else if (!strcmp(p[INSTR], "find")) {
		int r = find(H, p[ARG1]);
		if (r == 1) {
			fprintf(out, "True\n");
		} else {
			fprintf(out, "False\n");
		}		
	} else if (!strcmp(p[INSTR], "print")) {
		print(H, out);
	} else if (!strcmp(p[INSTR], "print_bucket")) {
		int index = strtol(p[ARG1], NULL, 10);
		if (index < H->n) {
			print_bucket(H, index, out);
		}
	}
	
	return 1;
}

int put (THash *H, char *key, char *value) {
	AEL ae = createElement(key, value);
	if (!ae) {
		return 0;
	}
	
	int index = disp(key) % H->n;
	
	int r = add(H, ae, index, cmp); //try to add
	
	//if item could not be added then free what has been allocated 
	if (r == 0 || r == -1) freeInf(ae);
	
	return r;
}


char *get (THash *H, char *key) {
	int index = disp(key) % H->n;
	
	return findEL(H, key, index, cmp2); 
}

int removeEntry (THash *H, char *key) {
	int index = disp(key) % H->n;
	
	return removeEL (H, key, index, cmp2, freeInf);
}

int find (THash *H, char *key) {
	int index = disp(key) % H->n;
	
	void *r = findEL(H, key, index, cmp2);
	
	if (!r) return 0;
	return 1;
}	

void print (THash *H, FILE *out) {
	for (int i = 0; i < H->n; i++) {
		if (IS_VOID(H->buckets[i]) == 0) {
			fprintf(out, "%d: ", i);
			work2(H->buckets[i], printElement, out);
			fprintf(out, "\n");
		}
	}
}

void print_bucket (THash *H, int index, FILE *out) {
	if (IS_VOID(H->buckets[index])) {
		fprintf(out, "VIDA\n");
	} else {
		work2(H->buckets[index], printElement, out);
		fprintf(out, "\n");
	}
}

		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
 

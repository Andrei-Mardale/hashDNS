/* MARDALE Andrei-Iulian - 311CB */
#include "dns.h"

#define BSIZE 1000

int main (int argc, char *argv[]) {
	if (argc != 4) return 3;
	int M = strtol(argv[1], NULL, 10); //get numerical value from string
	
	//open input file
	FILE *in = fopen(argv[2], "r");
	if (!in) return 2;
	
	//open output file
	FILE *out = fopen(argv[3], "w");
	if (!out) {
		fclose(in);
		return 2;
	}
	
	//buffer input which will be used to parse commands
	//aux is used to check return value of function fgets
	//aux tells us when to stop reading
	char *aux = NULL, *buffer = NULL;
	buffer = malloc(BSIZE * sizeof(char));
	if (!buffer) {
		fclose(in);
		fclose(out);
		return 2;
	}
	
	THash *H = initHash(M);
	
	if (!H) {
		fclose(in);
		fclose(out);
		free(buffer);
		return 2;
	}
	
	aux = fgets(buffer, BSIZE, in);
	while (aux) {
		if (buffer[0] == '\n') break; //limit case when end of file reached (almost) and last line is '\n'
		
		buffer[strlen(buffer) - 1] = '\0';
		
		//try to parse commands
		//if command is put and memory cannot be allocated then exit program (clean)
		if (parse(H, buffer, out) == -1) {
			fclose(in);
			fclose(out);
			free(buffer);
			destroyHash(&H, freeInf);
			return 2;
		}
		
		aux = fgets(buffer, BSIZE, in);
	}
	
	//free everything
	destroyHash(&H, freeInf);	
	fclose(in);
	fclose(out);
	free(buffer);
	
	return 0;
}

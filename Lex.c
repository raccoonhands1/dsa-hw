#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "List.h"

int read(FILE* in) {

	if(in == NULL) {
	  printf("Not able to open the file.");
	}

	int c = 0;
	
	char buffer[256];
	printf("Reading file data... \n");
	while(fgets(buffer, sizeof(buffer), in)) {
		c++;
		printf("%s", buffer);
	}


	return c;
}

int main(int argc, char* argv[]) {
	
	if(argc!=3) {
		fprintf(stderr, "%s", "please enter two valid arguments. \n Valid arguments are :\n [input] [output]\n");	
	}
	
	FILE* in = fopen(argv[1], "r");
	int c = read(in);
	fclose(in);

	char* arr = (char *)malloc(c * sizeof(char));

	


	return 0;
}





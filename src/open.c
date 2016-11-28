#include <stdio.h>
#include <stdlib.h>

FILE* open_image(char* argv){
	printf("filename: %s\n", argv);
	FILE* input_image = fopen(argv, "r+b");

	if(input_image == NULL){
		printf("cannot open file\n");
		exit(1);
	}
}

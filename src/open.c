#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/image.h"
#include "../include/open.h"


FILE* open_image(char* argv){
	printf("filename: %s\n", argv);
	FILE* input_image = fopen(argv, "r+b");

	
	if(input_image == NULL){
		printf("Cannot open file\n");
		exit(1);
	}
}

image_t open_header(FILE* input_image){
	int size[2];
	int error_code;

	fseek(input_image, 18, SEEK_SET);
	error_code = fread(size, sizeof(int), 2, input_image);
	if(error_code)
		printf("Read ok\n");
	else
		printf("Error with reading the header\n");

	pixel_t* pixel_array = malloc(size[0] * size[1] * sizeof(pixel_t));
	image_t header = {.width = size[0], .height = size[1], .pixel_buffer = pixel_array};
	return header;
}

image_t check_filetype(FILE* input_image, image_t header){
	char file_type[3];
	
	fread(file_type, 1, 2, input_image);
	file_type[2] = '\0';
	
	image_t (*options[])(FILE*) = {open_header}; 	

	if(!strcmp(file_type, "BM")){
		header = (*options[0])(input_image);
	} else {
		printf("You're trying to open unsupported file format\n");
		exit(0);
	}
	return header;
}

void read_array(pixel_t* array, FILE* input_image, image_t header, int litter){
	char dev_null;
	fseek(input_image, OFFSET, SEEK_SET);
	for(int i = 0; i < header.height; i++){
		fread((array + (i * header.width)), 3, header.width, input_image);
		fread(&dev_null, litter, 1, input_image);
	}
}

void write_image(FILE* input_image, image_t header, pixel_t* transformed_array){
	int error_code;
	int litter = header.width % 4;
	fseek(input_image, OFFSET, SEEK_SET);
	for(int i = 0; i < header.height; i++){
		error_code = fwrite((transformed_array + i * header.width), header.width*sizeof(pixel_t), 1, input_image);
		fwrite(&litter, litter, 1, input_image);
			
		if(!error_code){
			printf("Write failed\n");
			exit(0);
		}
	}
	printf("Write ok\n");
	fclose(input_image);
}

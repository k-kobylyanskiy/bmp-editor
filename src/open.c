#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/open.h"

FILE* open_image(char* argv){
	printf("filename: %s\n", argv);
	FILE* input_image = fopen(argv, "r+b");

	if(input_image == NULL){
		printf("cannot open file\n");
		exit(1);
	}
}

image_t open_header(FILE* input_image){
	int size[2];

	fseek(input_image, 18, SEEK_SET);
	fread(size, sizeof(int), 2, input_image);

	pixel_t* pixel_array = malloc(size[0] * size[1] * sizeof(pixel_t));
	image_t image = {.height = size[1], .width = size[0], .pixel_buffer = pixel_array};
	return image;
}

void read_array(pixel_t* array, FILE* input_image, image_t image, int offset, int litter){
	char dev_null;
	fseek(input_image, OFFSET, SEEK_SET);
	for(int i = 0; i < image.height; i++){
		fread((array + (i * image.width)), 3, image.width, input_image);
		fread(&dev_null, litter, 1, input_image);
	}
}

void write_image(FILE* input_image, image_t image, pixel_t* transformed_array){
	int litter = image.width % 4;
	fseek(input_image, OFFSET, SEEK_SET);
	for(int i = 0; i < image.height; i++){
		fwrite((transformed_array + i * image.width), 3, image.width, input_image);
		fwrite(&litter, litter, 1, input_image);
	}
	fclose(input_image);
}

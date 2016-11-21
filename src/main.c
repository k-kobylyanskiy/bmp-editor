#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <strings.h>
#include "../include/image.h"
#include "../include/rotate.h"


void read_array();

int main() {
	
	int size[2];
	int offset;
	int litter;
	FILE* input_image = fopen("res/trees1.bmp", "r+b");

	if(input_image == NULL){
		printf("cannot open file\n");
		return 1;
	}
	
	/* reading a size of the image */
	
	fseek(input_image, 18, SEEK_SET);
	fread(size, sizeof(int), 2, input_image);

	litter = size[0] % 4;
	
	pixel_t* pixel_array = malloc(size[0] * size[1] * sizeof(pixel_t));
	pixel_t* transformed_array = malloc(size[0] * size[1] * sizeof(pixel_t));

	image_t image = {.height = size[1], .width = size[0], .pixel_buffer = pixel_array};

	fseek(input_image, 10, SEEK_SET);
	fread(&offset, sizeof(int), 1, input_image);

	read_array(pixel_array, input_image, image, offset, litter);

	rotate_image(pixel_array, transformed_array, image);
	rewrite_header(image, input_image);

	fseek(input_image, offset, SEEK_SET);
	for(int i = 0; i < image.height; i++){
		fwrite((transformed_array + i * image.width), 3, image.width, input_image);
		fwrite(&size, litter, 1, input_image);
	}
	fclose(input_image);
	return 0;
}

void read_array(pixel_t* array, FILE* input_image, image_t image, int offset, int litter){
	char dev_null;
	fseek(input_image, offset, SEEK_SET);
	for(int i = 0; i < image.height; i++){
		fread((array + (i * image.width)), 3, image.width, input_image);
		fread(&dev_null, litter, 1, input_image);
	}
}

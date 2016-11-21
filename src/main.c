#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/image.h"

void read_array();
void rotate_image();
void rewrite_header();

int main() {
	
	int size[2];
	int offset;
	int litter;
	FILE* input_image = fopen("res/trees2.bmp", "r+b");

	if(input_image == NULL){
		printf("cannot open file\n");
		return 1;
	}
	
	/* reading a size of the image */
	
	fseek(input_image, 18, SEEK_SET);
	fread(size, sizeof(int), 2, input_image);

	litter = size[0] % 4;
	printf("litter is %d px\n", litter);
	
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
		printf("row is %d\n", i);
		fread((array + (i * image.width)), 3, image.width, input_image);
		fread(&dev_null, litter, 1, input_image);
	}
}

void rotate_image(pixel_t* array, pixel_t* transformed_array, image_t image){

	for(int i = 0; i < image.height; i++){
		for(int j = 0; j < image.width; j++)
			transformed_array[(image.width-j-1) * image.height + i] = array[i * image.width + j];
	}
}

void rewrite_header(image_t image, FILE* input_image){
	fseek(input_image, 18, SEEK_SET);
	fwrite(&image.height, sizeof(int), 1, input_image);
	fwrite(&image.width, sizeof(int), 1, input_image);
}


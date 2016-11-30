#include <stdio.h>
#include <stdlib.h>
#include "../include/rotate.h"
#include "../include/image.h"

void rotate_image(pixel_t* array, pixel_t* transformed_array, image_t header){
	for(int i = 0; i < header.height; i++){
		for(int j = 0; j < header.width; j++)
			transformed_array[(header.width-j-1) * header.height + i] = array[i * header.width + j];
	}
}

void rewrite_header(image_t image, FILE* input_image){
	fseek(input_image, 18, SEEK_SET);
	fwrite(&image.height, sizeof(int), 1, input_image);
	fwrite(&image.width, sizeof(int), 1, input_image);
}

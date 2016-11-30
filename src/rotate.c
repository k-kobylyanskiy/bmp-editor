#include <stdio.h>
#include <stdlib.h>
#include "../include/rotate.h"
#include "../include/image.h"

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

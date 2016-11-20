#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/image.h"
#include <errno.h>
#include <string.h>

void read_array();
void print_color();

int main() {
	
	pixel_t pixel = {0,0,0};

	int c;
	int size[2];
	int bps;
	int offset;
	FILE* input_image = fopen("res/image.bmp", "r+b");

	if(input_image == NULL){
		printf("cannot open file\n");
		return 1;
	}
	
	fseek(input_image, 18, SEEK_SET);
	fread(size, sizeof(int), 2, input_image);


	printf("pixel has size of %ld bytes\n", sizeof(pixel_t));
	pixel_t* pixel_array = malloc(size[0] * size[1] * sizeof(pixel_t));
	pixel_t* transformed_array = malloc(size[0] * size[1] * sizeof(pixel_t));

	image_t image = {.height = size[1], .width = size[0], .pixel_buffer = pixel_array};

	fseek(input_image, 28, SEEK_SET);
	fread(&bps, sizeof(int), 1, input_image);
	
	fseek(input_image, 10, SEEK_SET);
	fread(&offset, sizeof(int), 1, input_image);

	printf("array of pixels begin with %d byte\n", offset);  
	printf("bps is %d bit per pixel\n", bps);  
	printf("width is %d pixels, height is %d pixels\n", image.width, image.height);  

	read_array(pixel_array, input_image, image, offset);
	print_color(pixel_array, transformed_array, image);


	fseek(input_image, offset, SEEK_SET);
	c = fwrite(transformed_array, 3, image.width * image.height, input_image);
	printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
	printf("%d\n", c);
	fclose(input_image);
	return 0;
}

void read_array(pixel_t* array, FILE* input_image, image_t image, int offset){
	fseek(input_image, offset, SEEK_SET);
	/*printf("going to read %d pixels\n", image.width * image.height);*/
	fread(array, 3, image.width * image.height, input_image);
}

void print_color(pixel_t* array, pixel_t* transformed_array, image_t image){

	
	for(int i = 0; i < image.height; i++){
		//printf("(%d;%d;%d)\n", array[i].red, array[i].green, array[i].blue);
		for(int j = 0; j < image.width; j++){

			transformed_array[(image.height-j-1) * image.height + i].blue = array[i * image.height + j].blue;
			transformed_array[(image.height-j-1) * image.height + i].green = array[i * image.height + j].green;
			transformed_array[(image.height-j-1) * image.height + i].red = array[i * image.height + j].red;
		//	printf("(%d;%d;%d)\n", transformed_array[(image.height-j-1) * image.height + i].red, transformed_array[(image.height-j-1) * image.height + i].green, transformed_array[(image.height-j-1) * image.height + i].blue);
		}
	}
	int n = 40;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
	//		printf("1 - (%d;%d;%d)\n", array[i].red, array[i].green, array[i].blue);
		}
	//	printf("\n");
	}
}


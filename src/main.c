#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/image.h"

void read_array();
void print_color();

int main() {
	
	pixel_t pixel = {0,0,0};
	
	int size[2];
	int bps;
	int offset;
	FILE* input_image = fopen("res/image.bmp", "rwb");

	if(input_image == NULL){
		printf("cannot open file\n");
		return 1;
	}
	
	fseek(input_image, 18, SEEK_SET);
	fread(size, sizeof(int), 2, input_image);


	printf("pixel has size of %ld bytes\n", sizeof(pixel_t));
	pixel_t* pixel_array = malloc(size[0] * size[1] * sizeof(pixel_t));
	image_t image = {.height = size[1], .width = size[0], .pixel_buffer = pixel_array};

	fseek(input_image, 28, SEEK_SET);
	fread(&bps, sizeof(int), 1, input_image);
	
	fseek(input_image, 10, SEEK_SET);
	fread(&offset, sizeof(int), 1, input_image);

	printf("array of pixels begin with %d byte\n", offset);  
	printf("bps is %d bit per pixel\n", bps);  
	printf("width is %d pixels, height is %d pixels\n", image.width, image.height);  

	read_array(pixel_array, input_image, image, 139);

	return 0;
}

void read_array(pixel_t* array, FILE* input_image, image_t image, int offset){
	fseek(input_image, offset, SEEK_SET);
	/*printf("going to read %d pixels\n", image.width * image.height);*/
	fread(array, 3, image.width * image.height, input_image);
	print_color(array);
}

void print_color(pixel_t* array){
	for(int i = 0; i < 160000; i++)
		printf("(%d;%d;%d)\n", array[i].red, array[i].green, array[i].blue);
}


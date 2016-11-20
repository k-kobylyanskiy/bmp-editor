#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/image.h"

void read_pixel();

int main() {
	
	pixel_t pixel = {0,0,0};
	
	int size[2];
	int bps;
	int offset;
	FILE* input_image = fopen("res/image.bmp", "rb");

	if(input_image == NULL){
		printf("cannot open file\n");
		return 1;
	}

	


	fseek(input_image, 18, SEEK_SET);
	fread(size, sizeof(int), 2, input_image);

	fseek(input_image, 28, SEEK_SET);
	fread(&bps, sizeof(int), 1, input_image);
	
	fseek(input_image, 10, SEEK_SET);
	fread(&offset, sizeof(int), 1, input_image);

	printf("array of pixels begin with %d byte\n", offset);  
	printf("bps is %d bit per pixel\n", bps);  
	printf("width is %d pixels, height is %d pixels\n", size[0], size[1]);  

	read_pixel(pixel, input_image, 139);

	return 0;
}

void read_pixel(pixel_t pixel, FILE* input_image, int offset){
	unsigned char pixel_r;
	fseek(input_image, offset, SEEK_SET);
	fread(&pixel_r, 1, 1, input_image);
	printf("pixels is %d \n", pixel_r);
	return;
}

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <strings.h>
#include "../include/image.h"
#include "../include/open.h"
#include "../include/rotate.h"

int main(int argc, char* argv[]) {

	int litter;
	image_t image;
	FILE* input_image; 

	input_image = open_image(argv[1]);
	image = open_header(input_image);

	litter = image.width % 4;
	read_array(image.pixel_buffer, input_image, image, OFFSET, litter);

	pixel_t* transformed_array = malloc(image.width * image.height * sizeof(pixel_t));
	
	rotate_image(image.pixel_buffer, transformed_array, image);
	rewrite_header(image, input_image);

	fseek(input_image, OFFSET, SEEK_SET);
	for(int i = 0; i < image.height; i++){
		fwrite((transformed_array + i * image.width), 3, image.width, input_image);
		fwrite(&litter, litter, 1, input_image);
	}
	fclose(input_image);
	return 0;
}


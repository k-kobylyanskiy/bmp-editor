#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <strings.h>
#include "../include/image.h"
#include "../include/open.h"
#include "../include/rotate.h"

int main(int argc, char* argv[]) {

	int choice;
	int litter;
	image_t header;
	FILE* input_image; 

	input_image = open_image(argv[1]);
	header = open_header(input_image);
	
	litter = header.width % 4;
	read_array(header.pixel_buffer, input_image, header, litter);
	pixel_t* transformed_array = malloc(header.width * header.height * sizeof(pixel_t));

	printf("Please, enter whether you want to totate image(0) or filter(1)?\n"); 
	scanf("%d",&choice);

	if(choice){
		printf("Sorry\n"); 
		exit(0);
	} else {
		rotate_image(header.pixel_buffer, transformed_array, header);
		rewrite_header(header, input_image);
	}

	write_image(input_image, header, transformed_array);

	return 0;
}


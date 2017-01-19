#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"


void filter(pixel_t* array, pixel_t* transformed_array, image_t header){

	int remainder;
	int count;
	count = header.width * header.height /4 * 3; 
	remainder = header.width * header.height % 4;

	printf("Pixel  count: %d, pixel will not be  filtered: %d\n", count, remainder); 
	
}

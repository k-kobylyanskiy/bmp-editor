#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

unsigned char sat(unsigned char x) {
	if (x < 256) return x; return 255;
}

pixel_t sepia_one(pixel_t old){

	pixel_t pixel;

	const float c[3][3] = {
	{ .393f, .769f, .189f },
	{ .349f, .686f, .168f },
	{ .272f, .543f, .131f } };
	
	pixel.red = sat(old.red * c[0][0] + old.green * c[0][1] + old.blue * c[0][2]);
	pixel.green = sat(old.red * c[1][0] + old.green * c[1][1] + old.blue * c[1][2]);
	pixel.blue = sat(old.red * c[2][0] + old.green * c[2][1] + old.blue * c[2][2]);

	return pixel;
}

void filter(pixel_t* array, pixel_t* transformed_array, image_t header){

	for(int i = 0; i < header.height; i++){
		for(int j = 0; j < header.width; j++)
			transformed_array[i * header.width + j] = sepia_one(array[i * header.width + j]);
	}
}

#ifndef _IMAGE_

#define _IMAGE_

typedef struct {
	unsigned char green, red, blue;
} pixel_t;

typedef struct { 
	int width, height;
	pixel_t* pixel_buffer;
} image_t;

#endif

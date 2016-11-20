typedef struct {
	unsigned char red, green, blue;
} pixel_t;

typedef struct { 
	int width, height;
	pixel_t* pixel_buffer;
} image_t;


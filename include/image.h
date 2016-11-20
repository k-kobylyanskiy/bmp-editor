typedef struct {
	unsigned char blue, green, red;
} pixel_t;

typedef struct { 
	int width, height;
	pixel_t* pixel_buffer;
} image_t;


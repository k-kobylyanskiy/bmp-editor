#define OFFSET 138

FILE* open_image(char*);
image_t open_header(FILE*);
void read_array();
void write_image(FILE*, image_t, pixel_t*);

typedef enum {
	READ_OK = 0,
	READ_INVALID_SIGNATURE,
	READ_INVALID_BITS,
	READ_INVALID_HEADER
} read_error_code_t;

#define OFFSET 138

FILE* open_image(char*);
image_t open_header(FILE*);
void read_array();
image_t check_filetype(FILE*, image_t);
void write_image(FILE*, image_t, pixel_t*);

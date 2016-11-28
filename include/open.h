FILE* open_image(char*);

typedef enum {
	READ_OK = 0,
	READ_INVALID_SIGNATURE,
	READ_INVALID_BITS,
	READ_INVALID_HEADER
} read_error_code_t;

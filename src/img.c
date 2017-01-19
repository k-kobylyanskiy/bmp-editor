#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct pixel_t {
	char b, g, r;
} pixel_t;
#pragma pack(pop)

typedef struct image_t {
	uint32_t width, height;
	pixel_t* pixels;
} image_t;

image_t* new_image( uint32_t const width, uint32_t const height ) {
	image_t* new_img = (image_t*)malloc( sizeof(image_t) );
	new_img->pixels = (pixel_t*)malloc( sizeof(pixel_t) * width * height);

	new_img->width = width; new_img->height = height;

	return new_img;
}

void image_free( image_t* img ) {
	free(img->pixels);
	free(img);
}

pixel_t* get_pixel( const image_t* const img, const uint32_t x, const uint32_t y ) {
	return img-> pixels + img-> width * y + x ;
}

void image_rotation( const image_t* const src_img, image_t* const dest_img ) {
	uint32_t i, j;
	uint32_t cols = src_img-> width;
	uint32_t rows = src_img-> height;

	pixel_t* src_pixels = src_img-> pixels;
	pixel_t* dest_pixels = dest_img-> pixels;

	for( i = 0; i < rows; i++ ) {
		uint32_t current_row = i * cols;
		uint32_t current_col = rows - 1 - i;

		for( j = 0; j < cols; j++ ) 
			dest_pixels[j * rows + current_col] = src_pixels[current_row + j];
	}
}

unsigned char sat( uint64_t x ) {
	return ( x < 256 ) ? x : 255 ;
}

float char_to_float[256];

static void fill_char_to_float( void ) {
	size_t i = 0, size = 256;

	for( i = 0; i < size; i++ ) 
		char_to_float[i] = (float)i;	
}

void compute_four_pixels( char* components, float c[3][12], float* result );

static void duplicate_col( float matrix[3][12], size_t src_col, size_t dest_col, size_t count ) {
	size_t i;
	for( i = 0; i < count; i++ ) {
		matrix[0][dest_col + i] = matrix[0][src_col];
		matrix[1][dest_col + i] = matrix[1][src_col];
		matrix[2][dest_col + i] = matrix[2][src_col];
	}
}

static void create_multiplier( float multiplier[3][12] ) {
	size_t i;
	for( i = 0; i < 3; i++ ) {
		duplicate_col( multiplier, 0, 3 + i * 3, 1 );
		duplicate_col( multiplier, 1, 4 + i * 3, 1 );
		duplicate_col( multiplier, 2, 5 + i * 3, 1 );
	}	
}

static void write_result0( float result[12], char* components ) {
	size_t i;
	for( i = 0; i < 12; i++ ) 
		components[i] = sat( (uint32_t)result[i] );
}

void native_sepia( image_t* img ) {
	size_t i;
	pixel_t* pixels = img-> pixels;
	unsigned long pixels_count = ( img-> width * img-> height ) / 4;
	float result[12];
	float c[3][12] = {
		{ .393f, .349f, .272f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f },
		{ .769f, .686f, .543f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f },
		{ .189f, .168f, .131f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f, .0f }
	};

	fill_char_to_float();
	create_multiplier( c );

	for( i = 0; i < pixels_count; i++ ) {
		compute_four_pixels( (char*)pixels, c, result );
		write_result0( result, (char*)pixels );

		pixels = pixels + 4;
	}
}

static void sepia_one_pixel( pixel_t* const pixel ) {
	static const float c[3][3] = {
		{ .393f, .769f, .189f },
		{ .349f, .686f, .168f },
		{ .272f, .543f, .131f }
	};

	const pixel_t old = *pixel;

	pixel-> b = sat( old.r * c[0][0] + old.g * c[0][1] + old.b * c[0][2] );
	pixel-> g = sat( old.r * c[1][0] + old.g * c[1][1] + old.b * c[1][2] );
	pixel-> r = sat( old.r * c[2][0] + old.g * c[2][1] + old.b * c[2][2] );
}

void sepia( const image_t* const img ) {
	uint32_t x,y;

	for( y = 0; y < img-> height; y++ )
		for( x = 0; x < img-> width; x++ )
			sepia_one_pixel( get_pixel(img, x, y) );
}



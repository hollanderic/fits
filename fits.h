
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


typedef char

class  Fits {
	FILE *infile;
	uint8_t *databuffer;
	uint32_t bpp;
	uint32_t width;
	uint32_t height;

public:
	uint32_t fromFile(const char* fname);
};



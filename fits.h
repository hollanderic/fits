
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#define NUM_RECORDS 36

class  Fits {


public:
	Fits();
	~Fits();
	int32_t getWidth() {return width_;};
	int32_t getHeight() {return height_;};
	int32_t getDepth() {return bpp_;};
	char* getBuffer() {return (char*)databuffer_;};


	int32_t fromFile(const char* fname);

	FILE *infile;

private:
	char records_[NUM_RECORDS][80];
	uint8_t *databuffer_;
	uint32_t datasize_;
	uint32_t bpp_;
	uint32_t width_;
	uint32_t height_;

};



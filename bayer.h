#pragma once
#include <memory>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class BayerArray {
	std::unique_ptr<unsigned char> databuffer;
	uint32_t datasize;  //size of data in bytes;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
public:
	BayerArray(uint32_t width, uint32_t height, uint32_t pixsize);
	BayerArray(uint32_t **in);

	uint8_t get(uint32_t n);
	uint16_t get(uint32_t x,uint32_t y);
	uint32_t getSize(void);
};
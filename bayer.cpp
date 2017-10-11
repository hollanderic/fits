#include "bayer.h"
using namespace std;

BayerArray::BayerArray(uint32_t w, uint32_t h, uint32_t pixsize) {
	datasize = w*h*pixsize;
	width = w;
	height = h;
	bpp = pixsize;

	databuffer = std::unique_ptr<unsigned char>(new unsigned char [datasize]); //  new uint8_t [datasize];

	for (uint i=0; i < datasize; i++ ) {
		databuffer.get()[i] = (unsigned char)(i % 256);
	}
}

BayerArray::BayerArray(uint32_t **in) {
	printf("begin-%p  end-%p\n",std::begin(in), std::end(in));

}

uint8_t BayerArray::get(uint32_t n) {
	return databuffer.get()[n];
}

uint16_t BayerArray::get(uint32_t x, uint32_t y) {
	return *(uint16_t*)&(databuffer.get()[ y*width*bpp + x*bpp]);
}

uint32_t BayerArray::getSize(void) {
	return sizeof(databuffer);
}

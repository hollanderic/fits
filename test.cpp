
#include "bayer.h"

#include <stdio.h>


int main(int argc, const char **argv) {
	uint32_t x[][4] = {{1,2,3,4},{5,6,7,8}};

	printf("begin-%p  end-%p\n",std::begin(x), std::end(x));

	BayerArray bay(100,100,2);
	BayerArray bay2((uint32_t**)x);

	printf("0,0 = %u\n",bay.get(0,0));
	printf("10,10 = %u\n",bay.get(0,10));

	printf("size=%u\n",bay.getSize());

}
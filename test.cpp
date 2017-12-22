
#include "fits.h"

#include <stdio.h>


int main(int argc, const char **argv) {
	//std::shared_ptr<Fits> f;
	auto f=Fits::Open("300.fit");
	printf("use count = %ld\n",f.use_count());
	return 0;

}
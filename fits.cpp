
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fits.h"


/* TODOS

	Bury constructor and use refcounting
		may be challenging when outside entities want to use underlying data.

*/
Fits::Fits(void){};
Fits::~Fits(void){};



#define PROC_TOKEN(tkn,field) \
	if(!strncmp(token,tkn,strlen(tkn))) { \
		token=strtok(NULL,delim2); \
		if (token) field = (uint32_t)atoi(token); \
		continue; \
	}
int32_t Fits::fromFile(const char* fname){

	FILE *infile;
	const char delim[2]="=";
	const char delim2[3]="/\0";
	char * token;

	infile = fopen(fname,"rb");
	if (infile < 0) return -1;

	int32_t n = fread(records_,sizeof(records_),1,infile);
	for (int i=0; i < NUM_RECORDS; i++) {
		records_[i][79] = 0;
		printf("%s\n",records_[i]);
		token=strtok(records_[i],delim);

		PROC_TOKEN("BITPIX",bpp_)
		PROC_TOKEN("NAXIS1",width_)
		PROC_TOKEN("NAXIS2",height_)
		if(!strncmp(token,"END",3)) break;
	}
	datasize_ = width_ * height_ * (bpp_ / 8);

	databuffer_ = (uint8_t*)malloc(datasize_);
	n = fread(databuffer_, sizeof(uint8_t), datasize_, infile);
	fclose(infile);
	if (n == datasize_)
		printf("read %d bytes from file\n",datasize_);
	else
		printf("file read failed - read %d bytes\n",n);
	return 0;
}
#if 0
int main(int argc, char** argv){
	Fits fit;
	fit.fromFile(argv[1]);
	return 0;
}

#endif

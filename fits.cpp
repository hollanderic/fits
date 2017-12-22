
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
std::shared_ptr<Fits> Fits::Open(const char* fname){

	FILE *infile;
	const char delim[2]="=";
	const char delim2[3]="/\0";
	char * token;

	std::shared_ptr<Fits> newfit;
	newfit.reset(new Fits());

	infile = fopen(fname,"rb");
	if (infile < 0) return NULL;

	int32_t n = fread(newfit->records_,sizeof(newfit->records_),1,infile);
	for (int i=0; i < NUM_RECORDS; i++) {
		newfit->records_[i][79] = 0;
		printf("%s\n",newfit->records_[i]);
		token=strtok(newfit->records_[i],delim);

		PROC_TOKEN("BITPIX",newfit->bpp_)
		PROC_TOKEN("NAXIS1",newfit->width_)
		PROC_TOKEN("NAXIS2",newfit->height_)
		if(!strncmp(token,"END",3)) break;
	}
	newfit->datasize_ = newfit->width_ * newfit->height_ * (newfit->bpp_ / 8);

	newfit->databuffer_ = (uint8_t*)malloc(newfit->datasize_);
	n = fread(newfit->databuffer_, sizeof(uint8_t), newfit->datasize_, infile);
	fclose(infile);
	if (n == newfit->datasize_)
		printf("read %d bytes from file\n",newfit->datasize_);
	else
		printf("file read failed - read %d bytes\n",n);
	return std::move(newfit);
}

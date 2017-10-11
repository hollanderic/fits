#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define bool uint32_t;

char records[36][80];
char *test;

typedef struct {
	uint32_t bpp;
	uint32_t width;
	uint32_t height;
} fits_header_t;

fits_header_t fheader;
uint16_t *databuff;

#define IS_EVEN(x) (!(x%2))
#define IS_ODD(x) (x%2)
#define EDGE_CHECK(x, y) \
	if ((x == 0) || (y == 0)) return 0; \
	if ((x == (fheader.width -1)) || (y == (fheader.height - 1))) return 0;

static inline uint32_t idx(uint32_t x, uint32_t y) {
	return (fheader.width*y + x);
}

uint32_t isRedCell(uint32_t x, uint32_t y);

uint32_t isRedCell(uint32_t x, uint32_t y) {
	return (IS_EVEN(x) && IS_EVEN(y));
}
uint32_t isGreenCell(uint32_t x, uint32_t y) {
	return (IS_EVEN(x) && IS_ODD(y)) || (IS_ODD(x) && IS_EVEN(y));
}
uint32_t isBlueCell(uint32_t x, uint32_t y) {
	return (IS_ODD(x) && IS_ODD(y));
}
/*
rgrgrg
gbgbgb
rgrgrg
gbgbgb
*/
//get Red value for red cell
uint32_t rcell_Red_bilinear(uint32_t x, uint32_t y) {
	EDGE_CHECK(x,y)
	return (uint32_t)databuff[idx(x,y)];
}
//get Red value for green cell
uint32_t gcell_Red_bilinear(uint32_t x, uint32_t y) {
	EDGE_CHECK(x,y)
	if (IS_EVEN(y)) return (databuff[idx(x,y)] + databuff[idx(x,y)]) >> 1;
	return  (databuff[idx(x,y-1)] + databuff[idx(x,y+1)]) >> 1;
}
//get red value for red cell
uint32_t bcell_Red_bilinear(uint32_t x, uint32_t y) {
	EDGE_CHECK(x,y)
	return (uint32_t) ( databuff[idx(x-1,y-1)] + databuff[idx(x+1,y-1)] + \
						databuff[idx(x-1,y+1)] + databuff[idx(x+1,y+1)] ) >> 2;
}


uint32_t getRed(uint32_t x, uint32_t y){
	if (isRedCell(x,y)) return rcell_Red_bilinear(x,y);
	if (isBlueCell(x,y)) return bcell_Red_bilinear(x,y);
	return gcell_Red_bilinear(x,y);
}



#define PROC_TOKEN(tkn,field) \
	if(!strncmp(token,tkn,strlen(tkn))) { \
		token=strtok(NULL,delim2); \
		if (token) fheader.field = (uint32_t)atoi(token); \
		continue; \
	}

int main(int argc, const char **argv) {

	FILE *infile;
	FILE *outfile;
	const char delim[2]="=";
	const char delim2[3]="/\0";

	char * token;
	infile = fopen(argv[1],"rb");
	outfile = fopen(argv[2],"w+");
	fread(records,sizeof(records),1,infile);
	for (int i=0; i<36; i++) {
		records[i][79]=0;
		printf("%s\n",records[i]);
		token=strtok(records[i],delim);
		PROC_TOKEN("BITPIX",bpp)
		PROC_TOKEN("NAXIS1",width)
		PROC_TOKEN("NAXIS2",height)
		if(!strncmp(token,"END",3)) break;
	}
	printf("bpp = %u\n",fheader.bpp);
	printf("width = %u\n",fheader.width);
	printf("height = %u\n",fheader.height);
	uint32_t datasize = fheader.width * fheader.height * fheader.bpp/8;
	uint8_t *dataptr = malloc(datasize);
	fread(dataptr,sizeof(uint8_t),datasize,infile);


	databuff = (uint16_t*)dataptr;

	for (int x=0; x< datasize/2; x++) {
		uint16_t temp = databuff[x];
		databuff[x] = (((temp << 8)&0xff00) + (temp >>8))-32768;
		//printf("%x  %x\n",temp,databuff[x]);
	}


	for (int y=0; y< fheader.height; y++) {
		for(int x=0; x<fheader.width; x++) {
			uint16_t point = databuff[idx(x,y)];//getRed(x,y);
			//printf("%04x\n",point);
			fwrite(&point,sizeof(uint16_t),1,outfile);
		}
	}


	free(dataptr);
	fclose(infile);
	fclose(outfile);
}



typedef struct bmp_meta {
	u8 bmp_head[54];
	int* bmp_width;
	int* bmp_height;
	int rowsize;
}bmp_meta;

void readBMPhead (bmp_meta *pic);
void readBMProw (bmp_meta *pic,u32 *srcBufferU32);
void writeBMPhead (bmp_meta *pic);
void writeBMProw (bmp_meta *pic,u32 *desBufferU32);
void closefile() ;

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "integer.h"
#include "string.h"
#include "ff.h"
#include "SDoperation.h"
static FIL filsrc;
static FIL fildes;
static FATFS fatfs;

void readBMPhead(bmp_meta *pic) {

	UINT br;
	FRESULT status;
	BYTE work[FF_MAX_SS];
	status = f_mount(&fatfs, "", 0);
	if (status != FR_OK) {
		xil_printf("volume is not FAT format\n");

		f_mkfs("", FM_FAT32, 0, work, sizeof work);
		f_mount(&fatfs, "", 0);
	}

	f_open(&filsrc, "lena.bmp", FA_READ);
	f_lseek(&filsrc, 0);
	f_read(&filsrc, pic->bmp_head, 54, &br);
	xil_printf("Bmp head: \n\r");
	pic->bmp_width = (UINT *) (pic->bmp_head + 0x12);
	pic->bmp_height = (UINT *) (pic->bmp_head + 0x16);
	pic->rowsize = floor((24 * (*(pic->bmp_width)) + 31) / 32) * 4;
	xil_printf("\n width = %d, height = %d, row size = %d bytes \n\r",
			*(pic->bmp_width), *(pic->bmp_height), pic->rowsize);
	f_sync(&filsrc);
}

void readBMProw(bmp_meta *pic, u32 *srcBufferU32) {
	UINT br;
	int i;
	u8 srcBufferU8[3000];
	f_read(&filsrc, srcBufferU8, pic->rowsize, &br);
	for (i = 0; i < (pic->rowsize) / 4; i++) {
		*(srcBufferU32+i) = srcBufferU8[4 * i+3] << 24
				| srcBufferU8[4 * i + 2] << 16 | srcBufferU8[4 * i + 1] << 8
				| srcBufferU8[4 * i+0];
	}
	f_sync(&filsrc);
}

void writeBMPhead(bmp_meta *pic) {

	UINT bw;
	FRESULT status;
	f_open(&fildes, "lena_sdpl_copy_delay.bmp", FA_CREATE_ALWAYS | FA_WRITE);
	f_lseek(&fildes, 0);
	f_write(&fildes, pic->bmp_head, 54, &bw);
	f_sync(&fildes);
}

void writeBMProw(bmp_meta *pic, u32 *desBufferU32) {
	UINT bw;
	f_write(&fildes, desBufferU32, (pic->rowsize), &bw);
	f_sync(&fildes);

}

void closefile() {
	f_close(&filsrc);
	f_close(&fildes);
}

/******************************************************************************
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 ******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <math.h>
#include "platform.h"
#include "xil_printf.h"
#include "integer.h"
#include "string.h"
#include "sobel.h"
#include "ff.h"


static u8 RedBuffer[300000];
static u8 GreenBuffer[300000];
static u8 BlueBuffer[300000];
static u8 GrayBuffer[300000];
static u8 Sobel_h_res_Buffer[300000];
static u8 Sobel_v_res_Buffer[300000];
static u8 Contour_Buffer[300000];
static u8 zero = 0X0;
static u8* ZeroAddr = &zero;

static FATFS fatfs;
static struct bmp_meta pic1;

void load_sd_bmp() {

	FIL fil;
	UINT br;
	int i;
	int j;
	BYTE work[FF_MAX_SS];
	FRESULT status;
	//在 FatFs 模块上注册 /注销一个工作区 (文件系统对象 )
	status = f_mount(&fatfs, "", 0);
	if (status != FR_OK) {
		xil_printf("volume is not FAT format\n");
		//格式化SD卡
		f_mkfs("", FM_FAT32, 0, work, sizeof work);
		f_mount(&fatfs, "", 0);
	}

	//打开文件
	f_open(&fil, "lena.bmp", FA_READ);

	//移动文件读写指针到文件开头
	f_lseek(&fil, 0);

	//读取 BMP 文件d
	f_read(&fil, pic1.bmp_head, 54, &br);
	xil_printf("test.bmp head: \n\r");

	//打印 BMP 图片分辨率和大小
	pic1.bmp_width = (UINT *) (pic1.bmp_head + 0x12);
	pic1.bmp_height = (UINT *) (pic1.bmp_head + 0x16);
	pic1.bmp_size = (UINT *) (pic1.bmp_head + 0x22);

	pic1.rowsize = floor((24 * (*(pic1.bmp_width)) + 31) / 32) * 4;

	xil_printf("\n width = %d, height = %d, size = %d bytes , row size = %d bytes \n\r",
			*(pic1.bmp_width), *(pic1.bmp_height), *(pic1.bmp_size),pic1.rowsize);

	//读出图片，写入 DDR
	for (i = *(pic1.bmp_height) - 1; i >= 0; i--) {
		for (j = 0; j < *(pic1.bmp_width); j++) {
			f_read(&fil, BlueBuffer + i * (*(pic1.bmp_width)) +j, 1, &br);
			f_read(&fil, GreenBuffer + i * (*(pic1.bmp_width)) + j, 1, &br);
			f_read(&fil, RedBuffer + i * (*(pic1.bmp_width)) + j, 1, &br);
		}
		f_lseek(&fil,  54+pic1.rowsize*(*(pic1.bmp_height)-i));
	}
		f_close(&fil);

}

void write_sd_bmp()

{
	FIL fil;
	int i;
	int j;
	int k;
	UINT bw;

	//打开文件
	f_open(&fil, "copy2.bmp", FA_CREATE_ALWAYS | FA_WRITE);

	//移动文件读写指针到文件开头
	f_lseek(&fil, 0);

	//读取 BMP 文件头
	f_write(&fil, (void*) (pic1.bmp_head), 54, &bw);

	for (i = *(pic1.bmp_height) - 1; i >= 0; i--) {

		for (j = 0; j < *(pic1.bmp_width); j++) {
			f_write(&fil, BlueBuffer + i * (*(pic1.bmp_width)) + j, 1, &bw);
			f_write(&fil, GreenBuffer + i * (*(pic1.bmp_width)) + j, 1, &bw);
			f_write(&fil, RedBuffer + i * (*(pic1.bmp_width)) + j, 1, &bw);
		}
		for (k=0;k < pic1.rowsize-3*(* (pic1.bmp_width)); k++)
			f_write(&fil, ZeroAddr, 1, &bw);
	}
	f_close(&fil);
}

void write_gray_bmp(u8*gray,char* PATH)

{
	FIL fil;
	int i;
	int j;
	int k;
	UINT bw;

	//打开文件
	f_open(&fil,PATH, FA_CREATE_ALWAYS | FA_WRITE);

	//移动文件读写指针到文件开头
	f_lseek(&fil, 0);

	//读取 BMP 文件头
	f_write(&fil, (void*) (pic1.bmp_head), 54, &bw);

	for (i = *(pic1.bmp_height) - 1; i >= 0; i--) {

		for (j = 0; j < *(pic1.bmp_width); j++) {
			f_write(&fil, gray + i * (*(pic1.bmp_width)) + j, 1, &bw);
			f_write(&fil, gray + i * (*(pic1.bmp_width)) + j, 1, &bw);
			f_write(&fil, gray + i * (*(pic1.bmp_width)) + j, 1, &bw);
		}
		for (k=0;k < pic1.rowsize-3*(* (pic1.bmp_width)); k++)
			f_write(&fil, ZeroAddr, 1, &bw);
	}
	f_close(&fil);
}


int main() {
	init_platform();

	print("Hello World\n\r");

	load_sd_bmp();

	write_sd_bmp();

   sobelFilter(RedBuffer,GreenBuffer,BlueBuffer,GrayBuffer, Sobel_h_res_Buffer, Sobel_v_res_Buffer,Contour_Buffer, *(pic1.bmp_width), *(pic1.bmp_height));
   write_gray_bmp(GrayBuffer,"gray.bmp");
   write_gray_bmp(Sobel_h_res_Buffer,"sobelH.bmp");
   write_gray_bmp(Sobel_v_res_Buffer,"sobelV.bmp");
   write_gray_bmp(Contour_Buffer,"Contour2. bmp");
   print("Successfully ran Hello World application");
	cleanup_platform();
	return 0;
}

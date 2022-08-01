/*
 * Copyright 2018 Pedro Melgueira
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "xil_types.h"

#ifndef SOBEL_H
#define SOBEL_H


int rgbToGray(u8 *red, u8 *green, u8 *blue, u8 *gray, int width, int height);
void makeOpMem(u8 *buffer, int buffer_size, int width, int cindex, u8 *op_mem);
int convolution(u8 *X, int *Y, int c_size);
void itConv(u8 *buffer, int buffer_size, int width, int *op, u8 *res) ;
void contour(u8 *sobel_h, u8 *sobel_v, int gray_size, u8 *contour_img) ;
int sobelFilter(u8 *red, u8 *green,  u8 *blue , u8 *gray, u8 *sobel_h_res, u8 *sobel_v_res, u8 *contour_img, int width, int height);

struct bmp_meta {
	u8 bmp_head[54];
	int* bmp_width;
	int* bmp_height;
	int* bmp_size;
	int rowsize;
};



#endif


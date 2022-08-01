
/*******************************************************************
*
* CAUTION: This file is automatically generated by HSI.
* Version: 2022.1
* DO NOT EDIT.
*
* Copyright (C) 2010-2022 Xilinx, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT 

* 
* Description: Driver configuration
*
*******************************************************************/

#include "xparameters.h"
#include "xvprocss.h"

/*
* Subsystem Instance: <rgb_to_yuv422>
*   - List of sub-cores included in the subsystem
*/

#define XPAR_RGB_TO_YUV422_CSC_PRESENT	 1
#define XPAR_RGB_TO_YUV422_HCR_PRESENT	 1
#define XPAR_RGB_TO_YUV422_HSC_PRESENT	 1
#define XPAR_RGB_TO_YUV422_LTR_PRESENT	 1
#define XPAR_RGB_TO_YUV422_RESET_SEL_AXIS_PRESENT	 1
#define XPAR_RGB_TO_YUV422_VIDEO_ROUTER_XBAR_PRESENT	 1
#define XPAR_RGB_TO_YUV422_VSC_PRESENT	 1


/*
* List of sub-cores excluded from the subsystem <rgb_to_yuv422>
*   - Excluded sub-core device id is set to 255
*   - Excluded sub-core base address is set to 0
*/

#define XPAR_RGB_TO_YUV422_RESET_SEL_AXI_MM_PRESENT 0
#define XPAR_RGB_TO_YUV422_RESET_SEL_AXI_MM_DEVICE_ID 255
#define XPAR_RGB_TO_YUV422_RESET_SEL_AXI_MM_BASEADDR 0

#define XPAR_RGB_TO_YUV422_AXI_VDMA_0_PRESENT 0
#define XPAR_RGB_TO_YUV422_AXI_VDMA_0_DEVICE_ID 255
#define XPAR_RGB_TO_YUV422_AXI_VDMA_0_BASEADDR 0

#define XPAR_RGB_TO_YUV422_V_DEINTERLACER_0_PRESENT 0
#define XPAR_RGB_TO_YUV422_V_DEINTERLACER_0_DEVICE_ID 255
#define XPAR_RGB_TO_YUV422_V_DEINTERLACER_0_BASEADDR 0

#define XPAR_RGB_TO_YUV422_V_VCRESAMPLER_0_PRESENT 0
#define XPAR_RGB_TO_YUV422_V_VCRESAMPLER_0_DEVICE_ID 255
#define XPAR_RGB_TO_YUV422_V_VCRESAMPLER_0_BASEADDR 0

#define XPAR_RGB_TO_YUV422_V_VCRESAMPLER_1_PRESENT 0
#define XPAR_RGB_TO_YUV422_V_VCRESAMPLER_1_DEVICE_ID 255
#define XPAR_RGB_TO_YUV422_V_VCRESAMPLER_1_BASEADDR 0




XVprocSs_Config XVprocSs_ConfigTable[XPAR_XVPROCSS_NUM_INSTANCES] =
{
	{
		XPAR_RGB_TO_YUV422_DEVICE_ID,
		XPAR_RGB_TO_YUV422_BASEADDR,
		XPAR_RGB_TO_YUV422_HIGHADDR,
		XPAR_RGB_TO_YUV422_TOPOLOGY,
		XPAR_RGB_TO_YUV422_SAMPLES_PER_CLK,
		XPAR_RGB_TO_YUV422_MAX_DATA_WIDTH,
		XPAR_RGB_TO_YUV422_NUM_VIDEO_COMPONENTS,
		XPAR_RGB_TO_YUV422_MAX_COLS,
		XPAR_RGB_TO_YUV422_MAX_ROWS,
		XPAR_RGB_TO_YUV422_DEINT_MOTION_ADAPTIVE,

		{
			XPAR_RGB_TO_YUV422_RESET_SEL_AXI_MM_PRESENT,
			XPAR_RGB_TO_YUV422_RESET_SEL_AXI_MM_DEVICE_ID,
			XPAR_RGB_TO_YUV422_RESET_SEL_AXI_MM_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_RESET_SEL_AXIS_PRESENT,
			XPAR_RGB_TO_YUV422_RESET_SEL_AXIS_DEVICE_ID,
			XPAR_RGB_TO_YUV422_RESET_SEL_AXIS_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_AXI_VDMA_0_PRESENT,
			XPAR_RGB_TO_YUV422_AXI_VDMA_0_DEVICE_ID,
			XPAR_RGB_TO_YUV422_AXI_VDMA_0_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_VIDEO_ROUTER_XBAR_PRESENT,
			XPAR_RGB_TO_YUV422_VIDEO_ROUTER_XBAR_DEVICE_ID,
			XPAR_RGB_TO_YUV422_VIDEO_ROUTER_XBAR_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_CSC_PRESENT,
			XPAR_RGB_TO_YUV422_CSC_DEVICE_ID,
			XPAR_RGB_TO_YUV422_CSC_S_AXI_CTRL_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_V_DEINTERLACER_0_PRESENT,
			XPAR_RGB_TO_YUV422_V_DEINTERLACER_0_DEVICE_ID,
			XPAR_RGB_TO_YUV422_V_DEINTERLACER_0_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_HCR_PRESENT,
			XPAR_RGB_TO_YUV422_HCR_DEVICE_ID,
			XPAR_RGB_TO_YUV422_HCR_S_AXI_CTRL_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_HSC_PRESENT,
			XPAR_RGB_TO_YUV422_HSC_DEVICE_ID,
			XPAR_RGB_TO_YUV422_HSC_S_AXI_CTRL_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_LTR_PRESENT,
			XPAR_RGB_TO_YUV422_LTR_DEVICE_ID,
			XPAR_RGB_TO_YUV422_LTR_S_AXI_CTRL_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_V_VCRESAMPLER_0_PRESENT,
			XPAR_RGB_TO_YUV422_V_VCRESAMPLER_0_DEVICE_ID,
			XPAR_RGB_TO_YUV422_V_VCRESAMPLER_0_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_V_VCRESAMPLER_1_PRESENT,
			XPAR_RGB_TO_YUV422_V_VCRESAMPLER_1_DEVICE_ID,
			XPAR_RGB_TO_YUV422_V_VCRESAMPLER_1_BASEADDR
		},
		{
			XPAR_RGB_TO_YUV422_VSC_PRESENT,
			XPAR_RGB_TO_YUV422_VSC_DEVICE_ID,
			XPAR_RGB_TO_YUV422_VSC_S_AXI_CTRL_BASEADDR
		},
	}
};


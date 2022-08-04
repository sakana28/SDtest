#include "xparameters.h"
#include "xil_exception.h"
#include "xstreamer.h"
#include "xil_cache.h"
#include "xllfifo.h"
#include "xstatus.h"
#include "SDoperation.h"
#include "sleep.h"

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define FIFO_DEV_ID	   	XPAR_AXI_FIFO_0_DEVICE_ID

#define WORD_SIZE 4			/* Size of words in bytes */

#undef DEBUG

/************************** Function Prototypes ******************************/

int XLlFifoPollingExample(XLlFifo *InstancePtr, u16 DeviceId);
int TxSendRow(XLlFifo *InstancePtr, bmp_meta *picsrc);
int RxReceiveRow(XLlFifo *InstancePtr, u32* DestinationAddr, bmp_meta *picsrc);

/************************** Variable Definitions *****************************/
/*
 * Device instance definitions
 */
XLlFifo FifoInstance;
u32 DestinationBuffer[800];


/*****************************************************************************/
/**
 *
 * Main function
 *
 * This function is the main entry of the Axi FIFO Polling test.
 *
 * @param	None
 *
 * @return
 *		- XST_SUCCESS if tests pass
 * 		- XST_FAILURE if fails.
 *
 * @note		None
 *
 ******************************************************************************/
int main() {
	int Status;

	xil_printf("--- Entering main() ---\n\r");

	Status = XLlFifoPollingExample(&FifoInstance, FIFO_DEV_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("Axi Streaming FIFO Polling Example Test Failed\n\r");
		xil_printf("--- Exiting main() ---\n\r");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran Axi Streaming FIFO Polling Example\n\r");
	xil_printf("--- Exiting main() ---\n\r");

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
 *
 * This function demonstrates the usage AXI FIFO
 * It does the following:
 *       - Set up the output terminal if UART16550 is in the hardware build
 *       - Initialize the Axi FIFO Device.
 *	- Transmit the data
 *	- Receive the data from fifo
 *	- Compare the data
 *	- Return the result
 *
 * @param	InstancePtr is a pointer to the instance of the
 *		XLlFifo component.
 * @param	DeviceId is Device ID of the Axi Fifo Device instance,
 *		typically XPAR_<AXI_FIFO_instance>_DEVICE_ID value from
 *		xparameters.h.
 *
 * @return
 *		-XST_SUCCESS to indicate success
 *		-XST_FAILURE to indicate failure
 *
 ******************************************************************************/
int XLlFifoPollingExample(XLlFifo *InstancePtr, u16 DeviceId) {
	XLlFifo_Config *Config;
	bmp_meta picsrc;
	int Status;
	int i;


	Status = XST_SUCCESS;

	/* Initialize the Device Configuration Interface driver */
	Config = XLlFfio_LookupConfig(DeviceId);
	if (!Config) {
		xil_printf("No config found for %d\r\n", DeviceId);
		return XST_FAILURE;
	}

	/*
	 * This is where the virtual address would be used, this example
	 * uses physical address.
	 */
	Status = XLlFifo_CfgInitialize(InstancePtr, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed\n\r");
		return Status;
	}

	/* Check for the Reset value */
	Status = XLlFifo_Status(InstancePtr); //check ISR
	XLlFifo_IntClear(InstancePtr, 0xffffffff);
	Status = XLlFifo_Status(InstancePtr);
	if (Status != 0x0) {
		xil_printf("\n ERROR : Reset value of ISR0 : 0x%x\t"
				"Expected : 0x0\n\r", XLlFifo_Status(InstancePtr));
		return XST_FAILURE;
	}
	/* Get metadata of Test Pic */
	readBMPhead(&picsrc);
	/* Write metadata to Copy Pic */
	writeBMPhead(&picsrc);

	xil_printf(" Start Transmission ....\n\r");
	for (i = 0; i < *(picsrc.bmp_height); i++) {
	/* Transmit the Data Stream */
	Status = TxSendRow(InstancePtr,&picsrc);
	if (Status != XST_SUCCESS) {
		xil_printf("Transmission of Data failed\n\r");
		return XST_FAILURE;
	}
    usleep(10);
	/* Receive the Data Stream */
	Status = RxReceiveRow(InstancePtr, DestinationBuffer, &picsrc);
	if (Status != XST_SUCCESS) {
		xil_printf("Receiving data failed");
		return XST_FAILURE;
	}
	}
	closefile() ;
	return Status;
}

/*****************************************************************************/
/**
 *
 * TxSend routine, It will send the requested amount of data at the
 * specified addr.
 *
 * @param	InstancePtr is a pointer to the instance of the
 *		XLlFifo component.
 *
 * @param	SourceAddr is the address where the FIFO stars writing
 *
 * @return
 *		-XST_SUCCESS to indicate success
 *		-XST_FAILURE to indicate failure
 *
 * @note		None
 *
 ******************************************************************************/
int TxSendRow(XLlFifo *InstancePtr, bmp_meta *picsrc) {

	int i;
	u32 RowBuffer[(picsrc ->rowsize)/ WORD_SIZE];

	/* read a row of data from SD card*/
	readBMProw(picsrc, RowBuffer);

		for (i = 0; i < (picsrc ->rowsize)/ WORD_SIZE; i++) {


			if (XLlFifo_iTxVacancy(InstancePtr)) {
				XLlFifo_TxPutWord(InstancePtr, *(RowBuffer + i));

			}

		}

	/* Start Transmission by writing transmission length into the TLR */
	XLlFifo_iTxSetLen(InstancePtr, (picsrc ->rowsize));

	/* Check for Transmission completion */
	while (!(XLlFifo_IsTxDone(InstancePtr))) {

	}

	/* Transmission Complete */
	return XST_SUCCESS;
}

/*****************************************************************************/
/**
 *
 * RxReceive routine.It will receive the data from the FIFO.
 *
 * @param	InstancePtr is a pointer to the instance of the
 *		XLlFifo instance.
 *
 * @param	DestinationAddr is the address where to copy the received data.
 *
 * @return
 *		-XST_SUCCESS to indicate success
 *		-XST_FAILURE to indicate failure
 *
 * @note		None
 *
 ******************************************************************************/
int RxReceiveRow(XLlFifo *InstancePtr, u32* DestinationAddr, bmp_meta *picsrc) {

	int i;
	int Status;
	u32 RxWord;
	static u32 ReceiveLength;



	while (XLlFifo_iRxOccupancy(InstancePtr)) {
		/* Read Receive Length */
		ReceiveLength = (XLlFifo_iRxGetLen(InstancePtr)) / WORD_SIZE;
		for (i = 0; i < ReceiveLength; i++) {
			RxWord = XLlFifo_RxGetWord(InstancePtr);
			*(DestinationAddr + i) = RxWord;
		}
	}

	Status = XLlFifo_IsRxDone(InstancePtr);
	writeBMProw (picsrc,DestinationAddr);
	if (Status != TRUE) {
		xil_printf("Failing in receive complete ... \r\n");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

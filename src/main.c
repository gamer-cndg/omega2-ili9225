#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "ILI9225.h"

int main() {

	printf("Testing ILI9225 driver now.\n");

	//init random values generator (needed for demo)
	srand(time(NULL));

	//GPIO configuration of display
	ili9225_initparams_t params  = {
		.mosi = 8,	//MOSI
		.sclk = 7,	//SCLK
		.cs = 6,	//CS
		.led = -1,	//LED backlight (unused)
		.rst = 3,	//reset
		.rs = 1,	//D/C
		.speedInHz = 80 * 1000000 //80MHz
	};

	bool initOkay = ILI9225_Init(&params);
	if(!initOkay) {
		printf("[-] Failed to initialize ILI9255 display!\n");
		return -1;
	}

	//Clear with white color
	ILI9225_SetOrientation(0);
	ILI9225_ClearFramebuffer_White();
	ILI9225_CopyFramebuffer();

	//do graphics demo
	ILI9225_DoDemo();

	//display inverted picture
	ILI9225_Invert();
	ILI9225_CopyFramebuffer();

	//draw a few colors in a loop and measure FPS
	color_t colors[] = {
		COLOR_BLACK, COLOR_WHITE, COLOR_BLUE,
		COLOR_GREEN, COLOR_RED,	COLOR_NAVY,
		COLOR_DARKBLUE,	COLOR_DARKGREEN, COLOR_DARKCYAN,
		COLOR_CYAN, COLOR_TURQUOISE, COLOR_INDIGO,
		COLOR_DARKRED, COLOR_OLIVE
	};
	int numColors = (int) (sizeof(colors)/sizeof(*colors));

	struct timespec start, end;
	for(int i=0; i < 1000; i++) {
		//take time now
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		//uint16_t randomColor = (uint16_t)(rand() & 0xffff);
		ILI9225_FillFramebufferColor(colors[i % numColors]);
		ILI9225_CopyFramebuffer();

		clock_gettime(CLOCK_MONOTONIC_RAW, &end);

		uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
		int ms = (int)delta_us / 1000;
		printf("Frame time %d ms (FPS: %.3f)\n", ms, (1000.0f/ms));
	}

	//free it
	ILI9225_DeInit();

	return 0;
}

/*
 * ILI9225.h
 *
 *  Created on: Oct 15, 2017
 *      Author: max
 */

#ifndef ILI9225_H_
#define ILI9225_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* structure for initialization paramters */
typedef struct {
	//pins
	int mosi, sclk, cs, rst, rs, led;
	//speed
	int speedInHz;
} ili9225_initparams_t;

/* we use 16-bit color (R5G6G5) format here */
typedef uint16_t color_t;

/* Initialize the display with the given parameters */
bool ILI9225_Init(ili9225_initparams_t* initParams);
/* refresh the display by copying the frame buffer to it */
void ILI9225_CopyFramebuffer();
/* fill entire framebuffer with one color */
void ILI9225_FillFramebufferColor(uint16_t color);
/* clear framebuffer to black */
void ILI9225_ClearFramebuffer();
/* clear framebuffer to white */
void ILI9225_ClearFramebuffer_White();
/* draw a .xbm GIMP bitmap */
void ILI9225_DrawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
void ILI9225_DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
/* copy raw data into framebuffer */
void ILI9225_CopyBytesInFrameBuffer(int startIndex, const uint8_t* data, size_t dataLen);
/* sets orientation (0-3) */
void ILI9225_SetOrientation(uint8_t orientation);
/* gets the current orientation */
uint8_t ILI9225_GetOrientation();
/* draw a filled rectangle with coordinates (x1,y1) [upper left] to (x2,y2) [lower right] of some color */
void ILI9225_FillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
/* draws a colored line */
void ILI9225_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
/* draws a colored triangle */
void ILI9225_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
/* draws the bounds of a rectangle */
void ILI9225_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
/* draws the bounds of a circle */
void ILI9225_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
/* draws a filled circle */
void ILI9225_FillCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color);
/* inverts all colors in the framebuffer (xor 0xffffffff) */
void ILI9225_Invert();
/* turn the display on or off by writing into power registers. if off, it just displays white. */
void ILI9225_SetDisplayOnOff(bool flag);
/* set backlight display by controlling LED GPIO */
void ILI9225_SetBacklight(bool flag);
/* sets the background color used when writing text */
void ILI9225_SetBackgroundColor(uint16_t color);
/* draws a text with the given color at the given coordinates */
void ILI9225_DrawText(uint16_t x, uint16_t y, const char* s, uint16_t color);
/* same as DrawText, but uses COLOR_WHITE as the draw color */
void ILI9225_DrawText2(uint16_t x, uint16_t y, const char* s);
/* gets the maximum x value (dependent on orientation) */
uint16_t ILI9225_maxX();
/* gets the maximum y value (dependent on orientation) */
uint16_t ILI9225_maxY();
/* installs a new font. use the fonts declared below. */
void ILI9225_SetFont(const uint8_t* font);
/* do a graphics demo. */
void ILI9225_DoDemo();
/* gets a pointer to the raw framebuffer. use with causion. */
uint8_t* ILI9225_GetRawFrameBuffer();
void ILI9225_CopyExternalFrameBuffer(uint8_t* framebuf, size_t framebufLen);
void ILI9225_CopyExternalFrameBuffer2(const uint8_t* framebuf, int width, int height, int startX, int startY);

/* de-initialize it*/
void ILI9225_DeInit();

/* available fonts from DefaultFonts.c */
extern const uint8_t Terminal6x8[];
extern const uint8_t Terminal11x16[];
extern const uint8_t Terminal12x16[];
extern const uint8_t Trebuchet_MS16x21[];
/* test image, 180x220 */
extern const uint8_t ili9225_tux_img[];

/* Font definition */
typedef struct
{
	const uint8_t* font;
	uint8_t width;
	uint8_t height;
	uint8_t offset;
	uint8_t numchars;
	uint8_t nbrows;
} _currentFont;

/* macros for height and width */
#define ILI9225_LCD_WIDTH  176
#define ILI9225_LCD_HEIGHT 220

/* ILI9225 LCD Registers */
#define ILI9225_DRIVER_OUTPUT_CTRL      (0x01u)  // Driver Output Control
#define ILI9225_LCD_AC_DRIVING_CTRL     (0x02u)  // LCD AC Driving Control
#define ILI9225_ENTRY_MODE            	(0x03u)  // Entry Mode
#define ILI9225_DISP_CTRL1          	(0x07u)  // Display Control 1
#define ILI9225_BLANK_PERIOD_CTRL1      (0x08u)  // Blank Period Control
#define ILI9225_FRAME_CYCLE_CTRL        (0x0Bu)  // Frame Cycle Control
#define ILI9225_INTERFACE_CTRL          (0x0Cu)  // Interface Control
#define ILI9225_OSC_CTRL             	(0x0Fu)  // Osc Control
#define ILI9225_POWER_CTRL1            	(0x10u)  // Power Control 1
#define ILI9225_POWER_CTRL2           	(0x11u)  // Power Control 2
#define ILI9225_POWER_CTRL3            	(0x12u)  // Power Control 3
#define ILI9225_POWER_CTRL4            	(0x13u)  // Power Control 4
#define ILI9225_POWER_CTRL5            	(0x14u)  // Power Control 5
#define ILI9225_VCI_RECYCLING          	(0x15u)  // VCI Recycling
#define ILI9225_RAM_ADDR_SET1           (0x20u)  // Horizontal GRAM Address Set
#define ILI9225_RAM_ADDR_SET2           (0x21u)  // Vertical GRAM Address Set
#define ILI9225_GRAM_DATA_REG           (0x22u)  // GRAM Data Register
#define ILI9225_GATE_SCAN_CTRL          (0x30u)  // Gate Scan Control Register
#define ILI9225_VERTICAL_SCROLL_CTRL1   (0x31u)  // Vertical Scroll Control 1 Register
#define ILI9225_VERTICAL_SCROLL_CTRL2   (0x32u)  // Vertical Scroll Control 2 Register
#define ILI9225_VERTICAL_SCROLL_CTRL3   (0x33u)  // Vertical Scroll Control 3 Register
#define ILI9225_PARTIAL_DRIVING_POS1    (0x34u)  // Partial Driving Position 1 Register
#define ILI9225_PARTIAL_DRIVING_POS2    (0x35u)  // Partial Driving Position 2 Register
#define ILI9225_HORIZONTAL_WINDOW_ADDR1 (0x36u)  // Horizontal Address Start Position
#define ILI9225_HORIZONTAL_WINDOW_ADDR2	(0x37u)  // Horizontal Address End Position
#define ILI9225_VERTICAL_WINDOW_ADDR1   (0x38u)  // Vertical Address Start Position
#define ILI9225_VERTICAL_WINDOW_ADDR2   (0x39u)  // Vertical Address End Position
#define ILI9225_GAMMA_CTRL1            	(0x50u)  // Gamma Control 1
#define ILI9225_GAMMA_CTRL2             (0x51u)  // Gamma Control 2
#define ILI9225_GAMMA_CTRL3            	(0x52u)  // Gamma Control 3
#define ILI9225_GAMMA_CTRL4            	(0x53u)  // Gamma Control 4
#define ILI9225_GAMMA_CTRL5            	(0x54u)  // Gamma Control 5
#define ILI9225_GAMMA_CTRL6            	(0x55u)  // Gamma Control 6
#define ILI9225_GAMMA_CTRL7            	(0x56u)  // Gamma Control 7
#define ILI9225_GAMMA_CTRL8            	(0x57u)  // Gamma Control 8
#define ILI9225_GAMMA_CTRL9             (0x58u)  // Gamma Control 9
#define ILI9225_GAMMA_CTRL10            (0x59u)  // Gamma Control 10

/* works only with 9225C drivers? */
#define ILI9225C_INVOFF  0x20
#define ILI9225C_INVON   0x21

/* RGB 24-bits color table definition (RGB888). */
#define RGB888_RGB565(color) ((((color) >> 19) & 0x1f) << 11) | ((((color) >> 10) & 0x3f) << 5) | (((color) >> 3) & 0x1f)

#define COLOR_BLACK          RGB888_RGB565(0x000000u)
#define COLOR_WHITE          RGB888_RGB565(0xFFFFFFu)
#define COLOR_BLUE           RGB888_RGB565(0x0000FFu)
#define COLOR_GREEN          RGB888_RGB565(0x00FF00u)
#define COLOR_RED            RGB888_RGB565(0xFF0000u)
#define COLOR_NAVY           RGB888_RGB565(0x000080u)
#define COLOR_DARKBLUE       RGB888_RGB565(0x00008Bu)
#define COLOR_DARKGREEN      RGB888_RGB565(0x006400u)
#define COLOR_DARKCYAN       RGB888_RGB565(0x008B8Bu)
#define COLOR_CYAN           RGB888_RGB565(0x00FFFFu)
#define COLOR_TURQUOISE      RGB888_RGB565(0x40E0D0u)
#define COLOR_INDIGO         RGB888_RGB565(0x4B0082u)
#define COLOR_DARKRED        RGB888_RGB565(0x800000u)
#define COLOR_OLIVE          RGB888_RGB565(0x808000u)
#define COLOR_GRAY           RGB888_RGB565(0x808080u)
#define COLOR_SKYBLUE        RGB888_RGB565(0x87CEEBu)
#define COLOR_BLUEVIOLET     RGB888_RGB565(0x8A2BE2u)
#define COLOR_LIGHTGREEN     RGB888_RGB565(0x90EE90u)
#define COLOR_DARKVIOLET     RGB888_RGB565(0x9400D3u)
#define COLOR_YELLOWGREEN    RGB888_RGB565(0x9ACD32u)
#define COLOR_BROWN          RGB888_RGB565(0xA52A2Au)
#define COLOR_DARKGRAY       RGB888_RGB565(0xA9A9A9u)
#define COLOR_SIENNA         RGB888_RGB565(0xA0522Du)
#define COLOR_LIGHTBLUE      RGB888_RGB565(0xADD8E6u)
#define COLOR_GREENYELLOW    RGB888_RGB565(0xADFF2Fu)
#define COLOR_SILVER         RGB888_RGB565(0xC0C0C0u)
#define COLOR_LIGHTGREY      RGB888_RGB565(0xD3D3D3u)
#define COLOR_LIGHTCYAN      RGB888_RGB565(0xE0FFFFu)
#define COLOR_VIOLET         RGB888_RGB565(0xEE82EEu)
#define COLOR_AZUR           RGB888_RGB565(0xF0FFFFu)
#define COLOR_BEIGE          RGB888_RGB565(0xF5F5DCu)
#define COLOR_MAGENTA        RGB888_RGB565(0xFF00FFu)
#define COLOR_TOMATO         RGB888_RGB565(0xFF6347u)
#define COLOR_GOLD           RGB888_RGB565(0xFFD700u)
#define COLOR_ORANGE         RGB888_RGB565(0xFFA500u)
#define COLOR_SNOW           RGB888_RGB565(0xFFFAFAu)
#define COLOR_YELLOW         RGB888_RGB565(0xFFFF00u)

#endif /* ILI9225_H_ */

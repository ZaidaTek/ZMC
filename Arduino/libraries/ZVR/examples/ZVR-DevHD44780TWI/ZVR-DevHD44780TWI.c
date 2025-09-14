//**** **** ZVR_EXAMPLE_BLINK
//**** INCLUDE
#include <ZVR.h>
//**** PARAM - User-definable
#define ZVR_EXAMPLE_HD44780_ADDRESS		0x3f // TWI address of LCD
#define ZVR_EXAMPLE_HD44780_GRID_X		20 // horizontal number of chars
#define ZVR_EXAMPLE_HD44780_GRID_Y		4 // vertical number of chars
#define ZVR_EXAMPLE_HD44780_LOOP		125 // print delay
#define ZVR_EXAMPLE_HD44780_WAIT		1000 // LCD power-on ready delay
#define ZVR_EXAMPLE_HD44780_CHAR		'0' // first char to print
//**** MAIN
int main(void) {
	ZR_DEVICE lLCD;
	ZVB_TimeDelay(ZVR_EXAMPLE_HD44780_WAIT);
	ZVR_TWIInit(ZVR_TWI_RATE_100K, ZT_TRUE);
	ZVR_DevHD44780TWIInit(&lLCD, ZVR_EXAMPLE_HD44780_ADDRESS, ZVR_LCD_BACKLIGHT | ZVR_LCD_CURSOR | ZVR_LCD_BLINK, ZVR_EXAMPLE_HD44780_GRID_Y);
	ZVR_DevHD44780TWIWait();
	ZVR_DevHD44780TWIClear(&lLCD);
	ZVR_DevHD44780TWIWaitLong();
	ZVR_DevHD44780TWIHome(&lLCD);
	ZVR_DevHD44780TWIWaitLong();
	ZT_U8 lChar = ZVR_EXAMPLE_HD44780_CHAR - 1;
	ZT_U8 y = 0;
	ZT_U8 x = 0;
	do {
		ZVR_DevHD44780TWIWrite(&lLCD, ++lChar);
		ZVR_DevHD44780TWIWait();
		++x;
		if (!(x %= ZVR_EXAMPLE_HD44780_GRID_X)) {++y; y %= ZVR_EXAMPLE_HD44780_GRID_Y;}
		ZVR_DevHD44780TWICursor(&lLCD, x, y);
		ZVB_TimeDelay(ZVR_EXAMPLE_HD44780_LOOP);
	} while (0x1);
	return 0x0;
}

//**** **** ZVR_EXAMPLE_PFC8574
//**** INCLUDE
#include <ZVR.h>
//**** PARAM - User-definable
#define ZVR_EXAMPLE_PFC8574_ADDRESS		0x27
#define ZVR_EXAMPLE_PFC8574_LOOP		2000
//**** MAIN
int main(void) {
	ZT_U16 lNow;
	ZT_U16 lLast;
	ZVB_TimeDelay(1000);
	ZVR_SerialInit(0x0);
	ZVR_TWIInit(ZVR_TWI_RATE_100K, ZT_TRUE);
	ZVB_TimeInit();
	ZVR_TimeNow(&lLast);
	ZT_U8 lWrite = 0x0;
	ZT_U8 lRead;
	do {
		ZVR_DevPFC8574Write(TWI_ADDRESS, (lWrite ^= 0xff));
		ZVR_DevPFC8574Read(TWI_ADDRESS, &lRead);
		ZVR_SerialCharDigitHex(lWrite);
		ZVR_SerialCharDigitHex(lRead);
		ZVR_SerialCharNL();
		do {ZVR_TimeNow(&lNow);} while(lNow - lLast < LOOP_DELAY);
		lLast += LOOP_DELAY;
	} while (0x1);
}

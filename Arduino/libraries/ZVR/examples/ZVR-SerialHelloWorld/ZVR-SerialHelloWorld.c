//**** **** ZVR_EXAMPLE_SERIAL_HELLO
//**** INCLUDE
#include <ZVR.h>
//**** PARAM - User-definable
#define ZVR_EXAMPLE_SERIAL_HELLO_TEXT "Hello\n"
#define ZVR_EXAMPLE_SERIAL_HELLO_LOOP 1000
//**** MAIN
int main() {
	ZVR_SerialInit(ZVR_SERIAL_BAUD_500K);
	do {
		ZVR_SerialText((const ZT_U8*)ZVR_EXAMPLE_SERIAL_HELLO_TEXT);
		ZVB_TimeDelay(ZVR_EXAMPLE_SERIAL_HELLO_LOOP);
	} while (0x1);
	return 0x0;
}

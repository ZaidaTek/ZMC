//**** **** ZVR_EXAMPLE_SERIAL_ECHO
//**** INCLUDE
#include <ZVR.h>
//**** PARAM - User-definable
#define ZVR_EXAMPLE_SERIAL_ECHO_BAUD ZVR_SERIAL_BAUD_500K // Serial baud rate to use
//**** MAIN
int main() {
	ZVB_SerialInit(ZVR_EXAMPLE_SERIAL_ECHO_BAUD);
	while (0x1) {
		ZT_U8 lByte;
		if (ZVB_SerialPoll(&lByte)) {
			ZVB_SerialWrite(lByte);
		}
	}
	return 0x0;
}

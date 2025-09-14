//**** **** ZVR_EXAMPLE_DS1307
//**** INCLUDE
#include <ZVR.h>
//**** TASKS - User-definable
#define ZVR_EXAMPLE_DS1307_RTCR           0x1 // Read RTC clock and print in loop
#define ZVR_EXAMPLE_DS1307_RTCW           0x0 // Set RTC clock
#define ZVR_EXAMPLE_DS1307_SQWW           0x0 // Set square wave parameters // NOTE: SQW/OUT requires a pull-up!
#define ZVR_EXAMPLE_DS1307_RAMR           0x0 // Read 56-bytes onboard RAM
#define ZVR_EXAMPLE_DS1307_RAMW           0x0 // Write 56-bytes onboard RAM
//**** PARAM - User-definable
#define ZVR_EXAMPLE_DS1307_TWI_ADDRESS    0x68 // TWI Address of DS1307
#define ZVR_EXAMPLE_DS1307_TWI_RATE       ZVR_TWI_RATE_100K // TWI Rate to use (max. 100KHz)
#define ZVR_EXAMPLE_DS1307_TWI_PULLUP     ZT_TRUE // TWI pullup via ATmega328's I/O
#define ZVR_EXAMPLE_DS1307_RTC_DATE       ZVR_TIME_BUILD // RTC clock time to set, in seconds since 1970-01-01T00:00:00
#define ZVR_EXAMPLE_DS1307_RTC_HALT       ZT_FALSE // RTC clock halt state to set
#define ZVR_EXAMPLE_DS1307_RTC_LOOP       10000 // RTC clock read loop delay
#define ZVR_EXAMPLE_DS1307_SQW_ENABLE     ZT_TRUE // Square wave enabled state
#define ZVR_EXAMPLE_DS1307_SQW_LEVEL      ZT_TRUE // SQW/OUT state when square wave disabled
#define ZVR_EXAMPLE_DS1307_SQW_RATE       ZVR_DEV_DS1307_SQW_RATE_32768HZ // Square wave rate
const static ZT_U8 ZVR_EXAMPLE_DS1307_RAM[56] = { // RAM values to write
	0xef, 0xff, 0xde, 0xd7, 0xfe, 0xfb, 0xff, 0xd7,
	0xfd, 0xff, 0xbf, 0xf7, 0xef, 0xb7, 0xbf, 0xff,
	0xaf, 0xb9, 0xff, 0xf7, 0xff, 0xdf, 0xdf, 0xdf,
	0x78, 0x05, 0xa2, 0x1e, 0xf4, 0x04, 0x02, 0x20,
	0x54, 0x91, 0x28, 0xc2, 0x6d, 0x29, 0x47, 0x81,
	0x42, 0x50, 0x2d, 0xa2, 0x0c, 0x09, 0x65, 0x0a,
	0x90, 0x20, 0x45, 0x03, 0x99, 0x08, 0x75, 0xcb,
};
//**** MAIN
int main() {
	ZT_U8 lBuffer[21];
	ZT_U8 lHalt = ZVR_EXAMPLE_DS1307_RTC_HALT;
	ZR_SENSOR_DS1307 lRTC;
	lRTC.time = ZVR_EXAMPLE_DS1307_RTC_DATE;

	ZVB_SerialInit(ZVR_SERIAL_BAUD_500K);
	ZVR_TWIInit(ZVR_EXAMPLE_DS1307_TWI_RATE, ZVR_EXAMPLE_DS1307_TWI_PULLUP);

	ZVR_DevDS1307Config(&lRTC, sizeof(lRTC), ZVR_EXAMPLE_DS1307_TWI_ADDRESS, 0x0);
	ZVR_SerialText((const ZT_U8*)"CONF");
	ZVB_SerialCharDigitHex(lRTC.error);
	ZVB_SerialCharNL();
	ZVR_DevDS1307Init(&lRTC);
	ZVR_SerialText((const ZT_U8*)"INIT");
	ZVB_SerialCharDigitHex(lRTC.error);
	ZVB_SerialCharNL();

	#if defined(ZVR_EXAMPLE_DS1307_RAMR) && (ZVR_EXAMPLE_DS1307_RAMR != 0x0)
	for (ZT_U8 i = 0; i < 7; ++i) {
		ZVR_DevDS1307RAMRead(&lRTC, i << 3, lBuffer, 8);
		ZVR_SerialText((const ZT_U8*)"RAMR");
		ZVB_SerialCharDigitHex(lRTC.error);
		ZVB_SerialCharSpace();
		ZVB_SerialCharDigitHex(i << 3);
		for (ZT_U8 ii = 0; ii < 8; ++ii) {ZVB_SerialCharSpace(); ZVB_SerialCharDigitHex(lBuffer[ii]);}
		ZVB_SerialCharNL();
	}
	#endif
	
	#if defined(ZVR_EXAMPLE_DS1307_RAMW) && (ZVR_EXAMPLE_DS1307_RAMW != 0x0)
	for (ZT_U8 i = 0; i < 7; ++i) {
		ZVR_DevDS1307RAMWrite(&lRTC, i << 3, &ZVR_EXAMPLE_DS1307_RAM[i << 3], 8);
		ZVR_SerialText((const ZT_U8*)"RAMW");
		ZVB_SerialCharDigitHex(lRTC.error);
		ZVB_SerialCharSpace();
		ZVB_SerialCharDigitHex(i << 3);
		for (ZT_U8 ii = 0; ii < 8; ++ii) {ZVB_SerialCharSpace(); ZVB_SerialCharDigitHex(ZVR_EXAMPLE_DS1307_RAM[(i << 3) + ii]);}
		ZVB_SerialCharNL();
	}
	#endif
	
	#if defined(ZVR_EXAMPLE_DS1307_SQWW) && (ZVR_EXAMPLE_DS1307_SQWW != 0x0)
	ZVR_DevDS1307SQW(&lRTC, ZVR_EXAMPLE_DS1307_SQW_ENABLE, ZVR_EXAMPLE_DS1307_SQW_LEVEL, ZVR_EXAMPLE_DS1307_SQW_RATE);
	ZVR_SerialText((const ZT_U8*)"SQWW");
	ZVB_SerialCharDigitHex(lRTC.error);
	ZVB_SerialCharSpace();
	ZVB_SerialCharDigitHex(lRTC.config);
	ZVB_SerialCharNL();
	#endif
	
	#if defined(ZVR_EXAMPLE_DS1307_RTCW) && (ZVR_EXAMPLE_DS1307_RTCW != 0x0) && defined(ZVR_EXAMPLE_DS1307_RTC_DATE)
	ZVR_DevDS1307RTCSet(&lRTC, NULL, lHalt);
	ZVR_SerialText((const ZT_U8*)"RTCW");
	ZVB_SerialCharDigitHex(lRTC.error);
	ZVB_SerialCharSpace();
	ZVB_SerialCharDigitHex(lHalt);
	ZVB_SerialCharSpace();
	ZVR_TextISO8601Unix(lBuffer, &lRTC.time);
	ZVR_SerialText(lBuffer);
	ZVB_SerialCharNL();
	#endif
	
	#if defined(ZVR_EXAMPLE_DS1307_RTCR) && (ZVR_EXAMPLE_DS1307_RTCR != 0x0)
	do {
		ZVR_DevDS1307RTCRead(&lRTC, NULL, NULL);
		ZVR_SerialText((const ZT_U8*)"RTCR");
		ZVB_SerialCharDigitHex(lRTC.error);
		ZVB_SerialCharSpace();
		ZVB_SerialCharDigitHex(lHalt);
		ZVB_SerialCharSpace();
		ZVR_TextISO8601Unix(lBuffer, &lRTC.time);
		ZVR_SerialText(lBuffer);
		ZVB_SerialCharNL();
		ZVB_TimeDelay(ZVR_EXAMPLE_DS1307_RTC_LOOP);
	} while (0x1);
	#endif
	
	return 0x0;
}

//**** **** ZVR_EXAMPLE_DHT22
//**** INCLUDE
#include <ZVR.h>
//**** PARAM - User-definable
#define ZVR_EXAMPLE_DHT22_PIN		ZVR_PIN_A0 // pin on which DHT22 is connected
#define ZVR_EXAMPLE_DHT22_PULLUP	ZT_TRUE // use internal micro-controller pullup
#define ZVR_EXAMPLE_DHT22_LOOP		1000 // delay between readings
//**** MAIN
int main() {
	ZVR_TickInit(); // ABSOLUTELY REQUIRED, ELSE DEADLOCK DURING READ!!!
	ZVB_SerialInit(ZVR_SERIAL_DISABLE_RX | ZVR_SERIAL_BAUD_500K);
	
	ZR_SENSOR_DHT22 lSensor;
	ZVR_DevDHT22Config(&lSensor, sizeof(lSensor), ZVR_EXAMPLE_DHT22_PIN, ZVR_EXAMPLE_DHT22_PULLUP);
	ZVR_SerialText((const ZT_U8*)"CONF");
	ZVB_SerialCharDigitHex(lSensor.error);
	ZVB_SerialCharNL();
	
	ZVR_DevDHT22Init(&lSensor);
	ZVR_SerialText((const ZT_U8*)"INIT");
	ZVB_SerialCharDigitHex(lSensor.error);
	ZVB_SerialCharNL();

	do {
		ZVR_DevDHT22Read(&lSensor, NULL, NULL);

		ZT_U8 lBuffer[24];
		ZVR_SerialText((const ZT_U8*)"READ");
		ZVB_SerialCharDigitHex(lSensor.error);
		ZVB_SerialCharSpace();
		ZVR_TextDecimalI16(lBuffer, lSensor.temp);
		ZVR_SerialText(lBuffer);
		ZVB_SerialCharSpace();
		ZVR_TextDecimalI16(lBuffer, lSensor.rh);
		ZVR_SerialText(lBuffer);
		ZVB_SerialCharNL();

		ZVB_TimeDelay(ZVR_EXAMPLE_DHT22_LOOP);
	} while (0x1);

	return 0x0;
}

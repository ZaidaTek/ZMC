//**** **** ZVR_EXAMPLE_BLINK
//**** INCLUDE
#include <ZVR.h>
//**** PARAM - User-definable
#define ZVR_EXAMPLE_BLINK_TIMER 0x1
#define ZVR_EXAMPLE_BLINK_DELAY 1000
//**** MAIN
int main() {
	#if defined(ZVR_EXAMPLE_BLINK_TIMER) && ZVR_EXAMPLE_BLINK_TIMER
	ZVB_TimeInit();
	ZT_U16 lLast = 0;
	#endif // ZVR_EXAMPLE_BLINK_TIMER
	DDRB |= 0x20;
	while (0x1) {
		PORTB ^= 0x20;
		#if !defined(ZVR_EXAMPLE_BLINK_TIMER) || !(ZVR_EXAMPLE_BLINK_TIMER)
		ZVB_TimeDelay(ZVR_EXAMPLE_BLINK_DELAY);
		#else
		ZT_U16 lNow;
		do {ZVR_TimeNow(&lNow);} while (lNow - lLast < (ZT_U16)ZVR_EXAMPLE_BLINK_DELAY);
		lLast += (ZT_U16)ZVR_EXAMPLE_BLINK_DELAY;
		#endif // ZVR_EXAMPLE_BLINK_TIMER
	}
	return 0x0;
}

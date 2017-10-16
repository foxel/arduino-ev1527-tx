/* EV1527, RT1527, FP1527 or HS1527 encoding */
// inspired by http://forum.arduino.cc/index.php?topic=99714.0
// http://sc-tech.cn/en/HS1527.pdf

#include "ev1527_tx.h"

#define EV_1527_PULSETIME 330 // Time in microseconds for one pulse


ev1527_tx::ev1527_tx(int pin, int32_t address)
{
    _pin = pin;
    _address = address;
}

void ev1527_tx::signal(boolean state, int pulses) {
    digitalWrite(_pin, state);
    while (pulses--) {
		delayMicroseconds(EV_1527_PULSETIME);
	}
}

void ev1527_tx::signalBinary(boolean state) {
	if (state) {
		signal(HIGH, 3);
		signal(LOW, 1);
	} else {
		signal(HIGH, 1);
		signal(LOW, 3);
	}		
}

/* Transmit a message (lower 4 bits) */
void ev1527_tx::send(int8_t data) {
	pinMode(_pin, OUTPUT); 

	int r = 5;

	while (r--) {
		/* Preamble */
		signal(HIGH, 1);
		signal(LOW, 31);

		/* 20 Address bits */
		int32_t a_mask = 0x080000L;
		while (a_mask) {
			signalBinary((_address & a_mask) > 0L);
			a_mask >>= 1;
		}
		/*for(int i = 19; i >= 0; --i) {
			signalBinary((_address >> i) & 1);
		}*/

		/* The 4 data bits */
		int32_t d_mask = 0x08;
		while (d_mask) {
			signalBinary(data & d_mask);
			d_mask >>= 1;
		}
		
		//signalBinary(false);
	}

	digitalWrite(_pin, LOW);
}

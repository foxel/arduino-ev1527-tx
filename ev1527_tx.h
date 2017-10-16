
/* EV1527, RT1527, FP1527 or HS1527 encoding */

#ifndef ev1527_tx_h
#define ev1527_tx_h
#include "Arduino.h"

class ev1527_tx
{
  public:
    ev1527_tx(int pin, int32_t address); // this is the constructor
    void send(int8_t data);
  private:
    int _pin;	// this is Arduino input pin
    int32_t _address;	// this is 1527 address
    void signalBinary(boolean state);
    void signal(boolean state, int pulses);
};

#endif

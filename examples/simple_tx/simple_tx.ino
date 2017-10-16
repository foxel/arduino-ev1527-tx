#include <ev1527_tx.h>

#define LED_PIN 1
#define RF_PIN  0
#define RF_ADDR 0x0819a8L

ev1527_tx tx(RF_PIN, RF_ADDR);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  tx.send(0x02);
  digitalWrite(LED_PIN, LOW);
  delay(5000);
}

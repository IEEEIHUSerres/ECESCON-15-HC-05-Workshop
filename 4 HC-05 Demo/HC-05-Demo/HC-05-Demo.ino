/*
 * Bluetooth LED Control Demo
 * 
 * Description:
 * This Arduino sketch demonstrates controlling two LEDs via Bluetooth using
 * predefined commands sent over a serial connection. It utilizes an HC-05
 * Bluetooth module to receive commands from a paired device. By default it blinks all LEDs.
 * 
 * Commands:
 * - 'I' : Initialize and keep one LED on
 * - 'S' : Switch the LEDs
 * - 'D' : De-initialize and start the blinking mode
 * 
 * Author:
 * Iordanis Kostelidis
 * 
 * Date:
 * 13 April 2024
 * 
 * References:
 * - HC-05 Bluetooth Module Datasheet
 * - Arduino Serial Communication
 * 
 * Note:
 * - Ensure the HC-05 module is properly paired with the transmitting device.
 * - Use a serial monitor or a Bluetooth terminal app to send commands.
 * 
 * Disclaimer:
 * This code is provided as-is with no warranties. It may not cover all
 * use cases or error handling scenarios. Use it responsibly.
 */

#include <SoftwareSerial.h>

#define WHITE_LED_PIN 3
#define BLUE_LED_PIN 6

#define BT_TX_PIN 9
#define BT_RX_PIN 11

#define BT_BAUD_RATE 38400
#define SERIAL_BAUD_RATE 9600

int whiteLed = WHITE_LED_PIN;
int blueLed = BLUE_LED_PIN;

SoftwareSerial bt = SoftwareSerial(BT_TX_PIN, BT_RX_PIN);

bool initialized = false;

void setup();
void loop();
void ledSet(unsigned int ledPin, bool ledState);
void ledOn(unsigned int ledPin);
void ledOff(unsigned int ledPin);
void sleep(float seconds);

void noop();

void setup() {
  pinMode(whiteLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(SERIAL_BAUD_RATE);
  bt.begin(BT_BAUD_RATE);
}

void loop() {
  if(Serial.available()) {
    bt.write(Serial.read());
  }

  if (initialized) {
    if (not(bt.available())) {
      return;
    }
    int btValue = bt.read();
    Serial.write(btValue);
    // D = Desync
    if (btValue == 'D') {
      initialized = false;
      return;
    }
    // S = Swap
    if (btValue == 'S') {
      bool whiteStatus = digitalRead(whiteLed);
      ledSet(whiteLed, not(whiteStatus));

      bool blueStatus = digitalRead(blueLed);
      ledSet(blueLed, not(blueStatus));
      return;
    }
    return;
  }

  if (not(bt.available())) {
    noop();
    return;
  }

  int btValue = bt.read();
  Serial.write(btValue);
  // I = Initialize
  if (btValue == 'I') {
    initialized = true;
    ledOn(blueLed);
    ledOff(whiteLed);
    return;
  }
}

void ledSet(int ledPin, bool ledState) {
  digitalWrite(ledPin, ledState);
}

void ledOn(int ledPin) {
  ledSet(ledPin, true);
}

void ledOff(int ledPin) {
  ledSet(ledPin, false);
}

void sleep(float seconds) {
  int duration = seconds * 1000;
  delay(duration);
}

void noop() {
  ledOn(whiteLed);
  ledOn(blueLed);
  sleep(.4);
  ledOff(whiteLed);
  ledOff(blueLed);
  sleep(.4);
}

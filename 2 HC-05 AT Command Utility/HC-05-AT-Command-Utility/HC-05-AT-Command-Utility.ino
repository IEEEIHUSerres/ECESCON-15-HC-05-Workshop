/*
 * HC-05 AT Command Utility
 * 
 * Description:
 * This program demonstrates how to communicate with an HC-05 Bluetooth module
 * using AT commands. It allows configuring the module and testing basic
 * functionalities.
 * 
 * Author:
 * Iordanis Kostelidis
 * 
 * Date:
 * 13 April 2024
 * 
 * References:
 * - HC-05 Bluetooth Module Datasheet
 * - Arduino AT Command Set for HC-05
 * 
 * Notes:
 * - Ensure the HC-05 module is properly connected to the microcontroller.
 * - Use a serial monitor to interact with this utility.
 * 
 * Disclaimer:
 * This code is provided as-is with no warranties. It may not fully cover all
 * use cases or error handling scenarios. Use it at your own risk.
 */

#include <SoftwareSerial.h>

#define BT_TX_PIN 9
#define BT_RX_PIN 11
#define BT_BAUD_RATE 38400
#define SERIAL_BAUD_RATE 9600

SoftwareSerial BT = SoftwareSerial(BT_TX_PIN, BT_RX_PIN);

void setup();
void loop();

void setup() {
  BT.begin(BT_BAUD_RATE);
  Serial.begin(SERIAL_BAUD_RATE);

  Serial.println("HC-05 AT Command Utility");
  Serial.println("Author: Iordanis Kostelidis");
  Serial.println("== Basic HC-05 AT Commands ==");
  Serial.println("* AT");
  Serial.println("* AT+NAME");
  Serial.println("* AT+ADDR");
  Serial.println("* AT+VERSION");
  Serial.println("* AT+UART");
  Serial.println("* AT+ROLE");
  Serial.println("* AT+RESET");
  Serial.println("* AT+ORGL");
  Serial.println("* AT+PSWD");
}

void loop() {
  if(Serial.available()) BT.write(Serial.read());
  if(BT.available()) Serial.write(BT.read());
}

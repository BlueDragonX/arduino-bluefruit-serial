#define SOFTWARE_SERIAL_AVAILABLE 0

#include <Arduino.h>
#include <SPI.h>

#include "src/ble/Adafruit_BLE.h"
#include "src/ble/Adafruit_BluefruitLE_SPI.h"

#define BLE_SPI_CS 24
#define BLE_SPI_IRQ 23
#define BLE_VERBOSE true
#define CMD_SIZE 256

Adafruit_BluefruitLE_SPI ble(BLE_SPI_CS, BLE_SPI_IRQ);
char command[CMD_SIZE];

void setup_bluefruit() {
    while (!ble.begin(BLE_VERBOSE)) {
        Serial.println("bluefruit not connected or ready");
        delay(5000);
    }
    ble.echo(false);
    Serial.println( F("bluefruit initialized") );
    ble.info();
}

void setup() {
    while(!Serial) {
        delay(100);
    }
    Serial.println("booting bluefruit test ...");
    setup_bluefruit();
}

void loop() {
    // Display command prompt
    Serial.print(F("AT > "));

    // Check for user input and echo it back if anything was found
    getUserInput(command, CMD_SIZE-1);

    // Send command
    ble.println(command);

    // Check response status
    ble.waitForOK();
}

void getUserInput(char buffer[], uint8_t maxSize)
{
    memset(buffer, 0, maxSize);
    while(Serial.available() == 0) {
        delay(1);
    }
  
    uint8_t count=0;
  
    do {
        count += Serial.readBytes(buffer+count, maxSize);
        delay(2);
    } while((count < maxSize) && !(Serial.available() == 0));
}

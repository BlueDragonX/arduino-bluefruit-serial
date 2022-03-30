#define SOFTWARE_SERIAL_AVAILABLE 0

#include <Arduino.h>

#include "src/ble.h"

#define BLE_SPI_CS 24
#define BLE_SPI_IRQ 23
#define BLE_VERBOSE true
#define CMD_SIZE 256

BLE ble(BLE_SPI_CS, BLE_SPI_IRQ);

void setup() {
    while(!Serial) {
        delay(100);
    }
    while (!ble.begin(true)) {
        Serial.println("bluefruit not available");
        delay(5000);
    }
    Serial.println("bluefruit ready");
}

void loop() {
    while (Serial.available()) {
        ble.write(Serial.read());
    }
    while (ble.available()) {
        Serial.write(ble.read());
    }
}

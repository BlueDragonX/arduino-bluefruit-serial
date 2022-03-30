#include "ble.h"
#include "bluefruit/Adafruit_BLE.h"
#include "bluefruit/Adafruit_BluefruitLE_SPI.h"


bool BLE::begin(bool verbose) {
    if (!bluefruit_.begin(verbose)) {
        return false;
    }
    bluefruit_.setMode(BLUEFRUIT_MODE_COMMAND);
    if (verbose) {
        bluefruit_.info();
    }
    bluefruit_.echo(false);
    bluefruit_.enableModeSwitchCommand(false);
    //TODO: Add debug logging for command failures.
    bluefruit_.atcommand("AT+GAPSTARTADV");
    bluefruit_.setMode(BLUEFRUIT_MODE_DATA);
    return true;
}

bool BLE::connected() {
    return bluefruit_.isConnected();
}

void BLE::disconnect() {
    //TODO: Add debug logging for command failures.
    bluefruit_.atcommand("AT+GAPDISCONNECT");
}

void BLE::forget() {
    //TODO: Add debug logging for command failures.
    bluefruit_.setMode(BLUEFRUIT_MODE_COMMAND);
    bluefruit_.atcommand("AT+GAPDISCONNECT");
    bluefruit_.atcommand("AT+GAPDELBONDS");
    bluefruit_.setMode(BLUEFRUIT_MODE_DATA);
}

void BLE::setDeviceName(const uint8_t* name, size_t size) {
    bluefruit_.atcommand("AT+GAPDEVNAME", name, size);
}

int BLE::available() {
    return bluefruit_.available();
}

int BLE::read() {
    return bluefruit_.read();
}

int BLE::peek() {
    return bluefruit_.peek();
}

size_t BLE::write(uint8_t b) {
    return bluefruit_.write(b);
}

size_t BLE::write(const uint8_t *buffer, size_t size) {
    return bluefruit_.write(buffer, size);
}

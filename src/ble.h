#ifndef __BLE_H__
#define __BLE_H__

#include <Arduino.h>
#include "bluefruit/Adafruit_BluefruitLE_SPI.h"


// Create a BLE stream connection for serial communication.
class BLE : public Stream {
    public:
        // Create a BLE object that connects to a Bluefruit SPI module with the
        // given CS and IRQ pins.
        BLE(int8_t cs_pin, int8_t irq_pin) :
            bluefruit_(cs_pin, irq_pin, -1) {}

        // Initialize the Bluefruit device. The device is configured for serial
        // communication and advertising (pairing mode) is disabled.
        bool begin(bool verbose = false);

        // Return true if connected to a host.
        bool connected();

        // Disconnect the currently connected device and begin advertising.
        // Advertising stops after a connection is established.
        void disconnect();

        // Disconnect and forget any stored hosts. 
        void forget();

        // Set the name of the device. This is persisted across reboots.
        void setDeviceName(const uint8_t* name, size_t size);

        // Stream functions.
        int available() override;
        int read() override;
        int peek() override;
        size_t write(uint8_t) override;
        size_t write(const uint8_t* buffer, size_t size) override;
    private:
        Adafruit_BluefruitLE_SPI bluefruit_;
};

#endif  // __BLE_H__

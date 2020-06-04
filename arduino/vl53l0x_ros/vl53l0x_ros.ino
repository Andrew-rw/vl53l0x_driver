#include "Adafruit_VL53L0X.h"

/*
* Protocol description.
* Every message starts with 0xAD byte, followed by message type byte and ends with \l\n (0x0D, 0x0A)
* Message types:
* 0xEF - initialization failed
* 0xE0 - initialization successful, no errors
* 0x1D - range message, followed by two bytes range measurement
* 0xEA - out of range
*/
Adafruit_VL53L0X sensor = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;

unsigned long range_timer;

void setup() {
    Serial.begin(57600);
    // wait until Serial port is opened
    while (!Serial) {}
    // if initialization failed - write message and freeze
    if (!sensor.begin()) {
        Serial.write(0xAD);
        Serial.write(0xEF);
        Serial.write(0x0D);
        Serial.write(0x0A);
        while (1);
    }
    // initialization successful
    Serial.write(0xAD);
    Serial.write(0xE0);
    Serial.write(0x0D);
    Serial.write(0x0A);
}

void loop() {
    if ((millis() - range_timer) > 50) {
        // message start
        Serial.write(0xAD);
        sensor.rangingTest(&measure, false);
        if (measure.RangeStatus == 4) {
            // out of range
            Serial.write(0xEA);
        } else {
            // measured distance
            Serial.write(0x1D);
            Serial.write(measure.RangeMilliMeter & 0xff);
            Serial.write(measure.RangeMilliMeter >> 8);
        }
        // message end
        Serial.write(0x0D);
        Serial.write(0x0A);
        range_timer = millis();
    }
}

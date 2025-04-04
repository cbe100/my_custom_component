#ifndef ZMPT101B_H
#define ZMPT101B_H

#include "esphome.h"  // Include ESPHome's base header

#define DEFAULT_FREQUENCY 50.0f
#define DEFAULT_SENSITIVITY 500.0f

class ZMPT101B : public PollingComponent, public Sensor {
public:
    ZMPT101B(uint8_t pin, uint16_t frequency = DEFAULT_FREQUENCY)
        : PollingComponent(1000), pin_(pin), frequency_(frequency) {}  // Poll every second (1000ms)

    void setSensitivity(float value) { sensitivity_ = value; }

    float getRmsVoltage(uint8_t loopCount = 1);

    void setup() override {
        pinMode(pin_, INPUT);
    }

    void update() override {
        // Call the method to read the RMS voltage and update the state
        float voltage = getRmsVoltage(); // Call your method for RMS voltage
        publish_state(voltage);          // Publish the result to ESPHome
    }

private:
    uint8_t pin_;
    uint16_t frequency_;
    float sensitivity_ = DEFAULT_SENSITIVITY;

    int getZeroPoint();
};

#endif

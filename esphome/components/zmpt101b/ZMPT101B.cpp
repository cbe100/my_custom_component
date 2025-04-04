#include "ZMPT101B.h"
#include <cmath>

/// @brief ZMPT101B constructor
/// @param pin analog pin that ZMPT101B is connected to.
/// @param frequency AC system frequency
ZMPT101B::ZMPT101B(uint8_t pin, uint16_t frequency)
    : PollingComponent(1000) // Poll every second (1000ms)
{
    this->pin_ = pin;
    period = 1000000 / frequency;  // Microseconds per cycle
}

void ZMPT101B::setSensitivity(float value) {
    sensitivity_ = value;
}

int ZMPT101B::getZeroPoint() {
    uint32_t Vsum = 0;
    uint32_t measurements_count = 0;
    uint32_t t_start = micros();

    while (micros() - t_start < period) {
        Vsum += analogRead(pin_);
        measurements_count++;
    }

    return Vsum / measurements_count;
}

float ZMPT101B::getRmsVoltage(uint8_t loopCount) {
    double readingVoltage = 0.0f;

    for (uint8_t i = 0; i < loopCount; i++) {
        int zeroPoint = this->getZeroPoint();

        int32_t Vnow = 0;
        uint32_t Vsum = 0;
        uint32_t measurements_count = 0;
        uint32_t t_start = micros();

        while (micros() - t_start < period) {
            Vnow = analogRead(pin_) - zeroPoint;
            Vsum += (Vnow * Vnow);
            measurements_count++;
        }

        readingVoltage += sqrt(Vsum / measurements_count) / ADC_SCALE * VREF * sensitivity_;
    }

    return readingVoltage / loopCount;
}

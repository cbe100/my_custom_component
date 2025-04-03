#include "esphome.h"
#include <Arduino.h>
#include "ZMPT101B.h"

#define SENSITIVITY 509.0f

class ZMPT101BSensor : public PollingComponent, public Sensor {
 public:
  uint8_t adcPin;
  ZMPT101B *zmpt101b;
  // constructor
  ZMPT101BSensor(uint8_t adcPin) : PollingComponent(1000) {
    this->adcPin = adcPin;
    this->zmpt101b = new ZMPT101B(adcPin);
  }

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void setup() override {
    this->zmpt101b->setSensitivity(SENSITIVITY);
  }

  void update() override {
    float Vrms = this->zmpt101b->getRmsVoltage();
    publish_state(Vrms);
  }
};
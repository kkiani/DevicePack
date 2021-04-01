//#include "sensor.h"

class DigitalSensor: public Sensor{
  public:
  int value();

  using Sensor::Sensor;
};

int DigitalSensor::value() {
  int out = 0;
  for(int i=0; i<100; i++){
    out += digitalRead(this->pin);
  }

  if (out > 30){
    return 1;
  } else {
    return 0;
  }
}

class Lamp{
  private:
  int pin;
  
  public:
  static const int turn_on_cmd = 0x20;
  static const int turn_off_cmd = 0x21;
  
  Lamp(int pin);
  void execute(byte cmd);
  bool isOn();
  void setOn(bool state);
};

Lamp::Lamp(int pin){
  this->pin = pin;
}

void Lamp::execute(byte cmd){
  if (cmd == turn_on_cmd){
    digitalWrite(this->pin, HIGH);
  } else if (cmd == turn_off_cmd){
    digitalWrite(this->pin, LOW);
  }
}

bool Lamp::isOn(){
  return digitalRead(this->pin);
}

void Lamp::setOn(bool state){
  return digitalWrite(this->pin, state);
}

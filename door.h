class DoorLock{
  private:
  int pin;
  
  public:
  static const int turn_on_cmd = 0x30;
  static const int turn_off_cmd = 0x31;
  
  DoorLock(int pin);
  void execute(byte cmd);
  bool isLock();
  void setLock(bool state);
};

DoorLock::DoorLock(int pin){
  this->pin = pin;
}

void DoorLock::execute(byte cmd){
  if (cmd == turn_on_cmd){
    digitalWrite(this->pin, HIGH);
  } else if (cmd == turn_off_cmd){
    digitalWrite(this->pin, LOW);
  }
}

bool DoorLock::isLock(){
  return !digitalRead(this->pin);
}

void DoorLock::setLock(bool state){
  return digitalWrite(this->pin, !state);
}

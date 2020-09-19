class Button{
  private:
  int pin;
  
  public:
  Button(int pin);
  bool isPushed();
};

Button::Button(int pin){
  this->pin = pin;
}

bool Button::isPushed(){
  return !digitalRead(this->pin);
}

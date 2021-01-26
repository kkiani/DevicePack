#include "button.h"
#include "switch.h"
#include "sensor.h"

#define led_pin 13

Button doorButton(5);
Button lampButton(3);

Switch doorLock(byte(0x11), 4);
Switch lamp(byte(0x12), 2);
Switch humidifier(byte(0x13), 6);

Sensor motion(byte(0x21), 7);

timer = millis();

void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(led_pin, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
  

  doorButton.pushUpAction = doorButton_pushedUp;
  doorButton.pushDownAction = doorButton_pushedDown;
  
  lampButton.pushUpAction = lampButton_pushedUp;
  lampButton.pushDownAction = lampButton_pushedDown;
}

void loop() {
  doorButton.update();
  lampButton.update();

  // Receive
  if (Serial.available()>2){
    byte id = Serial.read();
    byte command = Serial.read();

    if (id == byte(0x00)){
      responceDeviceList();
      return;
    }

    doorLock.executeCodeWithId(command, id);
    lamp.executeCodeWithId(command, id);
    humidifier.executeCodeWithId(command, id);
  }

  // Send
  if (timer - millis() > 1000){
    postData(motion.id, byte(motion.value());
    timer = millis();
  }
}

void responceDeviceList(){
  byte deviceDefineId = byte(0x00);
  
  postData(deviceDefineId, doorLock.id);
  postData(deviceDefineId, lamp.id);
  postData(deviceDefineId, humidifier.id);
}

void postData(byte id, byte value){
  Serial.write(id);
  Serial.write(value);
}


// --------- Button CallBacks ------------
void doorButton_pushedUp(){
  doorLock.on();
  digitalWrite(led_pin, LOW);
}

void doorButton_pushedDown(){
  digitalWrite(led_pin, HIGH);
  doorLock.off();
}

void lampButton_pushedUp(){
  if (lamp.state() == true){
    lamp.off();
  } else {
    lamp.on();
  }
  digitalWrite(led_pin, LOW);
}

void lampButton_pushedDown(){
  digitalWrite(led_pin, HIGH);
}

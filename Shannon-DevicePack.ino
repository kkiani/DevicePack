#include "lamp.h"
#include "door.h"
#include "button.h"

#define led_status 13

Lamp lamp(2);
Button lampButton(3);
DoorLock door(4);
Button doorButton(5);

void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(led_status, OUTPUT);
}

void loop() {
  // Serial Commands
  if (Serial.available()){
    status_on();
    
    byte command = Serial.read();
    
    lamp.execute(command);
    door.execute(command);

    status_off();
  }

  // Buttons commands
  if (lampButton.isPushed()){
    status_on();
    lamp.setOn(!lamp.isOn());
    status_off();
  }

  if (doorButton.isPushed()){
    status_on();
    door.setLock(false);
    delay(1000);
    door.setLock(true);
    status_off();
  }
//  digitalWrite(led_status, HIGH);
//  delay(1000);
//  digitalWrite(led_status, LOW);
//  delay(500);
}

void status_off(){
  delay(200);
  digitalWrite(led_status, LOW);
}

void status_on(){
  digitalWrite(led_status, HIGH);
}

#include "button.h"
#include "switch.h"
#include "sensor.h"
#include "digitalSensor.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_Si7021.h"
#include <Adafruit_BMP280.h>

#define led_pin 13

Button doorButton(5);
Button lampButton(3);

Switch doorLock(byte(0x11), 4);
Switch lamp(byte(0x12), 2);
Switch humidifier(byte(0x13), 6);

DigitalSensor motion(byte(0x21), 8);

Adafruit_BMP280 bme; // I2C
Adafruit_Si7021 sensor = Adafruit_Si7021();  //id = 0x22 and 0x23
const byte humidity_id = 0x22;
const byte temperature_id = 0x23;


long previousMillis = 0;

void setup() {
  Serial.begin(9600);

  sensor.begin();

  pinMode(8, INPUT);
  
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
  byte serialBuff[2];
  if (Serial.available()){
    digitalWrite(led_pin, HIGH);
    
    Serial.readBytes(serialBuff, 2);
    byte id = serialBuff[0];
    byte command = serialBuff[1];
    
    if (id == byte(0x00)){
      responceDeviceList();
      
      delay(100);
      digitalWrite(led_pin, LOW);
      return;
    }

    doorLock.executeCodeWithId(command, id);
    lamp.executeCodeWithId(command, id);
    humidifier.executeCodeWithId(command, id);
    
    delay(100);
    digitalWrite(led_pin, LOW);
  }

  // Send
  if (millis() - previousMillis > 1000){
    postData(motion.id, byte(motion.value()));
    postData(humidity_id, byte(sensor.readHumidity()));
    postData(temperature_id, byte(sensor.readTemperature()));
    previousMillis = millis();
  }
}

void responceDeviceList(){
  byte deviceDefineId = byte(0x00);
  
  postData(deviceDefineId, doorLock.id);
  postData(deviceDefineId, lamp.id);
  postData(deviceDefineId, humidifier.id);
  postData(deviceDefineId, motion.id);
  postData(deviceDefineId, humidity_id);
  postData(deviceDefineId, temperature_id);
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

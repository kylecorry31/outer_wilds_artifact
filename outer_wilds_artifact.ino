#include "LowPower.h"

int state = 0;
int light_pin = 13;
int mic_pin = A0;
int ldr_pin = A2;

bool should_print = false;

int light_threshold = 60;
int dark_threshold = 40;
int mic_threshold = 450;

void setup() {
  pinMode(light_pin, OUTPUT); // Light
  pinMode(mic_pin, INPUT); // Mic
  pinMode(ldr_pin, INPUT); // LDR
  if (should_print){
    Serial.begin(9600);
  }
}

void loop() {
  if (state == 0){
    off_1();
  } else if (state == 1){
    off_2();
  } else if (state == 2){
    on();
  }
  if (!should_print){
    LowPower.powerDown(SLEEP_30MS, ADC_OFF, BOD_OFF);
  } else {
    delay(30);
  }
}

void off_1(){
  digitalWrite(light_pin, false);
  if (should_print){
    Serial.print("0: ");
    Serial.println(analogRead(ldr_pin));
  }
  if (analogRead(ldr_pin) > light_threshold){
    state = 1;  
  }
}

void off_2(){
  if (should_print){
    Serial.print("1: ");
    Serial.println(analogRead(ldr_pin));
  }
  if (analogRead(ldr_pin) < dark_threshold){
    state = 2;  
  }
}

void on(){
  int mic = analogRead(mic_pin);
  if (should_print){
    Serial.print("2: ");
    Serial.println(mic);
  }
  digitalWrite(light_pin, true);
  if (mic == 0 || mic > mic_threshold){
    state = 0;
  }
}

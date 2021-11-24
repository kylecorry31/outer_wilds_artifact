#include <LowPower.h>

int lastPower = 0;
bool on = false;
bool wasLight = false;
bool onCycleComplete = false;

void setup() {
  pinMode(10, OUTPUT); // Blue
  pinMode(11, OUTPUT); // Green
  pinMode(A2, INPUT); // Mic
  pinMode(A1, INPUT); // LDR
  pinMode(3, OUTPUT); // LDR power
  pinMode(2, OUTPUT); // Mic power
  Serial.begin(9600);
  Serial.println("START");
  turn_off();
}

void loop() {
  if (on){
    on_mode();
  } else {
    off_mode();
  }
}


void off_mode(){
  digitalWrite(2, true);
  int light_threshold = 300;
  int dark_threshold = 125;
  int light = analogRead(A1);
  Serial.print(light);
  Serial.print(" ");
  Serial.println(wasLight);
  delay(20);

  if (light > light_threshold){
    wasLight = true;
  }
  
  if (wasLight && light < dark_threshold){
    turn_on();
    return;
  }
  digitalWrite(2, false);
  LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
}

void turn_on(){
  Serial.println("ON");
  lastPower = 0;
  onCycleComplete = false;
  on = true;
  digitalWrite(3, false);
  digitalWrite(2, true);
}

void turn_off(){
  Serial.println("OFF");
  wasLight = false;
  on = false;
  digitalWrite(3, true);
  digitalWrite(2, false);
  digitalWrite(11, false);
  digitalWrite(10, false);
}

void on_mode(){
  int amount = 60;
  int maxPower = 30;
  int blueMaxPower = 5;
  int waitTime = 100;
  int offThreshold = 900;
  int micTime = 2000;
  
  int power = min(maxPower - (amount / 100.0 * maxPower) + random(0, amount), maxPower);
  int current = lastPower;
  int delta = power - lastPower;

  for (int i = 0; i < waitTime; i++){
    float pct = i / (float)waitTime;
    int current = lastPower + pct * delta;
    analogWrite(10, map(current, 0, maxPower, 0, blueMaxPower));
    analogWrite(11, current);
    int mic = analogRead(A2);
    Serial.println(mic);
    if (mic > offThreshold && onCycleComplete){
      turn_off();
      return;
    }
    delay(1);
  }
  lastPower = power;

  if (!onCycleComplete){
    delay(micTime);
  }
  
  onCycleComplete = true;
}

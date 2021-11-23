int lastPower = 0;
bool on = false;
bool wasLight = false;
int startTime = 0;

void setup() {
  pinMode(11, OUTPUT); // Blue
  pinMode(10, OUTPUT); // Green
  pinMode(A2, INPUT); // Mic
  pinMode(A1, INPUT); // LDR
  pinMode(3, OUTPUT); // LDR power
  pinMode(2, OUTPUT); // Mic power
  Serial.begin(9600);

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
  int light_threshold = 120;
  int dark_threshold = 80;
  int light = analogRead(A1);
  Serial.println(light);

  if (light > light_threshold){
    wasLight = true;
  }
  
  if (wasLight && light < dark_threshold){
    turn_on();
    return;
  }
  
  delay(1);
}

void turn_on(){
  lastPower = 0;
  startTime = millis();
  on = true;
  digitalWrite(3, false);
  digitalWrite(2, true);
}

void turn_off(){
  wasLight = false;
  on = false;
  digitalWrite(3, true);
  digitalWrite(2, false);
  digitalWrite(11, false);
  digitalWrite(10, false);
}

void on_mode(){
  int amount = 60;
  int maxPower = 40;
  int waitTime = 250;
  int offThreshold = 950;
  
  int power = min(maxPower - (amount / 100.0 * maxPower) + random(0, amount), maxPower);
  int current = lastPower;
  int delta = power - lastPower;

  for (int i = 0; i < waitTime; i++){
    float pct = i / (float)waitTime;
    int current = lastPower + pct * delta;
    analogWrite(11, current);
    analogWrite(10, current);
    int mic = analogRead(A2);
    Serial.println(mic);
    if ((millis() - startTime) > 1000 && mic > offThreshold){
      turn_off();
      return;
    }
    delay(1);
  }
  lastPower = power;
}

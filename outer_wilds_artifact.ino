int state = 0;

void setup() {
  pinMode(10, OUTPUT); // Light
  pinMode(A2, INPUT); // Mic
  pinMode(A1, INPUT); // LDR
}

void loop() {
  if (state == 0){
    off_1();
  } else if (state == 1){
    off_2();
  } else if (state == 2){
    on();
  }
  delay(20);
}

void off_1(){
  digitalWrite(10, false);
  if (analogRead(A1) > 300){
    state = 1;  
  }
}

void off_2(){
  if (analogRead(A1) < 125){
    state = 2;  
  }
}

void on(){
  digitalWrite(10, true);
  if (analogRead(A2) > 900){
    state = 0;
  }
}

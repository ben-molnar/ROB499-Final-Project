// Definitions for Arduino pins connected to input H-Bridge
int IN1 = 4;
int IN2 = 5;

int IN3 = 6;
int IN4 = 7;

int IN5 = 8;
int IN6 = 9;

int IN7 = 10;
int IN8 = 11;

int IN9 = 12;
int IN10 = 13;

void setup() {
  // Set the output pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(IN9, OUTPUT);
  pinMode(IN10, OUTPUT);

  Serial.begin(9600);

  // grabObject();
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command.equals("move_to_red_zone")) {
      moveToRed();
    }
    if (command.equals("move_to_blue_zone")) {
      moveToBlue();
    }
    if (command.equals("move_to_green_zone")) {
      moveToGreen();
    }
  }
        
}

// Movement functions
void moveToRed() {
  Serial.println("Moving arm to Red Zone");

  grabObject();

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(7000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  placeObject();

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(7000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  
}

void moveToGreen() {
  Serial.println("Moving arm to Green Zone");

  grabObject();

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(7000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  placeObject();

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(7000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}

void moveToBlue() {
  Serial.println("Moving arm to Blue Zone");

  grabObject();

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(4000);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  delay(3000);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);

  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  delay(1500);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);

  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, LOW);
  delay(2000);
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, HIGH);

  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  delay(1500);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);

  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  delay(3500);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(5200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN9, LOW);
  digitalWrite(IN10, HIGH);
  delay(2000);
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, HIGH);

}

void grabObject() {
  //about 2000ms to fully open grippers from being fully closed
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, LOW);
  delay(2000);
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(3800);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  delay(3200);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);

  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  delay(1200);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);

  digitalWrite(IN9, LOW);
  digitalWrite(IN10, HIGH);
  delay(1600);
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, HIGH);

  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  delay(1500);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);

  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  delay(3600);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(5100);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

}

void placeObject() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(3200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  delay(3000);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);

  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  delay(1500);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);

  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, LOW);
  delay(1500);
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, HIGH);

  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  delay(1500);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);

  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  delay(3500);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(4400);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN9, LOW);
  digitalWrite(IN10, HIGH);
  delay(2000);
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10, HIGH);
}

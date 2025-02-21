// Define motor pins
#define D1 1
#define D2 13
#define D3 12
#define D4 11
#define D5 10
#define D6 9
#define D7 8
#define D8 7

// Define sensor pins
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4
#define S6 A5

// Define LED pins
#define L1 5
#define L2 6
#define L3 4
#define L4 3
#define L5 2

//
#define RETURN1 HIGH
#define RETURN0 LOW

// Time in milliseconds (2.5 seconds)
#define TIMEON 2500  

// Track timers and states for each light
unsigned long startTimeL1, startTimeL2, startTimeL3, startTimeL4, startTimeL5;
bool L1On = false, L2On = false, L3On = false, L4On = false, L5On = false;

int S1data, S2data, S3data, S4data, S5data, S6data;
bool MotorON = false;

int delayInMs = 100;  // Stepper motor speed (lower = faster)

void setup() {
  // Set motor pins as OUTPUT
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  // Set sensor pins as INPUT
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);

  // Set LED pins as OUTPUT
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Turn off lights after TIMEON milliseconds
  if (L1On && currentMillis - startTimeL1 >= TIMEON) {
    digitalWrite(L1, RETURN0);
    L1On = false;
  }
  if (L2On && currentMillis - startTimeL2 >= TIMEON) {
    digitalWrite(L2, RETURN0);
    L2On = false;
  }
  if (L3On && currentMillis - startTimeL3 >= TIMEON) {
    digitalWrite(L3, RETURN0);
    L3On = false;
  }
  if (L4On && currentMillis - startTimeL4 >= TIMEON) {
    digitalWrite(L4, RETURN0);
    L4On = false;
  }
  if (L5On && currentMillis - startTimeL5 >= TIMEON) {
    digitalWrite(L5, RETURN0);
    L5On = false;
  }

  // Read sensor values
  S1data = analogRead(S1);
  S2data = analogRead(S2);
  S3data = analogRead(S3);
  S4data = analogRead(S4);
  S5data = analogRead(S5);
  S6data = analogRead(S6);

  // Turn on lights if sensor value is below threshold
  if (S1data < 100) {
    digitalWrite(L1, RETURN1);
    startTimeL1 = millis();
    L1On = true;
  }
  if (S2data < 100) {
    digitalWrite(L2, RETURN1);
    startTimeL2 = millis();
    L2On = true;
  }
  if (S3data < 100) {
    digitalWrite(L3, RETURN1);
    startTimeL3 = millis();
    L3On = true;
  }
  if (S4data < 100) {
    digitalWrite(L4, RETURN1);
    startTimeL4 = millis();
    L4On = true;
  }
  if (S5data < 100) {
    digitalWrite(L5, RETURN1);
    startTimeL5 = millis();
    L5On = true;
  }

  // Control motor based on S6
  MotorON = (S6data >= 20);

  if (!MotorON) {
    if (delayInMs > 10) {
      delayInMs -= 5;  // Gradually increase speed
      if (delayInMs < 10){
        delayInMs = 10;
      }
    }
    full_step();
  } 
  else {
    if (delayInMs < 100) {
      delayInMs += 2;  // Gradually decrease speed
      full_step();
    }

    // Ensure motor stops completely after slowing down
    stopMotor();
  }
}

void full_step() {
  // First step
  digitalWrite(D1, HIGH); digitalWrite(D5, HIGH);
  digitalWrite(D2, HIGH); digitalWrite(D6, HIGH);
  digitalWrite(D3, LOW);  digitalWrite(D7, LOW);
  digitalWrite(D4, LOW);  digitalWrite(D8, LOW);
  delay(delayInMs);

  // Second step
  digitalWrite(D1, LOW);  digitalWrite(D5, LOW);
  digitalWrite(D2, HIGH); digitalWrite(D6, HIGH);
  digitalWrite(D3, HIGH); digitalWrite(D7, HIGH);
  digitalWrite(D4, LOW);  digitalWrite(D8, LOW);
  delay(delayInMs);

  // Third step
  digitalWrite(D1, LOW);  digitalWrite(D5, LOW);
  digitalWrite(D2, LOW);  digitalWrite(D6, LOW);
  digitalWrite(D3, HIGH); digitalWrite(D7, HIGH);
  digitalWrite(D4, HIGH); digitalWrite(D8, HIGH);
  delay(delayInMs);

  // Fourth step
  digitalWrite(D1, HIGH); digitalWrite(D5, HIGH);
  digitalWrite(D2, LOW);  digitalWrite(D6, LOW);
  digitalWrite(D3, LOW);  digitalWrite(D7, LOW);
  digitalWrite(D4, HIGH); digitalWrite(D8, HIGH);
  delay(delayInMs);
}

void stopMotor() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
}

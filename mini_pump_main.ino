// Define Pump Pins (H-Bridge IC)
#define P1A 5
#define P2A 6
#define P3A 7
#define P4A 8

// Define Solenoid Pins
#define S1A   11
#define S2A   12
#define S3A   9
#define S4A   10
#define S12EN 0
#define S34EN 1

void setup() {
  Serial.begin(9600);
  // Pump control pins
  pinMode(P1A, OUTPUT);
  pinMode(P2A, OUTPUT);
  pinMode(P3A, OUTPUT);
  pinMode(P4A, OUTPUT);

  // Solenoid control pins
  pinMode(S1A, OUTPUT);
  pinMode(S2A, OUTPUT);
  pinMode(S3A, OUTPUT);
  pinMode(S4A, OUTPUT);

  pinMode(S12EN, OUTPUT);
  pinMode(S34EN, OUTPUT);

  // Solenoid in inflate position
  digitalWrite(S2A, LOW);
  digitalWrite(S2A, LOW);

  analogWrite(S12EN, 255);
  analogWrite(S34EN, 255);
}

void inflate() { 
  Serial.print("Inflating Bladder\t");
  digitalWrite(S2A, LOW);   // ensure solenoid in proper orientation
  digitalWrite(S4A, LOW);   // ensure solenoid in proper orientation
  digitalWrite(P2A, HIGH);  // turn on the pump
  digitalWrite(P4A, HIGH);  // turn on the pump
  Serial.println("Pumps ON");
  delay(2000);           // run the pump for a set time

  digitalWrite(P2A, LOW);  // turn off the pump
  digitalWrite(P4A, LOW);  // turn off the pump
  Serial.println("Pumps OFF");

  return;
}

void deflate(int time_ms) {
  // Switch solenoid on and off really quickly to let out a small amount of air
  
  Serial.println("Quick Switch Deflate");
  digitalWrite(S2A, HIGH);  // quickly switch solenoid from metal-common to common-plastic
  delay(time_ms);
  digitalWrite(S2A, LOW);   // quickly switch solenoid from common-plastic to metal-common

  return;
}

void empty() {
  // empty the bladders completely by switching the solenoid and letting the bladder return to atmospheric pressure
  Serial.println("Empty Baldder");
  digitalWrite(S2A, HIGH);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  digitalWrite(S4A, HIGH);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  digitalWrite(P2A, LOW);  // turn off the pump so as to not waste power (makes no difference for the bladder emptying)
  digitalWrite(P4A, LOW);  // turn off the pump so as to not waste power (makes no difference for the bladder emptying)
  delay(1000);
}

void everything() {
  digitalWrite(P2A, HIGH);  // turn on the pump
  digitalWrite(P4A, HIGH);  // turn on the pump
  digitalWrite(S2A, HIGH);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  digitalWrite(S4A, HIGH);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  delay(1000);
}

void solenoids() {
  digitalWrite(S2A, HIGH);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  digitalWrite(S4A, HIGH);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  Serial.println("Solenoids ON");
  delay(2000);

  digitalWrite(S2A, LOW);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  digitalWrite(S4A, LOW);  // switch solenoid position to "open" (common to plastic) to let all the air out)
  Serial.println("Solenoids OFF");
  delay(2000);
}

void loop() {
  solenoids();
//  inflate();
//  empty();

//  everything();
}

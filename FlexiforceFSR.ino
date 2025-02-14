int fsr1AnalogPin = 5; // FSR 1 (Yellow) is connected to analog pin 5
int fsr2AnalogPin = 0; // FSR 2 (Blue) is connected to analog pin 5
float fsr1Reading = 0;     // the analog reading from the FSR resistor divider
float fsr2Reading = 0;     // the analog reading from the FSR resistor divider

int counter = 0;
int calibrationSelect = 10;
 
void setup(void) {
  Serial.begin(9600); 
  Serial.println(); 
  Serial.println(); 
  Serial.println(); 
}

void printOutput(void) { // default
  while (true) {
    Serial.print("\t");
    Serial.print("Yellow:\t");
    Serial.print(analogRead(fsr1AnalogPin));
    Serial.print("\t");
    Serial.print("Blue:\t");
    Serial.println(analogRead(fsr2AnalogPin));
  }
}

void calibration(void) { // 0
  counter = 0;
  fsr1Reading = 0;
  Serial.println("Please place the mass on");
  delay(10000);
  Serial.println("Gathering data...");

  // Measure sensor readings for 5 seconds
  while(counter < 20000) {
//    Serial.println(analogRead(fsrAnalogPin));
    fsr1Reading = fsr1Reading + analogRead(fsr1AnalogPin);
    counter++;
  }

  Serial.print("Number of measurements: ");
  Serial.println(counter);

  Serial.print("Average measurement: ");
  Serial.println(fsr1Reading / counter);

  Serial.println("Remove mass");
  delay(10000);

  return;
}

float linearCalibration(float x) { // 1
  return 0.1824 * x;
}
 
void loop(void) {
  float value = analogRead(fsr1AnalogPin);
  float mass = 0;

  Serial.print("Mode Selected: ");
  
  switch (calibrationSelect) {
    case 0:
      Serial.println("Calibration");
      for (int i = 0; i < 5; i++) {
        calibration();
      }
      break;
    case 1:
      Serial.println("Linear Calibration");
      mass = linearCalibration(value);
      break;
    default:
      printOutput();
      break;
  }

  float force = mass * 9.80665;

  Serial.print("Force: ");
  Serial.println(force);
  
  delay(1000);
  exit(0);
}

const int ledPin =  LED_BUILTIN;
int ledState = LOW;
const int dir = 2; //determina a direção
const int stpPin = 3; //executa um passo
unsigned long previousMillis = 0;
double stepsPerRot = 200;

int stepperDirection = HIGH;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(stpPin, OUTPUT);
  digitalWrite(dir, stepperDirection); // low CW / high CCW
  Serial.begin(9600);
}

void loop() {
  backAndForth(3, 360, 12);
  delay(99999999999);


}

/*
 * Function: back and forth
 * Rotates stepper motor back and forth at specified parameters
 * loops: number of times to go back and forth
 * Degrees: range of motion over which motion is to span
 * rpm: speed in rotations per minute
 */
void backAndForth (int loops, double myDegrees, double rpm) {
  int steps = 0;
  int count = 0;
  double StepsTillDirectionChange = myDegrees*(stepsPerRot/360);
  double interval = 60000/(rpm*200);
  Serial.println(interval);
  
  while (count<=loops) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, HIGH);
      digitalWrite(stpPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(ledPin, LOW);
      digitalWrite(stpPin, LOW);
      steps++;
    }
    if (steps >= StepsTillDirectionChange) {
      count++;
      if (stepperDirection == LOW) {
        stepperDirection = HIGH;
      } else {
        stepperDirection = LOW;
      }
      digitalWrite(dir, stepperDirection);
      steps = 0;
    }
  }
}

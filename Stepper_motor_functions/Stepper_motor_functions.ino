#define CW  LOW
#define CCW HIGH

const double microStepSetting = 32;        //for full step, put 1. For half step, put 2. For 1/16 step, put 16. Etc :)
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
  //backAndForth(3, 360, 12);
  spin(3, 3, CCW);
  //delay(99999999999);


}

/*
   Function: back and forth
   Rotates stepper motor back and forth at specified parameters
   loops: number of times to go back and forth
   Degrees: range of motion over which motion is to span
   rpm: speed in rotations per minute
*/
void backAndForth (int loops, double myDegrees, double rpm) {
  int steps = 0;
  int count = 0;
  double StepsTillDirectionChange = myDegrees * (stepsPerRot * microStepSetting / 360);
  double interval = 60000 / (rpm * 200 * microStepSetting);
  Serial.println(interval);

  while (count <= loops) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, HIGH);
      digitalWrite(stpPin, HIGH);
      //delayMicroseconds(100);
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


/*
   Function: spin
   Rotates stepper motor around according to parameters
   rotations: number of rotations to complete
   rpm: speed in rotations per minute
   myDirection: direction in which to spin (use syntax CW or CCW)
*/
void spin (int rotations, double rpm, int myDirection) {
  int steps = 0;
  double interval = 60000 / (rpm * 200 * microStepSetting);
  digitalWrite(dir, myDirection);
  
  while (steps <= rotations * stepsPerRot) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, HIGH);
      digitalWrite(stpPin, HIGH);
      //delayMicroseconds(100);
      digitalWrite(ledPin, LOW);
      digitalWrite(stpPin, LOW);
      steps++;
    }
  }
}

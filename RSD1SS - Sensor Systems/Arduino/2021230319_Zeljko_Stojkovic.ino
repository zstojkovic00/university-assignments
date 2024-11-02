const int tempPin = A0;
const int photoresistorPin = A1;
const int buttonMinus = 6;
const int buttonPlus = 7;
const int greenPin = 9;
const int redPin = 10;
const int trigPin = 11;
const int echoPin = 12;

int buttonPlusState = LOW;
int buttonMinusState = LOW;

unsigned long lastMessageTime = 0;
unsigned long measurementStartTime = 0;
int measurementCount = 0;
float totalDistance = 0.0;
float totalTemperature = 0.0;
float totalIllumination = 0.0;


signed frequency = 5000; // (5 seconds)

void setup() {
  
   // Input with pull-up resistor (When button is not pressed, the pull-up resistor pulls the pin to a high logic level
  // and when the button is pressed the pin is pulled to a low logic level(ground))
  pinMode(buttonMinus, INPUT_PULLUP);
  pinMode(buttonPlus, INPUT_PULLUP);

  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(greenPin, HIGH); // Initially turn on green

  // Tells the Arduino to get ready to exchange messages with the Serial Monitor at a data rate of 9600 bits per second. 
  Serial.begin(9600);
}

void loop() {

  /// Capture the current time in milliseconds since the Arduino board started running
  unsigned long currentTime = millis();

  buttonMinusState = digitalRead(buttonMinus);
  buttonPlusState = digitalRead(buttonPlus);

  if (buttonPlusState == HIGH && buttonMinusState == LOW) {
    Serial.println("Plus button pressed");
    if (frequency < 10000) {
      frequency += 1000;
    }
    Serial.print("Frequency: ");
    Serial.print(frequency / 1000);
    Serial.println("s");
    buttonPlusState = LOW;
  } 
  else if (buttonMinusState == HIGH && buttonPlusState == LOW) {
    Serial.println("Minus button pressed");
    if (frequency > 1000) {
      frequency -= 1000;
    }
    Serial.print("Frequency: ");
    Serial.print(frequency / 1000);
    Serial.println("s");
    buttonMinusState = LOW;
  }
  
  
  // if time difference is greater or equal to specified `frequency`, basically if enough time has passed since the last message its time to send a new message
  if (currentTime - lastMessageTime >= frequency) {

    // Calculate the average measurements
    float averageDistance = totalDistance / measurementCount;
    float averageTemperature = totalTemperature / measurementCount;
    float averageIllumination = totalIllumination / measurementCount;

    // Print the message to the serial monitor
    Serial.println("**************************");
    Serial.print("Distance: ");
    Serial.print(averageDistance);
    Serial.println(" cm");
    Serial.print("Temperature: ");
    Serial.print(averageTemperature);
    Serial.println(" C");
    Serial.print("Illumination: ");
    Serial.print(averageIllumination);
    Serial.println(" lux");
    Serial.print("Count: ");
    Serial.println("**************************");


    if (averageTemperature > 30) {
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
    } else {
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, LOW);
    }

    // Reset variables for the next round of measurements
    measurementStartTime = currentTime;
    totalDistance = 0.0;
    totalTemperature = 0.0;
    totalIllumination = 0.0;
    measurementCount = 0;
    lastMessageTime = currentTime;
  }

// checks if enough time has passed since the last measurement and if so, next measurement will only be taken if atleast 0.5s have passed
if (currentTime - measurementStartTime >= 500) {
  float distance = measureDistance();
  float temperature = measureTemperature();
  float illumination = measureIllumination();
  
  measurementCount++;
  totalDistance += distance;
  totalTemperature += temperature;
  totalIllumination += illumination;
  measurementStartTime = currentTime;
  
}
  
  delay(100);
}

float measureDistance() {
  unsigned long duration;
  float distance;

  // Clears the trigger for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sends trigger for 10 microseconds and cuts off
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Duration input and distance calculations
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

float measureTemperature() {
  int tempRaw = analogRead(tempPin);
  float tempVoltage = tempRaw * 5.0 / 1023; // Convert to voltage (0-5V)
  float tempCelsius = (tempVoltage - 0.5) * 100; // Convert to temperature in Celsius

  return tempCelsius;
}

float measureIllumination() {
  
  int illumination = analogRead(photoresistorPin);
  return illumination;
}

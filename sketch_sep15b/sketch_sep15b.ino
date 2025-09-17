const int leds[] = {2, 3, 4, 5, 6, 7, 8, 9}; // LED pins
const int switchPin = 10;                    // Switch pin
const int pirPin = 11;                       // PIR sensor connected to digital pin 11
const int currentSensorPin = A1;             // ACS712 sensor connected to A1

float luxValue = -1.0; // Initialize lux value to a negative value
float powerWatts = 0.0;
bool motionDetected = false;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(pirPin, INPUT);
  pinMode(currentSensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int pirState = digitalRead(pirPin);
  
  // Read current sensor and update power consumption
  int analogValue = analogRead(currentSensorPin);
  float current = (analogValue - 512) / 102.4; // ACS712 sensitivity for 20A model
  powerWatts += abs(current) * 5; // Assuming a 5V supply voltage

  if (Serial.available() > 0) {
    luxValue = Serial.parseFloat();
  }

  if (pirState == HIGH) {
    // Motion detected, make LED at pin 2 brighter
    analogWrite(leds[0], 255); // Full brightness
    motionDetected = true;
  } else {
    motionDetected = false;
  }

  if (digitalRead(switchPin) == LOW) {
    // Switch is off, turn off all LEDs
    for (int i = 0; i < 8; i++) {
      digitalWrite(leds[i], LOW);
    }
  } else {
    // Switch is on
    if (luxValue < 100) {
      // Lux value is less than 100, turn on all LEDs except for pin 2
      for (int i = 0; i < 8; i++) {
        if (i != 0) {
          analogWrite(leds[i], 255); // Full brightness
        } else {
          if (motionDetected) {
            analogWrite(leds[i], 255); // Full brightness if motion detected
          } else {
            digitalWrite(leds[i], LOW); // Pin 2 off
          }
        }
      }
    } else if (luxValue >= 100 && luxValue <= 10000) {
      if (luxValue >= 300 && luxValue <= 500) {
        // Lux value between 300 and 500, set brightness to 70%
        for (int i = 0; i < 8; i++) {
          if (i != 0) {
            analogWrite(leds[i], 179); // 70% brightness
          } else {
            if (motionDetected) {
              analogWrite(leds[i], 255); // Full brightness if motion detected
            } else {
              digitalWrite(leds[i], LOW); // Pin 2 off
            }
          }
        }
      } else if (luxValue >= 900 && luxValue <= 1100) {
        // Lux value approximately 1000, set brightness to 50%
        for (int i = 0; i < 8; i++) {
          if (i != 0) {
            analogWrite(leds[i], 128); // 50% brightness
          } else {
            if (motionDetected) {
              analogWrite(leds[i], 255); // Full brightness if motion detected
            } else {
              digitalWrite(leds[i], LOW); // Pin 2 off
            }
          }
        }
      } else {
        // Lux value in the range (100, 300) or (500, 10000), turn off all LEDs except for pin 2
        for (int i = 0; i < 8; i++) {
          if (i != 0) {
            digitalWrite(leds[i], LOW);
          } else {
            if (motionDetected) {
              analogWrite(leds[i], 255); // Full brightness if motion detected
            } else {
              digitalWrite(leds[i], LOW); // Pin 2 off
            }
          }
        }
      }
    } else {
      // Lux value greater than 10,000, turn off all LEDs
      for (int i = 0; i < 8; i++) {
        digitalWrite(leds[i], LOW);
      }
    }
  }

  // Print lux value, PIR state, and cumulative power consumption to Serial Monitor
  Serial.print("Lux Value: ");
  Serial.println(luxValue);
  Serial.print("PIR State: ");
  Serial.println(pirState);
  Serial.print("Cumulative Power Consumption (Watts): ");
  Serial.println(powerWatts);

  delay(1000); // Adjust the delay as needed
}

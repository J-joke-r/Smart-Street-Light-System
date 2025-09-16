#include <Wire.h>
#include <BH1750.h>

const int leds[] = {2, 3, 4, 5, 6, 7, 8, 9}; // LED pins
const int switchPin = 10;                    // Switch pin
const int lightSensorPin = A0;               // BH1750 sensor connected to A0
const int pirPin = 11;                       // PIR sensor connected to digital pin 11

BH1750 lightSensor;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(switchPin, INPUT_PULLUP);
  lightSensor.begin();
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int lightIntensity = lightSensor.readLightLevel();
  int pirState = digitalRead(pirPin);

  if (pirState == HIGH) {
    // Motion detected, turn on all LEDs at full brightness
    for (int i = 0; i < 8; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } else {
    // No motion detected, control LEDs based on light intensity
    if (digitalRead(switchPin) == LOW) {
      // If the switch is pressed, turn on all LEDs
      for (int i = 0; i < 8; i++) {
        digitalWrite(leds[i], HIGH);
      }
    } else {
      // Control LEDs based on light intensity
      if (lightIntensity < 500) {
        // Low light intensity, LEDs glow dim
        for (int i = 0; i < 8; i++) {
          analogWrite(leds[i], 50);
        }
      } else if (lightIntensity > 1000) {
        // High light intensity, turn off LEDs
        for (int i = 0; i < 8; i++) {
          digitalWrite(leds[i], LOW);
        }
      } else {
        // Moderate light intensity, LEDs glow at medium brightness
        for (int i = 0; i < 8; i++) {
          analogWrite(leds[i], 150);
        }
      }
    }
  }

  // Print light intensity and PIR state to Serial Monitor
  Serial.print("Light Intensity: ");
  Serial.println(lightIntensity);
  Serial.print("PIR State: ");
  Serial.println(pirState);

  delay(1000); // Adjust the delay as needed
}

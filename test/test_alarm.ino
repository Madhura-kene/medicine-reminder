// test_alarm.ino
// Tests the 5-LED chaser animation and piezo buzzer for 5 seconds on startup

const int ledPins[] = {4, 5, 6, 7, 8};
const int buzzerPin = 9;
const int numLeds = 5;

unsigned long startTime;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  
  // Record startup time
  startTime = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Run the test for 5000 milliseconds (5 seconds)
  if (currentMillis - startTime < 5000) {
    // 5-LED Chaser animation
    int chaserSpeed = 100; // ms per LED
    int activeLed = (currentMillis / chaserSpeed) % numLeds;
    
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], i == activeLed ? HIGH : LOW);
    }
    
    // Buzzer pattern
    if ((currentMillis / 500) % 2 == 0) {
      tone(buzzerPin, 1000); // 1000 Hz tone
    } else {
      noTone(buzzerPin);
    }
  } else {
    // Test is over, turn everything off
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    noTone(buzzerPin);
  }
}

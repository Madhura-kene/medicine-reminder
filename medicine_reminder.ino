// medicine_reminder.ino
// Arduino Medicine Reminder with LED Chaser + Buzzer
// Timekeeping is based on millis(), assumes 24/7 power

const int ledPins[] = {4, 5, 6, 7, 8};
const int buzzerPin = 9;
const int numLeds = 5;

// Time constants in milliseconds
const unsigned long ONE_DAY = 86400000UL;      // 24 hours * 60 * 60 * 1000
const unsigned long ALARM1_TIME = 48600000UL;  // 1:30 PM (13.5 hours * 60 * 60 * 1000)
const unsigned long ALARM2_TIME = 73800000UL;  // 8:30 PM (20.5 hours * 60 * 60 * 1000)
const unsigned long ALARM_DURATION = 10000UL;  // 10 seconds

// START_OFFSET: Time since midnight when the Arduino is turned on.
// For example, if you power on the Arduino at 8:00 AM, 
// offset = 8 * 3600 * 1000 = 28800000UL
unsigned long START_OFFSET = 0; 

bool isAlarmActive = false;
unsigned long alarmStartTime = 0;

bool alarm1Triggered = false;
bool alarm2Triggered = false;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Calculate current time of day in milliseconds
  unsigned long timeOfDay = (currentMillis + START_OFFSET) % ONE_DAY;

  // Reset alarm triggers shortly after midnight
  if (timeOfDay < 5000) {
    alarm1Triggered = false;
    alarm2Triggered = false;
  }

  // Check if it's time for Alarm 1
  if (!isAlarmActive && !alarm1Triggered && timeOfDay >= ALARM1_TIME && timeOfDay < (ALARM1_TIME + 60000UL)) {
    isAlarmActive = true;
    alarmStartTime = currentMillis;
    alarm1Triggered = true;
  }

  // Check if it's time for Alarm 2
  if (!isAlarmActive && !alarm2Triggered && timeOfDay >= ALARM2_TIME && timeOfDay < (ALARM2_TIME + 60000UL)) {
    isAlarmActive = true;
    alarmStartTime = currentMillis;
    alarm2Triggered = true;
  }

  // Handle active alarm sequence
  if (isAlarmActive) {
    if (currentMillis - alarmStartTime < ALARM_DURATION) {
      runAlarmSequence(currentMillis);
    } else {
      // Alarm time is over, stop everything
      isAlarmActive = false;
      stopAlarm();
    }
  }
}

void runAlarmSequence(unsigned long currentMillis) {
  // 5-LED Chaser animation (e.g., each LED on for 100ms)
  int chaserSpeed = 100; // ms per LED
  int activeLed = (currentMillis / chaserSpeed) % numLeds;
  
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], i == activeLed ? HIGH : LOW);
  }

  // Buzzer pattern: beep on and off every 500ms
  // Tuning: change 1000 to a different frequency if desired (e.g. 2000 for higher pitch)
  if ((currentMillis / 500) % 2 == 0) {
    tone(buzzerPin, 1000); 
  } else {
    noTone(buzzerPin);
  }
}

void stopAlarm() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  noTone(buzzerPin);
}

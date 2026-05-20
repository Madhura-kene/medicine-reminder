# Arduino Medicine Reminder 

![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

A simple, beginner-friendly Arduino Uno based medicine reminder system. This project triggers a **5-LED chaser animation** and a **piezo buzzer** simultaneously for 10 seconds at scheduled medicine times (1:30 PM and 8:30 PM daily).

## Project Overview & Motivation 
Remembering to take daily medications can be challenging. This project provides an accessible, fun, and highly visible way to remind yourself or a loved one to take medicine. 

It is designed with **minimal components**—no Real-Time Clock (RTC) module is required. The system relies entirely on the Arduino's built-in `millis()` function for timekeeping. As long as the board remains powered 24/7, it will accurately trigger the alarms at the intended time!

## Components List & Wiring 

| Component | Quantity | Arduino Pin | Notes |
| :--- | :---: | :---: | :--- |
| **Arduino Uno** | 1 | N/A | The brain of the project |
| **White LEDs** | 5 | Pins 4, 5, 6, 7, 8 | Used for the chaser animation |
| **Piezo Buzzer** | 1 | Pin 9 | Used for the audible alarm beep |
| **220Ω Resistor** | 5 | N/A | Used in series with each LED (recommended) |
| **Breadboard** | 1 | N/A | For prototyping |
| **Jumper Wires** | Varies | N/A | For connections |

### Circuit Diagram Description
1. **LEDs:** Connect the positive leg (anode) of each LED to pins 4, 5, 6, 7, and 8. Connect the negative leg (cathode) of each LED to a 220Ω resistor, and connect the other end of the resistor to the common Ground (GND) rail on the breadboard.
2. **Piezo Buzzer:** Connect the positive pin of the buzzer to Arduino Pin 9. Connect the negative pin to the common Ground (GND) rail.
3. **Ground:** Connect the GND rail on your breadboard to one of the GND pins on the Arduino Uno.

## How `millis()` Timekeeping Works 

The `millis()` function returns the number of milliseconds passed since the Arduino board began running the current program. By tracking this number, we can create a "24-hour clock" to calculate what time it is relative to when the Arduino was turned on.

```cpp
unsigned long timeOfDay = (currentMillis + START_OFFSET) % ONE_DAY;
```

### Limitations of `millis()`
- **Power Reliance:** If the Arduino loses power or resets, the internal clock resets to 0. 
- **Rollover:** The `millis()` function resets to zero after approximately 50 days (which is accounted for, but can cause tiny shifts).
- **Drift:** The internal oscillator of an Arduino isn't perfectly accurate. Over the course of a week, the time might drift by a few minutes.

## Configuration Guide 

### How to Set `START_OFFSET` (Power-on Time)
By default, the code assumes you power on the Arduino at precisely midnight (00:00). If you want to turn it on at a different time, you must calculate the `START_OFFSET`.

The offset is the number of milliseconds since midnight.
**Formula:** `(Hours * 3600 * 1000) + (Minutes * 60 * 1000)`

**Example:** Powering on at 8:00 AM
```cpp
// 8 hours * 3600 seconds * 1000 milliseconds
unsigned long START_OFFSET = 28800000UL; 
```

### How to Change Reminder Times
The times are defined in milliseconds since midnight. Modify these constants at the top of the code:
```cpp
const unsigned long ALARM1_TIME = 48600000UL;  // 1:30 PM (13.5 hours * 3600 * 1000)
const unsigned long ALARM2_TIME = 73800000UL;  // 8:30 PM (20.5 hours * 3600 * 1000)
```
You can easily calculate a new time by multiplying the hour (in 24-hour format) by `3600000`. E.g. 6:00 PM (18:00) is `18 * 3600000 = 64800000UL`.

### Buzzer Frequency Tuning Guide 
If you want to change the pitch of the buzzer to make it more noticeable or less annoying, you can adjust the frequency in the `runAlarmSequence` function:
```cpp
tone(buzzerPin, 1000); // Current pitch is 1000 Hz
```
- **Higher Pitch:** Increase to `2000` or `3000`.
- **Lower Pitch:** Decrease to `500` or `800`.

## Future Improvements 
For a more robust and permanent installation, consider upgrading the project with a **DS3231 RTC (Real-Time Clock) module**. 
Adding an RTC module will:
- Eliminate time drift.
- Remember the current time even if the Arduino loses power (thanks to its coin-cell battery).
- Allow you to use standard `Hours:Minutes:Seconds` programming logic without worrying about `START_OFFSET` calculations!

#include <TinyWireM.h>
#include <Tiny4kOLED.h>

#define TRIG_PIN PB3
#define ECHO_PIN PB4

long duration;
float distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);

  oled.setFont(FONT8X16);
  oled.clear();
  oled.on();

  delay(1000);
}

float getDistance() {
  // Make sure trigger is LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10 microsecond trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo pulse
  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo is received
  if (duration == 0) {
    return -1;
  }

  // Calculate distance in centimeters
  distance = duration * 0.0343 / 2;

  return distance;
}

void loop() {

  float d = getDistance();

  oled.clear();

  oled.setCursor(15, 2);
  oled.print("DISTANCE");

  oled.setCursor(15, 4);

  if (d < 0) {
    oled.print("No Echo");
  } 
  else {
    oled.print(d, 1);
    oled.print(" cm");
  }

  delay(500);
}

#include <Adafruit_NeoPixel.h>

#define trigPin 10
#define echoPin 8
#define LED_PIN 6      // Pin for the WS2812B LED strip
#define NUMPIXELS 450   // Number of LEDs on your strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 65) {
    // Fade in to red
    fadeToColor(strip.Color(255, 0, 0), 10);  // Red
  } else {
    // Fade out
    fadeToColor(strip.Color(0, 0, 0), 10);  // Off
  }

  delay(500);  // Wait before taking another measurement
}

// Function to gradually fade to a specified color
void fadeToColor(uint32_t color, int steps) {
  uint32_t startColor = strip.getPixelColor(0);  // Assume all LEDs start with the same color
  uint8_t startR = (startColor >> 16) & 0xFF;
  uint8_t startG = (startColor >> 8) & 0xFF;
  uint8_t startB = startColor & 0xFF;
  uint8_t endR = (color >> 16) & 0xFF;
  uint8_t endG = (color >> 8) & 0xFF;
  uint8_t endB = color & 0xFF;

  for (int step = 0; step <= steps; step++) {
    uint8_t r = map(step, 0, steps, startR, endR);
    uint8_t g = map(step, 0, steps, startG, endG);
    uint8_t b = map(step, 0, steps, startB, endB);

    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
    delay(30);  // Adjust delay for smooth transition speed
  }
}

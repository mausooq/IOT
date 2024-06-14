#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int trigPin = 5;
const int echoPin = 18;
// Define sound speed in cm/uS
const float SOUND_SPEED = 0.034;

long duration;
float distanceCm;

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize the OLED display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);

    // Initialize ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    // Clear trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Set trigPin to HIGH state for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read echoPin, return sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate distance
    distanceCm = (duration * SOUND_SPEED) / 2;
    
    // Print distance to Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    
    // Display distance on OLED
    display.clearDisplay();
    display.setCursor(0, 20);
    display.print("Distance: ");
    display.print(distanceCm);
    display.print(" cm");
    display.display();
    delay(1000); // Wait for a second
}

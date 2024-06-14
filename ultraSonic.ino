const int trigPin = 5;
const int echoPin = 18;
// Define sound speed in cm/uS
const float SOUND_SPEED = 0.034;
            
long duration;
float distanceCm;
            
void setup() {
    Serial.begin(9600); // Start serial communication
    pinMode(trigPin, OUTPUT); // Set trigPin as an output
    pinMode(echoPin, INPUT); // Set echoPin as an input
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
                
    delay(1000); // Wait for a second
}
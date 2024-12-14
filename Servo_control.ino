#include <ESP32Servo.h>

static const int servoPin = 12;

Servo servo1;

void setup() {
  Serial.begin(115200);
  servo1.attach(servoPin); // Attach the servo to the pin
}

void loop() {
  // Turn servo to 90 degrees
  servo1.write(0);
  Serial.println("Servo at 90 degrees");
  delay(3000); // Wait for 3 seconds

  // Turn servo back to 0 degrees
  servo1.write(90);
  Serial.println("Servo at 0 degrees");
  delay(3000); // Wait for 3 seconds
}

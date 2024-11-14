#include <BluetoothSerial.h>

// Initialize Bluetooth
BluetoothSerial SerialBT;

// Define motor control pins
const int IN1 = 16;
const int IN2 = 17;
const int IN3 = 18;
const int IN4 = 19;
const int EN1 = 4;
const int EN2 = 5;

// Define motor speeds
int speedCar = 255; // Initial car speed. Change as needed from 0 to 255.

char command;

void setup() {
  // Set motor control pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  // Set motor speeds
  analogWrite(EN1, speedCar);
  analogWrite(EN2, speedCar);

  // Start the Bluetooth serial
  SerialBT.begin("ESP32_BT"); // Bluetooth device name

  // Print a message to the Serial Monitor
  Serial.begin(115200);
  Serial.println("ESP32 ready to control the robot!");
}

void loop() {
  // Check if a client has connected
  if (SerialBT.available() > 0) {
    command = SerialBT.read();
    Stop(); // Initialize with motors stopped
    // Serial.println(command);
    switch (command) {
      case 'F': forward(); break;
      case 'B': back(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case '1': speedCar = 61; break;
      case '2': speedCar = 102; break;
      case '3': speedCar = 153; break;
      case '4': speedCar = 204; break;
      case '5': speedCar = 255; break;
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN1, speedCar);
  analogWrite(EN2, speedCar);
}

void back() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN1, speedCar);
  analogWrite(EN2, speedCar);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN1, speedCar);
  analogWrite(EN2, speedCar);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN1, speedCar);
  analogWrite(EN2, speedCar);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <Keypad.h>

int e;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3D
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Encoder myEnc(48, 2);
Encoder Enc(49, 3);
Encoder Elbow(50, 18);
Encoder RotateOne(51, 19);
Encoder RotateTwo(52, 46);
Encoder WristOne(51, 19);
Encoder WristTwo(52, 46);
Encoder Hand(53, 47);
int mathVal;

int motor;
int changeMessage = 0;

int bootMessage = 0;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[COLS][ROWS] = {
  {'1', '4', '7', '0'},
  {'2', '5', '8', 'F'},
  {'3', '6', '9', 'E'},
  {'A', 'B', 'C', 'D'}
};

byte colPins[COLS] = {33, 32, 31, 30};
byte rowPins[ROWS] = {37, 36, 35, 34};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


int m1;
int m2;
int m3;
int m4;

void setup() {
  bootMessage = 0;
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
} long newPosition;
long oldPosition  = -999;

void loop() {
  if (bootMessage == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 32);
    display.print("Please press a ");
    display.setCursor(20, 39);
    display.print("letter key to ");
    display.setCursor(20, 46);
    display.print("begin.");
    display.display();
    bootMessage = 1;
  }

int y = analogRead(2);

char customKey = customKeypad.getKey();
int g = customKey;
//Key Code, 0-9 Correspond to # on Keypad
//17-22 Correspond to A-F on Keypad.
int key = map(g, 48, 70, 0, 22);

if (e == 0) {
  newPosition = myEnc.read();
} if (e == 1) {
  newPosition = Enc.read();
} if (e == 2) {
  newPosition = Elbow.read();
} if (e == 3) {
  newPosition = RotateOne.read() + RotateTwo.read();
} if (e == 4) {
  newPosition = WristOne.read() - WristTwo.read();
} if (e == 5) {
  newPosition = Hand.read();
}


if (key == 17) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  m1 = 14;
  m2 = 15;
  m3 = -1;
  m4 = -1;
  e = 0;
  motor = 1;
  changeMessage = 1;
} if (key == 18) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  m1 = 4;
  m2 = 5;
  m3 = -1;
  m4 = -1;
  e = 1;
  motor = 2;
  changeMessage = 1;
} if (key == 19) {

  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  m1 = 7;
  m2 = 6;
  m3 = -1;
  m4 = -1;
  e = 2;
  motor = 3;
  changeMessage = 1;
} if (key == 20) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  m1 = 22;
  m2 = 23;
  m3 = 24;
  m4 = 25;
  e = 3;
  motor = 4;
  changeMessage = 1;
} if (key == 21) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  m1 = 22;
  m2 = 23;
  m3 = 25;
  m4 = 24;
  e = 4;
  motor = 5;
  changeMessage = 1;
} if (key == 22) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  m1 = 26;
  m2 = 27;
  m3 = -1;
  m4 = -1;
  e = 5;
  motor = 6;
  changeMessage = 1;
}

// if (key == 20 && key == 21) {
//  Serial.println("ping");
//}

if (0 <= y && y <= 262) {
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
} else if (762 <= y && y <= 1023 ) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
} else if (262 <= y && y <= 762) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}

mathVal = newPosition - oldPosition;

if (newPosition != oldPosition) {
  Serial.print("Change in Value: ");
  Serial.println(mathVal);
  oldPosition = newPosition;
  Serial.print("New Position: ");
  Serial.println(newPosition);
  Serial.println("=============");
}

if (changeMessage == 1) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1, 0);
  display.print("Motor:");
  display.setTextSize(1);
  if (motor == 1) {
    display.setCursor(20, 32);
    display.print("Base");
  } if (motor == 2) {
    display.setCursor(20, 32);
    display.print("Shoulder");
  } if (motor == 3) {
    display.setCursor(20, 32);
    display.print("Elbow");
  } if (motor == 4) {
    display.setCursor(20, 32);
    display.print("Wrist - Spin");
  } if (motor == 5) {
    display.setCursor(20, 32);
    display.print("Wrist - Adjust");
  } if (motor == 6) {
    display.setCursor(20, 32);
    display.print("Hand");
  }
  display.display();
  changeMessage = 0;
}
}

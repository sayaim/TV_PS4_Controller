#define IR_SEND_PIN 3
#include <IRremote.hpp>

const int IR_SEND_PIN = 2;
const int power = 3;           //電源
const int input_switch = 4;    //入力切替
const int enter = 5;           //決定　：　circle
const int back =6;             //戻る　：　cross
const int joystick_x = A0;
const int joystick_y = A1;
const int joystick_sw = 7

int i = 0;
int mode = 0;
unsigned long time_data = 0;
unsigned long second = 0;
int x = analogRead(joystick_x);
int y = analogRead(joystick_y);
int sw = digitalRead(joystick_sw);


void setup() {

  Serial.begin(9600);
  IrSender.begin();
  pinMode(power, INPUT_PULLUP);
  pinMode(input_switch, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);
  pinMode(joystick_sw, INPUT_PULLUP);

}


void loop() {

  if (digitalRead(power) == LOW) {
    IrSender.sendPanasonic(0x8, 0x3D, 0);
  }
  if (digitalRead(input_switch) == LOW) {
    while (i < 6) {
      IrSender.sendPanasonic(0x8, 0x5, 0);
      delay(100);
    }
  }
  if (digitalRead(enter) == LOW) {
    IrSender.sendPanasonic(0x8, 0x49, 0);
  }
  if (digitalRead(back) == LOW) {
    IrSender.sendPanasonic(0x8, 0xD4, 0);
  }

  if (mode == 0) {
    tv_mode();
  } else {
    ps4_mode();
  }

  if (digitalRead(enter) == LOW && digitalRead(back) == LOW) {
    mode = 1 - mode;
  }

// 家のLEDlight　off
  if (sw == 0) {
    time_data = millis();
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    if (time_data == 432000000) {         // 5時間後
      IrSender.sendNEC(0x6D82, 1A, 0);
    }
  }
  
  delay(100);
}


void tv_mode() {
  // volume_up
  if (y < 50) {
    IrSender.sendPanasonic(0x8, 0x20, 0);
  }
  //  volume_down
  if (y > 970) {
    IrSender.sendPanasonic(0x8, 0x21, 0);
  }
  //  ch_next
  if (x > 970) {
    IrSender.sendPanasonic(0x8, 0x34, 0);
  }
  //  ch_previous
  if (x < 50) {
    IrSender.sendPanasonic(0x8, 0x35, 0);
  }
}


void ps4_mode() {
  // up
  if (y < 50) {
    IrSender.sendPanasonic(0x8, 0x4A);
  }
  //  down
  if (y > 970) {
    IrSender.sendPanasonic(0x8, 0x4B);
  }
  //  right
  if (x > 970) {
    IrSender.sendPanasonic(0x8, 0x4F);
  }
  //  left
  if (x < 50) {
    IrSender.sendPanasonic(0x8, 0x4E);
  }
}
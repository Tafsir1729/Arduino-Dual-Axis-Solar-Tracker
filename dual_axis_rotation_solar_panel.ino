#include <Servo.h>

int mode = 0;

int unnamed = 0;

int buttonState = 0;

int prevButtonState = 0;

int topLeftLight = 0;

int i = 0;

int topRightLight = 0;

int bottomLeftLight = 0;

int bottomRightLight = 0;

int LeftLight = 0;

int RightLight = 0;

int TopLight = 0;

int BottomLight = 0;

int j = 0;

Servo servo_9;

Servo servo_10;

void setup()
{
  pinMode(7, INPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);
  servo_9.attach(9);

  pinMode(A1, INPUT);
  servo_10.attach(10);

  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop()
{
  buttonState = digitalRead(7);
  if (buttonState != prevButtonState) {
    if (buttonState == HIGH) {
      if (mode == 1) {
        mode = 0;
        digitalWrite(12, HIGH);
        digitalWrite(11, LOW);
      } else {
        mode = 1;
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
      }
    }
  }
  prevButtonState = buttonState;
  delay(50); // Wait for 50 millisecond(s)
  if (mode == 0) {
    servo_9.write(map(analogRead(A0), 0, 1023, 10, 170));
    servo_10.write(map(analogRead(A1), 0, 1023, 10, 170));
  } else {
    topLeftLight = map(analogRead(A2), 0, 1023, 0, 100);
    topRightLight = map(analogRead(A3), 0, 1023, 0, 100);
    bottomLeftLight = map(analogRead(A4), 0, 1023, 0, 100);
    bottomRightLight = map(analogRead(A5), 0, 1023, 0, 100);
    TopLight = ((topRightLight + topLeftLight) / 2);
    BottomLight = ((bottomRightLight + bottomLeftLight) / 2);
    LeftLight = ((topLeftLight + bottomLeftLight) / 2);
    RightLight = ((topRightLight + bottomRightLight) / 2);
    if (abs((RightLight - LeftLight)) > 5) {
      if (RightLight < LeftLight) {
        if (servo_9.read() < 160) {
          servo_9.write((servo_9.read() + 1));
        }
      }
      if (RightLight > LeftLight) {
        if (servo_9.read() > 20) {
          servo_9.write((servo_9.read() - 1));
        }
      }
    }
    if (abs((TopLight - BottomLight)) > 5) {
      if (TopLight > BottomLight) {
        if (servo_10.read() < 160) {
          servo_10.write((servo_10.read() + 1));
        }
      }
      if (TopLight < BottomLight) {
        if (servo_10.read() > 20) {
          servo_10.write((servo_10.read() - 1));
        }
      }
    }
  }
}
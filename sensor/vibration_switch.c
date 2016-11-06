#include <wiringPi.h>
#include <stdio.h>

/**
 * This program is used to test both the knock_sensor and rgb_led.
 *
 * gcc -lwiringPi -o bin/vibration_switch vibration_switch.c
 */

#define VibratePin	0
#define Gpin		1
#define Rpin		2

#define CHANGE_DELAY    1000

void setLedColor(int color) {
  pinMode(Gpin, OUTPUT);
  pinMode(Rpin, OUTPUT);
  if (color == 0) {
    digitalWrite(Rpin, HIGH);
    digitalWrite(Gpin, LOW);
  } else if (color == 1) {
    digitalWrite(Rpin, LOW);
    digitalWrite(Gpin, HIGH);
  } else {
    printf("LED Error");
  }
}

int currentStatus = 0;
void printStatus(int newStatus) {
  if (newStatus != currentStatus) {
    if (newStatus == 0)
      printf("...ON\n");
    if (newStatus == 1)
      printf("OFF..\n");
    currentStatus = newStatus;
  }
}

int main() {
  int status = 0;
  int tmp = 0;
  int value = 1;

  if (wiringPiSetup() == -1) {
    // when initialize wiring failed, print message to screen
    printf("setup wiringPi failed !");
    return 1; 
  }

  pinMode(VibratePin, INPUT);

  while(1) {
    value = digitalRead(VibratePin);
    if (tmp != value){
    status ++;
    if (status > 1) {
      status = 0;
    }
    setLedColor(status);	
    printStatus(status);
    delay(CHANGE_DELAY);
  }
}
return 0;
}

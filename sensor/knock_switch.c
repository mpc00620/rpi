#include <wiringPi.h>
#include <stdio.h>

/**
 *
 * gcc -lwiringPi -o bin/knock_switch knock_switch.c
 */

#define ShockPin 0
#define LedPin 1

#define CHANGE_DELAY 100

int main() {
  int count;
  if (wiringPiSetup() == -1) {
    // when initialize wiring failed, print message to screen
    printf("setup wiringPi failed !");
    return 1; 
  }

  pinMode(ShockPin, INPUT);
  pinMode(LedPin, OUTPUT);

  while(1) {
    if(digitalRead(ShockPin) == LOW) {
      count++;
      printf("Detected knocking! Count=%d\n", count);
      digitalWrite(LedPin, !digitalRead(LedPin)); 
      delay(CHANGE_DELAY);
    } 
  }
  return 0;
}

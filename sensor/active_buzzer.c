#include <wiringPi.h>
#include <stdio.h>

/**
 *
 * gcc -lwiringPi -o bin/active_buzzer active_buzzer.c
 */

#define BuzzerPin      0

#define CHANGE_DELAY 100

int main() {
  if (wiringPiSetup() == -1) {
    // when initialize wiring failed, print message to screen
    printf("setup wiringPi failed !");
    return 1; 
  }

  pinMode(BuzzerPin,  OUTPUT);

  while(1) {
    digitalWrite(BuzzerPin, HIGH);
    delay(CHANGE_DELAY);
    digitalWrite(BuzzerPin, LOW);
    delay(CHANGE_DELAY);	
  }

  return 0;
}


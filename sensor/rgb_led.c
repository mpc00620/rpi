#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

/**
 *
 * gcc -lwiringPi -o bin/rgb_led rgb_led.c
 */

#define uchar unsigned char

#define LedPinRed    0
#define LedPinGreen  1
#define LedPinBlue   2

#define CHANGE_DELAY  100 

typedef struct rgb_color {
  uchar red;
  uchar green;
  uchar blue;
} rgb_color;

void ledInit() {
  softPwmCreate(LedPinRed,  0, 100);
  softPwmCreate(LedPinGreen,0, 100);
  softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(rgb_color color_val) {
  softPwmWrite(LedPinRed,   color_val.red);
  softPwmWrite(LedPinGreen, color_val.green);
  softPwmWrite(LedPinBlue,  color_val.blue);
}

int main() {
  if(wiringPiSetup() == -1) {
    // when initialize wiring failed, print message to screen
    printf("setup wiringPi failed !");
    return 1;
  }

  ledInit();

  while(1) {
    int r = 0;
    for (; r < 256; r += 25) {
      int g = 0;
      for (; g < 256; g += 25) {
        int b = 0;
        for (; b < 256; b += 25) {
          rgb_color color_value = {r, g, b};
          ledColorSet(color_value);
          delay(CHANGE_DELAY);
        }
      }
    }
    delay(CHANGE_DELAY * 100);
  }

  return 0;
}

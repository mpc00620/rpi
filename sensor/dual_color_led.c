#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

/**
 *
 * gcc -lwiringPi -o bin/dual_color_led dual_color_led.c
 */

#define uchar unsigned char

#define LedPinRed    0
#define LedPinGreen  1

#define CHANGE_DELAY  500

typedef struct rgb_color {
  uchar red;
  uchar green;
  uchar blue;
} rgb_color;

void ledInit() {
  softPwmCreate(LedPinRed,  0, 100);
  softPwmCreate(LedPinGreen,0, 100);
}

void ledColorSet(rgb_color color_val) {
  softPwmWrite(LedPinRed,   color_val.red);
  softPwmWrite(LedPinGreen, color_val.green);
}

int main() {
  if(wiringPiSetup() == -1) {
    // when initialize wiring failed, print message to screen
    printf("setup wiringPi failed !");
    return 1;
  }

  ledInit();

  rgb_color red   = {0xff, 0x00, 0x00};
  rgb_color green = {0x00, 0xff, 0x00};
  rgb_color custom_color_1 = {0xff, 0x45, 0x00};
  rgb_color custom_color_2 = {0xff, 0xff, 0x00};
  rgb_color custom_color_3 = {0x7c, 0xfc, 0x00};

  rgb_color color_sequence[5] = {red, green, custom_color_1, custom_color_2, custom_color_3};

  int i = 0;
  while(1) {
    ledColorSet(color_sequence[i%5]);
    delay(CHANGE_DELAY);
    i++;
  }

  return 0;
}

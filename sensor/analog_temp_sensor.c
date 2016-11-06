#include <wiringPi.h>
#include <stdio.h>
#include <math.h>

/**
 *
 * gcc -lwiringPi -lm -o bin/analog_temp_sensor analog_temp_sensor.c
 */


typedef unsigned char uchar;
typedef unsigned int uint;

#define ADC_CS 0
#define ADC_CLK 1
#define ADC_DIO 2

#define CHANGE_DELAY 1000
#define INPUT_VOLTAGE 5.0
#define READING_LEVELS 1024.0
#define ZERO_CELCIUS_IN_KELVIN 273.15

uchar get_ADC_Result() {
  uchar i;
  uchar dat1=0, dat2=0;
  digitalWrite(ADC_CS, 0);
  digitalWrite(ADC_CLK,0);
  digitalWrite(ADC_DIO,1); delayMicroseconds(2);
  digitalWrite(ADC_CLK,1); delayMicroseconds(2);
  digitalWrite(ADC_CLK,0); 
  digitalWrite(ADC_DIO,1); delayMicroseconds(2);
  digitalWrite(ADC_CLK,1); delayMicroseconds(2);
  digitalWrite(ADC_CLK,0); 
  digitalWrite(ADC_DIO,0); delayMicroseconds(2);
  digitalWrite(ADC_CLK,1); 
  digitalWrite(ADC_DIO,1); delayMicroseconds(2);
  digitalWrite(ADC_CLK,0); 
  digitalWrite(ADC_DIO,1); delayMicroseconds(2);

  for(i=0; i<8; i++) {
    digitalWrite(ADC_CLK,1); delayMicroseconds(2);
    digitalWrite(ADC_CLK,0); delayMicroseconds(2);
    pinMode(ADC_DIO, INPUT);
    dat1=dat1<<1 | digitalRead(ADC_DIO);
  }

  for(i=0; i<8; i++) {
    dat2 = dat2 | ((uchar)(digitalRead(ADC_DIO))<<i);
    digitalWrite(ADC_CLK,1); delayMicroseconds(2);
    digitalWrite(ADC_CLK,0); delayMicroseconds(2);
  }

  digitalWrite(ADC_CS,1);

  return (dat1==dat2) ? dat1 : 0;
}


int main() {
  uchar analogVal;
  double voltageReading, Rt, temp;

  if (wiringPiSetup() == -1) {
    // when initialize wiring failed, print message to screen
    printf("setup wiringPi failed !");
    return 1; 
  }

  pinMode(ADC_CS, OUTPUT);
  pinMode(ADC_CLK, OUTPUT);

  while(1) {
    pinMode(ADC_DIO, OUTPUT);
    analogVal = get_ADC_Result();
    printf("analogValue=%d\n", analogVal);
    voltageReading = INPUT_VOLTAGE * (double)(analogVal) / READING_LEVELS;

    printf("voltage=%lf\n", voltageReading); 
    printf("temparature=%lf celcius\n", (voltageReading-0.5)*100.0); 
    printf("temparature=%lf farenheit\n", ((voltageReading-0.5)*100.0*9.0)/5.0 + 32.0); 
    
    Rt = 10000 * (double)(voltageReading) / (INPUT_VOLTAGE - (double)(voltageReading));
    temp = 1 / (((log(Rt/10000)) / 3950)+(1 / (ZERO_CELCIUS_IN_KELVIN + 25)));
    temp = temp - ZERO_CELCIUS_IN_KELVIN;

    printf("Current temperature : %lf C\n", temp);
    delay(CHANGE_DELAY);
  }

  return 0;
}

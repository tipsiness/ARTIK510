#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int analogRead(int pin); 
int inputPin = 0; 
int currentRun = 0;
const int MAX_RUNS = 10;

int main(void) { 
    float tmp_val;
    while(currentRun < MAX_RUNS) {   
        int sensorVal = analogRead(inputPin);   
        tmp_val = sensorVal * 0.439453125 * 2; //mV
        printf("Raw: %d, Voltage(mV): %f, ", sensorVal, tmp_val);

        currentRun++;        
        sleep(1); 
    }
}

int analogRead(int pin) { 
  FILE * fd;
  char fName[64];
  char val[8];
 
  // open value file
  sprintf(fName, "/sys/devices/12d10000.adc/iio:device0/in_voltage%d_raw", pin);
 
  if((fd = fopen(fName, "r")) == NULL) {
     printf("Error: can't open analog voltage value\n");   
     return 0; 
  }	
 
  fgets(val, 8, fd);
  fclose(fd);
 
  return atoi(val);
}


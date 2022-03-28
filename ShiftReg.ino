#include "SimpleShiftRegister.h"

////////////////////////////////////////////////// EXAMPLE ////////////////////////////

#define CLOCK_PIN 4
#define DATA_PIN 2
#define LATCH_PIN 3
#define CLEAR_REGISTER_PIN 5
#define NUMBER_OF_SERIAL_ICS 3 // ex. if we want to connect 3 shift registers in series 

//connecting 2 or more shift registers in series:
// QH' is the serial out pin and it connects to the data pin on the next shift register
// connect the clock pin, lathc pin and clear register in paralel with all the shift registerss

ShiftRegister reg(CLOCK_PIN, DATA_PIN, LATCH_PIN, CLEAR_REGISTER_PIN, NUMBER_OF_SERIAL_ICS);

// if you are declaring only one shift registr, you dont have to pass the NUMBER_OF_SERIAL_ICS value to the constructor

void setup(){
  Serial.begin(115200);
  reg.init(); //initialize the ic

}

void loop(){

  for(int i = 0; i<reg.getSize(); i++){
    reg[i] = true;
    reg.execute();
    delay(30);
    reg[i] = false;
    reg.execute();
    delay(30);
  }

  for(int i = reg.getSize()- 1; i>0; i--){
    reg[i] = true;
    reg.execute();
    delay(30);
    reg[i] = false;
    reg.execute();
    delay(30);
  }

  Serial.println(reg.getSize());
 
}
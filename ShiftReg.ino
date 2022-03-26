#include "SimpleShiftRegister.h"

////////////////////////////////////////////////// EXAMPLE ////////////////////////////

#define CLOCK_PIN 4
#define DATA_PIN 2
#define LATCH_PIN 3
#define CLEAR_REGISTER_PIN 5

ShiftRegister reg(CLOCK_PIN, DATA_PIN, LATCH_PIN, CLEAR_REGISTER_PIN);

void setup(){
  Serial.begin(115200);
  reg.init(); //initialize the ic

}

void loop(){

  reg.writeToRegister(10); //writes the value 10 in binary into the register 00001010
  delay(1000);
  Serial.println(reg.getValue()); // prints the current value in  the register  ex. 10
  //reg.getValue() returns int with the current value of the register

  reg[3] = false; // setting the third bit of the register true or false and you must use .execute();
  reg.execute(); //when you use [ ] to output the changed values of bit array into register
  delay(1000);

  reg[4] = !reg[4]; // toogle the 4 bit of the register
  reg.execute(); 
  delay(1000);

  Serial.println(reg.getValue());
  delay(1000);

  reg[0] = true; //  
  reg[1] = true; //  THE VALUE IS STILL CHANGED WITHOUT THE .execute() METHOD
  reg[2] = true; //
  reg[3] = true; //

  Serial.println(reg.getValue());
  delay(1000);
  reg.execute();

}
//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
//          Simple Class for interfacing the 74HC595 Shift Register                 //
//                                                                                  //
//                      Created by Petar Chichev                                    //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////




class ShiftRegister{
	
	private:
		
		int SIZE_OF_ARRAY;
		short pinClock, pinData, pinLatch, clearRegisterPin;
		bool latch = false;
    short numberOfShiftRegisters;
		
		// it takes 8 bytes since one boolean variable is 1 byte
		// using calloc to set all mem blocks to 0
		bool* bitArray; 

   
    void latchUp(){
      digitalWrite(pinLatch,0);
    }

    void latchDown(){
      digitalWrite(pinLatch,1);
    }

    void writeBit(bool value){
      digitalWrite(pinData,value);
      digitalWrite(pinClock,1);
      digitalWrite(pinClock,0);
    }

    void clearRegister(){
       digitalWrite(clearRegisterPin, 0);
       digitalWrite(clearRegisterPin, 1);
     }
		
			
		void writeArrayToRegister(bool latch){
      //first clear the register
      clearRegister();
			// code for writing the array of bits into the microcontroller

        latchUp();
      //code
        for(int i = SIZE_OF_ARRAY -1; i >= 0; i--){
          writeBit(bitArray[i]);
        }

      if(latch){
        //refresh the ic
        latchDown();
      }
		}
		
		
	public:
		
			~ShiftRegister(){
			//free allocated memory
			free(bitArray);
		}

    //initialize all pins
     void init(){
       pinMode(pinLatch, OUTPUT);
       pinMode(pinClock, OUTPUT);
       pinMode(pinData, OUTPUT);
       pinMode(clearRegisterPin, OUTPUT);
       digitalWrite(pinLatch,0);
       digitalWrite(pinClock,0);
       digitalWrite(pinData,0);
       digitalWrite(clearRegisterPin, 1);
    }

		
		ShiftRegister(short pinClock, short pinData, short pinLatch, short clearRegisterPin, short numberOfShiftRegisters = 1){
			
			this->pinClock = pinClock;
			this->pinData = pinData;
			this->pinLatch = pinLatch;
      this->clearRegisterPin = clearRegisterPin;

      numberOfShiftRegisters < 1 ? this->numberOfShiftRegisters = 1 : this->numberOfShiftRegisters = numberOfShiftRegisters;

      SIZE_OF_ARRAY = this->numberOfShiftRegisters * 8;

      bitArray = (bool*)calloc(SIZE_OF_ARRAY, sizeof(bool));

		}
		

		
		//writes to the register
		//it writes the whole bite and turns the latch on to enable
		void writeToRegister(short data){
			for(short i = SIZE_OF_ARRAY-1; i>=0 ; i--){
				bitArray[i] = (data >> i) & 1;
			}
			//shifting with automatic latch at the end
			writeArrayToRegister(true);
		}
		
		//returns the numerial value of the shifted byte
		short getValue(){
			short data = 0x00;
			for(short i = SIZE_OF_ARRAY-1; i >=0; i--){
				data = (data << 1) | bitArray[i];
			}
			return data;
    }

    //When you use the bit manipulation with [ ] subscript operator, you have to execute to write to register.
    void execute(){
      writeArrayToRegister(true);
    }

    //returns the size of pins declared ex. 3 registers * 8 pins = 24 pins.
    int getSize(){
      return SIZE_OF_ARRAY;
    }
	
	
	//overload the  [] operator to manipulate bits;
	 bool& operator[](int a){

     if (a < SIZE_OF_ARRAY){
       return bitArray[a];
     }else{
       bool *ref = nullptr;
       return *ref;
     }
		  
    }

	

};


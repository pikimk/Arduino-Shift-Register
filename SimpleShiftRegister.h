//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
//          Simple Class for interfacing the 74HC595 Shift Register                 //
//                                                                                  //
//                      Created by Petar Chichev                                    //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////




class ShiftRegister{
	
	private:
		
		const short SIZE_OF_ARRAY = 8;
		short pinClock, pinData, pinLatch, clearRegisterPin;
		bool latch = false;
		
		// it takes 8 bytes since one boolean variable is 1 byte
		// using calloc to set all mem blocks to 0
		bool* bitArray = (bool*)calloc(SIZE_OF_ARRAY, sizeof(bool));

   
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

		
		ShiftRegister(short pinClock, short pinData, short pinLatch, short clearRegisterPin){
			
			this->pinClock = pinClock;
			this->pinData = pinData;
			this->pinLatch = pinLatch;
      this->clearRegisterPin = clearRegisterPin;
      init();
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
	
	
	//overload the  [] operator to manipulate bits;
	 bool& operator[](int a){
		  return bitArray[a];
    }

	

};


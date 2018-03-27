
byte invertedKeys = 0b0;
byte pressedKey = 0b0;
byte pressedKeyPosition = 0;

bool serialDebugALL = true;
bool serialDebugAux = false;
bool serialDebugPreview = false;
bool serialDebugProgram = false;
bool serialDebugBigBoard = false;
bool serialDebugEFF = false;
bool serialDebugLeverArm = false;
bool serialDebugDSK = true;

byte bigBoard      = 0b01000000;
byte boardDSK      = 0b00100000;
byte boardAux      = 0b01100000;
byte boardEFF      = 0b00010000;
byte boardLeverArm = 0b10000000;
byte boardWipe     = 0b00000000;


bool readingProgramKeys = false;

byte matricaAuxLedke[4][8] = {
  {1, 2, 4, 8, 64, 32, 16, 128},
  {1, 2, 4, 8, 16, 32, 64, 128},
  {1, 2, 4, 8, 16, 32, 64, 128},
  {1, 2, 16, 32, 64, 128, 0, 0},
};

byte stevilkeMatrica[16]{
  0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111,
  0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001
};


void setupGVGBoard() {
  // put your setup code here, to run once:
  DDRA = 0b00000000;  //input port A   - button input
  DDRC = 0b11111111;  //output port C  - board select
  DDRL = 0b11111111;  //output port L  - LED pins
  DDRG = 0b111;  //output port G  - Function pins

  
  PORTL = 0b00000000; //Lights on low
  PORTG = 0b000; //Function pins on low
  
//  ledke = 0b00000001;
//  PORTC = 0b01100000; //TO JE AUX BOARD
//  Serial.println(".");
//  Serial.println("Intro Animacija!");
//  for(int j=0;j<4;j++){
//    for(int i=0;i<8;i++){
//      PORTC = 0b01100000 + j;
//      PORTG = 0b1;
//      delay(0.1);
//      PORTL = matricaAuxLedke[j][i];
//      delay(150);
//      Serial.print("#");
//    }
//    PORTL = 0b0;
//    PORTG = 0b00000000;delay(0.1);
//  }
//  Serial.println("#");

  // ########### NASTAVI IZHODE ZA LUČKE ############
  resetBigBoardLightOutputs();
}

void resetBigBoardLightOutputs(){
  PORTG = 0b0; delay(0.1);
  PORTC = 0b01000110;  delay(0.1);
  PORTL = 0b00111111; delay(0.1);
  PORTG = 0b1;   delay(0.1); 
  PORTG = 0b0; delay(0.1);
}


void brisiLedke(byte boardAux, byte tipkeSelected){
  izhod = boardAux + tipkeSelected;
  PORTC = izhod;
  delay(10);
  PORTG = 0b00000011;
  delay(1);
  PORTL = 0b00000000;
  PORTG = 0b00000000;
}

byte bigBoardKeyMatrixLastState[2][6]{
    {0b0,0b0,0b0,
     0b0,0b0,0b0},
    {0b0,0b0,0b0,
     0b0,0b0,0b0}
};
byte bigBoardKeyMatrix[2][6]{
    {0b0,0b0,0b0,
     0b0,0b0,0b0},
    {0b0,0b0,0b0,
     0b0,0b0,0b0}
};
byte bigBoardKeyMatrixPressed[2][6]{
    {0b0,0b0,0b0,
     0b0,0b0,0b0},
    {0b0,0b0,0b0,
     0b0,0b0,0b0}
};
byte EFFKeyMatrix[5]{
    0b0,0b0,0b0,0b0,0b0
};
byte LeverArmKeyMatrix[16];
//byte EFFLightMatrix[5]{
//    0b0,0b0,0b0,0b0,0b0
//};

bool keyIsDown[2][6];
bool keyEFFIsDown[5];
bool keyLeverArmIsDown[16];
bool keyDSKIsDown[16];

void readBigBoardKey() {
  for (uint8_t mux=0;mux<2;mux++){
    for(uint8_t column=0;column<6;column++){
      //readingProgramKeys = true;
      izhod = bigBoard + (mux<<3) + column;
      PORTC = izhod; delay(0.1);
      pressedKey = PINA;
      //if(pressedKey != bigBoardKeyMatrix[column]){
      //if(bigBoardKeyMatrixLastState[mux][column] != pressedKey){
      if((keyIsDown[mux][column] == true) && (pressedKey == 0b11111111)){
        keyIsDown[mux][column] = false;
      } else 
      if ((pressedKey != 0b11111111) && (keyIsDown[mux][column] == false)){
        keyIsDown[mux][column] = true;
        if (serialDebugBigBoard && serialDebugALL) {
          Serial.println(F("########## BIG BOARD KEYS ###########"));
          Serial.print(F("PORTC:  "));
          Serial.println(PORTC,BIN);
          Serial.print(F("Selected column ")); Serial.print(column);
          Serial.print(F(" and pressed key:  "));
          Serial.println(~pressedKey,BIN);
          Serial.print(F("Pressed key in column in program matrix:  "));
          Serial.println(pressedKeyPosition);
          Serial.print(F("bigBoardKeyMatrix[mux][column]:  "));
          Serial.println(bigBoardKeyMatrix[mux][column],BIN);
        }
        bigBoardKeyMatrix[mux][column] =  bigBoardKeyMatrix[mux][column] ^ ~pressedKey;
        setLightBigBoard(izhod, bigBoardKeyMatrix[mux][column]);
        
        invertedKeys = ~pressedKey;
        pressedKeyPosition=(int)(log(invertedKeys)/log(2));
        if (serialDebugBigBoard && serialDebugALL) {
          
          
        }
      }
    }
  }
} // END readBigBoardKey

void setLightBigBoard(byte bigBoardizhod, byte bigBoardKeys){
  PORTC = bigBoardizhod; delay(0.1);
  if (serialDebugBigBoard && serialDebugALL) {
    Serial.println(F("########## Bigboar Lucke ###########"));
    Serial.print("Debug: IZHOD: ");
    Serial.println(bigBoardizhod,BIN);
    Serial.print(F("Debug: Prižigam lucko 1-8 v njenem stolpcu "));
    Serial.println(bigBoardKeys);
  }
  PORTL = bigBoardKeys;
  PORTG = 0b1; delay(0.1);
  PORTG = 0b0;
}


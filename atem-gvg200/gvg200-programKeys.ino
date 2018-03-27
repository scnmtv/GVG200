//pripravljeno za GVG200 XPT PANEL MODULE
//Program tipke - 5. vrstica:
//01010000 01010001 01010010

byte pressedKeysProgram_OLD[6] = {
  0, 0, 0, 0, 0, 0
};
byte pressedKeysProgram = 0;

uint16_t programInput[3][8] = {
  {1,2,3,4,5,6,7,8},
  {1000,2001,2002,3010,3011,3020,3021,0},
  {4010,5010,5020,7001,7002,99999,99999,99999}
};

byte matricaPregramLedke[6][8] = {
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
};

byte currentProgramTallyKey[2];
uint16_t currentProgramTallyInput = 9696;
byte muxProgram = 0b10000;

void readProgramKeys(){
//  Serial.println("Debug: Zagnana funckcija readProgramKeys");
  for(uint8_t column=0;column<3;column++){
    readingProgramKeys = true;
    izhod = bigBoard + muxPreview + column;
    PORTC = izhod; delay(0.1);
    pressedKey = PINA;
    if(pressedKey != pressedKeysProgram_OLD[column]){
      if (pressedKey != 0b11111111){
        if (serialDebugProgram && serialDebugALL) {
          Serial.println(F("########## PROGRAM KEY ###########"));
          Serial.print(F("PORTC:  "));
          Serial.println(PORTC,BIN);
          Serial.print(F("Selected column ")); Serial.print(column);
          Serial.print(F(" and pressed key:  "));
        }
        invertedKeys = ~pressedKey;
        pressedKeyPosition=(int)(log(invertedKeys)/log(2));
        if (serialDebugProgram && serialDebugALL) {
          Serial.println(invertedKeys,BIN);
          Serial.print(F("Pressed key in column in program matrix:  "));
          Serial.println(pressedKeyPosition);
          Serial.print(F("Sent atem Program input:  "));
          Serial.println(programInput[column][pressedKeyPosition]);
        }
        AtemSwitcher.setProgramInputVideoSource(0, programInput[column][pressedKeyPosition]);
      }
      pressedKeysProgram_OLD[column]=pressedKey;
    }
    readingProgramKeys = false;
  }
}

void setProgramTallyLights(uint16_t atemProgramTallySource){ //PROGRAM TALLY

  
  //resetBigBoardLightOutputs();

  if(AtemSwitcher.getTransitionInTransition(0)){
    if(currentProgramTallyKey[0] == currentPreviewTallyKey[0]-3){
      PORTC = currentPreviewTallyKey[0]-3; delay(0.1);
      PORTL = currentPreviewTallyKey[1]+currentProgramTallyKey[1];
      PORTG = 0b1; delay(0.1);
      PORTG = 0b0;
    } else {
      PORTC = currentPreviewTallyKey[0]-3; delay(0.1);
      PORTL = currentPreviewTallyKey[1];
      PORTG = 0b1; delay(0.1);
      PORTG = 0b0;
    }
  }
  
  if (atemProgramTallySource != currentProgramTallyInput){
//    Serial.println("Debug: Drugucen tally - Zagnana funckcija setProgramTallyLights");
    for(int column=0;column<3;column++){
      for (uint8_t keyNumber = 0; keyNumber < 8; keyNumber++)  {
        if(atemProgramTallySource == programInput[column][keyNumber]){
          brisiProgramLedke();
          izhod = bigBoard + muxPreview + column;
          PORTC = izhod; delay(0.1);
          if (serialDebugProgram && serialDebugALL) {
            Serial.println(F("########## PROGRAM TALLY ###########"));
            Serial.print("Debug: Program je na inputu: ");
            Serial.println(programInput[column][keyNumber]);
            Serial.print("Debug: programTallyLights Stolpec: ");
            Serial.println(column);
            Serial.print("Debug: programTallyLights Tipka: ");
            Serial.println(keyNumber);
            Serial.print(F("Debug: Prižigam program lucko 1-8 v njenem stolpcu "));
            Serial.print(column);
            Serial.print(F(": "));
            Serial.println(0b1 << keyNumber);
          } 
          currentProgramTallyKey[0] = izhod;
          currentProgramTallyKey[1] = 0b1 << keyNumber;
          PORTL = 0b1 << keyNumber;
          PORTG = 0b1; delay(0.1);
          PORTG = 0b0;
        }
      }
    }
    currentProgramTallyInput = atemProgramTallySource;
  }
} //PROGRAM TALLY

void brisiProgramLedke(){
  for(int column=0;column<3;column++){
    izhod = bigBoard + muxPreview + column;
    PORTC = izhod; delay(0.1);
    PORTL = 0b00000000;
    PORTG = 0b1; delay(0.1); 
    PORTG = 0b0;
  }
}


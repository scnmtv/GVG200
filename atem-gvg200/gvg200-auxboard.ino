//pripravljeno za GVG200 AUX PANEL

uint16_t auxInput[3][8] = {
  {0,1,2,3,4,5,6,7},
  {8,1000,2001,2002,3010,3011,3020,3021},
  {4010,5010,5020,7001,7002,10010,10011,99999}
};

uint16_t currentAuxTally = 6969;

void brisiAuxLedke(){
  for(int i=0;i<4;i++){
    izhod = 0b01100000 + i;
    
  PORTC = izhod; delay(0.1);
  PORTG = 0b00000001; delay(0.1);
  PORTL = 0b00000000;
  PORTG = 0b00000000;
  }
}
byte pressedKeysAux_OLD[4] = {
  0, 0, 0, 0
};


void readAuxKeys(){
  for(uint8_t column=0;column<4;column++){
//    Serial.println("Debug: Zagnana funckcija readAuxKeys");
    izhod = 0b01100000 + column;
    PORTC = izhod;  delay(0.1);
    pressedKey = PINA;
    if((pressedKey != pressedKeysAux_OLD[column]) && (!readingProgramKeys)){
      if (pressedKey != 0b11111111){
        if (serialDebugAux && serialDebugALL) {
          Serial.println("############readingProgramKeys#########");
          Serial.println(readingProgramKeys);
          Serial.println("########## AUX KEY ###########");
          Serial.print("PORTC:  ");
          Serial.println(PORTC,BIN);
          Serial.print(column);
          Serial.print(":  ");
          Serial.println(pressedKey,BIN);
        }
        invertedKeys = ~pressedKey;
        input=(int)(log(invertedKeys)/log(2));
        if (serialDebugAux && serialDebugALL) {
          Serial.print("Pressed key:  ");
          Serial.println(invertedKeys,BIN);
          Serial.print("Pressed key in group:  ");
          Serial.println(input);
          Serial.print("Set AUX1 to input:  ");
          Serial.println(auxInput[column][input]);
        }
        AtemSwitcher.setAuxSourceInput(0, auxInput[column][input]);
      }
      pressedKeysAux_OLD[column]=pressedKey;
    }
  }
}

void setAuxTallyLights(uint16_t atemAuxTallySource){
//  Serial.println("Debug: Zagnana funckcija setLights");
  if (atemAuxTallySource != currentAuxTally){
    for(int column=0;column<3;column++){
      for (uint8_t keyNumber=0;keyNumber<8;keyNumber++)  {
        if (atemAuxTallySource == auxInput[column][keyNumber]){
          Serial.println(atemAuxTallySource);
          brisiAuxLedke();        
          izhod = boardAux + column;
          PORTC = izhod; delay(0.1);
          PORTG = 0b1; delay(0.1);
          PORTL = matricaAuxLedke[column][keyNumber]; delay(0.1);
          PORTG = 0b0;
          if (serialDebugAux && serialDebugALL) {
            Serial.println(F("########## AUX TALLY ###########"));
            Serial.print("Debug: AUX je na inputu: ");
            Serial.println(auxInput[column][keyNumber]);
            Serial.print("Debug: auxInput Stolpec: ");
            Serial.println(column);
            Serial.print("Debug: auxInput Tipka: ");
            Serial.println(keyNumber);
            Serial.print(F("Debug: Prižigam AUX lucko 1-8 v njenem stolpcu "));
            Serial.print(column);
            Serial.print(F(": "));
            Serial.println(matricaAuxLedke[column][keyNumber],BIN);
          }
        }
      }
    }
    currentAuxTally = atemAuxTallySource;
  }
}


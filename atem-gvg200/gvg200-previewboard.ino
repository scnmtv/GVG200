//pripravljeno za GVG200 XPT PANEL MODULE
//Previe tipke - 6. vrstica:
//board mux  col
//010   10   011
//010   10   100
//010   10   101

uint16_t previewInput[3][8] = {
  {1,2,3,4,5,6,7,8},
  {1000,2001,2002,3010,3011,3020,3021,0},
  {4010,5010,5020,7001,7002,99999,99999,99999}
};

byte pressedKeysPreview_OLD[6] = {
  0, 0, 0, 0, 0, 0
};
byte pressedKeysPreview = 0;

byte currentPreviewTallyKey[2];
uint16_t currentPreviewTallyInput = 9696;

byte muxPreview = 0b10000;

void readPreviewKeys(){
//  Serial.println("Debug: Zagnana funckcija readPreviewKeys");
  for(uint8_t column=0;column<3;column++){
    izhod = bigBoard + muxPreview + column + 3;
    PORTC = izhod; delay(0.1);
    pressedKey = PINA;
    if(pressedKey != pressedKeysPreview_OLD[column]){
      if (pressedKey != 0b11111111){
        if (serialDebugPreview && serialDebugALL) {
        Serial.println(F("########## PREVIEW KEY ###########"));
        Serial.print(F("PORTC:  "));
        Serial.println(PORTC,BIN);
        Serial.print(F("Selected column ")); Serial.print(column+3);
        Serial.print(F(" and pressed key:  "));
        }
        invertedKeys = ~pressedKey;
        pressedKeyPosition=(int)(log(invertedKeys)/log(2));
        if (serialDebugPreview && serialDebugALL) {
        Serial.println(invertedKeys,BIN);
        Serial.print(F("Pressed key in column in preview matrix:  "));
        Serial.println(pressedKeyPosition);
        Serial.print(F("Sent atem PREVIEW input:  "));
        Serial.println(previewInput[column][pressedKeyPosition]);
        }
        AtemSwitcher.setPreviewInputVideoSource(0, previewInput[column][pressedKeyPosition]);
      }
      pressedKeysPreview_OLD[column]=pressedKey;
    }
  }
}

void setPreviewTallyLights(uint16_t atemPreviewTallySource){
  //resetBigBoardLightOutputs();
  
  if (atemPreviewTallySource != currentPreviewTallyInput){
//    Serial.println("Debug: Drugucen tally - Zagnana funckcija setPreviewTallyLights");
    for(int column=0;column<3;column++){
      for (uint8_t keyNumber = 0; keyNumber < 8; keyNumber++)  {
        if(atemPreviewTallySource == previewInput[column][keyNumber]){
          brisiPreviewLedke();
          
          izhod = bigBoard + muxPreview + column + 3;
          PORTC = izhod; delay(0.1);
          if (serialDebugPreview && serialDebugALL) {
            Serial.println(F("########## PREVIEW TALLY ###########"));
            Serial.print("Debug: PREVIEW je na inputu: ");
            Serial.println(previewInput[column][keyNumber]);
            Serial.print("Debug: previewTallyLights Stolpec: ");
            Serial.println(column);
            Serial.print("Debug: previewTallyLights Tipka: ");
            Serial.println(keyNumber);
            Serial.print(F("Debug: Prižigam Preview lucko 1-8 v njenem stolpcu "));
            Serial.print(column);
            Serial.print(F(": "));
            Serial.println(0b1 << keyNumber);
          }
          currentPreviewTallyKey[0] = izhod;
          currentPreviewTallyKey[1] = 0b1 << keyNumber;
          PORTL = 0b1 << keyNumber;
          PORTG = 0b1; delay(0.1);
          PORTG = 0b0;
        }
      }
    }
    currentPreviewTallyInput = atemPreviewTallySource;
    
  }
}

void brisiPreviewLedke(){
  for(int column=0;column<3;column++){
    izhod = bigBoard + muxPreview + column + 3;
    PORTC = izhod; delay(0.1);
    PORTL = 0b00000000;
    PORTG = 0b1; delay(0.1); 
    PORTG = 0b0;
  }
}


//pripravljeno za GVG200 XPT PANEL MODULE
//Previe tipke - 6. vrstica:
//board mux  col
//010   10   011
//010   10   100
//010   10   101

//uint16_t effInput[3][8] = {
//  {1,2,3,4,5,6,7,8},
//  {1000,2001,2002,3010,3011,3020,3021,0},
//  {4010,5010,5020,7001,7002,99999,99999,99999}
//};
//
uint8_t matricaEFFLedke[5][8] = {
  // 0xFF ta pozicija ne prizge nobene lucke
  // pozicija 1,4 prižge 0x23
  //          4,3 prižge 0x40
  {0x10, 0x13, 0x05, 0x02, 0x04, 0x27, 0x11, 0x00},
  {0x15, 0x25, 0x20, 0x01, 0x23, 0x26, 0x14, 0x07},
  {0x03, 0x24, 0x22, 0xFF, 0x17, 0x16, 0x12, 0x06},
  {0x42, 0x30, 0x45, 0x34, 0x31, 0x32, 0x35, 0x41},
  {0xFF, 0x33, 0x21, 0x40, 0x43, 0x46, 0x47, 0x44}
};


byte pressedKeysEFF_OLD[5] = {
  0, 0, 0, 0, 0
};
//byte pressedKeysPreview = 0;
//
//byte currentPreviewTallyKey[2];
//uint16_t currentPreviewTallyInput = 9696;



void readEFFKeys(){
//  Serial.println("Debug: Zagnana funckcija readPreviewKeys");
  for(uint8_t column=0;column<5;column++){
    izhod = boardEFF + column;
    PORTC = izhod; delay(0.1);
    
//    PORTL = 0b11111111;
//    PORTG = 0b1; delay(0.1);
//    PORTG = 0b0;
    
    pressedKey = PINA;
   // if(pressedKey != pressedKeysEFF_OLD[column]){
      if((keyEFFIsDown[column] == true) && (pressedKey == 0b11111111)){
        keyEFFIsDown[column] = false;
      } else 
      if ((pressedKey != 0b11111111) && (keyEFFIsDown[column] == false)){
        keyEFFIsDown[column] = true;
        if (serialDebugALL && serialDebugEFF) {
        Serial.println(F("########## EFF KEY ###########"));
        Serial.print(F("PORTC:  "));
        Serial.println(PORTC,BIN);
        Serial.print(F("Selected column ")); Serial.print(column);
        Serial.print(F(" and pressed key:  "));
        Serial.println(pressedKey,BIN);
        }
        invertedKeys = ~pressedKey;
        pressedKeyPosition=(int)(log(invertedKeys)/log(2));
        if (serialDebugALL && serialDebugEFF) {
          Serial.print(F("Pressed key in column in EFF matrix:  "));
          Serial.println(pressedKeyPosition+1);
        }
        //EFFKeyMatrix[column] = EFFKeyMatrix[column] ^ ~pressedKey;
        setLightEFF(column, pressedKeyPosition);
        
        
        //AtemSwitcher.setPreviewInputVideoSource(0, previewInput[column][pressedKeyPosition]);
      }
      //pressedKeysEFF_OLD[column]=pressedKey;
   // }
  }
}

void setDisplayEFF(){
  for(uint8_t column=5;column<8;column++){
    for (uint8_t crtica=0;crtica<16;crtica++)  {
      PORTC = boardEFF + column; delay(0.1);
      PORTL = stevilkeMatrica[crtica];
      PORTG = 0b1; delay(500.1); 
      PORTG = 0b0;
    }
    PORTL = 0b10000000;
    PORTG = 0b1; delay(500.1); 
    PORTG = 0b0;
  }
}

void setLightEFF(byte kolona, byte EFFKeys){
  byte kolona_new;
  byte EFFKeys_new;
  kolona_new = matricaEFFLedke[kolona][EFFKeys]>>4; 
  EFFKeys_new = matricaEFFLedke[kolona][EFFKeys] & 0x0F;
  EFFKeys_new = 0.5 + pow(2,EFFKeys_new);
  EFFKeyMatrix[kolona_new] = EFFKeyMatrix[kolona_new] ^ EFFKeys_new;
  PORTC = boardEFF + kolona_new; delay(0.1);
  if (serialDebugALL && serialDebugEFF) {
    Serial.println(F("########## EFF Lucke ###########"));
    Serial.print("Debug: kolona: ");
    Serial.println(kolona,BIN);
    Serial.print("Debug: EFFKeys: ");
    Serial.println(EFFKeys);
    Serial.print("Debug: kolona_new: ");
    Serial.println(kolona_new,BIN);
    Serial.print("Debug: EFFKeys_new: ");
    Serial.println(EFFKeys_new,BIN);
    Serial.print("Debug: IZHOD: ");
    Serial.println(PORTC,BIN);
    Serial.print(F("Debug: Prižigam lučke 1-8 v njenem stolpcu "));
    Serial.println(EFFKeyMatrix[kolona_new],BIN);
  }
  PORTL = EFFKeyMatrix[kolona_new];
  PORTG = 0b1; delay(0.1); 
  PORTG = 0b0;
}

//
//void setPreviewTallyLights(uint16_t atemPreviewTallySource){
//  //resetBigBoardLightOutputs();
//  
//  if (atemPreviewTallySource != currentPreviewTallyInput){
////    Serial.println("Debug: Drugucen tally - Zagnana funckcija setPreviewTallyLights");
//    for(int column=0;column<3;column++){
//      for (uint8_t keyNumber = 0; keyNumber < 8; keyNumber++)  {
//        if(atemPreviewTallySource == previewInput[column][keyNumber]){
//          brisiPreviewLedke();
//          
//          izhod = bigBoard + muxPreview + column + 3;
//          PORTC = izhod; delay(0.1);
//          if (serialDebugPreview && serialDebugALL) {
//            Serial.println(F("########## PREVIEW TALLY ###########"));
//            Serial.print("Debug: PREVIEW je na inputu: ");
//            Serial.println(previewInput[column][keyNumber]);
//            Serial.print("Debug: previewTallyLights Stolpec: ");
//            Serial.println(column);
//            Serial.print("Debug: previewTallyLights Tipka: ");
//            Serial.println(keyNumber);
//            Serial.print(F("Debug: Prižigam Preview lucko 1-8 v njenem stolpcu "));
//            Serial.print(column);
//            Serial.print(F(": "));
//            Serial.println(0b1 << keyNumber);
//          }
//          currentPreviewTallyKey[0] = izhod;
//          currentPreviewTallyKey[1] = 0b1 << keyNumber;
//          PORTL = 0b1 << keyNumber;
//          PORTG = 0b1; delay(0.1);
//          PORTG = 0b0;
//        }
//      }
//    }
//    currentPreviewTallyInput = atemPreviewTallySource;
//    
//  }
//}
//
//void brisiPreviewLedke(){
//  for(int column=0;column<3;column++){
//    izhod = bigBoard + muxPreview + column + 3;
//    PORTC = izhod; delay(0.1);
//    PORTL = 0b00000000;
//    PORTG = 0b1; delay(0.1); 
//    PORTG = 0b0;
//  }
//}


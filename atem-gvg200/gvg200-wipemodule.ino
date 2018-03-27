////pripravljeno za GVG200 XPT PANEL MODULE
////Previe tipke - 6. vrstica:
////board mux  col
////010   10   011
////010   10   100
////010   10   101
//
////uint16_t effInput[3][8] = {
////  {1,2,3,4,5,6,7,8},
////  {1000,2001,2002,3010,3011,3020,3021,0},
////  {4010,5010,5020,7001,7002,99999,99999,99999}
////};
////
//uint8_t matricaLeverArmLedke[8][8] = {
//  {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47},
//  {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27},
//  {0x30, 0x31, 0x32, 0x33, 0x34, 0x36, 0x35, 0x37},
//  {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17},
//  {0x60, 0x61, 0x62, 0x63, 0x67, 0x65, 0x66, 0x64},
//  {0x03, 0x02, 0x01, 0x00, 0x07, 0x06, 0x05, 0x04},
//  {0x53, 0x52, 0x51, 0x50, 0x57, 0x56, 0x55, 0x54},
//  {0x70, 0x71, 0x72, 0x73, 0x74, 0x77, 0x76, 0x75}
//};
//
//
//byte pressedKeysLeverArm_OLD[5] = {
//  0, 0, 0, 0, 0
//};
////byte pressedKeysPreview = 0;
////
////byte currentPreviewTallyKey[2];
////uint16_t currentPreviewTallyInput = 9696;
//
//
//
//void readLeverArmKeys(){
////  Serial.println("Debug: Zagnana funckcija readPreviewKeys");
//  for(uint8_t column=0;column<8;column++){
//    izhod = boardLeverArm + column;
//    PORTC = izhod; delay(0.1);
//    
////    PORTL = 0b11111111;
////    PORTG = 0b1; delay(0.1);
////    PORTG = 0b0;
//    
//    pressedKey = PINA;
//    // CUT KEY
//    if ((pressedCut == true) && (pressedKey != 0b11101111) && (column == 7)){
//      pressedCut = false;
//    } else
//    if((pressedKey == 0b11101111) && (column == 7) && !pressedCut){
//      AtemSwitcher.performCutME(0);
//      pressedCut = true;
//    } else
//    // AUTO KEY
//    if ((pressedAuto == true) && (pressedKey != 0b11111110) && (column == 7)){
//      pressedAuto = false;
//    } else
//    if((pressedKey == 0b11111110) && (column == 7) && !pressedAuto){
//      AtemSwitcher.performAutoME(0);
//      pressedAuto = true;
//    } else
//    if((keyLeverArmIsDown[column] == true) && (pressedKey == 0b11111111)){
//      keyLeverArmIsDown[column] = false;
//    } else {
//      if ((pressedKey != 0b11111111) && (keyLeverArmIsDown[column] == false)){
//        keyLeverArmIsDown[column] = true;
//        if (serialDebugALL && serialDebugLeverArm) {
//        Serial.println(F("########## Lever Arm Board KEY ###########"));
//        Serial.print(F("PORTC:  "));
//        Serial.println(PORTC,BIN);
//        Serial.print(F("Selected column ")); Serial.print(column);
//        Serial.print(F(" and pressed key:  "));
//        Serial.println(pressedKey,BIN);
//        }
//        invertedKeys = ~pressedKey;
//        pressedKeyPosition=(int)(log(invertedKeys)/log(2));
//        if (serialDebugALL && serialDebugLeverArm) {
//          Serial.print(F("Pressed key in column in Lever Arm Board matrix:  "));
//          Serial.println(pressedKeyPosition+1);
//        }
//        
//        //EFFKeyMatrix[column] = EFFKeyMatrix[column] ^ ~pressedKey;
//        setLightLeverArm(column, pressedKeyPosition);
//      }  
//      //AtemSwitcher.setPreviewInputVideoSource(0, previewInput[column][pressedKeyPosition]);
//    }
//  }
//}
//
//
//
////void setDisplayLeverArm(){
////  for(uint8_t column=5;column<8;column++){
////    for (uint8_t crtica=0;crtica<16;crtica++)  {
////      PORTC = boardEFF + column; delay(0.1);
////      PORTL = stevilkeMatrica[crtica];
////      PORTG = 0b1; delay(500.1); 
////      PORTG = 0b0;
////    }
////    PORTL = 0b10000000;
////    PORTG = 0b1; delay(500.1); 
////    PORTG = 0b0;
////  }
////}
//
//void setLightLeverArm(byte kolona, byte LeverArmPressedKey){
//  byte kolona_new;
//  byte LeverArmPressedKey_new;
//
//  kolona_new = matricaLeverArmLedke[kolona][LeverArmPressedKey]>>4; 
//  LeverArmPressedKey_new = matricaLeverArmLedke[kolona][LeverArmPressedKey] & 0x0F;
//  LeverArmPressedKey_new = 0.5 + pow(2,LeverArmPressedKey_new);
//  LeverArmKeyMatrix[kolona_new] = LeverArmKeyMatrix[kolona_new] ^ LeverArmPressedKey_new;
//  PORTC = boardLeverArm + kolona_new; delay(0.1);
//  
//  if ((LeverArmPressedKey == 4) && (kolona == 7)){
//    if(pressedCut){
//      PORTL = LeverArmKeyMatrix[kolona_new];
//      PORTG = 0b1; delay(0.1); 
//      PORTG = 0b0;
//    } else {
//      PORTL = 0b0;
//      PORTG = 0b1; delay(0.1); 
//      PORTG = 0b0;
//    }
//  } else
//  if ((LeverArmPressedKey == 0) && (kolona == 7)){
//    if(AtemSwitcher.getTransitionInTransition(0)){
//      PORTL = LeverArmKeyMatrix[kolona_new];
//      PORTG = 0b1; delay(0.1); 
//      PORTG = 0b0;
//    } else {
//      PORTL = 0b0;
//      PORTG = 0b1; delay(0.1); 
//      PORTG = 0b0;
//    }
//  } else {
//    if (serialDebugALL && serialDebugLeverArm) {
//      Serial.println(F("########## EFF Lucke ###########"));
//      Serial.print("Debug: kolona: ");
//      Serial.println(kolona,BIN);
//      Serial.print("Debug: EFFKeys: ");
//      Serial.println(LeverArmPressedKey);
//      Serial.print("Debug: kolona_new: ");
//      Serial.println(kolona_new,BIN);
//      Serial.print("Debug: EFFKeys_new: ");
//      Serial.println(LeverArmPressedKey_new,BIN);
//      Serial.print("Debug: IZHOD: ");
//      Serial.println(PORTC,BIN);
//      Serial.print(F("Debug: Prižigam lučke 1-8 v njenem stolpcu "));
//      Serial.println(LeverArmKeyMatrix[kolona_new],BIN);
//    }
//    PORTL = LeverArmKeyMatrix[kolona_new];
//    PORTG = 0b1; delay(0.1); 
//    PORTG = 0b0;
//    if(kolona_new==4){
//      PORTC = 0b10010000;  delay(0.1);
//      PORTL = 0b11; delay(0.1);
//      PORTG = 0b1; delay(0.1);
//      PORTG = 0b0;
//    }
//  }
//}
//
////
////void setPreviewTallyLights(uint16_t atemPreviewTallySource){
////  //resetBigBoardLightOutputs();
////  
////  if (atemPreviewTallySource != currentPreviewTallyInput){
//////    Serial.println("Debug: Drugucen tally - Zagnana funckcija setPreviewTallyLights");
////    for(int column=0;column<3;column++){
////      for (uint8_t keyNumber = 0; keyNumber < 8; keyNumber++)  {
////        if(atemPreviewTallySource == previewInput[column][keyNumber]){
////          brisiPreviewLedke();
////          
////          izhod = bigBoard + muxPreview + column + 3;
////          PORTC = izhod; delay(0.1);
////          if (serialDebugPreview && serialDebugALL) {
////            Serial.println(F("########## PREVIEW TALLY ###########"));
////            Serial.print("Debug: PREVIEW je na inputu: ");
////            Serial.println(previewInput[column][keyNumber]);
////            Serial.print("Debug: previewTallyLights Stolpec: ");
////            Serial.println(column);
////            Serial.print("Debug: previewTallyLights Tipka: ");
////            Serial.println(keyNumber);
////            Serial.print(F("Debug: Prižigam Preview lucko 1-8 v njenem stolpcu "));
////            Serial.print(column);
////            Serial.print(F(": "));
////            Serial.println(0b1 << keyNumber);
////          }
////          currentPreviewTallyKey[0] = izhod;
////          currentPreviewTallyKey[1] = 0b1 << keyNumber;
////          PORTL = 0b1 << keyNumber;
////          PORTG = 0b1; delay(0.1);
////          PORTG = 0b0;
////        }
////      }
////    }
////    currentPreviewTallyInput = atemPreviewTallySource;
////    
////  }
////}
////
////void brisiPreviewLedke(){
////  for(int column=0;column<3;column++){
////    izhod = bigBoard + muxPreview + column + 3;
////    PORTC = izhod; delay(0.1);
////    PORTL = 0b00000000;
////    PORTG = 0b1; delay(0.1); 
////    PORTG = 0b0;
////  }
////}


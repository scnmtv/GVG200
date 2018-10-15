//pripravljeno za GVG200 AUX PANEL

//delayi gredo lahko na manj
byte ledke = 0; 
byte tipke = 0; 
byte ledke_old[4] = {
  0,0,0,0
};
byte tipke_old[4] = {
  0,0,0,0
};
byte auxLedke[4][8] = {
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,64,32,16,128},
  {1,2,4,8,64,32,16,128},
  {1,2,64,32,16,128,4,8},
};
byte izhod = 0;
byte boardAux = 0b01100000;
byte tipkeSelect = 0b00000000;

void setup() {
  // put your setup code here, to run once:
  DDRA = 0b00000000;  //input port A   - button input
  DDRC = 0b11111111;  //output port C  - board select
  DDRL = 0b11111111;  //output port L  - LED pins
  DDRG = 0b111;  //output port G  - Function pins

  Serial.begin(9600);
  PORTL = 0b00000000; //Lights on low
  PORTG = 0b000; //Function pins on low
  
  ledke = 0b00000001;
  PORTC = 0b01100000;
  Serial.println("Intro Animacija!");
  for(int j=0;j<4;j++){
    ledke = 0b00000001;
    for(int i=0;i<8;i++){
      PORTG = 0b00000011;
      delay(10);
      PORTL = auxLedke[j][i];
      ledke <<= 1;
      delay(10);
      PORTG = 0b00000000;
      delay(150);
      Serial.print("#");
    }
    PORTC++;
  }
  Serial.println("#");
  brisiLedke();
}

void brisiLedke(){
  PORTG = 0b00000011;
  delay(1);
  PORTL = 0b00000000;
  PORTG = 0b00000000;
}

void beriTipke(int tipkeSelected){
  izhod = boardAux + tipkeSelected;
  PORTC = izhod;
  delay(10);
  tipke = PINA;
  if(tipke != tipke_old[tipkeSelected]){
    if (tipke != 0b11111111){
      Serial.println("#####################");
      Serial.print("PORTC:  ");
      Serial.println(PORTC,BIN);
      Serial.print(tipkeSelected);
      Serial.print(":  ");
      Serial.println(tipke,BIN);
      ledke = ~tipke;
      if (ledke != ledke_old[tipkeSelected]){
        brisiLedke();
        PORTG = 0b00000011;
        delay(10);
        ledke=(int)(log(ledke)/log(2));
        PORTL = auxLedke[tipkeSelected][ledke];
        PORTG = 0b00000000;
        delay(10);
        Serial.print("PORTL1: ");
        Serial.println(PORTL,BIN);
      }
    }
    tipke_old[tipkeSelected]=tipke;
  }
  delay(10);
}

void loop() {
  tipkeSelect = tipkeSelect % 4;
  beriTipke(tipkeSelect);
  delay(10);
  tipkeSelect++;
}


/* PREŠNJI AUXBOARD V ATEM_GVG200
 *  //pripravljeno za GVG200 AUX PANEL

void brisiAuxLedke(byte boardAux, byte tipkeSelected){
  izhod = boardAux + tipkeSelected;
  PORTC = izhod;
  delay(1);
  PORTG = 0b00000011;
  delay(1);
  PORTL = 0b00000000;
  PORTG = 0b00000000;
}
byte pressedKeysAux_OLD[4] = {
  0, 0, 0, 0
};
byte pressedKeysAux = 0;
byte boardAux = 0b01100000;

void beriTipkeAux(byte tipkeSelected){
  izhod = boardAux + tipkeSelected;
  PORTC = izhod;
  delay(1);
  pressedKeysAux = PINA;
  if(pressedKeysAux != pressedKeysAux_OLD[tipkeSelected]){
    if (pressedKeysAux != 0b11111111){
      Serial.println("#####################");
      Serial.print("PORTC:  ");
      Serial.println(PORTC,BIN);
      Serial.print(tipkeSelected);
      Serial.print(":  ");
      Serial.println(pressedKeysAux,BIN);
      invertedKeys = ~pressedKeysAux;
      Serial.print("Ledke:  ");
      Serial.println(invertedKeys,BIN);
      input=(int)(log(invertedKeys)/log(2));
      Serial.print("Pressed key in group:  ");
      Serial.println(input);
      Serial.print("Set AUX1 to input:  ");
      Serial.println(auxInput[tipkeSelected][input]);
      AtemSwitcher.setAuxSourceInput(0, auxInput[tipkeSelected][input]);
//      if (ledke != ledke_old[tipkeSelected]){
//        ledke=(int)(log(ledke)/log(2));
//        setLights(boardAux,tipkeSelected,ledke);
//        PORTG = 0b00000000;
//        delay(10);
//        Serial.print("PORTL1: ");
//        Serial.println(PORTL,BIN);
//      }
    }
    pressedKeysAux_OLD[tipkeSelected]=pressedKeysAux;
  }
}

void setAuxLights(byte boardAux, byte tipkeSelected, byte input){
//  Serial.println("Debug: Zagnana funckcija setLights");
  izhod = boardAux + tipkeSelected;
  PORTC = izhod;
//  Serial.print("PORTC v setLights:  ");
//  Serial.println(PORTC,BIN);
  delay(1);
  if (matricaAuxLedke[tipkeSelected][input] != trenutnaLucka){
    Serial.print("Prizigam AUX lucko: ");
    Serial.println(matricaAuxLedke[tipkeSelected][input],BIN);
    brisiAuxLedke(boardAux,tipkeSelected);
    PORTG = 0b00000011;
    delay(10);
    PORTL = matricaAuxLedke[tipkeSelected][input];
    PORTG = 0b00000000;
    trenutnaLucka = matricaAuxLedke[tipkeSelected][input];
  }
}

 *  
 *  /
 */

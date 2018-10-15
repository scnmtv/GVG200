//pripravljeno za GVG200 AUX PANEL

//delayi gredo lahko na manj
byte ledke = 0; 
byte mux1 = 0;
byte mux2 = 0;
byte tipke = 0; 
byte ledke_old[4] = {
  0,0,0,0
};
byte tipke_old[6] = {
  0,0,0,0,0,0
};
byte matricaLedke[6][8] = {
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
  {1,2,4,8,16,32,64,128},
};
byte izhod = 0;
byte bigBoard = 0b01000000;
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
  
  ledke = 0b00000000;
  PORTC = 0b01000000;//izbira boarda XPT PANEL MODULE
}

void brisiLedke(int tipkeSelected, int muxSelected){
  muxSelected <<= 3;
  int izhod = bigBoard + tipkeSelected + muxSelected;
  PORTC = izhod;
  delay(1);
  PORTG = 0b00000011;
  delay(1);
  PORTL = 0b00000000;
  PORTG = 0b00000000;
}

void prizgiLedke( int muxSelected, int tipkeSelected){
  muxSelected <<= 3;
  int izhod = bigBoard + tipkeSelected + muxSelected;
  PORTC = izhod;
  for(int i=0;i<8;i++){
    PORTG = 0b00000001;
    delay(1);
    //Serial.print("Prizigam ledko:  ");Serial.print(matricaLedke[tipkeSelected][i],BIN);Serial.print(" na mux:  ");Serial.println(izhod,BIN);
    PORTL = matricaLedke[tipkeSelected][i];
    //PORTL = 0b1111100;
    delay(250);
    PORTG = 0b00000000;
    PORTC = 0b00000110;
    delay(1);
    PORTG = 0b00000000;
    PORTC = izhod;
    delay(1);
  }
}

void beriTipke( int muxSelected, int tipkeSelected){
  muxSelected <<= 3; 
  //Serial.print("tipkeSelected:  ");Serial.println(tipkeSelected,BIN);
  int izhod = bigBoard + tipkeSelected + muxSelected;
  //Serial.print("Board in tipke select izhod:  ");  Serial.println(izhod,BIN);
  //Serial.print("Mux1:  ");  Serial.println(mux1,BIN);
  //Serial.print("Mux2:  ");  Serial.println(mux2,BIN);
  //digitalWrite(30,HIGH);
  //digitalWrite(41,HIGH);
  PORTC = izhod;
  delay(1);
  tipke = PINA;
  //Serial.print("Stanje na portu od tipk:  ");  Serial.println(tipke,BIN);
  if(tipke != tipke_old[tipkeSelected]){
    if (tipke != 0b11111111){
      Serial.println("#####################");
      Serial.print("PORTC:  ");
      Serial.println(PORTC,BIN);
      Serial.print(tipkeSelected,BIN);
      Serial.print(":  ");
      Serial.println(tipke,BIN);
      tipke_old[tipkeSelected]=tipke;
    }
  }
}

void loop() {
//  for(int i=0;i<4;i++){
//    for(int j=0;j<7;j++){
//      //beriTipke(i,j);
//      //brisiLedke(i,j);
//      prizgiLedke(i,j);
//    }
//  }
//        PORTC = 0b01000000 + 0b10000 + 0b11;
//        delay(1);
//        PORTL = 0b11111111;
//        PORTG = 0b101;
//        delay(0.001);
//        PORTG = 0b001;

//    PORTG = 0b1;
//    PORTL = 0b11111111;
//    PORTC = 0b01000110;
//    delay(1);
//    byte bla = 0;
//    //**************** ROČNO ************
//    for(int i=0;i<3;i++){
//      for(int j=0;j<6;j++){
//        bla = i << 3;
//        PORTC = 0b01000000 + bla + j;  delay(1);
//        delay(1);
//        //Serial.println(PORTC,BIN);
//        PORTL = 0b10101010;
//        PORTG = 0b1;
//        delay(1);
//        PORTG = 0b0;
//        PORTL = 0b11111111;  
//        delay(1);
//        PORTC = 0b01000110;
//      }
//    }
//**************** ROČNO ************
//        byte bla = 0;
//        //**************** ROČNO ************
//        for(int i=0;i<3;i++){
//          for(int j=0;j<6;j++){
//            for(int k=0;k<8;k++){
//              bla = i << 3;
//              PORTC = 0b01000000 + bla + j;   delay(1);
//              //Serial.println(PORTC,BIN);
//              PORTL = 0b1 << k;
//              PORTG = 0b1;
//              delay(1);
//              PORTG = 0b0;
//              PORTC = 0b01000110;  delay(1);
//              PORTL = 0b11111111;
//              PORTG = 0b1;
//              delay(500);
//              
//              PORTC = 0b01000000 + bla + j; delay(0.1);
//              //Serial.println(PORTC,BIN);
//              PORTG = 0b11;
//              delay(1);
//            }   
//          }
//        }
        PORTC = 0b01000110;  delay(0.1);
        PORTL = 0b11111111;
        PORTG = 0b1;   delay(0.1); 
        PORTG = 0b0;
        
        PORTC = 0b01000000 + 0b00000 + 0b00;  delay(0.1);;
        //Serial.println(PORTC,BIN);
        PORTL = 0b10101010;
        PORTG = 0b1; delay(0.1);
        PORTG = 0b0;
        
        delay(1000);
        
        PORTC = 0b01000000 + 0b00000 + 0b11;  delay(0.1);
        //PORTC = 0b01000110;  delay(0.1);
        //PORTL = 0b0;
        PORTG = 0b10; delay(0.1); 
        PORTG = 0b0;
        delay(1000);
//
//        PORTC = 0b01000000 + 0b10000 + 0b01;  delay(1);
//        //Serial.println(PORTC,BIN);
//        PORTL = 0b10101010;
//        PORTG = 0b1;
//        delay(1);
//        PORTG = 0b0;
//        PORTC = 0b01000110;  delay(1);
//        PORTL = 0b11111111;
//        PORTG = 0b1; 
        
    
//  beriTipke(0b0011,0b10);
  
//    for(int j=0;j<4;j++){
//      //beriTipke(i,j);
//      //brisiLedke(i,j);
//      prizgiLedke(0b0011,j);
//    }
}

// SPI

#include<SPI.h>
#include<MFRC522.h>

#define SS_PIN D4
#define RST_PIN D3

MFRC522 rfid(SS_PIN, RST_PIN);

String tag = "";

void setupRFID() {
  SPI.begin(); // kich hoat giao SPI
  rfid.PCD_Init();
}

void scanEventRFID() {
  if (!rfid.PICC_IsNewCardPresent()) //
    return ;

  if(rfid.PICC_ReadCardSerial()){
    for(byte i = 0; i<4; i++) {
      tag += rfid.uid.uidByte[i];
    }
  }

  Serial.println(tag);

  tag = "";

  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1();
    
}

void setup() {
  Serial.begin(9600);
  setupRFID();
}


void loop () {
  scanEventRFID();
}

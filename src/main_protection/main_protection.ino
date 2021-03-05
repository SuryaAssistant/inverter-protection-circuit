/*
 * Protection circuit for 48V input to inverter 
 * 
 * Last update : 5 Maret 2021
 * 
 */

 
#define VBAT_PIN A0
#define CURRENT_PIN A1
#define VPROCTEC_PIN 8
#define CPROTEC_PIN 7


void setup(){
  Serial.begin(115200);
  pinMode(VBAT_PIN, INPUT);
  pinMode(CURRENT_PIN, INPUT);
  pinMode(VPROTEC_PIN, OUTPUT);
  pinMode(CPROTEC_PIN, OUTPUT);

  
}

void loop(){
  //Kosong
}


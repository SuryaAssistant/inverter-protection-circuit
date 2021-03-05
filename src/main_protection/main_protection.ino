/*
   Protection circuit for 48V input to inverter
   Reading battery voltage using voltage divider
   Reading current through ACS712ELCTR-30A-T

   Last update : 5 Maret 2021

*/


#define VBAT_PIN A0
#define CURRENT_PIN A1
#define VPROTEC_PIN 8
#define CPROTEC_PIN 7

#define R1 56000
#define R2 5100

//Voltage from voltage divider battery (A0)
int input_battery;
double battery_voltage;


unsigned int x = 0;
float AcsValue = 0.0, Samples = 0.0, AvgAcs = 0.0, AcsValueF = 0.0;

void setup() {
  Serial.begin(115200);
  pinMode(VBAT_PIN, INPUT);
  pinMode(CURRENT_PIN, INPUT);
  pinMode(VPROTEC_PIN, OUTPUT);
  pinMode(CPROTEC_PIN, OUTPUT);
}

void loop() {
  //Read battery value from voltage divider (adc)
  input_battery = analogRead(A0);
  battery_voltage = ((input_battery / 1023) * 5) * ((R2 + R1) / R1);

  if (battery_voltage > 50 || battery_voltage < 35) {
    digitalWrite(VPROTEC_PIN, LOW);
  }
  if (battery_voltage <= 50 && battery_voltage >= 35) {
    digitalWrite(VPROTEC_PIN, HIGH);
  }

  read_acs();


  print_data();

  delay(100);
}


void read_acs() {

  for (int x = 0; x < 150; x++) { //Get 150 samples
    AcsValue = analogRead(A0);     //Read current sensor values
    Samples = Samples + AcsValue;  //Add samples together
    delay (3); // let ADC settle before next sample 3ms
  }
  AvgAcs = Samples / 150.0; //Taking Average of Samples

  //((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
  //2.5 is offset(I assumed that arduino is working on 5v so the viout at no current comes
  //out to be 2.5 which is out offset. If your arduino is working on different voltage than
  //you must change the offset according to the input voltage)
  //0.066v(66mV) is rise in output voltage when 1A current flows at input
  AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) ) / 0.066;
}


void print_data() {
  Serial.print("Tegangan baterai : ");
  Serial.println(battery_voltage);
  Serial.print("Arus : ");
  Serial.println(AcsValueF);
}


/*
   Protection circuit for 48V input to inverter

   Last update : 5 Maret 2021

*/


#define VBAT_PIN A0
#define CURRENT_PIN A1
#define VPROCTEC_PIN 8
#define CPROTEC_PIN 7

#define R1 56000
#define R2 5100

//Voltage from voltage divider battery (A0)
int input_battery;
double battery_voltage;

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

  print_data();
}


void print_data() {
  Serial.print("Tegangan baterai : ");
  Serial.println(battery_voltage);

}


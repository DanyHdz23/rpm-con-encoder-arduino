/*Ejemplo para variar la velocidad de un motor
con pwm*/
#define motor 3 // PIN 3 
const int POT = A0; //Potenciometro

void setup() {
  pinMode(motor,OUTPUT);
}
void loop() {
  analogWrite(motor,analogRead(POT)/4);
}
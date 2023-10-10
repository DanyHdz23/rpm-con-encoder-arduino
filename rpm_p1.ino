/* Microcontroladores y Microprocesadores
Elaborado por:
    Daniel Hernández Hernández
    Alberto Ismael Alemán Bonfil
    Alan Omar Rodriguez Carmona
*/
//Calculo de rpm de un motor con encoder óptico FC-03//
/// Variables //
#define motor 3 // PIN D3 
const int POT = A0; //Potenciometro
int encoder_pin = 2; //Pin 2, donde se conecta el encoder       
unsigned int rpm = 0; // Revoluciones por minuto calculadas.
volatile byte pulses = 0; // Número de pulsos leidos por el Arduino en un segundo
unsigned long timeold = 0; // Tiempo 
unsigned int pulsesperturn = 20; // Número de muescas que tiene el disco del encoder.
const int wheel_diameter = 64; // Diámetro de la rueda pequeña[mm]
static volatile unsigned long debounce = 0; // Tiempo del rebote.
////  Configuración del Arduino ////
void setup(){
  Serial.begin(9600); // Configuración del puerto serie  
   pinMode(encoder_pin, INPUT); // Configuración del pin nº2
   attachInterrupt(0, counter, RISING); // Configuración de la interrupción 0, donde esta conectado. 
   pulses = 0;
   rpm = 0;
   timeold = 0;
  Serial.print("RPM ");
  Serial.print("Frecuencia ");
}
////  Programa principal /////
 void loop(){
  analogWrite(motor,analogRead(POT)/4); 
    if (millis() - timeold >= 1000){  // Se actualiza cada segundo
      noInterrupts(); //Don't process interrupts during calculations // Desconectamos la interrupción para que no actué en esta parte del programa.
      rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses; // Calculamos las revoluciones por minuto
      timeold = millis(); // Almacenamos el tiempo actual.
      Serial.print(rpm,DEC); Serial.print("   ");
      Serial.println(pulses,DEC); Serial.print("     ");
      pulses = 0;  // Inicializamos los pulsos.
      interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
   }
  }
////Fin de programa principal ////
////////Función que cuenta los pulsos buenos //// Correccion para evitar la lectura de señales paracitas y que influyan en el calculo.
 void counter(){
  if(  digitalRead (encoder_pin) && (micros()-debounce > 500) && digitalRead (encoder_pin) ) { 
// Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
        debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
        pulses++;}  // Suma el pulso bueno que entra.
        else ; } 
void setup() {
  // Configuracion del puerto A como salida
  DDRA= 0B11111111;
  // Inicializacion apagando los leds
  PORTA=0B00000000; 
}
void loop() {
 PORTA=0B11111111; //Encendido de todos los leds.
 delay(1000); // Espera de un segundo
 PORTA=0B00000000; //Apagado de todos los leds.
 delay(1000);
 PORTA=0B10101010; // Encendido alternado de leds.
 delay(1000);
 PORTA= 0B11110000;//Encendido de los leds de los 4 últimos pines del puertoA.
 delay(10000);
 PORTA=0B00001111;//Encendido de los leds de los 4 primeros pines del puertoA.
 delay(1000);
}

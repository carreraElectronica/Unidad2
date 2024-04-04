//Declaramos un array para los números del display de ánodo común
int numerosDisplay[10] = { 192, 249, 164, 176, 153, 146, 131, 248, 128, 152 };
void setup() {
  //Configuramos el puerto A y C como salidas
  DDRA = 255;  //0 DDRB=0B111111111;
  DDRC = 255;
  // Se apaga todos los segmentos del display

  PORTC = 0B11111111;
  //Se desactivan los transistores
  PORTA = 0B11111111;
  // Se configuran los pines de los botones como entradas
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
}
// Declaración de variables para la función llamada separación
int numero = 0;
int mil, centena, decena, unidad, aux;
// La funcion separacion descompone el valor de numero
void separacion() {
  mil = numero / 1000;
  centena = numero - mil * 1000;
  aux = centena;
  centena = centena / 100;
  decena = aux - centena * 100;
  aux = decena;
  decena = decena / 10;
  unidad = aux - decena * 10;
}
// Creacion de la funcion barrido
void barrido() {
  //Activacion del display D1 y muestra del valor mil
  PORTA = 0B11111110;
  PORTC = numerosDisplay[mil];
  delay(50);
  //Activacion del display D2 y muestra del valor centena
  PORTA = 0B11111101;
  PORTC = numerosDisplay[centena];
  delay(50);
  //Activacion del display D3 y muestra del valor decena
  PORTA = 0B11111011;
  PORTC = numerosDisplay[decena];
  delay(50);
  //Activacion del display D4 y muestra del valor unidad
  PORTA = 0B11110111;
  PORTC = numerosDisplay[unidad];
  delay(100);
}
void loop() {
  //lectura de los pulsadores
  int pulsador1 = digitalRead(52);
  int pulsador2 = digitalRead(53);
  //Tiempo de espera para evitar falsas pulsaciones
  delay(200);
  // Instrucciones para el pulsador1 sea accionado
  if (pulsador1 == 0) {
    if (numero < 9999) {
      numero++;
    } else {
      numero = 0;
    }
  }
  //Instrucciones para cuando el pulsador2 sea presionado
  if (pulsador2 == 0) {
    if (numero > 0) {
      numero--;
    } else {
      numero = 9999;
    }
  }
  // Llamado a la funcion separacion y barrido para presentar el valor de numero
  separacion();
  barrido();
}

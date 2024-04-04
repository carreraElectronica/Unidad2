//Declaramos un array para los numeros del display de ánodo común
int numerosDisplay[10] = { 192, 249, 164, 176, 153, 146, 131, 248, 128, 152 };
// Incluir la libreria del LCD
#include <LiquidCrystal.h>
//Asignamos pines para RS,E,D4,D5,D6,D7
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);
void setup() {
  //Configuracion para el display de 7 segmentos
  DDRL = 255;
  DDRB = 255;
  // Se apaga todos los segmentos del display
  PORTL = 0B11111111;
  //Se desactican los transistores
  PORTB = 0B11111111;
  //Configuración del puerto como salidas para columnas( 1's) y entradas para filas (0's)
  DDRA = 0B11110000;
  //Deshabilitacion de la columnas y activacion del modo PULLUP
  PORTA = 0B11111111;
  //Configuracion individual de los pines de las filas
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  //Iniciamos el display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Juego de luces");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Introduzca nro");
  lcd.setCursor(0, 1);
  lcd.print("de repeticiones");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Repeticiones:");
  //Pines como entradas para los pulsadores
  //Pulsadores para el tiempo
  pinMode(41, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  //Pulsador para encender un foco de 110V
  pinMode(39, INPUT_PULLUP);
  //Puerto para los leds
  DDRK = 255;
  PORTK = 0;
  //Pin para el rele
  pinMode(21, OUTPUT);
}
//Declaracion de variables para almacenar los estados de cada fila
int f1, f2, f3, f4;
void leerFilas() {
  //lectura y asignacion de las cuatro filas
  f1 = digitalRead(22);
  f2 = digitalRead(23);
  f3 = digitalRead(24);
  f4 = digitalRead(25);
  //tiempo de espera antirebote
  delay(100);
}
//Declaracion de variable para almacenar el caracter de la tecla presionada
int tecla;
int numero = 0;
void barridoTeclado() {
  // Asignacion para que la tecla presionada se guarde solo una vez
  tecla = 16;
  //Habilitacion de la Columna 1
  PORTA = 0B11101111;
  //Llamada a la funcion leerFilas para el monitoreo
  leerFilas();
  //Asignacion de numeros a la variable tecla segun el interruptor presionado
  if (f1 == 0) { tecla = 1; }
  if (f2 == 0) { tecla = 4; }
  if (f3 == 0) { tecla = 7; }
  if (f4 == 0) { tecla = 10; }  //Para tecla *
  //Habilitacion de la Columna 2
  PORTA = 0B11011111;
  leerFilas();
  if (f1 == 0) { tecla = 2; }
  if (f2 == 0) { tecla = 5; }
  if (f3 == 0) { tecla = 8; }
  if (f4 == 0) { tecla = 0; }
  //Habilitacion de la Columna 3
  PORTA = 0B10111111;
  leerFilas();
  if (f1 == 0) { tecla = 3; }
  if (f2 == 0) { tecla = 6; }
  if (f3 == 0) { tecla = 9; }
  if (f4 == 0) { tecla = 11; }  // Para la tecla #
                                //Habilitacion de la Columna 4
  PORTA = 0B01111111;
  leerFilas();
  if (f1 == 0) { tecla = 12; }  //A
  if (f2 == 0) { tecla = 13; }  //B
  if (f3 == 0) { tecla = 14; }  //C
  if (f4 == 0) { tecla = 15; }  //D
  //Asignacion del valor de la tecla presionada a numero si el valor no es 16
  if (tecla < 16) { numero = tecla; }
}
//Varaible para almacenar los valores separados
int mil, centena, decena, unidad, aux;
// Variable para el tiempo de los leds
int tiempo = 200;
// La funcion separacion descompone el valor de numero
void separacion() {
  mil = tiempo / 1000;
  centena = tiempo - mil * 1000;
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
  PORTB = 0B11111110;
  PORTL = numerosDisplay[mil];
  delay(100);
  //Activacion del display D2 y muestra del valor centena
  PORTB = 0B11111101;
  PORTL = numerosDisplay[centena];
  delay(100);
  //Activacion del display D3 y muestra del valor decena
  PORTB = 0B11111011;
  PORTL = numerosDisplay[decena];
  delay(100);
  //Activacion del display D4 y muestra del valor unidad
  PORTB = 0B11110111;
  PORTL = numerosDisplay[unidad];
  delay(100);
}
//funciones de juegos de luces
void juego1(int tiempo) {
  PORTK = 0B10000001;
  delay(tiempo);
  PORTK = 0B01000010;
  delay(tiempo);
  PORTK = 0B00100100;
  delay(tiempo);
  PORTK = 0B00011000;
  delay(tiempo);
  PORTK = 0B00100100;
  delay(tiempo);
  PORTK = 0B01000010;
  delay(tiempo);
  PORTK = 0B10000001;
  delay(tiempo);
  numero = 0;
}
int pulsos = 0;
void loop() {
  //Lectura de los pulsadores
  int pulsador1 = digitalRead(41);
  int pulsador2 = digitalRead(40);
  int pulsador3 = digitalRead(39);
  delay(200);
  //Control del tiempo de leds
  if (pulsador1 == 0) {
    if (tiempo < 9999) {
      tiempo += 100;
    } else {
      tiempo = 0;
    }
  }
  if (pulsador2 == 0) {
    if (tiempo > 0) {
      tiempo -= 100;
    } else {
      tiempo = 9999;
    }
  }
  //Control de encendido del foco a traves de un rele
  if (pulsador3 == 0) {
    if (pulsos < 2) {
      pulsos++;
    } else {
      pulsos = 0;
    }
  }
  if (pulsos == 1) { digitalWrite(21, HIGH); }
  if (pulsos == 2) { digitalWrite(21, LOW); }
  //Obtencion de los 4 digitos e impresion
  barridoTeclado();
  separacion();
  barrido();
  lcd.setCursor(0, 1);
  lcd.print(numero);
  lcd.print(" ");
  //Control de repeticiones del juego
  int repeticiones;
  repeticiones = numero;
  for (int veces = 0; veces < repeticiones; veces++) {
    juego1(tiempo);
  }
  PORTK = 0;
}

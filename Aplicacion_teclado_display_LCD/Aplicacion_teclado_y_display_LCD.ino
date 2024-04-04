// Incluir la libreria del LCD
#include <LiquidCrystal.h>
//Asignamos pines para RS,E,D4,D5,D6,D7
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);
void setup() {
  //Configuración del puerto como salidas para columnas (1's) y entradas para filas (0's)
  DDRA = 0B11110000;
  //Deshabilitacion de las columnas y activacion del modo PULLUP
  PORTA = 0B11111111;
  //Configuracion individual de los pines de las filas
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  //Iniciamos el display
  lcd.begin(16, 2);
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
//Funcion para formar un numero de cuatro digitos
int digito;
int fourdig;
void valor() {
  if (numero < 10) {
    digito++;
    if (digito == 1) { fourdig = numero; }
    if (digito == 2) { fourdig = fourdig * 10 + numero; }
    if (digito == 3) { fourdig = fourdig * 10 + numero; }
    if (digito == 4) {
      fourdig = fourdig * 10 + numero;
      digito = 0;
    }
  }
}
// Variable para controlar en que fila se muestra
int fila = 0;
void loop() {
  numero = 16;
  barridoTeclado();
  valor();
  //Cambio de fila al presionar la tecla D
  if (numero == 15) {
    fila = 1;
    fourdig = 0;
  }
  // Limpiar el teclado
  if (numero == 10) {
    lcd.clear();
    //reinicio del valor de 4 digitos
    fourdig = 0;
    fila = 0;
  }
  if (fila == 0) {
    lcd.setCursor(0, 0);
    lcd.print(fourdig);
    //eliminar residuos
    lcd.print("   ");
  }
  if (fila == 1) {
    lcd.setCursor(0, 1);
    lcd.print(fourdig);
    lcd.print("   ");
  }

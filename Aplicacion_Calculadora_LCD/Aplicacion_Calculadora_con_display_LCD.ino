#include <LiquidCrystal.h>
LiquidCrystal lcd(27, 26, 25, 24, 23, 22);
int mil, centena, decena, unidad, dato1 = 1234;
int dato, tecla, f1, f2, f3, f4, num, numero, aux, aux1, aux2, opera, veces;
int x[10] = { 192, 249, 164, 176, 153, 146, 131, 248, 128, 152 };
void setup() {
  DDRL = 255;         //declaramos al puerto L como salidas
  DDRK = 255;         //declaramos al puerto K como salidas
  DDRC = 0B00001111;  //declarando los primeros 4 pines como entradas;
  PORTC = 255;
  pinMode(33, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  lcd.begin(16, 2);  //inicializamos la LCD
}
void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(numero);
  lcd.print("  ");
  dato1 = numero;
  teclado();
  separa();
  barrido();
  if (dato < 10) {
    num++;
    if (num == 1) { numero = dato; }
    if (num == 2) { numero = numero * 10 + dato; }
    if (num == 3) { numero = numero * 10 + dato; }
    if (num == 4) {
      numero = numero * 10 + dato;
      num = 0;
    }
    dato = 16;
  }
  if (dato == 15) {
    veces++;
    if (veces == 1) { aux1 = numero; }
    if (veces == 2) { aux2 = numero; }
    lcd.setCursor(15, 0);
    lcd.print("+");
    opera = 1;
    dato = 16;
    num = 0;
  }
  if (dato == 14) {
    veces++;
    if (veces == 1) { aux1 = numero; }
    if (veces == 2) { aux2 = numero; }
    lcd.setCursor(15, 0);
    lcd.print("-");
    opera = 2;
    dato = 16;
    num = 0;
  }
  if (dato == 13) {
    veces++;
    if (veces == 1) { aux1 = numero; }
    if (veces == 2) { aux2 = numero; }
    lcd.setCursor(15, 0);
    lcd.print("*");
    opera = 3;
    dato = 16;
    num = 0;
  }
  if (dato == 12) {
    veces++;
    if (veces == 1) { aux1 = numero; }
    if (veces == 2) { aux2 = numero; }
    lcd.setCursor(15, 0);
    lcd.print("/");
    opera = 4;
    dato = 16;
    num = 0;
  }
  if (dato == 11) {
    num = 0;
    veces = 0;
    if (opera == 1) { numero = aux1 + aux2 + numero; }
    dato = 16;
    if (opera == 2) { numero = aux1 - aux2 - numero; }
    dato = 16;
    if (opera == 3) { numero = aux1 * aux2 * numero; }
    dato = 16;
    if (opera == 4) { numero = aux1 / aux2 / numero; }
    dato = 16;
  }
}
void separa() {
  mil = numero / 1000;
  centena = numero - mil * 1000;
  aux = centena;
  centena = centena / 100;
  decena = aux - centena * 100;
  aux = decena;
  decena = decena / 10;
  unidad = aux - decena * 10;
}
void barrido() {
  PORTL = 0B11111110;
  PORTK = x[mil];
  delay(50);
  PORTL = 0B11111101;
  PORTK = x[centena];
  delay(50);
  PORTL = 0B11111011;
  PORTK = x[decena];
  delay(50);
  PORTL = 0B11110111;
  PORTK = x[unidad];
  delay(50);
}
void teclado() {
  tecla = 16;
  PORTC = 0B11111110;
  leer();
  if (f1 == 0) { tecla = 7; }
  if (f2 == 0) { tecla = 4; }
  if (f3 == 0) { tecla = 1; }
  if (f4 == 0) { tecla = 10; }
  PORTC = 0B11111101;
  leer();
  if (f1 == 0) { tecla = 8; }
  if (f2 == 0) { tecla = 5; }
  if (f3 == 0) { tecla = 2; }
  if (f4 == 0) { tecla = 0; }
  PORTC = 0B11111011;
  leer();
  if (f1 == 0) { tecla = 9; }
  if (f2 == 0) { tecla = 6; }
  if (f3 == 0) { tecla = 3; }
  if (f4 == 0) { tecla = 11; }
  PORTC = 0B11110111;
  leer();
  if (f1 == 0) { tecla = 12; }
  if (f2 == 0) { tecla = 13; }
  if (f3 == 0) { tecla = 14; }
  if (f4 == 0) { tecla = 15; }

  if (tecla < 16) {
    dato = tecla;
    delay(300);
  }
}
void leer() {
  f1 = digitalRead(33);
  f2 = digitalRead(32);
  f3 = digitalRead(31);
  f4 = digitalRead(30);
}

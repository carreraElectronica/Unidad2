//Declaramos un array para los numeros del display de ánodo común
int numerosDisplay[10] = { 192, 249, 164, 176, 153, 146, 131, 248, 128, 152 };
void setup() {
  //Configuración del puerto como salidas y entradas
  DDRA = 0B11110000;
  //Deshabilitacion de la columnas y activacion del modo PULLUP
  PORTA = 0B11111111;
  //Configuracion individual de los pines de las filas
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  //Configuracion para el display de 7 segmentos
  DDRC = 255;
  DDRB = 255;
  // Se apaga todos los segmentos del display
  PORTC = 0B11111111;
  //Se desactican los transistores
  PORTB = 0B11111111;
}

//Declaracion de variables para almacenar los estados de cada fila
int f1, f2, f3, f4;
void leerFilas() {
  //lectura y asignacion de las cuatro filas
  f1 = digitalRead(22);
  f2 = digitalRead(23);
  f3 = digitalRead(24);
  f4 = digitalRead(25);
  //tiempo de espera anti rebote
  delay(200);
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
int fordig;
// La funcion separacion descompone el valor de numero
void separacion() {
  mil = fordig / 1000;
  centena = fordig - mil * 1000;
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
  PORTC = numerosDisplay[mil];
  delay(50);
  //Activacion del display D2 y muestra del valor centena
  PORTB = 0B11111101;
  PORTC = numerosDisplay[centena];
  delay(50);
  //Activacion del display D3 y muestra del valor decena
  PORTB = 0B11111011;
  PORTC = numerosDisplay[decena];
  delay(50);
  //Activacion del display D4 y muestra del valor unidad
  PORTB = 0B11110111;
  PORTC = numerosDisplay[unidad];
  delay(50);
}
//Funcion para formar un numero de cuatro digitos
int digito;
void valor() {
  if (numero < 10) {
    digito++;
    if (digito == 1) { fordig = numero; }
    if (digito == 2) { fordig = fordig * 10 + numero; }
    if (digito == 3) { fordig = fordig * 10 + numero; }
    if (digito == 4) {
      fordig = fordig * 10 + numero;
      digito = 0;
    }
  }
}
  void loop() {
    numero = 16;
    barridoTeclado();
    valor();
    separacion();
    barrido();
  }

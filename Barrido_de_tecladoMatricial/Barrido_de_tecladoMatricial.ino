void setup() {
  //Configuración del puerto como salidas para columnas (1's) y entradas para filas (0's)
  DDRA = 0B11110000;
  //Deshabilitación de las columnas y activación del modo PULLUP
  PORTA = 0B11111111;
  //Configuración individual de los pines de las filas
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  //Inicialización de la comunicación serial para ver el valor de numero
  Serial.begin(9600);
}
/*Declaración de variables para almacenar los estados de cada fila*/
int f1, f2, f3, f4;
void leerFilas() {
  //lectura y asignación de las cuatro filas
  f1 = digitalRead(22);
  f2 = digitalRead(23);
  f3 = digitalRead(24);
  f4 = digitalRead(25);
  //tiempo de espera anti rebote
  delay(200);
}

/*Declaración de variable para almacenar el carácter de la tecla presionada*/
int tecla;
int numero;
void barridoTeclado() {
  // Asignación para que la tecla presionada se guarde solo una vez
  tecla = 16;
  //Habilitación de la Columna 1
  PORTA = 0B11101111;
  /*Llamada a la función leerFilas para el monitoreo*/
  leerFilas();
  /*Asignación de números a la variable tecla según el interruptor presionado*/
  if (f1 == 0) { tecla = 1; }
  if (f2 == 0) { tecla = 4; }
  if (f3 == 0) { tecla = 7; }
  if (f4 == 0) { tecla = 10; }  //Para tecla *

  //Habilitación de la Columna 2
  PORTA = 0B11011111;
  leerFilas();
  if (f1 == 0) { tecla = 2; }
  if (f2 == 0) { tecla = 5; }
  if (f3 == 0) { tecla = 8; }
  if (f4 == 0) { tecla = 0; }
  //Habilitación de la Columna 3
  PORTA = 0B10111111;
  leerFilas();
  if (f1 == 0) { tecla = 3; }
  if (f2 == 0) { tecla = 6; }
  if (f3 == 0) { tecla = 9; }
  if (f4 == 0) { tecla = 11; }  // Para la tecla #
  //Habilitación de la Columna 4
  PORTA = 0B01111111;
  leerFilas();
  if (f1 == 0) { tecla = 12; }  //A
  if (f2 == 0) { tecla = 13; }  //B
  if (f3 == 0) { tecla = 14; }  //C
  if (f4 == 0) { tecla = 15; }  //D

  /*Asignación del valor de la tecla presionada a número si el valor no es 16*/
  if (tecla < 16) { numero = tecla; }
}
void loop() {
  barridoTeclado();
  // Imprimir el número en el puerto serial
  Serial.println(numero);
  delay(300);
}

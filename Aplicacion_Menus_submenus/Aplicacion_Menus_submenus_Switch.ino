#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
int r, A, a, b, AR, P1, P2, P3, P4, P5, P6, P7, pul, tecla, dato;
int salir = 0;
float AC, pi = 3.14;
void setup() {
  pinMode(35, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.clear();
  menu1();
  pulsador();
}
void loop() {
  pulsador();
  switch (dato) {
    case 1:
      salir = 0;
      menu2();
      while (salir == 0) {
        lcd.setCursor(4, 1);
        lcd.print(r);
        lcd.setCursor(9, 1);
        lcd.print(AC);
        pulsador();
        if (P4 == 0) {
          if (r < 10) {
            r++;
            AC = pi * (r * r);
          }
          pul = 3;
        }
        if (P5 == 0) {
          if (r > 0) {
            r--;
            AC = pi * (r * r);
          }
          pul = 3;
        }
        if (P3 == 0) { salir = 1; }
      }
      menu1();
      break;
    case 2:
      salir = 0;
      menu3();
      while (salir == 0) {
        lcd.setCursor(3, 1);
        lcd.print(a);
        lcd.setCursor(8, 1);
        lcd.print(b);
        lcd.setCursor(15, 0);
        lcd.print(AR);
        pulsador();
        if (P4 == 0) {
          if (a < 10) {
            a++;
            AR = a * b;
          }
          pul = 3;
        }
        if (P5 == 0) {
          if (a > 0) {
            a--;
            AR = a * b;
          }
          pul = 3;
        }
        if (P6 == 0) {
          if (b < 10) {
            b++;
            AR = a * b;
          }
          pul = 3;
        }
        if (P7 == 0) {
          if (b > 0) {
            b--;
            AR = a * b;
          }
          pul = 3;
        }
        if (P3 == 0) {
          salir = 1;
        }
        pul = 3;
      }
      menu1();
      break;
  }
}
void menu1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   menu1  ");
  lcd.setCursor(0, 1);
  lcd.print("1.AC  2.AR  3.Calc");
}
void menu2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   A del circulo  ");
  lcd.setCursor(0, 1);
  lcd.print("r=     A=  ");
}
void menu3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("M rectangulo A=  ");
  lcd.setCursor(0, 1);
  lcd.print("a=    b=  ");
}
void pulsador() {
  pul = 3;
  P1 = digitalRead(36);
  P2 = digitalRead(35);
  P3 = digitalRead(34);
  P4 = digitalRead(33);
  P5 = digitalRead(32);
  P6 = digitalRead(31);
  P7 = digitalRead(30);
  if (P1 == 0) {
    pul = 1;
  } else if (P2 == 0) {
    pul = 2;
  } else {
    pul = 0;
  }
  if (pul < 3) {
    dato = pul;
    delay(300);
  }
}

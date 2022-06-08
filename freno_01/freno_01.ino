/* PROTORIPO FRENO AUXILIAR DE AUTOMOVIL
 * 
 * Motor a pasos con mecanismo piñon-cremallera 
 * para convertir el mov. giratorio en mov. lineal.
 * 
 * Se presiona un disco de metal para frenarlo.
 * 
 * Sensor para detectar posicion inicial.
 */

// Fines de carrera, con resistencias pull-down, cuando se presionan cambian de 0 a 5 V
#define PIN_SW1 6 //frontal
#define PIN_SW2 7 //trasero
//byte sw1; //estado actual del switch 1
//byte sw1prev = 0; //estado previo
//byte sw2; //estado actual del switch 2
//byte sw2prev = 0; //estado previo


// Motor a pasos con controlador A4988
#define PIN_DIR 8
#define PIN_STEP 9

// Inicializar LCD
#include <LiquidCrystal.h>
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
#define T_LCD 500 //periodo de actualización de LCD
unsigned long tlcd = 0; //momento de actualizar LCD
unsigned long t;

#define PIN_POT A0 //potenciómetro
unsigned int pot; //lectura del pot
unsigned int vel; //velocidad

void setup() {
  // Usar 16 columnas y 2 filas
  lcd.begin(16, 2);
  // Mensaje inicial
  lcd.setCursor(0, 0);
  lcd.print("EXHALACION");
  lcd.setCursor(0, 1);
  //lcd.print("Potencia:");
  lcd.print("Velocidad:");
  //Serial.begin(9600);

  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  digitalWrite(PIN_STEP, 0);
  digitalWrite(PIN_DIR, 0);

  pinMode(PIN_POT, INPUT);
  analogRead(PIN_POT);

  pinMode(PIN_SW1, INPUT);
  pinMode(PIN_SW2, INPUT);
}

void loop() {
  // Enviar pulso al conrolador del motor
  digitalWrite(PIN_STEP, 1); //positivo
  delayMicroseconds(100); //esperar
  digitalWrite(PIN_STEP, 0); //regresar a cero

  t = millis(); //leer momento actual
  if (t >= tlcd) {// Si es momento de actualizar la LCD
    tlcd += T_LCD; //agregar periodo de actualización
    pot = analogRead(PIN_POT); //leer pot
    vel = ((1023 - pot) * 3 / 31) + 1;
    lcd.setCursor(11, 1); //posición para escribir
    lcd.print(vel); //escribir valor
    lcd.print("  "); //espacios para borrar carateres de la escritura anterior
  }
  else { //si no es momento de actualizar la LCD realizar un retardo
    delay(1); //retardo mínimo
    delayMicroseconds(pot*2); //retardo proporcional a la lectura del pot
  }

  // El motor ya avanzó un paso, checar fines de carrera
  //frontal
  if (digitalRead(PIN_SW1)) {//acaba de ser presionado
    digitalWrite(PIN_DIR, 0);
    lcd.setCursor(0, 0); //posición para escribir
    lcd.print("EX"); //escribir valor
  }
  //trasero
  if (digitalRead(PIN_SW2)) {//acaba de ser presionado
    digitalWrite(PIN_DIR, 1);
    lcd.setCursor(0, 0); //posición para escribir
    lcd.print("IN"); //escribir valor
  }
  /*
    sw1 = digitalRead(PIN_SW1); //frontal
    if ((sw1 == 1) and (sw1prev = 0)) {//acaba de ser presionado
    digitalWrite(PIN_DIR, 0);
    lcd.setCursor(0, 0); //posición para escribir
    lcd.print("EX"); //escribir valor
    }
    sw1prev = sw1; //actualizar estado previo

    sw2 = digitalRead(PIN_SW2); //trasero
    if ((sw2 == 1) and (sw2prev = 0)) {//acaba de ser presionado
    digitalWrite(PIN_DIR, 1);
    lcd.setCursor(0, 0); //posición para escribir
    lcd.print("IN"); //escribir valor
    }
    sw2prev = sw2; //actualizar estado previo
  */
}

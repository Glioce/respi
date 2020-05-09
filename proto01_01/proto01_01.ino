/* RESPIRADOR ARTIFICIAL
 *  
 * Modelo 3D obtenido de Frax3D
 * 
 * El prototipo tiene un programa que controla la velocidad de desplazamiento del pistón,
 * pero es demasiado lento.
 * En esta versión del programa se incrementará la velocidad usando reduciendo la
 * tasa de actualización de la LCD (que requiere varios ms) y tal vez interrupciones y timers.
 * 
 * Se usa la biblioteca LiquidCrystal

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/


#include <LiquidCrystal.h>

// Inicializar LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  Serial.println(millis());
}

#include <LiquidCrystal.h>

//motor
const int DC_MOTOR = 3;

//LCD
const int RS = 4;
const int E = 5;
const int DB4 = 6;
const int DB5 = 7;
const int DB6 = 8;
const int DB7 = 9;

//temp sensor
const int TEMP_SENSOR = A0;

//LED
const int RED_LED = 10;
const int BLUE_LED = 11;
const int GREEN_LED = 12;

//degree character
const char DEGREE = (char) 178;

//initialize LCD
LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);
int tempC;

void setup()
{
  pinMode(DC_MOTOR, OUTPUT); //motor
  lcd.begin(16, 2); //lcd
  pinMode(TEMP_SENSOR, INPUT); //temp sensor
  for (int i = RED_LED; i <= GREEN_LED; i++) //LEDs
    pinMode(i, OUTPUT);
  
  //print never-changing text to LCD
 lcd.print("TEMP :");
}

void loop()
{
  //read sensor value 20-358
  int tempSensorValue = analogRead(TEMP_SENSOR);
  // map sensor value 20-358 to -40 to 125
  tempC = map(tempSensorValue, 20, 358, -40, 125);
  
    
  //if-else chain to decide color, LCD screen, and fan speed
  if (tempC <= 20) {
     writeToLCD(tempC, "COLD!     "); 
     analogWrite(DC_MOTOR, 0);
     digitalWrite(RED_LED, LOW);
     digitalWrite(BLUE_LED, HIGH);
     digitalWrite(GREEN_LED, HIGH);
  } else if (tempC <= 25) {
     writeToLCD(tempC, "SEMI-WARM   "); 
     analogWrite(DC_MOTOR, .25 * 255);
     digitalWrite(RED_LED, LOW);
     digitalWrite(BLUE_LED, HIGH);
     digitalWrite(GREEN_LED, LOW);
  } else if (tempC <= 32) {
     writeToLCD(tempC, "WARM       "); 
     analogWrite(DC_MOTOR, .50 * 255);
     digitalWrite(RED_LED, LOW);
     digitalWrite(BLUE_LED, LOW);
     digitalWrite(GREEN_LED, HIGH);
  } else if (tempC <= 38) {
     writeToLCD(tempC, "HOT       "); 
     analogWrite(DC_MOTOR, .75 * 255);
     digitalWrite(RED_LED, HIGH);
     digitalWrite(BLUE_LED, HIGH);
     digitalWrite(GREEN_LED, LOW);
  } else {
     writeToLCD(tempC, "EXTREME    "); 
     analogWrite(DC_MOTOR, 255);
     digitalWrite(RED_LED, HIGH);
     digitalWrite(BLUE_LED, LOW);
     digitalWrite(GREEN_LED, LOW);
  }
  
}

//function to write text to the LCD since the location never changes
void writeToLCD(int temp, String tempDesc) {
  
  lcd.setCursor(5, 0);
  lcd.print(temp);
  lcd.print(DEGREE);
  lcd.print("C    ");
  lcd.setCursor(0, 1);
  lcd.print(tempDesc);
}

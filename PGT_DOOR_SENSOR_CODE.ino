#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "SparkFun_VL6180X.h"

#include <LiquidCrystal_I2C.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

VL6180xIdentification identification;
VL6180x sensor(0x29);


LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Wire.begin();
  lox.begin(0x30);
  delay(300);
  sensor.VL6180xInit();
  sensor.VL6180xDefautSettings();

  
  
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Sparrow Design");
  lcd.setCursor(0,1);
  lcd.print("Door Jam PGT");
  delay(2000);
  lcd.clear();
  delay(200);

}

bool skip = 0;
bool skip1 = 0;

void loop()
{

  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  // initial start 
  lcd.setCursor(0,0);
  lcd.print("Long  : ");
  lcd.setCursor(0,1);
  lcd.print("Short : ");

  if (measure.RangeStatus != 4 && measure.RangeMilliMeter<5000 && measure.RangeMilliMeter>50){  // phase failures have incorrect data
    lcd.setCursor(9,0); skip = 0;
    lcd.print(measure.RangeMilliMeter);}
  else{
    lcd.setCursor(9,0); skip = 1;
    lcd.print("ERR");}
  
  if(sensor.getDistance()<255){
    lcd.setCursor(9,1);  skip1 = 0;
    lcd.print(sensor.getDistance());}ta
  else{
    lcd.setCursor(9,1); skip1 = 1;
    lcd.print("ERR");}
    


  delay(300);

  if(skip == 0){
    lcd.setCursor(9,0);
    lcd.print("                 ");}
  if(skip1 == 0){
    lcd.setCursor(9,1);
    lcd.print("                 ");}

}

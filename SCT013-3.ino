#include <Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "EmonLib.h"

EnergyMonitor emon1;                                                                            
EnergyMonitor emon2;
EnergyMonitor emon3;

int tegangan = 220.0;

//pin yang digunakan sensor SCT
int pin_sct1 = 35;
int pin_sct2 = 39;
int pin_sct3 = 36;

// dapat dicek menggunakan i2c finder

void setup()
{
  Serial.begin(115200);
  lcd.begin(); //prosedur pemanggilan LCD
  lcd.setBacklight(255);

  lcd.setCursor(00, 00); //set pada baris 1 dan kolom 1
  lcd.print("SHOTBLAST DIAKTIFKAN"); //menuliskan "Hello World"
  delay(1000);
  lcd.clear(); //menghapus data sebelumnya

  delay(3000);

  //calib - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pin_sct1, 30);//20/6/5.18/4.74/48
  emon2.current(pin_sct2, 30);
  emon3.current(pin_sct3, 30);
}

void loop()
{
  // Read current values from all three sensors
  float Irms1 = emon1.calcIrms(1480);
  float Irms2 = emon2.calcIrms(1480);
  float Irms3 = emon3.calcIrms(1480);
  
  // Check if any of the current values is less than 3A and set it to 0
//  if (Irms1 < 3) {
//    Irms1 = 0;
//  }
//  if (Irms2 < 3) {
//    Irms2 = 0;
//  }
  if (Irms3 < 3) {
    Irms3 = 0;
  }
  
  // Print current values to the serial monitor
  Serial.print("Arus 1 yang terbaca : ");
  Serial.println(Irms1, 4);
  Serial.print("Arus 2 yang terbaca : ");
  Serial.println(Irms2, 4);
  Serial.print("Arus 3 yang terbaca : ");
  Serial.println(Irms3, 4);

  // Display current values on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Arus 1 (A): ");
  lcd.print(Irms1, 2);
  
  lcd.setCursor(0, 1);
  lcd.print("Arus 2 (A): ");
  lcd.print(Irms2, 2);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arus 3 (A): ");
  lcd.print(Irms3, 2);

  delay(2000);
}

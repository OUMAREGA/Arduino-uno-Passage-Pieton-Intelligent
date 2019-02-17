#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorRed = 0;
const int colorGreen = 255;
const int colorBlue = 0;
/**
  Le bouton poussoir
*/
int etatBouton;
int boutonPressed = 0;
int boutonNonPressed = 1;
/**
  Les leds
*/
int ledVertCoteVoitures = 13;
int ledJauneCoteVoitures = 12;
int ledRougeCoteVoitures = 11;
int ledRougeCotePietons = 10;
int ledVertCotePietons = 9;
/**
  Le capteur Ultrason
*/
int trig = 7;
int echo = 6;
long lecture_echo;
long distanceEncm;

void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorRed, colorGreen, colorBlue);
  /**
    Leds
  */
  pinMode(ledVertCoteVoitures, OUTPUT);
  pinMode(ledJauneCoteVoitures, OUTPUT);
  pinMode(ledRougeCoteVoitures, OUTPUT);
  pinMode(ledRougeCotePietons, OUTPUT);
  pinMode(ledVertCotePietons, OUTPUT);
  // bouton poussoir
  pinMode(2, INPUT);
  Serial.begin(9600);
  /**
     Capteur
  */
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bonne passage !");
  lcd.setCursor(0,1);
  lcd.print("Le feu est vert");
  digitalWrite(ledVertCotePietons, HIGH);
  digitalWrite(ledRougeCoteVoitures, HIGH);
  delay(5000);
  digitalWrite(ledJauneCoteVoitures, HIGH);
  digitalWrite(ledRougeCoteVoitures, LOW);
  delay(5000);
  int dureeEnSeconde = 10;
  for (int i = 0; i < dureeEnSeconde; ++i)
  {
    digitalWrite(ledJauneCoteVoitures, LOW);
    digitalWrite(ledVertCotePietons, LOW);
    digitalWrite(ledVertCoteVoitures, HIGH);
    digitalWrite(ledRougeCotePietons, HIGH);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10); // envoi d'une impulsion sur trig de 10 microsecondes
    digitalWrite(trig, LOW);
    lecture_echo = pulseIn(echo, HIGH);
    distanceEncm = lecture_echo / 58; // lecture_echo*340/(2*10000)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance cm : ");
    lcd.print(distanceEncm);
    lcd.setCursor(0,1);
    lcd.print("Bouton non Presse");
    etatBouton = digitalRead(2);
    if  ( (etatBouton == boutonPressed) && (distanceEncm > 25))
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Distance cm : ");
      lcd.print(distanceEncm);
      lcd.setCursor(0, 1);
      lcd.print("Buton Presse");
      delay(1000);
      digitalWrite(ledJauneCoteVoitures, LOW);
      digitalWrite(ledVertCoteVoitures, LOW);
      digitalWrite(ledRougeCotePietons, LOW);
      loop();
    }
    if ( (etatBouton == boutonPressed) && (distanceEncm < 25) )
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Distance cm : ");
      lcd.print(distanceEncm);
      lcd.setCursor(0, 1);
      lcd.print("Buton Presse");
      delay(1000);
    }

    else if (etatBouton == boutonNonPressed)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Distance cm : ");
      lcd.print(distanceEncm);
      lcd.setCursor(0,1);
      lcd.print("Bouton non Presse");
      delay(1000);
      digitalWrite(ledVertCoteVoitures, LOW);
      digitalWrite(ledRougeCotePietons, LOW);
    }
  }
}

int Reihenfolge[501];
int Runde;
int Splashdelay = 300;
int Farbe;
int Highscore;

// Schalter
int Start;
int n;
int Schalter1;
int a;
int Schalter2;
int d;
int Schalter3;
int e;
int Schalter4;
int l;
//LEDs
int Rot = 11;
int Blau = 3;
int Gruen = 4;
int Gelb = 7;


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C Lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  // Random Reihenfolge
  randomSeed(analogRead(A1));
  // LCD initiieren
  Lcd.init();
  Lcd.backlight();
  // Pins konfigurieren und festlegen
  pinMode(9, INPUT_PULLUP);   //Start/Reset Schalter
  pinMode(10, INPUT_PULLUP);  //Schalter 1
  pinMode(11, INPUT_PULLUP);  //Schalter 2
  pinMode(12, INPUT_PULLUP);  //Schalter 3
  pinMode(13, INPUT_PULLUP);  //Schalter 4
  pinMode(2, OUTPUT);         //Lämpchen 1(rot)
  pinMode(3, OUTPUT);         //Lämpchen 2(blau)
  pinMode(4, OUTPUT);         //Lämpchen 3(grün)
  pinMode(5, OUTPUT);         //Lämpchen 4(gelb)
  //Pin Schalter zuweisen
  Start = digitalRead(9);
  Schalter1 = digitalRead(10);
  Schalter2 = digitalRead(11);
  Schalter3 = digitalRead(12);
  Schalter4 = digitalRead(13);
  //Pin LEDs zuweisen
  Rot = digitalRead(2);
  Blau = digitalRead(3);
  Gruen = digitalRead(4);
  Gelb = digitalRead(5);
}

void loop() {
  Splashscreen();
}

void LEDsAus() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void SpielStart() {
  Start = digitalRead(9);
  if (Start == 0) {
    START();
  }
}

void START() {
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print("-----START------");
  delay(1000);
  Lcd.clear();
  Lcd.setCursor(4, 0);
  Lcd.print("Runde:");
  SimonSays();
}


void SimonSays() {
  for (Runde = 1; Runde < 501; Runde++) {
    Lcd.setCursor(10, 0);
    Lcd.print(Runde);
    for (int Wiederholung = 1; Runde > Wiederholung; Wiederholung++) {
      digitalWrite(Reihenfolge[Wiederholung], HIGH);
      delay(400);
      LEDsAus();
      delay(500);
    }
    Farbe = random(2, 6);
    Reihenfolge[Runde] = Farbe;
    digitalWrite(Farbe, HIGH);
    delay(500);
    LEDsAus();
    for (int Wiederholung = 1; Runde >= Wiederholung; Wiederholung++) {
      int Gedrueckt = Abfrage();
      Serial.println(Gedrueckt);
      if (Reihenfolge[Wiederholung] == Gedrueckt) {
        digitalWrite(Gedrueckt, HIGH);
        delay(200);
        LEDsAus();
        delay(200);
      }

      else {
        Lcd.clear();
        Lcd.setCursor(0, 0);
        Lcd.print("Game");
        delay(400);
        Lcd.setCursor(5, 0);
        Lcd.print("Over");
        if (Highscore < Runde - 1) {
          Highscore = Runde - 1;
        }
        delay(400);
        Lcd.setCursor(0, 1);
        Lcd.print("Highscore:");
        Lcd.setCursor(10, 1);
        Lcd.print(Highscore);
        delay(5000);
        Splashscreen();
        return;
      }
    }

    delay(1000);
  }
  Lcd.clear();
  Lcd.setCursor(1, 0);
  Lcd.print("Congratulations");
  Lcd.setCursor(4, 1);
  Lcd.print("You won!");
  delay(10000);
  Splashscreen();
}

int Abfrage() {
  while (1 == 1) {
    Schalter1 = digitalRead(10);
    Schalter2 = digitalRead(11);
    Schalter3 = digitalRead(12);
    Schalter4 = digitalRead(13);

    if (Schalter1 == 0) {
      delay(100);
      while (digitalRead(10) == 0);
      return 2;
    }
    if (Schalter2 == 0) {
      delay(100);
      while (digitalRead(11) == 0);
      return 3;
    }
    if (Schalter3 == 0) {
      delay(100);
      while (digitalRead(12) == 0);
      return 4;
    }
    if (Schalter4 == 0) {
      delay(100);
      while (digitalRead(13) == 0);
      return 5;
    }
  }
}

void Splashscreen() {  //Display-Animation bis Start/Reset Knopf gedrückt wird
  Lcd.clear();
  Lcd.setCursor(3, 0);
  Lcd.print("S");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(4, 0);
  Lcd.print("i");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(5, 0);
  Lcd.print("m");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(6, 0);
  Lcd.print("o");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(7, 0);
  Lcd.print("n");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(9, 0);
  Lcd.print("S");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(10, 0);
  Lcd.print("a");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(11, 0);
  Lcd.print("y");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(12, 0);
  Lcd.print("s");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(0, 1);
  Lcd.print(">");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(1, 1);
  Lcd.print(">");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(2, 1);
  Lcd.print("Press");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(8, 1);
  Lcd.print("Start");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(13, 1);
  Lcd.print("<");
  SpielStart();
  delay(Splashdelay);
  Lcd.setCursor(14, 1);
  Lcd.print("<");
  SpielStart();
  delay(Splashdelay);
  Lcd.clear();
  delay(Splashdelay);
  Lcd.setCursor(3, 0);
  Lcd.print("Simon Says");
  SpielStart();
  Lcd.setCursor(0, 1);
  Lcd.print(">>Press Start<<");
  Lcd.clear();
  SpielStart();
  delay(250);
  Lcd.setCursor(3, 0);
  Lcd.print("Simon Says");
  SpielStart();
  Lcd.setCursor(0, 1);
  Lcd.print(">>Press Start<<");
  SpielStart();
  delay(500);
  Lcd.clear();
  delay(500);
  SpielStart();
  Lcd.setCursor(3, 0);
  Lcd.print("Simon Says");
  Lcd.setCursor(0, 1);
  SpielStart();
  Lcd.print(">>Press Start<<");
  delay(500);
}

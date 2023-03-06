#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int redLedPin = 13;
const int greenLedPin = 8;
const int button = 3;

int buttonState = 0;
long duration;
int distance;
int safetyDistance;
int doorOpened = 0; 

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {

  lcd.init();
  lcd.clear();
  lcd.print("HOME SECURITY");
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(button, INPUT);
  doorOpened = 0;
}


void loop() {

  doorOpened = doorOpened + 1;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  buttonState = digitalRead(button);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  safetyDistance = distance;
    
  if (safetyDistance >= 10){
    doorOpened = 0;
    digitalWrite(buzzer, HIGH);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  }
  else{
    digitalWrite(buzzer, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }

  if(buttonState == HIGH){
    if (safetyDistance >= 10){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Door is open ");
    }
    else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Door was opened ");
    lcd.setCursor(0,1);
    lcd.print(doorOpened);
    lcd.print(" seconds ago");
    }
    delay(1000);
  } 

  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm      ");
    delay(250);
  }
}

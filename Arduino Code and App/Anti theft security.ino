#include<SoftwareSerial.h>
#include<Servo.h>
#include<LiquidCrystal.h>

Servo servo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int led = 13;
int buzzer = 6;
int pin = 7;
int ldr = A0;
int bluetoothTx = 10;
int bluetoothRx = 9;

int Contrast = 75;
int value = 0;
int pirState = LOW;
int right = 123;
int lighton = 2;
int lightoff = 9;
int ldron = 3;
int ldroff = 8;
int on = 1;
int off = 0;
int number = 0;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{


  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  pinMode(pin, INPUT);
  servo.attach(8);
  servo.write(0);
  delay(2000);
  Serial.begin(9600);
  bluetooth.begin(9600);

  /*lcd.clear();
  analogWrite(6, Contrast);
  lcd.begin(16, 2);*/

}

void loop() {




  if (bluetooth.available() > 0)
  {

    number = bluetooth.read();
    Serial.println(number);


    if (number == right)
    {
      servo.write(90);
      delay(4000);
      /*lcd.setCursor(0, 0);
      lcd.print("Door-Unlocked");
      lcd.setCursor(0, 1);
      lcd.print("Welcome");
      delay(5000);
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Prankishor is");
      lcd.setCursor(0, 1);
      lcd.print("King");
      delay(5000);
      lcd.clear();*/
      servo.write(0);
      Serial.println("Unlocked");


    }
    else if (number == on)
    {
      while (number == on)
      {
        value = digitalRead(pin);
        if (value == HIGH) {
          bluetooth.write("1");
          digitalWrite(led, HIGH);
          tone(buzzer, 450);
          delay(5000);
          
          noTone(buzzer);
          delay(500);

          if (pirState == LOW) {
            Serial.println("Motion Dectected");
            pirState = HIGH;

          }

        }
        else {
          digitalWrite(led, LOW);
          noTone(buzzer);
          if (pirState == HIGH) {
            Serial.println("Motion Ended");

          }
        }
      }
    }
    else if (number == off)
    {
      //TURN OFF PIR SEnsor
      digitalWrite(led, LOW);
    }
    else if (number == lighton)
    {
      digitalWrite(led, HIGH);
    }
    else if (number == lightoff)
    {
      digitalWrite(led, LOW);
    }
    else if (number == ldron)
    {
      //ldron


      while (number == ldron)
      {
        int ldrStatus = analogRead(ldr);
        if (ldrStatus <= 800) {
          digitalWrite(led, LOW);
          Serial.println("Led is off cause its daytime");
          break;
        }
        else {
          digitalWrite(led, HIGH);
          Serial.println("led is on cause its dark");
        }
      }
    }
    else if (number == ldroff)
    {
      //ldr off
      digitalWrite(led, LOW);
    }
    else
    {
      Serial.println("Invalid");
    }

  }
}

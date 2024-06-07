#include <Servo.h>
#include <SoftwareSerial.h>
Servo myservo;
int pos = 0;
boolean fire = false;
#define Left A0
#define Right A2
#define Forward A1
#define RM1 6
#define RM2 7
#define LM1 10
#define LM2 11
#define pump 5
char val;
void setup() {
    pinMode(Left, INPUT);
    pinMode(Right, INPUT);
    pinMode(Forward, INPUT);
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
    myservo.attach(3);
    myservo.write(90);
    Serial.begin(9600);
}
void put_off_fire() {
    delay(500);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    digitalWrite(pump, HIGH);
    delay(500);
    for (pos = 50; pos <= 130; pos += 1) {
        myservo.write(pos);
        delay(30);
    }
    for (pos = 130; pos >= 50; pos -= 1) {
        myservo.write(pos);
        delay(30);
    }
    digitalWrite(pump, LOW);
    myservo.write(90);
    fire = false;
}
void loop() {  
    if (Serial.available()) {
        while (Serial.available() > 0) {
            val = Serial.read();
            Serial.println(val);
        }
        if (val == 'f') 
        {
            Serial.println("forward");
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, LOW);
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
            delay(1500);
        } else if (val == 'l') {
            Serial.println("ledt");
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, HIGH);
            Serial.println("l completed");
            delay(1000);
        } else if (val == 'r') {
            {
                digitalWrite(RM1, HIGH);
                digitalWrite(RM2, HIGH);
                digitalWrite(LM1, HIGH);
                digitalWrite(LM2, LOW);
                delay(1000);
            }
        } else if (val == 's') {
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, HIGH);
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, HIGH);
        }
        else if (val == 'b')  
        {
            digitalWrite(LM1, LOW);
            digitalWrite(LM2, HIGH);
            digitalWrite(RM1, LOW);
            digitalWrite(RM2, HIGH);
            delay(1000);
        } else if (val == 'p') {
            digitalWrite(pump, HIGH);
            delay(500);
            for (pos = 50; pos <= 130; pos += 1) {
                myservo.write(pos);
                delay(30);
            }
            for (pos = 130; pos >= 50; pos -= 1) {
                myservo.write(pos);
                delay(30);
            }
            digitalWrite(pump, LOW);

            myservo.write(90);
        }
    } else if (!Serial.available()) {
        myservo.write(90);
        if (digitalRead(Left) == 1 && digitalRead(Right) == 1 &&
                digitalRead(Forward) == 1) {
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, HIGH);
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, HIGH);
        }
        else if (digitalRead(Forward) == 0) {
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, LOW);
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
            fire = true;
        }
        else if (digitalRead(Left) == 0) {
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, HIGH);
        }
        else if (digitalRead(Right) == 0) {
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, HIGH);
            digitalWrite(LM1, HIGH);
            digitalWrite(LM2, LOW);
        }
        delay(500);
        while (fire == true) {
            put_off_fire();
        }
    }
}

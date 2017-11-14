/*
SWITCHER v1.1.0

Turns light switch on and off

Frank Cusano
November 1, 2016
*/

//#define BLYNK_DEBUG // Uncomment this to see debug prints
#define BLYNK_PRINT Serial
#include "blynk/blynk.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "c1887d280b9141259ed91fe807d5d462";

Servo myservo;       // create servo object
int servoPin = D0;   // pin connected to servo
int pos = 0;         // initial position of servo

void setup(){
    Serial.begin(9600);     // begin serial communication with baud rate of 9600
    delay(5000);            // allow board to settle
    Blynk.begin(auth);      // begin BLYNK application using my token
    RGB.control(true);
    myservo.attach(servoPin,700,2650);
}

void loop(){
    Blynk.run(); 
}

// turns light on
void lightsOn(){
    myservo.write(180);
    delay(1000);
    myservo.write(95);
    delay(400);
    digitalWrite(servoPin, LOW);
    delay(10);
    myservo.attach(servoPin,700,2650);
}

// turns light off
void lightsOff(){
    myservo.write(0);
    delay(1000);
    myservo.write(85);
    delay(400);
    digitalWrite(servoPin, LOW);
    delay(10);
    myservo.attach(servoPin,700,2650);
}

void flashRGB(int light){
    if (light == 1){
        for (int x = 0; x < 3; x++){
            RGB.color(0, 0, 255);
            delay(90);
            RGB.color(0, 0, 0);
            delay(90);
        }
    }
    else if (light == 0){
        for (int x = 0; x < 3; x++){
            RGB.color(255, 0, 0);
            delay(90);
            RGB.color(0, 0, 0);
            delay(90);
        }
    }
}

// reads from BLYNK app whether or not the switch is on or off
BLYNK_WRITE(V4){
    if (param.asInt() == 1){
        Blynk.setProperty(V4, "color", "#04C0F8");
        lightsOn();
        flashRGB(1);
    }
    if (param.asInt() == 0){
        Blynk.setProperty(V4, "color", "#D3435C");
        lightsOff();
        flashRGB(0);
    }
}
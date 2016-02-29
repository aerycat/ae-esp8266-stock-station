#include "LedConctrol.h"

// get current color
int LedConctrol::getCurrentColor(int stockStatus) {  
    if(stockStatus > 0){
        color = led_red;
    }else if(stockStatus < 0){
        color = led_green;
    }else if(stockStatus == 0){
        color = led_blue;
    }
    return color;
}

// get current blink frequency
float LedConctrol::getCurrentBlink(int stockStatus) {
    int range = abs(stockStatus);
    if(range == 1){
        blink = 0;
    }else if(range == 2){
        blink = 0.5;
    }else if(range == 3){
        blink = 0.05;
    }
    return blink;
}

// initialization
void LedConctrol::initialize() {
    pinMode(led_red, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_blue, OUTPUT);
    digitalWrite(led_red, 0);
    digitalWrite(led_green, 0);
    digitalWrite(led_blue, 0);
    Serial.println("Initialized");
}

// change color
void LedConctrol::colorAction(int color){
    digitalWrite(led_red, 0);
    digitalWrite(led_green, 0);
    digitalWrite(led_blue, 0);
    digitalWrite(color, 1);
    Serial.print("Color change to: ");
    Serial.println(color);
}

// change blink frequency
void LedConctrol::blinkAction(){
    int ledStatus = digitalRead(color);
    digitalWrite(color, !ledStatus); 
}


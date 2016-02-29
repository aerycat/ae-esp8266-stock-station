#include <Arduino.h>

class LedConctrol {
  private:
    int color;
    float blink = 0;
    // Set LED color gpio ID
    // gpio D1 is 5, gpio D2 is 4, gpio D3 is 0
    const int led_red = 0;
    const int led_green = 4;
    const int led_blue = 5;
    
  public:
    int getCurrentColor(int stockStatus);
    float getCurrentBlink(int stockStatus);
    void initialize();
    void colorAction(int color);
    void blinkAction();
};
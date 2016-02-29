#include <Ticker.h>
#include <ESP8266WiFi.h>
#include "StockClinet.h"
#include "LedConctrol.h"

StockClinet stock;
LedConctrol led;
Ticker stockUpdateTicker;
Ticker ledBlinkTicker;


// your network SSID (name)
char ssid[] = "<SSID>";
// your network password
char pass[] = "<PASSWORD>";

// initializing the system status
int gStatus = 99;
// update count <for debug>
int updateCount = 0;
// update frequency (second)
int updateFreq = 5;

// ticker trigger
bool readyForStockUpdate = true;
bool readyForledBlink = false;

// temporary variable
int tmp_stock_status;
int tmp_led_color;
float tmp_led_blink;

// ticker callback
void stockUpdateTickerCallback() {
  readyForStockUpdate = true;
}
void ledBlinkTickerCallback() {
  led.blinkAction();
}


/* main function */
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  
  led.initialize();
  
  // start connecting to WiFi network
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // update the stock data
  stockUpdateTicker.attach(updateFreq, stockUpdateTickerCallback);
}


void loop() {
  if (readyForStockUpdate) {
    readyForStockUpdate = false;
    
    // print the log <for debug>
    if(updateCount < 32000){ updateCount++; };
    Serial.print("Update count: ");
    Serial.println(updateCount++);
    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());
    
    // change LED status
    tmp_stock_status = stock.updateStockData();
    if (gStatus != tmp_stock_status) {
      gStatus = tmp_stock_status;
      tmp_led_color = led.getCurrentColor(tmp_stock_status);
      tmp_led_blink = led.getCurrentBlink(tmp_stock_status);
      if (tmp_led_blink == 0) {
        ledBlinkTicker.detach();
        led.colorAction(tmp_led_color);
      } else {
        led.colorAction(tmp_led_color);
        ledBlinkTicker.attach(tmp_led_blink, ledBlinkTickerCallback);
      }
    }
  }
}




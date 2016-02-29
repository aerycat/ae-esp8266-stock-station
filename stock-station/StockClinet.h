#include <Arduino.h>
#include <ESP8266WiFi.h>

class StockClinet {
  private:
    // this example using Sina(www.sina.com) stock api, which returned a String result
    // sh000001 (SSE Composite Index)
    const int httpPort = 80;
    const char *httpHost = "hq.sinajs.cn";
    String query = "/list=sh000001";
    String httpHost_str = httpHost;
    
    int status = 0;
    float todayStart, yesterdayEnd, current, percentage;
    
  public:
    int updateStockData();
    void getKey(String line);
    
    int getStatus();
    float getTodayStart();
    float getYesterdayEnd();
    float getCurrent();
    float getPercentage();
};

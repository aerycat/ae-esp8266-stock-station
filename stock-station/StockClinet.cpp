#include "StockClinet.h"

// create a http request
int StockClinet::updateStockData() {
  WiFiClient client;
  if (!client.connect(httpHost, httpPort)) {
    Serial.println("Connection failed");
    return status;
  }
  
  Serial.println("Connected to: " + httpHost_str + ':' + httpPort);

  client.print("GET " + query);
  client.println(" HTTP/1.1\r\n");
  client.println("Host: localhost\r\n");
  client.println("Connection: close\r\n");
  client.println();
  
  int tryCount = 0;
  //   wait for the result
  while (!client.available() && tryCount < 5) {
    delay(100);
    tryCount++;
  }

  while (client.available()) {
    getKey(client.readStringUntil('\n'));
  }
  
  Serial.println();
  Serial.println("Closing connection");
  Serial.println();
  return status;
}

// parse the string of result
void StockClinet::getKey(String line) {
    Serial.print("Respone data: ");
    Serial.println(line);
    if (line.indexOf("var") != -1) {
        char *cstr = new char[line.length() + 1];
        strcpy(cstr, line.c_str());
        char *token = strtok(cstr, ",");
        for(int readKeyPosition=1; readKeyPosition<4; readKeyPosition++ ){
            token = strtok(NULL, ",");
            if(readKeyPosition == 1){
                todayStart = atof(token);
            }else if(readKeyPosition == 2){
                yesterdayEnd = atof(token);
            }else if(readKeyPosition == 3){
                current = atof(token);
            }
        }
        if(yesterdayEnd != 0 && current !=0){
            percentage = (current - yesterdayEnd)/yesterdayEnd*100;
            Serial.print("Percentage: ");
            Serial.println(percentage);
        }
        if(percentage != NULL) {
            if(percentage == 0){
                status = 0;
            }else if(percentage > 0 && percentage < 2){
                status = 1;
            }else if(percentage >= 2 && percentage < 4){
                status = 2;
            }else if(percentage >=4 ){
                status = 3;
            }else if(percentage < 0 && percentage > -2){
                status = -1;
            }else if(percentage <= -2 && percentage > -4){
                status = -2;
            }else if(percentage <= -4){
                status = -3;
            }
        }
        delete [] cstr;
    }
}



// gets the internal variables <for debug>
float StockClinet::getTodayStart() {
  return todayStart;
}
float StockClinet::getYesterdayEnd() {
  return todayStart;
}
float StockClinet::getCurrent() {
  return current;
}
float StockClinet::getPercentage() {
  return percentage;
}
int StockClinet::getStatus() {
  return status;
}


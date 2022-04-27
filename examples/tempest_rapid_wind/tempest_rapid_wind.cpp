/* 
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2022  Lincoln Lavoie <lincoln.lavoie@gmail.com> 
 */

#include <Arduino.h>
#include <WiFi.h>
#include <wf.h>

const char SSID[] = "YourSSID";
const char PASS[] = "YourPassword";

// Create the WeatherFlow Receiver Object
// This also sets the units of the object at create time.
WeatherFlow WF(Imperial);

void setup(){

    Serial.begin(9600);

    // Connect to the local Wi-Fi network.
    Serial.printf("Connecting to Wi-Fi SSID: %s\r\n", SSID);
    WiFi.begin(SSID, PASS);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    // Begin listing for UDP WeatherFlow API packets
    WF.Begin();
}

void loop(){
    if( WF.ReceiveLoop() ){
      
        // Check for Wind data
        if( WF.RapidWind().Valid() ){
            Serial.printf("\r\n------------------------\r\nValid Rapid Wind data:\r\n");
            Serial.printf("\tWind Speed: %f\r\n", WF.RapidWind().WindSpeed());
            Serial.printf("\tWind Direction: %d\r\n", WF.RapidWind().WindDirection());
        }
        
    }
}
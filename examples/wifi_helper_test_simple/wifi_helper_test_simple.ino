#include <ESP8266WiFi.h>
#include <WiFiHelper.h>

const char* ssid     = "NAT.11";
const char* pass     = "guestnetwork";

WiFiHelper wifi(ssid, pass);

void init_wifi()
{
    wifi.on_connecting([](const void* message)
    {
        Serial.println ("connecting..");
    });

    wifi.on_connected([](const void* message)
    {
        Serial.println ((char*)message);
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());        
    });

    wifi.begin();
}

void init_hardware()
{
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println();
}

void setup()
{
    init_hardware();
    init_wifi();
}

void loop()
{
    wifi.loop();
}
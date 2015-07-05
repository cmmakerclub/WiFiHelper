#include "WiFiHelper.h"

WiFiHelper::WiFiHelper(const char* ssid, const char* password)
{
    init_config(ssid, password);

}

void WiFiHelper::init_config(const char* ssid, const char* password)
{
    prev_millis = millis();

    _ssid = String(ssid);
    _password = String(password);
}

void WiFiHelper::begin()
{
    _connect();
}
void WiFiHelper::connect()
{
    _connect();
}


void WiFiHelper::on_disconnected(wifi_callback_t callback)
{
    _user_on_disconnected = callback;
}

void WiFiHelper::on_connected(wifi_callback_t callback)
{
    _user_on_connected = callback;
}

void WiFiHelper::on_connecting(wifi_callback_t callback)
{
    _user_on_connecting = callback;
}

void WiFiHelper::loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        // return WiFi.status();
    }
    else
    {
        INFO_PRINTLN("CLASS: WIFI CONNECTED...");
        if (_user_on_disconnected != NULL)
        {
            _user_on_disconnected("wifi: WiFi disconnected.");
        }

        INFO_PRINTLN("RECONNECTING WIFI...");
        _connect();
    }
}

void WiFiHelper::_connect()
{
    _retries = 0;
    WiFi.begin(_ssid.c_str(), _password.c_str());

    while ((WiFi.status() != WL_CONNECTED))
    {
        if (_user_on_connecting != NULL)
        {
            char buf[3];
            itoa(WiFi.status(), buf, 10);
            _user_on_connecting((void*) buf);
        }

        DEBUG_PRINT(WiFi.status());
        DEBUG_PRINTLN(" ");

        INFO_PRINT(WiFi.status());
        INFO_PRINTLN(" ");
        _retries++;
        delay(500);
    }

    INFO_PRINTLN();
    INFO_PRINTLN("CLASS: WIFI CONNECTED...");

    if (_user_on_connected != NULL)
    {
        _user_on_connected("class: WIFI connected.");
    }

}


WiFiHelper::~WiFiHelper()
{

}

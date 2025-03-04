#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // Copy the incoming data to ensure it's properly null-terminated
    char buffer[250];
    if (len > 249)
        len = 249; // Prevent buffer overflow

    memcpy(buffer, incomingData, len);
    buffer[len] = '\0'; // Ensure null termination

    // Echo the received message back to serial
    Serial.print("Received: ");
    Serial.println(buffer);
}

void setup()
{
    // Initialize Serial
    Serial.begin(115200);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(OnDataRecv);

    Serial.println("ESP-NOW Listener Ready");
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop()
{
    // Nothing to do here - ESP-NOW callbacks do all the work
    delay(10);
}
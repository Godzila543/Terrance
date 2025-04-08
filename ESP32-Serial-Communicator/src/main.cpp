/*
 * ESP32 Relay Script
 * Receives commands from Windows via Serial and relays them to the rover ESP32 using ESP-NOW
 */
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// ESP-NOW peer MAC address (rover ESP32)
// You need to replace this with your rover ESP32's MAC address
uint8_t roverMacAddress[] = {0x10, 0x06, 0x1C, 0x41, 0xAC, 0xB8};

// Create a structured object to hold motor RPM values
typedef struct motor_command
{
  int left_rpm;
  int right_rpm;
} motor_command;

// Create a command instance
motor_command currentCommand;

// Buffer for incoming serial data
String serialBuffer = "";

// Callback function when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  if (status == ESP_NOW_SEND_SUCCESS)
  {
    Serial.println("{\"status\":\"sent_ok\"}");
  }
  else
  {
    Serial.println("{\"status\":\"sent_fail\"}");
  }
}

void setup()
{
  // Initialize Serial for communication with Windows
  Serial.begin(115200);
  while (!Serial)
  {
    ; // Wait for serial port to connect
  }

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("{\"error\":\"ESP-NOW init failed\"}");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);

  // Register the rover ESP32 as a peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, roverMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("{\"error\":\"Failed to add peer\"}");
    return;
  }

  Serial.println("{\"status\":\"ready\"}");
}

void loop()
{
  // Read incoming serial data
  while (Serial.available())
  {
    char c = Serial.read();
    serialBuffer += c;

    // Process messages terminated by newline
    if (c == '\n')
    {
      // Parse the JSON command
      DynamicJsonDocument doc(64);
      DeserializationError error = deserializeJson(doc, serialBuffer);

      if (!error)
      {
        // Extract command values
        currentCommand.left_rpm = doc["left_rpm"];
        currentCommand.right_rpm = doc["right_rpm"];

        // Send command to rover ESP32 via ESP-NOW
        esp_err_t result = esp_now_send(roverMacAddress, (uint8_t *)&currentCommand, sizeof(currentCommand));

        if (result != ESP_OK)
        {
          Serial.println("{\"error\":\"Failed to send command\"}");
        }
      }
      else
      {
        Serial.println("{\"error\":\"JSON parsing failed\"}");
      }

      // Clear the buffer for the next command
      serialBuffer = "";
    }
  }
}
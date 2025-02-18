#include <WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "SEDS";
const char *password = "";

// UDP configuration
WiFiUDP udp;
const unsigned int localUdpPort = 4210; // Local port to listen on
char incomingPacket[255];

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    auto addr = WiFi.localIP(); // Get IP address
    Serial.println(addr.toString());

    // Start UDP
    udp.begin(localUdpPort);
    Serial.print("Listening on UDP port ");
    Serial.println(localUdpPort);
}

void loop()
{
    int packetSize = udp.parsePacket();
    if (packetSize)
    {
        int len = udp.read(incomingPacket, 255);
        if (len > 0)
        {
            incomingPacket[len] = 0;
        }
        Serial.print("Received packet: ");
        Serial.println(incomingPacket);

        // Process command (e.g., update motor RPM, etc.)
    }
    delay(10);
}

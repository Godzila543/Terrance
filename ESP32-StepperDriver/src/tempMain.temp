#include <WiFi.h>
#include <esp_now.h>

// ---------------------------
// Configuration for Stepper Motors
// ---------------------------

// Define the step pin for each motor. Adjust these GPIO pins as needed.
#define MOTOR1_STEP_PIN 13
#define MOTOR2_STEP_PIN 12
#define MOTOR3_STEP_PIN 14
#define MOTOR4_STEP_PIN 27

// Define a unique LEDC PWM channel for each motor.
#define MOTOR1_CHANNEL 0
#define MOTOR2_CHANNEL 1
#define MOTOR3_CHANNEL 2
#define MOTOR4_CHANNEL 3

// Each motor has 200 full steps per revolution and is set to 32 microsteps.
#define STEPS_PER_REV 200
#define MICROSTEPS 32
#define TOTAL_STEPS (STEPS_PER_REV * MICROSTEPS) // 200 * 32 = 6400 pulses/rev

// ---------------------------
// Data Structure for ESP-NOW Message
// ---------------------------
// The structure contains an RPM command for each motor.
typedef struct struct_message
{
    int rpm1;
    int rpm2;
    int rpm3;
    int rpm4;
} struct_message;

// ---------------------------
// Function Prototypes
// ---------------------------
void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len);

// ---------------------------
// Helper Function: Convert RPM to Pulse Frequency
// ---------------------------
// Frequency (Hz) = (RPM * TOTAL_STEPS) / 60
uint32_t rpmToFrequency(int rpm)
{
    // Clamp the rpm value to a safe range (e.g., 0 to 1000 RPM).
    rpm = constrain(rpm, 0, 1000);
    // Compute frequency: (rpm * 6400) / 60.
    uint32_t freq = (uint32_t)rpm * TOTAL_STEPS / 60;
    return freq;
}

// ---------------------------
// Setup
// ---------------------------
void setup()
{
    Serial.begin(115200);
    delay(1000);

    // --- Configure LEDC channels for stepper pulse generation ---
    // Use ledcSetup() to initialize each channel.
    // The initial frequency is set very low (1 Hz) and will be updated when a command is received.
    // Using ledcWriteTone() later lets us change the frequency on the fly.
    ledcSetup(MOTOR1_CHANNEL, 1, 8);
    ledcAttachPin(MOTOR1_STEP_PIN, MOTOR1_CHANNEL);

    ledcSetup(MOTOR2_CHANNEL, 1, 8);
    ledcAttachPin(MOTOR2_STEP_PIN, MOTOR2_CHANNEL);

    ledcSetup(MOTOR3_CHANNEL, 1, 8);
    ledcAttachPin(MOTOR3_STEP_PIN, MOTOR3_CHANNEL);

    ledcSetup(MOTOR4_CHANNEL, 1, 8);
    ledcAttachPin(MOTOR4_STEP_PIN, MOTOR4_CHANNEL);

    // --- Initialize Wi-Fi in Station Mode (required for ESP‑NOW) ---
    WiFi.mode(WIFI_STA);
    Serial.print("ESP32 MAC Address: ");
    Serial.println(WiFi.macAddress());

    // --- Initialize ESP‑NOW ---
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP‑NOW");
        while (true)
        {
            delay(1000); // Halt if ESP‑NOW initialization fails
        }
    }
    // Register the receive callback function.
    esp_now_register_recv_cb(onDataRecv);

    Serial.println("ESP‑NOW initialized. Waiting for RPM commands for stepper motors...");
}

// ---------------------------
// Main Loop
// ---------------------------
void loop()
{
    // The hardware PWM generates step pulses.
    // Nothing is required in the loop; new RPM commands are handled in the ESP‑NOW callback.
    delay(100);
}

// ---------------------------
// ESP‑NOW Receive Callback
// ---------------------------
void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len)
{
    // Print sender MAC address.
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac_addr[0], mac_addr[1], mac_addr[2],
             mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print("Received message from: ");
    Serial.println(macStr);

    // Check that the incoming data size matches our structure.
    if (len != sizeof(struct_message))
    {
        Serial.print("Received message of unexpected size: ");
        Serial.println(len);
        return;
    }

    // Copy the incoming data into our message structure.
    struct_message msg;
    memcpy(&msg, data, sizeof(msg));

    // Debug: Print the received RPM values.
    Serial.print("Motor 1 RPM: ");
    Serial.println(msg.rpm1);
    Serial.print("Motor 2 RPM: ");
    Serial.println(msg.rpm2);
    Serial.print("Motor 3 RPM: ");
    Serial.println(msg.rpm3);
    Serial.print("Motor 4 RPM: ");
    Serial.println(msg.rpm4);

    // --- Compute the step pulse frequency for each motor ---
    uint32_t freq1 = rpmToFrequency(msg.rpm1);
    uint32_t freq2 = rpmToFrequency(msg.rpm2);
    uint32_t freq3 = rpmToFrequency(msg.rpm3);
    uint32_t freq4 = rpmToFrequency(msg.rpm4);

    Serial.print("Motor 1 step frequency: ");
    Serial.print(freq1);
    Serial.println(" Hz");
    Serial.print("Motor 2 step frequency: ");
    Serial.print(freq2);
    Serial.println(" Hz");
    Serial.print("Motor 3 step frequency: ");
    Serial.print(freq3);
    Serial.println(" Hz");
    Serial.print("Motor 4 step frequency: ");
    Serial.print(freq4);
    Serial.println(" Hz");

    // --- Update the LEDC PWM output for each motor ---
    // ledcWriteTone() dynamically sets the frequency of the PWM signal.
    // A frequency of 0 disables the output (stops stepping).
    ledcWriteTone(MOTOR1_CHANNEL, freq1);
    ledcWriteTone(MOTOR2_CHANNEL, freq2);
    ledcWriteTone(MOTOR3_CHANNEL, freq3);
    ledcWriteTone(MOTOR4_CHANNEL, freq4);
}

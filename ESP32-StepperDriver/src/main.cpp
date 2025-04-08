/*
 * ESP32 Rover Script with LEDC PWM for stepper control
 * Receives commands via ESP-NOW and controls stepper motors using ESP32's LEDC peripheral
 */
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Define stepper motor connections
// Left motor
#define LEFT_STEP_PIN 14
#define LEFT_DIR_PIN 12

// Right motor
#define RIGHT_STEP_PIN 27
#define RIGHT_DIR_PIN 26

// Define motor parameters
#define STEPS_PER_REV 200   // Steps per revolution (adjust for your motor)
#define MICROSTEPS 16       // Microstepping setting on your driver
#define MAX_FREQUENCY 20000 // Maximum step frequency in Hz

// LEDC configuration
#define LEDC_RESOLUTION 8    // 8-bit resolution (0-255)
#define LEDC_LEFT_CHANNEL 0  // LEDC channel for left motor
#define LEDC_RIGHT_CHANNEL 1 // LEDC channel for right motor

// Create a structured object to hold motor RPM values
typedef struct motor_command
{
    int left_rpm;
    int right_rpm;
} motor_command;

// Status LED (built-in LED on most ESP32 dev boards)
#define STATUS_LED 2
unsigned long lastCommandTime = 0;
unsigned long lastStatusBlink = 0;
bool ledState = false;

// Current motor state
volatile int leftSpeed = 0;  // in Hz
volatile int rightSpeed = 0; // in Hz
bool leftEnabled = false;
bool rightEnabled = false;

// Function to convert RPM to frequency in Hz
int rpmToFrequency(int rpm)
{
    // Calculate steps per second: (RPM / 60) * steps_per_revolution * microsteps
    if (rpm == 0)
        return 0;
    float abs_rpm = abs(rpm);
    return (abs_rpm / 60.0) * STEPS_PER_REV * MICROSTEPS;
}

// Setup motor direction based on RPM sign
void setMotorDirection(int rpm, int dirPin)
{
    digitalWrite(dirPin, rpm >= 0 ? HIGH : LOW);
}

// Configure the LEDC channel for a motor
void setupMotorPWM(uint8_t channel, uint8_t pin)
{
    ledcSetup(channel, 1, LEDC_RESOLUTION); // Start with 1Hz
    ledcAttachPin(pin, channel);
    ledcWrite(channel, 128); // 50% duty cycle (127/255)
}

// Update the LEDC frequency for a motor
void updateMotorSpeed(uint8_t channel, int frequency)
{
    if (frequency > 0)
    {
        ledcSetup(channel, frequency, LEDC_RESOLUTION);
        ledcWrite(channel, 128); // 50% duty cycle
    }
    else
    {
        ledcSetup(channel, 1, LEDC_RESOLUTION); // 1Hz when stopped
        ledcWrite(channel, 0);                  // 0% duty cycle (effectively off)
    }
}

// Callback function when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // Update command time (for watchdog)
    lastCommandTime = millis();

    // Toggle LED to indicate command received
    digitalWrite(STATUS_LED, HIGH);

    if (len == sizeof(motor_command))
    {
        motor_command *command = (motor_command *)incomingData;

        // Set motor directions
        setMotorDirection(command->left_rpm, LEFT_DIR_PIN);
        setMotorDirection(command->right_rpm, RIGHT_DIR_PIN);

        // Convert RPM to frequency
        leftSpeed = rpmToFrequency(command->left_rpm);
        rightSpeed = rpmToFrequency(command->right_rpm);

        // Update motor speeds
        updateMotorSpeed(LEDC_LEFT_CHANNEL, leftSpeed);
        updateMotorSpeed(LEDC_RIGHT_CHANNEL, rightSpeed);

        // Update motor enabled state
        leftEnabled = (leftSpeed > 0);
        rightEnabled = (rightSpeed > 0);
    }

    // Turn off LED after processing
    digitalWrite(STATUS_LED, LOW);
}

void setup()
{
    // Initialize serial for debugging
    Serial.begin(115200);

    // Initialize status LED
    pinMode(STATUS_LED, OUTPUT);
    digitalWrite(STATUS_LED, LOW);

    // Configure motor direction pins
    pinMode(LEFT_DIR_PIN, OUTPUT);
    pinMode(RIGHT_DIR_PIN, OUTPUT);
    digitalWrite(LEFT_DIR_PIN, HIGH);
    digitalWrite(RIGHT_DIR_PIN, HIGH);

    // Setup LEDC channels for stepper motor control
    setupMotorPWM(LEDC_LEFT_CHANNEL, LEFT_STEP_PIN);
    setupMotorPWM(LEDC_RIGHT_CHANNEL, RIGHT_STEP_PIN);

    // Initialize ESP-NOW
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register callback function for incoming data
    esp_now_register_recv_cb(OnDataRecv);

    // Print MAC address (you'll need this for the relay ESP32)
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop()
{
    // Safety check: Stop motors if no command received in last 2 seconds
    if (millis() - lastCommandTime > 2000)
    {
        if (leftEnabled || rightEnabled)
        {
            updateMotorSpeed(LEDC_LEFT_CHANNEL, 0);
            updateMotorSpeed(LEDC_RIGHT_CHANNEL, 0);
            leftEnabled = false;
            rightEnabled = false;
        }

        // Blink LED to indicate connection loss
        if (millis() - lastStatusBlink > 500)
        {
            ledState = !ledState;
            digitalWrite(STATUS_LED, ledState);
            lastStatusBlink = millis();
        }
    }
}
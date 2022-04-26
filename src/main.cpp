#include <Arduino.h>
#include <arduino_secrets.h>
#include <Wifi.h>
#include <PubSubClient.h>

#define PIN_NO_BUTTON 26
#define PIN_NO_LED_RED 14
#define PIN_NO_LED_GREEN 22
#define PIN_NO_BUZZER 33

WiFiClient espClient;
PubSubClient client(espClient);

volatile bool buttonState;

void buttonClicked() {
    buttonState = digitalRead(PIN_NO_BUTTON);
}

void writeForX(int pin, int milliseconds) {
    digitalWrite(pin, 1);
    delay(milliseconds);
    digitalWrite(pin, 0);
}

void writeForOneSecond(int pin) {
    writeForX(pin, 1000);
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();

    if (strcmp(topic, "led") == 0) {
        writeForOneSecond(PIN_NO_LED_RED);
        writeForOneSecond(PIN_NO_LED_GREEN);
    } else if (strcmp(topic, "led_red") == 0) {
        writeForOneSecond(PIN_NO_LED_RED);
    } else if (strcmp(topic, "led_green") == 0) {
        writeForOneSecond(PIN_NO_LED_GREEN);
    } else if (strcmp(topic, "buzzer") == 0) {
        writeForX(PIN_NO_BUZZER, 100);
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("arduinoClient")) {
            Serial.println("connected");
            client.publish("hello", "world");
            client.subscribe("led");
            client.subscribe("led_red");
            client.subscribe("led_green");
            client.subscribe("buzzer");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

static void wifi_init(void) {
    Serial.begin(115200);
    WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.localIP());
}

static void mqtt_init(void) {
    client.setServer(SECRET_MQTT_SERVER, 1883);
    client.setCallback(callback);
}

void setup() {
    pinMode(PIN_NO_LED_RED, OUTPUT);
    digitalWrite(PIN_NO_LED_RED, LOW);

    pinMode(PIN_NO_LED_GREEN, OUTPUT);
    digitalWrite(PIN_NO_LED_GREEN, LOW);

    pinMode(PIN_NO_BUZZER, OUTPUT);
    digitalWrite(PIN_NO_BUZZER, LOW);

    pinMode(PIN_NO_BUTTON, INPUT);
    attachInterrupt(PIN_NO_BUTTON, buttonClicked, CHANGE);

    wifi_init();

    mqtt_init();
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    if (buttonState) {
        buttonState = false;
        client.publish("button", "pressed");
    }
}

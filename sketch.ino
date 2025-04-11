#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin (not used)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PIR_PIN 5      // PIR sensor output pin
#define BUZZER_PIN 18  // Buzzer pin
#define LED_PIN 23     // LED pin

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_BLACK, 0x3C)) {
    Serial.println("OLED display not found!");
    while (true);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println("Motion Detector Ready");
  display.display();
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    Serial.println("🚨 Motion Detected!");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);

    display.clearDisplay();
    display.setCursor(10, 20);
    display.setTextSize(2);
    display.println("🚨 ALERT!");
    display.setTextSize(1);
    display.println("Motion Detected!");
    display.display();

    delay(2000);  // Alarm duration
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);

    display.clearDisplay();
    display.setCursor(10, 20);
    display.setTextSize(1);
    display.println("Monitoring...");
    display.display();
  }
}


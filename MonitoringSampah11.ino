#define BLYNK_TEMPLATE_ID "TMPL6y1LnhfSy"
#define BLYNK_TEMPLATE_NAME "monitor sampah"
#define BLYNK_AUTH_TOKEN "RNWud9983d3uOfbYGSgZh0piIReNia9k"
#define ALARM_PIN V3

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "satu bangsa";
const char* password = "00000000";

#define SDA_PIN 32
#define SCL_PIN 33
const int trigPin = 26;
const int echoPin = 25;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

LiquidCrystal_I2C lcd(0x27, 16, 2); 

RTC_DS3231 rtc;

int maintenanceSwitch = 0;

void connectToWiFi() {
    Serial.print("Menghubungkan ke Wi-Fi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    int attempt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        attempt++;
        if (attempt > 20) { 
            Serial.println("Gagal terhubung ke Wi-Fi. Restart perangkat.");
            ESP.restart();
        }
    }
    Serial.println("\nWi-Fi terhubung");
}

void connectToBlynk() {
    Serial.println("Menghubungkan ke Blynk...");
    Blynk.config(BLYNK_AUTH_TOKEN);
    if (Blynk.connect()) {
        Serial.println("Blynk terhubung!");
    } else {
        Serial.println("Gagal terhubung ke Blynk. Cek token atau jaringan.");
    }
}

BLYNK_WRITE(V5) {
    maintenanceSwitch = param.asInt();
    Serial.println(maintenanceSwitch);
}

void setup() {
    Serial.begin(9600);  
    delay(1000); 
    Serial.println("Inisialisasi dimulai");

    connectToWiFi();
    connectToBlynk();
    
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!rtc.begin()) {
        Serial.println("RTC tidak ditemukan");
        while (1);
    }
    if (rtc.lostPower()) {
        Serial.println("RTC kehilangan daya, mengatur waktu sekarang...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    if (!display.begin(SSD1306_PAGEADDR, 0x3C)) { 
        Serial.println("OLED tidak ditemukan");
        while (1);
    }
    display.clearDisplay();
    display.display();

    lcd.init();
    lcd.backlight();
    lcd.clear();

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.println("Inisialisasi selesai");
}

void loop() {
    unsigned long previousMillis = 0;
    const long interval = 1000;
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        Blynk.run();
    }

    DateTime now = rtc.now();
    Serial.print("Waktu sekarang: ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;  

    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");

    Blynk.virtualWrite(V1, distance);

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);

    if (distance > 0 && distance < 5) {
        Serial.println("Sampah Penuh");

        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);

        const char* text1 = "SAMPAH";
        const char* text2 = "PENUH";

        int16_t x1, y1;
        uint16_t w, h;

        display.getTextBounds(text1, 0, 0, &x1, &y1, &w, &h);
        int16_t posX1 = (display.width() - w) / 2;
        int16_t posY1 = (display.height() / 2) - h;

        display.getTextBounds(text2, 0, 0, &x1, &y1, &w, &h);
        int16_t posX2 = (display.width() - w) / 2;
        int16_t posY2 = (display.height() / 2) + 5;

        display.setCursor(posX1, posY1);
        display.println(text1);

        display.setCursor(posX2, posY2);
        display.println(text2);

        display.display();

        Blynk.virtualWrite(ALARM_PIN, 1);

        Blynk.virtualWrite(V4, "Sampah Penuh");
    } else {
        display.clearDisplay();
        display.display();

        Blynk.virtualWrite(ALARM_PIN, 0);

        Blynk.virtualWrite(V4, "Tidak Penuh");
    }

    if (now.hour() >= 21 && now.hour() < 22) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MAINTENANCE");
        lcd.setCursor(0, 1);
        lcd.print("17:00-18:00");
    
    } if (maintenanceSwitch == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MAINTENANCE");
    } else {
        lcd.clear(); 
    }

    delay(1000); 
}

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>

#define BLYNK_TEMPLATE_ID "TMPL6qY6lPrUs"
#define BLYNK_TEMPLATE_NAME "UTS"
#define BLYNK_AUTH_TOKEN "sKFnstojSUdkbjcS6Kk-42neN3gjuWC0"

char ssid[] = "2chan";
char pass[] = "12345677";

#define DHTPIN D2            // Pin data DHT11 terhubung ke D2
#define DHTTYPE DHT11        // Tipe sensor DHT11
#define MQ135_A0 A0          // Pin analog MQ-135 terhubung ke A0
#define SERVO_PIN D1         // Pin servo terhubung ke D1

DHT dht(DHTPIN, DHTTYPE);
Servo ventilasiServo;

bool manualControl = false; // Variabel untuk mode manual kontrol servo

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  ventilasiServo.attach(SERVO_PIN);
  ventilasiServo.write(0); // Posisi awal servo (ventilasi tertutup)

  pinMode(MQ135_A0, INPUT);
}

// Fungsi untuk memantau kualitas udara
void monitorAirQuality() {
  if (!manualControl) { // Hanya aktif jika mode manual tidak aktif
    int airQualityValue = analogRead(MQ135_A0);
    Blynk.virtualWrite(V2, airQualityValue);

    Serial.print("Kualitas Udara (ppm): ");
    Serial.println(airQualityValue);

    if (airQualityValue > 300) {
      ventilasiServo.write(90); // Buka ventilasi
      Serial.println("Ventilasi dibuka - Kualitas udara buruk.");
      
      // Mengirim event "overlimit" ke Blynk jika kualitas udara buruk
      Blynk.logEvent("overlimit", "Kualitas udara buruk! PPM melebihi batas.");
      
      // Event untuk membuka ventilasi
      Blynk.logEvent("ventilasi", "Ventilasi terbuka karena kualitas udara.");
    } else {
      ventilasiServo.write(0); // Tutup ventilasi
      Serial.println("Ventilasi ditutup - Kualitas udara baik.");
    }
  }
}

// Fungsi untuk memantau suhu dan kelembapan
void monitorEnvironment() {
  float currentHumidity = dht.readHumidity();
  float currentTemperature = dht.readTemperature();

  Blynk.virtualWrite(V1, currentTemperature); // Virtual Pin V1 untuk Suhu
  Blynk.virtualWrite(V3, currentHumidity);    // Virtual Pin V3 untuk Kelembapan

  Serial.print("Suhu (C): ");
  Serial.println(currentTemperature);
  Serial.print("Kelembapan (%): ");
  Serial.println(currentHumidity);
  Serial.println("-------------------------------");
  delay(1000);
}

// Fungsi Blynk untuk kontrol manual servo melalui Virtual Pin V4
BLYNK_WRITE(V4) {
  int pinValue = param.asInt(); // Membaca nilai dari Virtual Pin V4
  manualControl = (pinValue == 1); // Aktifkan mode manual jika V4 bernilai 1

  if (manualControl) {
    ventilasiServo.write(90); // Buka ventilasi secara manual
    Serial.println("Ventilasi dibuka - Mode manual aktif.");
  } else {
    ventilasiServo.write(0); // Tutup ventilasi secara manual
    Serial.println("Ventilasi ditutup - Mode manual nonaktif.");
  }
}

void loop() {
  Blynk.run();
  monitorAirQuality();
  monitorEnvironment();
}
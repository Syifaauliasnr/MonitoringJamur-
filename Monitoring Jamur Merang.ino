#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11
#define sensorPin 15

int buzzer = 32;
int Sensor_input = 4; 
int bacasensor = 0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(buzzer, OUTPUT);
  pinMode(sensorPin, INPUT);
  dht.begin();
}
void loop() {
  delay(500);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  int sensor_Aout = analogRead(Sensor_input);  /*Analog value read function*/
  Serial.print("Gas Sensor: ");  
  Serial.print(sensor_Aout);   /*Read value printed*/
  Serial.print("\t");
  Serial.print("\t");
  if (sensor_Aout > 350) {    /*if condition with threshold 1800*/
      
    tone(buzzer, 5000); /*LED set HIGH if Gas detected */
  }
  else {
    
    noTone(buzzer);  /*LED set LOW if NO Gas detected */
  }

  bacasensor = digitalRead(sensorPin); // Instruksi untuk membaca nilai digital sensor
  if (bacasensor == LOW) {             // Instruksi untuk mengaktifkan LED Merah jika api terdeteksi
    Serial.print("Digital value: ");   // Tampilkan nilai digital sensor pada serial monitor
    Serial.println(bacasensor);
    Serial.println("Flame detected");  // Menampilkan karakter pada serial monitor
    tone(buzzer, 5000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
     
  } else {
    Serial.print("Digital value: ");     //Instruksi untuk mengaktifkan LED Hijau jika tidak ada api
    Serial.println(bacasensor);
    noTone(buzzer);
    Serial.println("No flame detected"); // Menampilkan karakter pada serial monitor
    delay(1000);
  }
}

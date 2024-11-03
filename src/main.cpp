#include "DHT.h"
#include "lcdLib.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
// Filename : main.cpp lcdlib.h
// Author : Loris Bousselat
// Date : 2024-November-02
// Equipment used : esp32   dht11 captor and lcd display
// Description :
//   display the output of the captor on a LCD display
///////////////////////////////////////////////////////////////////////////

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
const int refreshRate = 4000; // 4 seconds

// the precision of the captor is +/- 5 % for humidity
// and +/- 2 degrees celsius
int humidity;
int temperature;

void readValues()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("start...");
  setLcd();
  dht.begin();
}

void loop()
{
  readValues();
  // Print the humidity and temperature
  Serial.print("Humidity: " + String(humidity) + " %\t");
  Serial.println("Temperature: " + String(temperature) + " C");

  clearLCD();
  printLCD(0, 0, "Humidity:    " + String(humidity) + "%");
  printLCD(1, 0, "Temperature: " + String(temperature) + "C");
  delay(refreshRate);
}

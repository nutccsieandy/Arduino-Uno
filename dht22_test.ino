#include "SPI.h"
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <stdio.h>
//define the constant infromation
#define BLACK    0x0000
#define BLUE     0xF800
#define RED      0x001F
#define GREEN    0x07E0
#define CYAN     0xFFE0
#define MAGENTA  0xF81F
#define YELLOW   0x07FF
#define WHITE    0xFFFF
#define TFT_DC 9
#define TFT_CS 10
#define DHTTYPE DHT22
#define DHTPIN 5
// Monitor and Sensor Setting
DHT dht(DHTPIN,DHTTYPE);
Adafruit_ILI9341 tft= Adafruit_ILI9341(TFT_CS,TFT_DC);
void setup()
{
    Serial.begin(9600);
    tft.begin();
    tft.setCursor(20,60);//set the coordinate
    tft.fillTriangle(10, 110, 20, 100, 30, 110, YELLOW);//draw the pattern
    tft.setCursor(60,40);
    tft.fillCircle(80, 120, 20, RED);
    tft.setCursor(26,120);
    tft.setTextColor(ILI9341_WHITE);//set text color
    tft.setTextSize(3);//set text size
    tft.println("HELLO!");
    tft.setCursor(20,160);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.println("I am Andy.");
    dht.begin();
}
void loop()
{
   // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  tft.setCursor(0,200);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("TEMPERTURE: ");
  tft.print(t);
  tft.println("C");
  tft.print("Humidity: ");
  tft.print(h);
  tft.println("%"); 
  //Warning notification 
  if(t>=60)
  {
     tft.setTextColor(ILI9341_RED); 
     tft.println("Warning:");
     tft.print("TEMPERTURE>=60");
  }
}

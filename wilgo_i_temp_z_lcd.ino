/*
Code for displaing temperature and humidity on screen
*/
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHT11_PIN  13 // ESP32 pin GPIO21 connected to DHT11 sensor

DHT dht11(DHT11_PIN, DHT11);

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  Serial.begin(9600);
  dht11.begin(); // initialize the DHT11 sensor
}

void loop(){
    // HUMIDITY and TEMPERATURE SENSOR
    // read humidity
    float humi  = dht11.readHumidity();
    // read temperature in Celsius
    float tempC = dht11.readTemperature();

    if ( isnan(tempC) || isnan(humi)) {
      Serial.println("Failed to read from DHT11 sensor!");
    } else {
      // set cursor to first column, first row
      //lcd.setCursor(0, 0);
      // print message on Serial and on LCD
      Serial.print("Humidity:");
      Serial.print(humi);
      Serial.print("%");
      lcd.setCursor(0, 0);
      lcd.print("Humidity: ");
      lcd.print(humi);
      lcd.print("%");

      //lcd.setCursor(0, 1);
      Serial.print("Temperature: ");
      Serial.print(tempC);
      Serial.println("°C");
      lcd.setCursor(0, 1); 
      lcd.print("Temp: ");
      lcd.print(tempC);
      lcd.print(" C");
    }
      delay(2000);
}
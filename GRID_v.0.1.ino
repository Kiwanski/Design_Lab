#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHT11_PIN  13 // ESP32 pin GPIO21 connected to DHT11 sensor

DHT dht11(DHT11_PIN, DHT11);

int moisture,sensor_analog;
const int sensor_pin = 34;  /* Soil moisture sensor O/P pin */


// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);
// special singes for LCD
byte heart[] = {B00000,B00000,B01010,B11111,B11111,B01110,B00100,B00000};
byte water_droplet[] = {B00000,B00100,B01110,B01110,B11111,B11111,B01110,B00000};
byte stopnie[] = {B00000,B11100,B10100,B11100,B00000,B00000,B00000,B00000};
byte empty[] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000};

void setup() {
  Serial.begin(115200);
  // initialize LCD
  lcd.init();                      
  lcd.backlight();
  lcd.createChar(0 , heart);
  lcd.createChar(1 , water_droplet);
  lcd.createChar(2 , stopnie);
  lcd.createChar(3 , empty);
  // initialize the DHT11 sensor
  dht11.begin(); 

}

void loop() {
    // AIR HUMIDITY and TEMPERATURE SENSOR
    float humi  = dht11.readHumidity();
    float tempC = dht11.readTemperature();

    // SOIL HUMIDITY SENSOR
    sensor_analog = analogRead(sensor_pin);
    moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );

    if ( isnan(tempC) || isnan(humi)) {
      Serial.println("Failed to read from DHT11 sensor!");
    } else {
      // set cursor to first column, first row
      // print message on Serial and on LCD
        //Serial.print("Humidity:");
        //Serial.print(humi);
        //Serial.print("%");
      lcd.setCursor(0, 0);
      lcd.print("Air");
      lcd.write(1);
      lcd.print("%");
      lcd.print(":");
      lcd.print(humi);
      lcd.setCursor(8, 0);
      lcd.write(3);
        //Serial.print("Temperature: ");
        //Serial.print(tempC);
        //Serial.println("°C");
      lcd.setCursor(9, 0);
      lcd.write(2); 
      lcd.print("C:");
      lcd.print(tempC);

      lcd.setCursor(0, 1); 
      lcd.print("Plant");
      lcd.write(1);
      lcd.print("%");
      lcd.print(":");
      lcd.print(moisture);

    }
      delay(2000);
}
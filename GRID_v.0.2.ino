#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP32Servo.h>
#define DHT11_PIN  13 // ESP32 pin GPIO21 connected to DHT11 sensor

DHT dht11(DHT11_PIN, DHT11);

int moisture,sensor_analog;
const int sensor_pin = 34;  /* Soil moisture sensor O/P pin */
const int relay1 = 14; // Air Fan
const int relay2 = 27; // Water pump
static const int servoPin = 12; //servo pin
Servo servo1; //servo

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
  //initailze relay
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  //initailzie servo
  servo1.attach(servoPin);
}

void loop() {
  //SENSOR READ 

    // AIR HUMIDITY and TEMPERATURE SENSOR READ
    float humi  = dht11.readHumidity();
    float tempC = dht11.readTemperature();

    // SOIL HUMIDITY SENSOR READ
    sensor_analog = analogRead(sensor_pin);
    moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );

  // LCD WRITE / DISPLEY

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

    delay(2000);

    // IF temp to low state
    if (tempC > 17) {
    digitalWrite(relay1, LOW);
    servo1.write(0);
    Serial.println("Went:open; Fan: ON;");

    delay(5000); 
  
    digitalWrite(relay1, HIGH);
    servo1.write(90);
    Serial.println("Went:closed; Fan: OFF;");
    delay(5000);
    }

    // Watering plant
    if (moisture < 80) {
    digitalWrite(relay2, LOW);
    Serial.println("Pump: ON;");

    delay(2000);

    digitalWrite(relay2, HIGH);
    Serial.println("Pump: OFF;");
    delay(20000);
    }
}
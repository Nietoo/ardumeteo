#include <DHT.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 11, 2, 3, 4, 5);

const int VOLTAGE = 5;

const int TMP36_PIN = 0; 
const int DHT_PIN = 12;
const int LDR_PIN = 5;
DHT dht(DHT_PIN, DHT11);

//Icono de termómetro
byte LCD_TEMP[8] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B01110,
};
//Icono de gota
byte LCD_HUMI[8] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110,
};
//Icono de bombilla
byte LCD_BULB[8] = {
  B01110,
  B10001,
  B10001,
  B10101,
  B01110,
  B01110,
  B01110,
  B00100,
};
//Icono del símbolo de grados (º)
byte LCD_DEGR[8] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

int CHAR_TEMP = 0; 
int CHAR_HUMI = 1; 
int CHAR_BULB = 2; 
int CHAR_DEGR = 3; 


void setup(){
  Serial.begin(9600);  
  
  dht.begin();
  
  lcd.createChar(CHAR_TEMP, LCD_TEMP);
  lcd.createChar(CHAR_HUMI, LCD_HUMI);
  lcd.createChar(CHAR_BULB, LCD_BULB);
  lcd.createChar(CHAR_DEGR, LCD_DEGR);
  lcd.begin(16, 2);
  lcd.clear();   
}

float getTemp(int pin){
  float voltage = analogRead(pin) * VOLTAGE /1024.0;
  return (voltage - 0.5) * 100;
}

void loop(){
 int luminosidad = analogRead(LDR_PIN) / 10.24 + 0.5; 
 float tempAnal = getTemp(TMP36_PIN); 
 int tempDig = dht.readTemperature(); 
 int humidity = dht.readHumidity();
 
 lcd.home();  
 lcd.print(" ");
 lcd.write(byte(CHAR_TEMP)); 
 lcd.print(" ");
 if(tempAnal < 10){
  lcd.print("0"); 
 }  
 lcd.print(tempAnal); 
 lcd.write(byte(CHAR_DEGR)); 
 lcd.print("C ");
 if(tempDig < 10){
  lcd.print("0"); 
 } 
 lcd.print(tempDig);
 lcd.write(byte(CHAR_DEGR)); 
 lcd.print("C ");
 
 lcd.setCursor(0, 1);
 lcd.print(" "); 
 lcd.write(byte(CHAR_HUMI));
 lcd.print(" ");
 if(humidity < 10){
  lcd.print("0"); 
 } 
 lcd.print(humidity); 
 lcd.print("%   "); 
 lcd.write(byte(CHAR_BULB));
 lcd.print(" ");
 if(luminosidad < 10){
  lcd.print("0"); 
 }
 lcd.print(luminosidad); 
 lcd.print("%");
 
 lcd.display();
 Serial.println("*****************************");
 Serial.print("Temperatura TMP36: ");
 Serial.println(tempAnal);
 Serial.print("Temperatura DHT11: ");
 Serial.println(tempDig);
 Serial.print("Humedad relativa DHT11: ");
 Serial.println(humidity);
 Serial.print("Luminosidad: ");
 Serial.println(luminosidad); 
 
 delay(1000);
}

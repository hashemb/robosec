#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const byte ROWS = 4; 
const byte COLS = 3; 
char customKey = 0;
#define Password_Length 7

//int signalPin = 12;
int speakerOut = 13;
char Data[Password_Length]; 
char Master[Password_Length] = "123456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
int count = 0;
int count2 = 0;
int count3 = 0;
int MAX_COUNT = 24;
int statePin = LOW;
int sensor = 11;
int state = LOW;             // by default, no motion detected
int val = 0;  



 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

LiquidCrystal_I2C lcd(0x3f, 20, 4); //for new LCD
byte rowPins[ROWS] = {5,6,7,8}; 
byte colPins[COLS] = {2,3,4}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
 Serial.begin(9600);
 pinMode(sensor, INPUT);      
 lcd.init();
  
  
  
}
  
void loop(){

val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
  
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      sensor_detect();
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        lcd.noBacklight();
        state = LOW;       // update variable state to LOW
    }
  }



    
}
  


void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}


 void sensor_detect()//This function is called whenever someone is around
 {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello!");
  delay(1000);
  lcd.clear();
  lcd.print("Enter Password:");
  while(digitalRead(sensor)== HIGH)
   {
    customKey = customKeypad.getKey();
   if (customKey){
    
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print("*"); 
    data_count++; 
    }

  if(data_count == Password_Length-1){

    lcd.clear();

    if(!strcmp(Data, Master)){
      
      lcd.print("Correct");
      tone( 13, 5000, 100);
      delay(160);
      tone( 13, 5000, 50);             
      delay(5000);
      }
    else{
      lcd.print("Incorrect");
       siren();
       siren();
       siren();
      delay(1000);
      }
      
    
    lcd.clear();
    clearData();  
  }

   
   
   }

  
}

 
 
  void siren()//This function will make the alarm sound using the piezo buzzer
{
  
for(int hz = 440; hz < 1000; hz++){
    tone(13, hz, 50);
    delay(5);
  }
  noTone(13);

}

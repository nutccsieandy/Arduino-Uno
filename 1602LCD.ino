#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
byte k1[8]={0x04,0x04,0x04,0x07,0x04,0x04,0x04,0x1F,};
LiquidCrystal_PCF8574 lcd(0x27); 
// set the LCD address to 0x27
int value;
void setup()
{
  lcd.begin(16, 2); // initialize the lcd  
  lcd.createChar(0,k1);
  pinMode(A1, INPUT);
} // setup()
void loop(){   
    value=analogRead(A1);
    lcd.setBacklight(value);
    lcd.home();
    lcd.setCursor(0, 0);
    lcd.print("ANDY-CHEN");
    lcd.setCursor(0, 1);
    delay(200);
    lcd.write(byte(0));
    lcd.setCursor(8,1);
    for(int i=0;i<8;i++)
    {
      lcd.scrollDisplayLeft();
      delay(200);
    }
    for(int i=0;i<15;i+=2)
    {
      for(int j=0;j<(15-i);j++)
      {
        lcd.scrollDisplayRight();
        delay(200);
      }
       for(int j=0;j<(15-i-1);j++)
      {
        lcd.scrollDisplayLeft();
        delay(200);
      }     
    }
    lcd.clear();
    delay(1000);
} // loop()
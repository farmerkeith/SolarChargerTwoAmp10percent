// LCD object for 1602 LCD (2 rows of 16 characters each)
// screen layouts
// startup screen
//character 0   1  2   3  4  5   6  7  8      9  10    11 12  13 14 15 
//row 1    "Charger301"                          clear =  =   =  =  = 
//row 2    clear

// run screen off state
//character 0   1  2   3  4  5   6  7  8      9  10 11  12  13 14 15 
//row 1    'P' '=' Vpp = '.' Vpp =  =  Space 'A'  = Ipp '.' Ipp =  =
//row 2    'B' '=' Vbb = '.' Vbb =  =  Space "pwm="         "off" 

// run screen start state
//character 0   1  2   3  4  5   6  7     8      9  10    11   12  13     14    15 
//row 1    'P' '=' Vpp = '.' Vpp =  =     Space 'A' =     Ipp '.'  Ipp    =      =
//row 2    'B' '=' Vbb = '.' Vbb =  Space D9     D9 space D10  D10 space  Period = 

int x=2;

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack

class lcd1602 {
  public:
  lcd1602 (); // constructor
  void begin();
//  void setBacklightPin(uint8_t pin){lcd.setBacklightPin(pin,0);}
//  void setBacklightPin(int pin, byte polarity){lcd.setBacklightPin(pin, polarity);}
//  void setBacklight (bool b){lcd.setBacklight(b);}
//  void clear(){lcd.clear();}
//  void home(){lcd.home();}
//  void print(float f){lcd.print(f);}
//  void print(char[] c){lcd.print(c);}
//  void print(String s){lcd.print(s);}
//  void setCursor(int col, int row){lcd.setCursor(col,row);}
  void solarVoltage(float value);
  void solarCurrent(float value);
  void batteryVoltage(float value);
  void pwm1(float INvalue,float SDvalue, float PWMvalue); // dcm
  void pwm1(float INvalue, float PWMvalue); // ccm
  void pwm1(String value); // off state
    
} lcd1602;

// constructor
lcd1602::lcd1602() {
}

// project-specific functions

void lcd1602::begin(){
  lcd.begin(16, 2);
  lcd.setBacklightPin(3,0);
  lcd.setBacklight(0);
  lcd.clear();
  lcd.home() ;
  lcd.print("Charger301");
  pwm1("off");
}

void lcd1602::solarVoltage(float value){
  byte decimals = 3;
  if (lcdPwm1) {
    decimals=1;
  }
  lcd.setCursor(0,0);
  lcd.print("P");
  lcd.print(value,decimals);
  lcd.print(' ');
}

void lcd1602::solarCurrent(float value){
  byte startPos=8;
  byte decimals = 3;
  if (lcdPwm1) {
    decimals=1;
    startPos=5;
  }
  lcd.setCursor(startPos,0);
  lcd.print(" A");
  lcd.print(value,decimals);
  lcd.print(' ');
}

void lcd1602::batteryVoltage(float value){
  byte line=1;
  byte startPos=0;
  byte decimals = 3;
  if (lcdPwm1) {
    decimals=1;
    startPos=11;
    line=0;
  }
  lcd.setCursor(startPos,line);
  lcd.print("B");
  lcd.print(value,decimals);
  lcd.print(' ');
}

void lcd1602::pwm1(float INvalue,float SDvalue, float PWMvalue){
  // for dcm
  byte startPos=8;
  byte decimals = 0;
  if (lcdPwm1) {
    startPos=0;
    decimals=2;
  }
  lcd.setCursor(startPos,1);
  lcd.print(INvalue,decimals);
  lcd.print(' ');
  lcd.print(SDvalue,decimals);
  lcd.print(' ');
  lcd.print(PWMvalue,decimals);
  lcd.print(' ');
}

void lcd1602::pwm1(float INvalue, float PWMvalue){ 
  // for ccm
  byte startPos=8;
  byte decimals = 2;
  if (lcdPwm1) {
    startPos=0;
    decimals=4;
  }
  lcd.setCursor(startPos,1);
  lcd.print(INvalue,decimals);
  lcd.print(' ');
  lcd.print(PWMvalue,decimals);
  lcd.print(' ');
}

void lcd1602::pwm1(String value){
  lcd.setCursor(8,1);
  lcd.print("pwm:");
  lcd.print(value);
  lcd.print("  ");
}



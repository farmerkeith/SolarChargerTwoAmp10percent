// Author farmerkeith 18 Jan 2018
// latest update 24 Jan 2018
// this sketch has been written from scratch based on other work by this author.
// Two analog pin A0 and A2 for voltage measuring have resistive dividers attached, 100k/20k
// One analog pin A1 for current measuring has a Hall Effect sensor attached (eg ACS712 5A)
// All measurements use Vcc as reference
// LCD is 1602 via I2C
// PWM uses a state machine to manage charger conditions and outputs PWM to D9 and D10.

#include "ArduinoReadVoltsCurrentBasic.h" // associated tab file
// instantiate objects
readVoltsAmps A0Volts(0,0); // instantiates class as object A0Volts on pin A0, 5V ref
readVoltsAmps A1Amps (1,0); // instantiates class as object A1Amps on pin A1, 5V ref
readVoltsAmps A2Volts(2,0); // instantiates class as object A2Volts on pin A2, 5V ref

#include "LCD1602AB.h"
#include "repeatEvery.h"    // associated tab file
#include "readVoltage.h"    // associated tab file

// test configuration constants
const bool testing = 1;  // 1 for artificial voltage readings; 0 for using actual readings
const bool testingPvModel = 0;  // 
const bool testingBatteryModel = 0;  // activates serial print
const bool testingPwmStartup = 0;  // 
const bool testingPwmCurrentDelta = 0;  // 
const bool testingPwmPower = 0;  // activates serial print
const bool testingPwmCurrent = 0;  // activates serial print
const bool testingPwmVoltage = 1;  // activates serial print


// hardware configuration constants
const byte INpin = 9;    // main PWM output to IN of IR2184
const byte SDpin=10;   // SD/ == Enable pin of IR2184, High, Low or PWM depending on mode

// charger configuration constants
const int startupVoltageMargin = 6000; // millivolts. Initiate PWM if Panel voltage is this much higher than Battery voltage
const int shutDownVoltageMargin = 1000; // millivolts. End PWM if Panel voltage is less than this much higher than Battery voltage
const int minCurrent = 100;    // milliAmps
const int startCurrent=500;    // milliAmps
const int maxStartTime=5000;   // milli seconds
const int minOffTime=5000;     // milli seconds
const int maxCurrent = 2000;   // milliAmps

// battery management constants
const int floatVoltage=12600;  // milliVolts
const int boostVoltage=14200;  // milliVolts
const int boostTimeLimit=3600; // seconds
const int boostTimeReset=3600; // seconds

// voltage and current measurement calibration
const unsigned long a0fullScale = 30604; // mV, Vpp
const unsigned long a1fullScale = 13500; // mA, Ipp
const unsigned long a2fullScale = 30418; // mV, Vbb
const long a1ZeroScale = 512; // adc code, Ipp


#include "pwm.h"                // associated tab file
#include "charger.h"            // associated tab file
#include "testing.h"            // associated tab file


void setup() {
  Serial.begin(115200);
  Serial.println("\n charger 301");

  // set pin D10 to Output, Low 
  pinMode (SDpin, OUTPUT);
  digitalWrite (SDpin, LOW);
  pinMode (INpin , OUTPUT);
  digitalWrite (INpin , LOW);
  // initialise timer object
//  initialize(pwmPeriod);
//  Timer1Fast.initializeFast(pwmPeriod); // set a period of length 30 uS =480 clock cycles

  lcd1602.begin();
 

// configure objects readVoltsAmps
  A0Volts.init(); // initialise object
  // resistive divider is 100K/20K so ratio is 120/20=6. So Full Scale = 5V*6=30V=30,000 mV
  A0Volts.calibrateScale(a0fullScale); // mV full scale: adjust this to get the correct Panel voltage
  A0Volts.calibrateZero(0); // adc* 100 zero offset
    
  A1Amps.init(); // initialise object 
  A1Amps.calibrateAmps(a1fullScale); // mA full scale: adjust this to get the correct Panel current
  A1Amps.calibrateZeroAmps(a1ZeroScale); // adc zero offset
    
  A2Volts.init(); // initialise object
  // resistive divider is 100K/20K so ratio is 120/20=6. So Full Scale = 5V*6=30V=30,000 mV
  A2Volts.calibrateScale(a0fullScale); // mV full scale: adjust this to get the correct Battery voltage
  A2Volts.calibrateZero(0); // adc* 100 zero offset

} // end of setup()

void loop() {
//  repeatEvery(2000, readVoltsAndAmps);
  repeatEvery(10000, countLoops);
//  repeatEvery(1000, chargerRun);
//  repeatEvery(500, unitTestPvModel);
//  repeatEvery(500, unitTestBatteryModel);
//  repeatEvery(500, unitTestPwmStartup);
//  repeatEvery(500, unitTestPwmCurrentDelta);
//  repeatEvery(500, unitTestPwmPower);
//  repeatEvery(500, unitTestPwmCurrent);
  repeatEvery(500, unitTestPwmVoltage);

}



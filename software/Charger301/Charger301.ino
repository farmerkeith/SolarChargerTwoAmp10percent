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


// test printout configuration constants
const bool lcdPwm1 = 0;  // 1 for detailed pwm display
const bool testing = 0;  // 1 for serial printing from charger class while testing
const bool pwm1testing = 0;  // 1 for serial printing from pwm class while testing
const bool testingOneLine=1; // 0 removes line feeds in the same cycle
const bool testingFormatSpacing=1; // 0 removes extra space characters

// test activation constants
const bool testingPvModel = 0;       // 1 activates test
const bool testingBatteryModel = 0;  // 1 activates test
const bool testingPwmStartup = 0;    // 1 activates test
const bool testingPwmCurrentDelta = 0;  // 1 activates test
const bool testingPwmPower = 0;      // 1 activates test
const bool testingPwmCurrent = 0;    // 1 activates test
const bool testingPwmVoltage = 0;    // 1 activates test
const bool unitTestingActive = testingPvModel || testingBatteryModel ||        // continues on next line
             testingPwmStartup || testingPwmCurrentDelta || testingPwmPower || // continues on next line
             testingPwmCurrent || testingPwmVoltage;

// test model behaviour constants
const float socChargeFactor = 0.001; // soc increase per amp of Ibb
const float socDischargeFactor = 0.0001; // soc decrease per cycle
const float pvIlluminationFactor = 0.9; // 0 to 1.00
const float initialSoc = 0.1; // initial battery state of charge


// hardware configuration constants
const byte INpin=9;    // main PWM output to IN of IR2184
const byte SDpin=10;   // SD/ == Enable pin of IR2184. High, Low or PWM depending on mode

// charger configuration constants
// const int startupVoltageMargin = 6000; // millivolts. Initiate PWM if Panel voltage is this much higher than Battery voltage
// const int shutDownVoltageMargin = 1000; // millivolts. End PWM if Panel voltage is less than this much higher than Battery voltage
const int minCurrent = 100;    // milliAmps
const int startCurrent=400;    // milliAmps minimum to start
const int maxStartTime=5000;   // milli seconds
const int minOffTime=5000;     // milli seconds
const int maxCurrent = 5000;   // milliAmps
const int chargerRepeatPeriod = 500; // milliseconds

// battery management constants
const int floatVoltage=12600;  // milliVolts
const int boostVoltage=14200;  // milliVolts
//const int boostTimeLimit=3600; // seconds
const int boostTimeLimit=120; // seconds for testing (2 minutes)
//const int boostTimeReset=3600; // seconds
const int boostTimeReset=120; // seconds for testing (2 minutes)

// voltage and current measurement calibration
  // A0 resistive divider is 100K/20K so ratio is 120/20=6. So Full Scale = 5V*6=30V=30,000 mV
const unsigned long a0fullScale = 30604; // Vpp, mV full scale: adjust this to get the correct Panel voltage
  // A1 reads output of Hall effect sensor ACS712. Sensitivity 185 mV/A so Full Scale = 2.5V/0.185V*1000=13,500 mA
const unsigned long a1fullScale = 13500; // Ipp, mA full scale: adjust this to get the correct Panel current
const long a1ZeroScale = 512; // adc code, Ipp adc zero offset: will be adjusted automatically for zero current
  // A2 resistive divider is 100K/20K so ratio is 120/20=6. So Full Scale = 5V*6=30V=30,000 mV
const unsigned long a2fullScale = 30418; // Vbb, mV full scale: adjust this to get the correct Battery voltage

// include tab files (order is important)
#include "LCD1602AB.h"
#include "repeatEvery.h"    // associated tab file
#include "readVoltage.h"    // associated tab file
#include "pwm.h"                // associated tab file
#include "testModels.h"         // associated tab file
#include "charger.h"            // associated tab file
#include "testing.h"            // associated tab file

void setup() {
  Serial.begin(115200);
  Serial.println("\n charger 301");

  // set pin D10 to Output, Low 
  pinMode (SDpin, OUTPUT);
  digitalWrite (SDpin, LOW);
  // set pin D9 to Output, Low 
  pinMode (INpin , OUTPUT);
  digitalWrite (INpin , LOW);
//  Timer1Fast.initializeFast(20);

  lcd1602.begin();
 

  // configure objects readVoltsAmps
  A0Volts.init(); // initialise object
  A0Volts.calibrateScale(a0fullScale); 
  A0Volts.calibrateZero(0); // adc* 100 zero offset
    
  A1Amps.init(); // initialise object 
  A1Amps.calibrateAmps(a1fullScale); 
  A1Amps.calibrateZeroAmps(a1ZeroScale); // adc zero offset
    
  A2Volts.init(); // initialise object
  A2Volts.calibrateScale(a0fullScale); // 
  A2Volts.calibrateZero(0); // adc* 100 zero offset

} // end of setup()

void loop() {
//  repeatEvery(2000, readVoltsAndAmps);
  repeatEvery(10000, countLoops);
  repeatEvery(chargerRepeatPeriod, chargerRun);
  repeatEvery(5000, unitTestRun);
}



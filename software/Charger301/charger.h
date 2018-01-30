// file charger.h created 17 Jan 2018
// From off state, check for adequate voltage on solar panel, and if so start PWM on D9, D10
// Once on, check that solar panel voltage has not dropped too much, if so stop PWM and disable the IR2184

// libraries
#include "Timer1Fast.h"

class charger {
//  private:
  public:
  const float VppStartMin=16;   // V
  const float VppStartMax=28;   // V
  const float VbbStartMin=11.5; // mV
  const float VbbStartMax=12.8; // mV
  
  enum State {
    off,
    start,
    bulk,
    floatV,
    boost,
    boostFloat,
    currentLimitedFloat,
    currentLimitedBoost
  };
  State currentState=off;
  State lastState=start; // could be any state other than off
  float Vpp=12;
  float Ipp=0;
  float Vbb=12;
  long boostTime=0; // seconds. Time spent in boost state per day
  unsigned long timer = 0;
  public:
  void run();
  private:
  void goToOff(); 
  void goToStart();
  void goToBulk();
  void goToFloatV();
  void goToBoost();
  void goToBoostFloat();
  void goToCurrentLimitedFloat();
  void goToCurrentLimitedBoost();
  void runOff();
  void runStart();
  void runBulk();
  void runFloatV();
  void runBoost();
  void runBoostFloat();
  void runCurrentLimitedFloat();
  void runCurrentLimitedBoost();
  void printState(State currentState);
  void incrementBoostTime();
  public:
  bool unitTest(float Vb, float Vp,float Ip);
} charger;

void chargerRun (bool flag, unsigned long & Time){
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    Serial.print (F("\nPerforming chargerRun function at time "));
    Serial.print ((float)millis()/1000,3);

    charger.run();
    
/*
    Serial.print (" Vpp= ");
    Serial.print(Vpp,3);
    Serial.print (" Ipp= ");
    Serial.print(Ipp,3);
    Serial.print (" Vbb= ");
    Serial.println(Vbb,3);
*/    
  }
  Time = lastTime;
}


void charger::run(){
//  Serial.print("\n line 81 Vpp="); Serial.print(Vpp);
  printState(currentState);
//  Serial.print("\n currentState="); Serial.print(currentState);
//  Serial.print("\n pwm Mode="); Serial.print(pwm1.mode);

  if (testing){
    if (currentState==off) Vpp = pvModel.getVoc(); // only for off state
//    else if (currentState==bulk) Vpp=Vbb*pwm1.Tpe/pwm1.Tp;
    else if (pwm1.mode==2){
      float IppL = (Vpp-Vbb)/pwm1.L*pwm1.Tp*pwm1.Tp/32/pwm1.Tt;
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, pwm1.Tp, pwm1.Tt);
//      Serial.print("\n line 91 Vpp1="); Serial.print(Vpp1);
    } else if (pwm1.mode==3){
      Vpp = Vbb * pwm1.Tt/pwm1.Tp;
//      Serial.print("\n line 94 Vpp1="); Serial.print(Vpp1);
    }
    
//    Serial.print("\n line 98 pwm1.Tt="); Serial.print(pwm1.Tt);
//    Serial.print(" pwm1.Tp="); Serial.print(pwm1.Tp);
//    Serial.print("\n line 100 Vpp="); Serial.print(Vpp);
    Ipp = pvModel.current(Vpp);
    Vbb = battery.voltage(Ipp*Vpp/Vbb);

/*    
    if (currentState==off){
      ++Vpp;  // artificial value for testing
      Vbb=12; // artificial value for testing
    } else{
      Vpp-=0.5; // artificial value for testing
      Vbb=12;   // artificial value for testing
    }
*/    
  } else {
    Vpp = A0Volts.getVolts(); // returns (float) Volts
    Vbb = A2Volts.getVolts(); // returns (float) Volts
    Ipp = A1Amps.getAmps(); // returns (float) Amps
  }
//  Serial.print(F("Ipp="));   Serial.println(Ipp,3);

  switch (currentState){
  case off:
    if(lastState!=off) goToOff();
    else runOff();
  break;
  case start:
    if(lastState!=start) goToStart();
    else runStart();
  break;
  case bulk:
    if(lastState!=bulk) goToBulk();
    else runBulk();
  break;
  case floatV:
    if(lastState!=floatV) goToFloatV();
    else runFloatV();
  break;
  case boost:
//    Serial.print("\n charger Line 135 caseBoost Vpp="); Serial.print(Vpp);
    if(lastState!=boost) goToBoost();
    else runBoost();
  break;
  case boostFloat:
    if(lastState!=boostFloat) goToBoostFloat();
    else runBoostFloat();
  break;
  case currentLimitedFloat:
    if(lastState!=currentLimitedFloat) goToCurrentLimitedFloat();
    else runCurrentLimitedFloat();
  break;
  case currentLimitedBoost:
    if(lastState!=currentLimitedBoost) goToCurrentLimitedBoost();
    else runCurrentLimitedBoost();
  break;
  default:
  break;
  }
  lcd1602.solarVoltage(Vpp);
  lcd1602.solarCurrent(Ipp);
  lcd1602.batteryVoltage(Vbb);
}

void charger::goToOff(){
  if (testing) Serial.println(F("\ngoToOff"));
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=off;
  timer = millis();
  Timer1Fast.disablePwm(SDpin);
  digitalWrite (SDpin, LOW);
  Timer1Fast.disablePwm(INpin);
  lcd1602.pwm1("off");
}

void charger::runOff(){
//  Serial.print(F("runOff, millis="));Serial.print(millis());
//  Serial.print(F(" timer="));Serial.print(timer);
//  Serial.print(F(" minOffTime="));Serial.println(minOffTime);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if ((long)(millis()-timer)<minOffTime) {
//    currentState=off;
    long Ipp1=A1Amps.getVoltCode(20);
    A1Amps.calibrateZeroAmps(Ipp1/100);
//    Serial.print(F("Calibration")); Serial.println(Ipp1);
  } else { // minimum off time expired
    if (testing){
      // if ((Vpp - Vbb)*1000>=startupVoltageMargin) currentState=start;
      // same as normal test
      if (Vbb>=VbbStartMin&&Vbb<=VbbStartMax&&Vpp>=VppStartMin&&Vpp<=VppStartMax) currentState=start;
    } else {
      // Conditions to go from off state to start state:
      // Vbb nominal range 11.7<Vbb<12.6  (no load, no charge, SOC=10% to 100%)
      // Vpp nominal range 19 < Vpp < 21.2 at NOCT
      // Vpp extreme range 16 < Vpp < 28 at +85C to -40C
      if (Vbb>=VbbStartMin&&Vbb<=VbbStartMax&&Vpp>=VppStartMin&&Vpp<=VppStartMax) currentState=start;
    }
  }
}

void charger::goToStart(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=start;  
  timer = millis();
  // set up pwm for start state re-Done
  pwm1.startup(Vbb,Vpp,Ipp); // set up pwm to initiate charging
//  Timer1Fast.startPwm(INpin, 65536*INduration/pwmPeriod,0); 
//  Timer1Fast.startPwm(SDpin, 65536*SDduration/pwmPeriod,0); 
  lcd1602.pwm1(pwm1.readAtime(), pwm1.readBtime() ,pwm1.readPeriod());
}

void charger::runStart(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing){
    // IppL = (Vpp-Vbb)/pwm1.L*Tp*Tp/32/Tt;
    // Vpp=Vbb*pwm1.Tt/pwm1.Tp;
    Vpp=19.5;
    // Vpp=pvModel.getVoc()-0.65;
//    Serial.print("\n charger Line 195 Vpp="); Serial.print(Vpp);
    Ipp=pvModel.current(Vpp);
//    Serial.print("\n line 212  Ipp="); Serial.print(Ipp);
    //    if ((Vpp - Vbb)*1000<=shutDownVoltageMargin) currentState=off;
  } 
  // else {
    // Vpp should have reduced, Vbb should have increased, Ipp should become positive.
    // change in Vbb, Vpp not checked
    // Ipp should be between 0.2 and 0.5 Amps.
    // transition to next state based on Ipp >= startCurrent
    // startCurrent is global constant in mA, set to 200 milli Amps
    
    if ((long)(millis()-timer)>maxStartTime) currentState=off;
    if (Ipp>=(float)startCurrent/1000){
      if(Vbb<(float)floatVoltage/1000) currentState=bulk;
      else if (boostTime/1000<boostTimeLimit) currentState=boost;
      else currentState=floatV;
    pwm1.setInductance(Vbb,Vpp,Ipp); // 
    }
//  }
}

void charger::goToBulk(){
//  Serial.print("\n charger Line 219 Vbb*pwm1.Tpe/pwm1.Tp="); 
//  Serial.println(Vbb*pwm1.Tpe/pwm1.Tp);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=bulk;
  // set up pwm for bulk state
  pwm1.initPower(Vbb,Vpp,Ipp); // set up pwm for MPPT (under float voltage?)
}

void charger::runBulk(){
  // run MPPT algorithm
//  Serial.print("\n charger Line 229 Vbb*pwm1.Tpe/pwm1.Tp="); 
//  Serial.print(Vbb*pwm1.Tpe/pwm1.Tp);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm1.Tt, pwm1.Tp, pwm1.Tpe);
  if (testing){
    Ipp=pvModel.current(Vpp);
  }
  pwm1.power(Vbb, Vpp, Ipp); 
//  Serial.print ("\n Mode="); Serial.print(pwm1.mode);
  if (pwm1.mode==2){
    float IppL = (Vpp-Vbb)/pwm1.L*pwm1.Tp*pwm1.Tp/32/pwm1.Tt;
    Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, pwm1.Tp, pwm1.Tt);
  } else if (pwm1.mode==3){
    Vpp = Vbb * pwm1.Tt/pwm1.Tp;
  }
//  Serial.print("\n charger Line 244 Vpp="); Serial.println(Vpp);
//  Vpp = Vpp1;
//  Serial.print("\n charger Line 231 Ipp="); Serial.println(Ipp);
//  Serial.print ("floatVoltage="); Serial.println(floatVoltage);
  if (Ipp<=(float)minCurrent/1000) currentState=off;
  if (Vbb>=(float)floatVoltage/1000){
    if (boostTime/1000>boostTimeLimit) currentState=floatV;
    else currentState=boost;
  }
  if (Ipp>maxCurrent) currentState = currentLimitedFloat;
//  if (testing) printState(currentState);  
}

void charger::goToFloatV(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=floatV;
  // ToDo set up pwm for floatV state
}
void charger::runFloatV(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  // algorithm to keep Vbb at floatVoltage
  pwm1.voltage(Vbb, Vpp, Ipp, floatVoltage/1000);  
  if (Ipp<=minCurrent) currentState=off;
  if (Ipp<=minCurrent) currentState=off;
  if (Vbb < floatVoltage) currentState=bulk;
}

void charger::goToBoost(){
//  Serial.print("\n charger Line 285 goToBoost Vpp="); Serial.print(Vpp);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=boost;
  timer=millis(); // for measuring time in boost state
  // set up pwm for boost state
  pwm1.initPower(Vbb,Vpp,Ipp); // set up pwm for MPPT (under float voltage?)
//  Serial.print("\n charger Line 295 goToBoost Vpp="); Serial.print(Vpp);
}

void charger::runBoost(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
//  Serial.print("\n charger Line 299 runBoost Vpp="); Serial.print(Vpp);
  incrementBoostTime();
//  Serial.print("\n charger Line 301 runBoost boostTime="); Serial.print(boostTime/1000);
  // run MPPT algorithm
  pwm1.power(Vbb, Vpp, Ipp);  
  if (Ipp<=(float)minCurrent/1000) currentState=off;
  if (boostTime/1000>boostTimeLimit) {
    currentState=off;
    if (testing) Serial.print ("\n boost time limit exceeded");
  }
  else if (Vbb>=boostVoltage) currentState=boostFloat;
  if (Ipp>maxCurrent) currentState=currentLimitedBoost;
}

void charger::goToBoostFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=boostFloat;
  timer=millis();
  // set up pwm for boostFloat state
}
void charger::runBoostFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  incrementBoostTime();
  // algorithm to keep Vbb at boostVoltage
  pwm1.voltage(Vbb, Vpp, Ipp, boostVoltage/1000);  
//  constantVoltageAlgorithm(boostVoltage);
  if (Ipp<=minCurrent) currentState=off;
  if (boostTime/1000>boostTimeLimit) currentState=off;
  else if (Vbb<boostVoltage) currentState=boost;
}

void charger::goToCurrentLimitedFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=currentLimitedFloat;
  // ToDo set up pwm for CurrentLimitedFloat state
}
void charger::runCurrentLimitedFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  // ToDo algorithm to keep Ipp at maxCurrent
  pwm1.current(Vbb, Vpp, Ipp, maxCurrent/1000);  
//  constantCurrentAlgorithm(maxCurrent);
  if (Ipp<=minCurrent) currentState=off;
  if (Ipp<maxCurrent) currentState=bulk;
}

void charger::goToCurrentLimitedBoost(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  lastState=currentLimitedBoost;
  // ToDo set up pwm for CurrentLimitedBoost state
}
void charger::runCurrentLimitedBoost(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  // algorithm to keep Ipp at maxCurrent
  pwm1.current(Vbb, Vpp, Ipp, maxCurrent/1000);  
  if (Ipp<=minCurrent) currentState=off;
  if (Ipp<maxCurrent) currentState=boost;
}

void charger::printState(State currentState){
  Serial.print (F(" charger State is "));
  switch (currentState){
    case off: Serial.print(F("off")); break;
    case start: Serial.print(F("start")); break;
    case bulk: Serial.print(F("bulk")); break;
    case floatV: Serial.print(F("floatV")); break;
    case boost: Serial.print(F("boost")); break;
    case boostFloat: Serial.print(F("boostFloat")); break;
    case currentLimitedFloat: Serial.print(F("currentLimitedFloat")); break;
    case currentLimitedBoost: Serial.print(F("currentLimitedBoost")); break;
    default:  Serial.print(F("unknown")); break;
  }
}

void charger::incrementBoostTime(){
  boostTime += (long)(millis()-timer); // increment boostTime
  timer=millis();
}




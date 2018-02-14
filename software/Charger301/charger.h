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
  const float VbbStartMin=11.2; // V
  const float VbbStartMax=12.6; // V
  
  enum State {
    off, start, bulk, floatV, boost, boostFloat,
    currentLimitedFloat, currentLimitedBoost
  };
  
  State currentState=off;
//  State lastState=start; // could be any state other than off
  State nextState = off; 
  float Vbb=12, Vpp=12, Ipp=0;
  long boostTime=0; // seconds. Time spent in boost state per day
  unsigned long timer = 0;
  public:
  void run();
//  private:
  void stateAfterOff();
  void stateAfterStart();
  void stateAfterBulk();
  void stateAfterFloatV();
  void stateAfterBoost();
  void stateAfterBoostFloat();
  void stateAfterCurrentLimitedFloat();
  void stateAfterCurrentLimitedBoost();
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
    if (unitTestingActive==0){
      Serial.print (F("\nChargerRun fn at time "));
      Serial.print ((float)millis()/1000,3);
      charger.run();
    }
  }
  Time = lastTime;
}

void charger::run(){
//  Serial.print("\n line 81 Vpp="); Serial.print(Vpp);
  printState(currentState);
  if (testing) { // debug printing
    printChargerHeader(boostTime);
//    Serial.print (F("\n charger::run entry"));
//    printVVIIdelta(Vbb, Vpp, Ipp, 0);
//    printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
//    Serial.println();
  }

  if (testing){
    if (currentState==off) Vpp = pvModel.getVoc(); // only for off state
    else if (pwm.mode==2||pwm.mode==1){ // dcm or start
      float IppL = (Vpp-Vbb)/pwm.L*pwm.Tp*pwm.Tp/32/pwm.Tt;
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, pwm.Tp, pwm.Tt);
    } else if (pwm.mode==3){ // ccm
      Vpp = Vbb * pwm.Tt/pwm.Tp;
    }
    
    Ipp = pvModel.current(Vpp);
    Vbb = battery.voltage(Ipp*Vpp/Vbb);
    battery.incrementSoc(Ipp); 

    float IppL = (Vpp-Vbb)*pwm.Tp*pwm.Tp/32/pwm.L/pwm.Tt;
    float Lm = (Vpp-Vbb)*pwm.Tp*pwm.Tp/32/IppL/pwm.Tt;
  } else { // not testing
    Vpp = A0Volts.getVolts(); // returns (float) Volts
    Vbb = A2Volts.getVolts(); // returns (float) Volts
    Ipp = A1Amps.getAmps(); // returns (float) Amps
  }
// --------------------------------------------
  switch (currentState){ // determine next state
  case off:   stateAfterOff();   break;
  case start: stateAfterStart(); break;
  case bulk:  stateAfterBulk();  break;
  case floatV: stateAfterFloatV(); break;
  case boost:  stateAfterBoost();  break;
  case boostFloat: stateAfterBoostFloat(); break;
  case currentLimitedFloat: stateAfterCurrentLimitedFloat(); break;
  case currentLimitedBoost: stateAfterCurrentLimitedBoost(); break;
  default: break;
  }
  
// --------------------------------------------
  switch (nextState){
  case off:
    if(currentState!=off) goToOff();
    else runOff();
  break;
  case start:
    if(currentState!=start) goToStart();
    else runStart();
  break;
  case bulk:
    if(currentState!=bulk) goToBulk();
    else runBulk();
  break;
  case floatV:
    if(currentState!=floatV) goToFloatV();
    else runFloatV();
  break;
  case boost:
    if(currentState!=boost) goToBoost();
    else runBoost();
  break;
  case boostFloat:
    if(currentState!=boostFloat) goToBoostFloat();
    else runBoostFloat();
  break;
  case currentLimitedFloat:
    if(currentState!=currentLimitedFloat) goToCurrentLimitedFloat();
    else runCurrentLimitedFloat();
  break;
  case currentLimitedBoost:
    if(currentState!=currentLimitedBoost) goToCurrentLimitedBoost();
    else runCurrentLimitedBoost();
  break;
  default:
  break;
  }
  lcd1602.solarVoltage(Vpp);
  lcd1602.solarCurrent(Ipp);
  lcd1602.batteryVoltage(Vbb);
  if (currentState==off){
    lcd1602.pwm1("off ");
  } else {
    if (pwm.mode==3) lcd1602.pwm1(pwm.readAtime(), pwm.readPeriod());
    else lcd1602.pwm1(pwm.readAtime(), pwm.readBtime() ,pwm.readPeriod());
  }
  
//  if (testing){
//    Serial.print (F("\n charger::run exit "));
//    printVVIIdelta(Vbb, Vpp, Ipp, 0);
//    printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
//    Serial.println();
//  }
}

void charger::stateAfterOff(){
  nextState = off;
  if ((long)(millis()-timer)>=minOffTime) { // minimum off time expired
    // Conditions to go from off state to start state:
    // Vbb nominal range 11.7<Vbb<12.6  (no load, no charge, SOC=10% to 100%)
    // Vpp nominal range 19 < Vpp < 21.2 at NOCT
    // Vpp extreme range 16 < Vpp < 28 at +85C to -40C
    if (Vbb>=VbbStartMin&&Vbb<VbbStartMax&&Vpp>=VppStartMin&&Vpp<=VppStartMax) nextState=start;
  }
}

void charger::goToOff(){
  if (testing) Serial.println(F("\ngoToOff"));
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  currentState=off;
  timer = millis();
  Timer1Fast.disablePwm(SDpin);
  digitalWrite (SDpin, LOW);
  Timer1Fast.disablePwm(INpin);
  lcd1602.pwm1("off");
}

void charger::runOff(){
//  Serial.print(F("\ncharger line 188: runOff, Ipp="));Serial.print(Ipp);
//  Serial.print(F(" L="));Serial.print(pwm1.L);
//  Serial.print(F(" timer="));Serial.print(timer);
//  Serial.print(F(" minOffTime="));Serial.println(minOffTime);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  long Ipp1=A1Amps.getVoltCode(20);
  A1Amps.calibrateZeroAmps(Ipp1/100);
  if (testing) Serial.print(F("\n Current calibration")); Serial.println(Ipp1);
  if (boostTime!=0){
//      Serial.print (F("\n charger line 229 timer=")); Serial.print (timer);
//      Serial.print (F(" millis - timer=")); Serial.print (millis()-timer);
//      Serial.print (F(" boostTimeReset*1000=")); Serial.print ((long)boostTimeReset*1000);;
    if ((long)(millis()-timer)>(long)boostTimeReset*1000) {
      boostTime = 0; // reset boost timer
      if (testing) Serial.print (F("\n boost Time reset"));
    }
  }
}

void charger::stateAfterStart(){
  nextState = start;
  if ((long)(millis()-timer)>maxStartTime) nextState=off; // startup fail
  if (Ipp*1000>=startCurrent){ // startup success
    if(Vbb*1000<floatVoltage) nextState=bulk;
    else if (boostTime/1000<boostTimeLimit) nextState=boost;
    else nextState=floatV;
  }
}

void charger::goToStart(){
//  Serial.print(F("\ncharger line 223: goToStart, Ipp="));Serial.print(Ipp);
//  Serial.print(F(" L="));Serial.print(pwm1.L);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  currentState=start;  
  timer = millis();
  // set up pwm for start state re-Done
  pwm.startup(Vbb,Vpp,Ipp); // set up pwm to initiate charging
  // also updates inductance L
//  Timer1Fast.startPwm(INpin, 65536*INduration/pwmPeriod,0); 
//  Timer1Fast.startPwm(SDpin, 65536*SDduration/pwmPeriod,0); 
//  lcd1602.pwm1(pwm1.readAtime(), pwm1.readBtime() ,pwm1.readPeriod());
}

void charger::runStart(){
//  Serial.print(F("\ncharger line 238: runStart, Ipp="));Serial.print(Ipp);
//  Serial.print(F(" L="));Serial.print(pwm1.L);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  if (testing){
    // IppL = (Vpp-Vbb)/pwm.L*Tp*Tp/32/Tt;
    // Vpp=Vbb*pwm1.Tt/pwm.Tp;
    // Vpp=pvModel.getVoc()-0.65;
    //    Serial.print("\n charger Line 195 Vpp="); Serial.print(Vpp);
    Ipp=pvModel.current(Vpp);
  } 
    // Vpp should have reduced, Vbb should have increased, Ipp should become positive.
    // change in Vbb, Vpp not checked
    // Ipp should be between 0.2 and 0.5 Amps.
    // transition to next state based on Ipp >= startCurrent
    // startCurrent is global constant in mA, set to 200 milli Amps
}

void charger::stateAfterBulk(){
  nextState = bulk; // default
  if (Ipp*1000<=minCurrent) nextState=off;
  if (Ipp*1000>maxCurrent) nextState = currentLimitedFloat;
  if (Vbb*1000>=floatVoltage){
    if (boostTime/1000>boostTimeLimit) nextState=floatV;
    else nextState=boost;
  }
}

void charger::goToBulk(){
  if (currentState==start) pwm.setInductance(Vbb,Vpp,Ipp); // last chance to update inductance with meaured value
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  currentState=bulk;
  // set up pwm for bulk state
  pwm.initPower(Vbb,Vpp,Ipp); // set up pwm for MPPT (under float voltage?)
}

void charger::runBulk(){
  // run MPPT algorithm
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  if (testing) Ipp=pvModel.current(Vpp); 
  pwm.power(Vbb, Vpp, Ipp); 
  //  Serial.print ("\n Mode="); Serial.print(pwm1.mode);
  if (testing){
    if (pwm.mode==2){
      float IppL = (Vpp-Vbb)/pwm.L*pwm.Tp*pwm.Tp/32/pwm.Tt;
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, pwm.Tp, pwm.Tt);
    } else if (pwm.mode==3){
      Vpp = Vbb * pwm.Tt/pwm.Tp;
    }
  }
}

void charger::stateAfterFloatV(){
  nextState = floatV;
  if (Ipp*1000<=minCurrent) nextState=off;
  if (Vbb*1000 < floatVoltage) nextState=bulk;
}

void charger::goToFloatV(){
  if (currentState==start) pwm.setInductance(Vbb,Vpp,Ipp); // update inductance with meaured value
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  pwm.setDcm();
  currentState=floatV;
  pwm.voltage(Vbb, Vpp, Ipp, (float)floatVoltage/1000);  // check
}

void charger::runFloatV(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  // algorithm to keep Vbb at floatVoltage
  pwm.voltage(Vbb, Vpp, Ipp, (float)floatVoltage/1000);  
}

void charger::stateAfterBoost(){
  nextState = boost;
  if (Ipp*1000<=minCurrent) nextState=off;
  if (Ipp*1000>maxCurrent) nextState=currentLimitedBoost;
  if (boostTime/1000>boostTimeLimit) nextState=off; 
  else if (Vbb*1000>=boostVoltage) nextState=boostFloat;
}

void charger::goToBoost(){
  if (currentState==start) pwm.setInductance(Vbb,Vpp,Ipp); // update inductance with meaured value
  timer=millis() -chargerRepeatPeriod;
  incrementBoostTime();
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  currentState=boost;
  // set up pwm for boost state
  pwm.initPower(Vbb,Vpp,Ipp); // set up pwm for MPPT
}

void charger::runBoost(){
//  Serial.print("\n line 318 runBoost, Vpp="); Serial.println(Vpp);
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
//  Serial.print("\n charger Line 299 runBoost Vpp="); Serial.print(Vpp);
  incrementBoostTime();
//  Serial.print("\n charger Line 301 runBoost boostTime="); Serial.print(boostTime/1000);
  // run MPPT algorithm
  pwm.power(Vbb, Vpp, Ipp);  
}

void charger::stateAfterBoostFloat(){
  nextState = boostFloat;
  if (Ipp*1000<=minCurrent) nextState=off;
  if (boostTime/1000>boostTimeLimit) nextState=off; 
  else if (Vbb*1000<boostVoltage) nextState=boost;
}

void charger::goToBoostFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  timer=millis() -chargerRepeatPeriod;
  incrementBoostTime();
  pwm.setDcm();
  currentState=boostFloat;
  // set up pwm for boostFloat state
}
void charger::runBoostFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  incrementBoostTime();
  // algorithm to keep Vbb at boostVoltage
  pwm.voltage(Vbb, Vpp, Ipp, (float)boostVoltage/1000);  
}

void charger::stateAfterCurrentLimitedFloat(){
  nextState = currentLimitedFloat;
  if (Ipp*1000<=minCurrent) nextState=off;
  if (Ipp*1000<maxCurrent) nextState=bulk;
  if (Vbb*1000>=floatVoltage){
    if (boostTime/1000<boostTimeLimit) nextState=currentLimitedBoost;
    else nextState=floatV;
  }
}

void charger::goToCurrentLimitedFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  currentState=currentLimitedFloat;
  pwm.current(Vbb, Vpp, Ipp, (float)maxCurrent/1000);  
}

void charger::runCurrentLimitedFloat(){
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  pwm.current(Vbb, Vpp, Ipp, (float)maxCurrent/1000);  
//  constantCurrentAlgorithm(maxCurrent);
}

void charger::stateAfterCurrentLimitedBoost(){
  nextState = currentLimitedBoost;
  if (Ipp*1000<=minCurrent) nextState=off;
  if (Ipp*1000<maxCurrent) nextState=boost;
  else if (Vbb*1000>=boostVoltage) nextState=boostFloat;
  if (boostTime/1000>boostTimeLimit) nextState=off;
}

void charger::goToCurrentLimitedBoost(){
//  Serial.print("\n line 373 go to current limited Boost, Vpp="); Serial.println(Vpp);
  timer=millis() -chargerRepeatPeriod;
  incrementBoostTime();
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  currentState=currentLimitedBoost;
  pwm.current(Vbb, Vpp, Ipp, (float)maxCurrent/1000);  
}
void charger::runCurrentLimitedBoost(){
  incrementBoostTime();
  if (testing) printVVIIdelta(Vbb, Vpp, Ipp, 0);
  if (testing) printTTT(pwm.Tt, pwm.Tp, pwm.Tpe, pwm.mode);
  // algorithm to keep Ipp at maxCurrent
  pwm.current(Vbb, Vpp, Ipp, (float)maxCurrent/1000);  
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

// void charger::incrementOffTime(){
//    offTime += (long)(millis()-timer); // increment offTime
//  timer=millis();
// }



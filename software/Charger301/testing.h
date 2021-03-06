// testing tab file created 24 Jan 2018
// unit test functions for power (mppt), voltage limit, current limit
// 


void printTestHeader(float target, String testType){
      Serial.print ("\npwm1." + testType +"_Test:Time=");
      Serial.print ((float)millis()/1000,3);
      Serial.print (F(" target=")); Serial.print (target);
      Serial.print (F(" battery_soc=")); Serial.print (battery.readSoc());
      Serial.print (F(" pv_illumination=")); Serial.print (pvModel.getIllumination());
}

void printVIIdelta(float Vpp, float Ipp, float IppL){
  if (testingOneLine) Serial.print ("\n");
  Serial.print (F(" Vpp="));   Serial.print(Vpp,3);
  Serial.print (F(" Ipp="));   Serial.print(Ipp,4);
  Serial.print (F(" IppL="));   Serial.print(IppL,4);
  Serial.print (F(" Ipp_delta="));   Serial.print(Ipp-IppL,4);
  Serial.print (F(" soc="));   Serial.print(battery.readSoc(),4);
  //  Serial.print (F("\n Mode=")); Serial.print (pwm1.readMode());
}

void unitTestPvModel (){
// test of pvModel.current(illumination)
    if (testingPvModel){
      Serial.print (F("\n pvModel.current Test:Time="));
      Serial.print ((float)millis()/1000,3);
    }
    static float Vpp = 10;
    static float illu=0.2;
    pvModel.setIllumination(illu);
    Vpp+=1; 
    if (Vpp>28) {
      Vpp=10;
      illu+=0.2; if (illu>1.01) illu=0;
//      pvModel.setIllumination(illu);
    }
    float current = pvModel.current(Vpp);
    if (testingPvModel){
      Serial.print (F(" Vpp="));
      Serial.print (Vpp);
      Serial.print (F(" current="));
      Serial.print (current);
    }
}

void unitTestBatteryModel (){
// test of batteryModel.voltage(soc)
    if (testingBatteryModel){
      Serial.print (F("\nbatteryModel.voltage Test:Time="));
      Serial.print ((float)millis()/1000,3);
    }
    static float Vbb = 10;
    static float Ibb = 1; // -0.1;
    static float soc = 0.9;
/*    
    Ibb += 0.1;
    if (Ibb>=1.2) {
      Ibb = 0;
      soc+=0.1; 
      if (soc>=1.1) {
        soc=0.9;
      }
    }
*/      
    battery.incrementSoc(Ibb);
    soc=battery.readSoc();
    Vbb = battery.voltage(Ibb);
    if (testingBatteryModel){
      Serial.print (F(" SOC="));
      Serial.print (soc,3);
      Serial.print (F(" Ibb="));
      Serial.print (Ibb,3);
      Serial.print (F(" Vbb="));
      Serial.print (Vbb,3);
    }
    if (Vbb>12.9) Ibb=0.04;
    else Ibb=0.9;
}
//-----------------end of model tests ---------

void unitTestPwmStartup (){
// test of pwm1.startup(Vbb, Vpp, Ipp)
    if (testingPwmStartup){
      Serial.print (F("\npwm1.startup_Test:Time="));
      Serial.print ((float)millis()/1000,3);
    }
    static float Vbb=battery.voltage(0);
    static float Vpp;
    static float Ipp=0.1;
    if (Vpp<charger.VppStartMin-2) Vpp=charger.VppStartMin-2;
//    if (Vbb<charger.VbbStartMin) Vbb=charger.VbbStartMin;
    ++Vpp;
    if (Vpp>charger.VppStartMax+2){
      Vpp=charger.VppStartMin-2;
      if (Vbb==charger.VbbStartMin) Vbb=charger.VbbStartMax;
      else {
        Vbb=charger.VbbStartMin;
        Ipp += 0.05;
      }
    }
    if (testingPwmStartup){
      Serial.print (" Vbb=");
      Serial.print(Vbb,2);
      Serial.print (" Vpp=");
      Serial.print(Vpp,2);
      Serial.print (" Ipp=");
      Serial.print(Ipp,2);
    }
    if (Vbb>=charger.VbbStartMin&&Vbb<=charger.VbbStartMax&&Vpp>=charger.VppStartMin&&Vpp<=charger.VppStartMax){
//      charger.goToStart();
      pwm.startup(Vbb, Vpp, Ipp);
    } else {
      charger.goToOff();
      if (testingPwmStartup){
        Serial.print (" Values outside range allowed");
      }
    }
    lcd1602.solarVoltage(Vpp);
    lcd1602.solarCurrent(Ipp);
    lcd1602.batteryVoltage(Vbb);
    lcd1602.pwm1(pwm.readAtime(), pwm.readBtime() ,pwm.readPeriod());
  
}

void unitTestPwmCurrentDelta (){
// test of pwm1.currentUp(Vbb, Vpp, Ipp)
    if (testingPwmCurrentDelta){
      Serial.print (F("\npwm1.currentUp_Test:Time="));
      Serial.print ((float)millis()/1000,3);
    }
    static float Vbb;
    static float Vpp;
    static float Ipp=0.5;
    if (Vpp<charger.VppStartMin-2) Vpp=charger.VppStartMin-2;
    if (Vbb<charger.VbbStartMin) Vbb=charger.VbbStartMin;
    Vpp+=4;
    if (Vpp>charger.VppStartMax+2){
      Vpp=charger.VppStartMin-2;
      if (Vbb==charger.VbbStartMin) Vbb=charger.VbbStartMax;
      else {
        Vbb=charger.VbbStartMin;
        Ipp += 2;
      }
    }
    pwm.Tt=12*16;
    pwm.Tp=7*16;
    pwm.Tpe=8*16;
    pwm.setCcm();
    if (testingPwmCurrentDelta){
      Serial.print (" Vbb=");
      Serial.print(Vbb,2);
      Serial.print (" Vpp=");
      Serial.print(Vpp,2);
      Serial.print (" Ipp=");
      Serial.print(Ipp,2);
    }

    if (Vbb>=charger.VbbStartMin&&Vbb<=charger.VbbStartMax&&
      Vpp>=charger.VppStartMin&&Vpp<=charger.VppStartMax){
      pwm.IppDelta(Vbb, Vpp, Ipp,1);
    } else {
      if (testingPwmCurrentDelta){
        if (testingOneLine) Serial.print ("\n");
        Serial.print (" Values_outside_range allowed");
        Serial.print(F(" Tt/16="));
        Serial.print((float)pwm.Tt/16,4);
        Serial.print(F(" Tp/16="));
        Serial.print((float)pwm.Tp/16,4);
        Serial.print(F(" Tpe/16="));
        Serial.print((float)pwm.Tpe/16,4);
      }
    }
}

void unitTestPwmPower (){
// test of pwm1.power(Vbb, Vpp, Ipp)
    if (testingPwmPower) printTestHeader(0, "power");
    static float Vbb=charger.VbbStartMin;
    static float Vpp=pvModel.getVoc();
    static int Tt=12*16; // 12 us initial value
    static int Tp=Tt*8*Vbb/Vpp/10; // 80% of ccm value 
    static int Tpe=Tp+16;
    static float Ibb ; 
    static float IppL; 
    static float Ipp ; 
    static bool firstTime=1;
    if (firstTime) {
      firstTime=0;
      pwm.setDcm();
      pvModel.setIllumination(0.8);
      battery.setSoc(0.1);
    }
    
    if(pwm.mode==3) IppL = ((Vpp-Vbb)*Vbb)/Vpp*Tp/(2.4 *pwm.L)/16; // ccm, includes f=1.0
    else IppL = (Vpp-Vbb)/pwm.L*Tp*Tp/32/Tt; // dcm
    Ipp=pvModel.current(Vpp);
    if (testingPwmPower){
      printVIIdelta(Vpp, Ipp, IppL);
      //  Serial.print (F("\n Mode=")); Serial.print (pwm1.readMode());
    }
    if (pwm.readMode()==2) { // dcm
      // applicable to dcm only  
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, Tp, Tt);
      Ipp = pvModel.current(Vpp);
      
    } else if (pwm.readMode()==3) { // ccm
      Vpp = Vbb*Tt/Tp;
      Ipp=pvModel.current(Vpp);
      IppL=Ipp; // no meaning,
    }
/*
    if (Vpp>charger.VppStartMax){
      Vpp=charger.VppStartMin;
      if (Vbb==charger.VbbStartMin) Vbb=charger.VbbStartMax;
      else Vbb=charger.VbbStartMin; 
    }
*/    
//    static float Wpp = Vpp*Ipp;
    Ibb = Ipp * Vpp / Vbb;
    Vbb = battery.voltage(Ibb);
//    battery.incrementSoc(Ibb);
    pwm.Tt=Tt;
    pwm.Tp=Tp;
    pwm.Tpe=Tpe;
//    if (Tt<320) pwm1.setDcm();
    // calculate Ipp based on Tp and Tt
    // Ip mean=(Vpp-Vbb)/L*Tp^2/2/Tt
    
    if (testingPwmPower){
      printVVIIdelta(Vbb, Vpp, Ipp, IppL);
      printTTT(Tt, Tp, Tpe, pwm.mode);
    }
    if (Vbb>=charger.VbbStartMin-1&&Vbb<=charger.VbbStartMax+3 && \
        Vpp>=charger.VppStartMin-4&&Vpp<=charger.VppStartMax){

//    Ipp = pvModel.current(Vpp); // adjust Ipp

    pwm.power(Vbb, Vpp, Ipp);
    Tt=pwm.Tt; // times after pwm1 has run power()
    Tp=pwm.Tp;
    Tpe=pwm.Tpe;
//    Vpp=Vbb*Tt*8/Tp/10; // adjust Vpp to correspond to new Timer values
    
    } else {
      if (testingPwmPower){
        Serial.print (" Values_outside_range allowed");
        printTTT(Tt, Tp, Tpe, pwm.mode);
/*        
        Serial.print(F(" Tt/16="));
        Serial.print((float)pwm1.Tt/16,4);
        // Serial.print(F(" pwm1.Tp="));
        // Serial.print(pwm1.Tp);
        Serial.print(F(" Tp/16="));
        Serial.print((float)pwm1.Tp/16,4);
        Serial.print(F(" Tpe/16="));
        Serial.print((float)pwm1.Tpe/16,4);
*/        
      }
    }
}

void unitTestPwmCurrent (){
// test of pwm1.current(Vbb, Vpp, Ipp)
    float target=3; // Amps
    if (testingPwmCurrent) printTestHeader(target, "current");
    static float Vbb=charger.VbbStartMin;
    static float Vpp=pvModel.getVoc();
    static int Tt=12*16; // 12 us initial value
    static int Tp=Tt*8*Vbb/Vpp/10; // 80% of ccm value 
    static int Tpe=Tp+16;
    static float Ibb=0 ; 
    static float IppL; 
    static float Ipp ; 
    static bool firstTime=1;
    if (firstTime) {
      firstTime=0;
      pwm.setDcm();
      pvModel.setIllumination(1);
      battery.setSoc(0);
      IppL = (Vpp-Vbb)/pwm.L*Tp*Tp/32/Tt;
      Ipp=pvModel.current(Vpp);
    }
    if (testingPwmCurrent){
      printVIIdelta(Vpp, Ipp, IppL);
    }
    if (pwm.readMode()==2) { // dcm
      
      IppL = (Vpp-Vbb)/pwm.L*Tp*Tp/32/Tt; // load line for dcm
      Ipp=pvModel.current(Vpp);
      if (testingPwmVoltage) printVIIdelta(Vpp, Ipp, IppL);
      // match dcm load line to pv output  
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, Tp, Tt);
      Ipp = pvModel.current(Vpp);
      
    } else if (pwm.readMode()==3) { // ccm
      Vpp = Vbb*Tt/Tp;
      Ipp=pvModel.current(Vpp);
      IppL=Ipp; // no meaning,
    }
    Ibb = Ipp * Vpp / Vbb;
    Vbb = battery.voltage(Ibb);
    battery.incrementSoc(Ibb);
    pwm.Tt=Tt;
    pwm.Tp=Tp;
    pwm.Tpe=Tpe;
    if (testingPwmCurrent){
      printVVIIdelta(Vbb, Vpp, Ipp, IppL);
      printTTT(Tt, Tp, Tpe, pwm.mode);
    }
    if (Vbb>=charger.VbbStartMin-1&&Vbb<=charger.VbbStartMax+3 && \
        Vpp>=charger.VppStartMin-4&&Vpp<=charger.VppStartMax+3){

    pwm.current(Vbb, Vpp, Ipp, target); // test target
    
    Tt=pwm.Tt; // times after pwm1 has run power()
    Tp=pwm.Tp;
    Tpe=pwm.Tpe;
    
    } else {
      if (testingPwmCurrent){
        Serial.print (F(" Values_outside allowed_range"));
        printTTT(Tt, Tp, Tpe, pwm.mode);
      }
    }
}

void unitTestPwmVoltage (){
// test of pwm1.voltage(Vbb, Vpp, Ipp, target)
    float target=charger.VbbStartMax+0.2;
    if (testingPwmVoltage) printTestHeader(target, "voltage");
    pvModel.setIllumination(0.5);
    static float Vbb=charger.VbbStartMin;
    static float Vpp=pvModel.getVoc();
    static int Tt=12*16; // 12 us initial value
    static int Tp=Tt*8*Vbb/Vpp/10; // 80% of ccm value 
    static int Tpe=Tp+16;
    static float Ibb=0 ; 
    static float Ipp=0 ; 
    static float IppL=0; 
    static bool firstTime=1;
    if (firstTime) {
      firstTime=0;
      pwm.setDcm();
      battery.setSoc(0.1);
    }
    if (pwm.readMode()==2) { // dcm
      IppL = (Vpp-Vbb)/pwm.L*Tp*Tp/32/Tt; // load line for dcm
      Ipp=pvModel.current(Vpp);
//      if (testingPwmVoltage) printVIIdelta(Vpp, Ipp, IppL);
      // match dcm load line to pv output  
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, Tp, Tt);
      Ipp = pvModel.current(Vpp);

    } else if (pwm.readMode()==3) { // ccm
      Vpp = Vbb*Tt/Tp;
//      if (Ipp==0) Serial.println("\n line 541 Ipp=zero!");
      Ipp=pvModel.current(Vpp);
//      if (Ipp==0){
//        Serial.print("\n line 543 Ipp=zero!");
//        Serial.print(" Vpp="); Serial.print(Vpp);
//      }
      IppL=Ipp; // no meaning,
    }
    // static float Wpp = Vpp*Ipp;
    Ibb = Ipp * Vpp / Vbb;
    Vbb = battery.voltage(Ibb);
    battery.incrementSoc(Ibb);
    pwm.Tt=Tt;
    pwm.Tp=Tp;
    pwm.Tpe=Tpe;
    // calculate Ipp based on Tp and Tt
    // Ip mean=(Vpp-Vbb)/L*Tp^2/2/Tt
    
    if (testingPwmVoltage){
      printVVIIdelta(Vbb, Vpp, Ipp, IppL);
      printTTT(Tt, Tp, Tpe, pwm.mode);
    }
    if (Vbb>=charger.VbbStartMin&&Vbb<=charger.VbbStartMax+3 && \
        Vpp>=charger.VppStartMin-4&&Vpp<=charger.VppStartMax){

    pwm.voltage(Vbb, Vpp, Ipp, target); // test target
    
    Tt=pwm.Tt; // pwm times after pwm1 has run voltage()
    Tp=pwm.Tp;
    Tpe=pwm.Tpe;
    
    } else {
      if (testingPwmVoltage){
        Serial.print (F(" Values_outside allowed_range"));
        printTTT(Tt, Tp, Tpe, pwm.mode);
      }
    }
}

void unitTestRun(bool flag, unsigned long & Time){
// generic unit test
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    // put function call(s) here
    if (testingPvModel) unitTestPvModel();  // activates test
    if (testingBatteryModel) unitTestBatteryModel();  // activates test
    if (testingPwmStartup) unitTestPwmStartup();  // activates test
    if (testingPwmCurrentDelta) unitTestPwmCurrentDelta();  // activates test
    if (testingPwmPower) unitTestPwmPower();  // activates test
    if (testingPwmCurrent) unitTestPwmCurrent();  // activates test
    if (testingPwmVoltage) unitTestPwmVoltage();  // activates test
  }
  Time = lastTime;
}


// testing tab file created 24 Jan 2018

class batteryModel{
  // simple model of a 12V FLA battery
  float soc=0; // State of Charge
  float Vbb=12;  // Battery voltage
  float Ibb=0;   // Battery current; positive for charging
  const float floatVoltage=12.600;  // 
  const float boostVoltage=14.200;  // 
  const float VbbSoc10=11.5; // mV
  const float VbbSoc100=12.8; // mV

  public:
  batteryModel(float SOC);  // constructor
  float voltage(float Ibb); // returns Vbb dependent on SOC and Ibb
  void setSoc(float s);
  void incrementSoc(float Ibb); // increments soc according to the current
  float readSoc(){return soc;}
  
}  battery(0.5);

batteryModel::batteryModel(float s){ // constructor
  setSoc(s);
}

void batteryModel::setSoc(float s){
  if (s<0) s=0;
  if (s>1) s=1;
  soc=s;
}

float batteryModel::voltage(float Ibb){ // returns Vbb dependent on SOC and Ibb
  Vbb = VbbSoc10 +(VbbSoc100-VbbSoc10)*(soc-0.1)/0.9; // soc influence only
  if (soc<1) Vbb += Ibb/8;
  else {
    Vbb += Ibb*2;
    if (Vbb>boostVoltage+1) Vbb=boostVoltage+1;
  }
  return Vbb;     
}

void batteryModel::incrementSoc(float Ibb){ // increments soc according to the current
  soc += Ibb/1000; 
  if (soc>1) soc=1;
}

class pvModel {
  // simple modelling of a "12V" solar panel
  const float Voc100=21.28;
  const float Voc0=19;
  const float Vmpp100=18.28;
  const float Vmpp0=15.5;
  const float Capacity=150; // watts 
  float illumination, Voc, Vmpp, maxPwr; // current state
  
  public:
  pvModel (float illu);
  void setIllumination (float illu);
  float current (float volts);
  float getVoc (){return Voc;} 
  float getIllumination (){return illumination;}
  
} pvModel(0.5);

// constructor
pvModel::pvModel (float illu){
  setIllumination (illu);
}

void pvModel::setIllumination (float illu){
  if (illu<0) illu=0;
  if (illu>1) illu=1; 
  illumination = illu;
  Voc=Voc0+(Voc100-Voc0)*illu;
  if (illu<0.5122) Vmpp=Vmpp0;
  else Vmpp=Vmpp100-(Vmpp100-Vmpp0)*2.05036*(1-illu);
  // =IF(illu<=0.5122,Vmpp0 ,Vmpp100-(Vmpp100-Vmpp0)*2.05036*(1-illu))
  maxPwr=Capacity * illu;
  }

float pvModel::current (float Vpp){
  if (testingPvModel) Serial.print("\n pvModel");
  float current;
  float Impp = maxPwr/Vmpp;
  if (testingPvModel){
    Serial.print(F(" illumination="));  Serial.print(illumination*100); Serial.print('%');
    Serial.print(F(" Voc="));  Serial.print(Voc);
    Serial.print(F(" Vmpp="));  Serial.print(Vmpp);
    Serial.print(F(" maxPwr="));  Serial.print(maxPwr);
    Serial.print(F(" Impp="));  Serial.print(Impp);
  }
  if (Vpp<Vmpp) current = Impp;
  else if (Vpp<Voc) current = maxPwr*(Voc-Vpp)/(Voc-Vmpp)/Vpp;
       else current = 0; 
  // =IF(Vpp<Vmpp,Impp,IF(Vpp<Voc,maxPwr*(Voc-Vpp)/(Voc-Vmpp)/Vpp,0))
  if (testingPvModel) {
    Serial.print(F(" Vpp="));  Serial.print(Vpp);
    Serial.print(F(" current="));  Serial.print(current);
    }
  return current;
}
//-----------------end of class definitions ---------

void unitTestPvModel (bool flag, unsigned long & Time){
// test of pvModel.current(illumination)
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    if (testingPvModel){
      Serial.print (F("\n\npvModel.current Test:Time="));
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
      Serial.println (current);
    }
  }
  Time = lastTime;
}

void unitTestBatteryModel (bool flag, unsigned long & Time){
// test of batteryModel.voltage(soc)
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    if (testingBatteryModel){
      Serial.print (F("\n\nbatteryModel.voltage Test:Time="));
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
  Time = lastTime;
}
//-----------------end of model tests ---------

void unitTestPwmStartup (bool flag, unsigned long & Time){
// test of pwm1.startup(Vbb, Vpp, Ipp)
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    if (testingPwmStartup){
      Serial.print (F("\npwm1.startup_Test:Time="));
      Serial.print ((float)millis()/1000,3);
    }
    static float Vbb;
    static float Vpp;
    static float Ipp=0.1;
    if (Vpp<charger.VppStartMin-2) Vpp=charger.VppStartMin-2;
    if (Vbb<charger.VbbStartMin) Vbb=charger.VbbStartMin;
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
    pwm1.startup(Vbb, Vpp, Ipp);
    } else {
      if (testingPwmStartup){
        Serial.print (" Values outside range allowed");
      }
    }
  }
  Time = lastTime;
}

void unitTestPwmCurrentDelta (bool flag, unsigned long & Time){
// test of pwm1.currentUp(Vbb, Vpp, Ipp)
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
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
    pwm1.Tt=12*16;
    pwm1.Tp=7*16;
    pwm1.Tpe=8*16;
    pwm1.setCcm();
    if (testingPwmCurrentDelta){
      Serial.print (" Vbb=");
      Serial.print(Vbb,2);
      Serial.print (" Vpp=");
      Serial.print(Vpp,2);
      Serial.print (" Ipp=");
      Serial.print(Ipp,2);
    }

    if (Vbb>=charger.VbbStartMin&&Vbb<=charger.VbbStartMax&&Vpp>=charger.VppStartMin&&Vpp<=charger.VppStartMax){
    pwm1.currentDelta(Vbb, Vpp, Ipp,1);
    } else {
      if (testingPwmCurrentDelta){
        Serial.print (" Values_outside_range allowed");
        Serial.print(F(" Tt/16="));
        Serial.print((float)pwm1.Tt/16,4);
        Serial.print(F(" Tp/16="));
        Serial.print((float)pwm1.Tp/16,4);
        Serial.print(F(" Tpe/16="));
        Serial.print((float)pwm1.Tpe/16,4);
      }
    }
  }
  Time = lastTime;
}

float matchDcmToPv(float Ipp, float IppL, float Vbb, float Vpp, int Tp, int Tt){ // function in unitTestPwmVoltage
      // match load line to pv output  
      if (IppL>Ipp){
        while(IppL>Ipp){
          Vpp -= 0.0001;
          IppL = (Vpp-Vbb)/pwm1.L*Tp*Tp/32/Tt;
          Ipp=pvModel.current(Vpp);
        }
      } else if (Ipp>IppL){
        while(Ipp>IppL){
          Vpp += 0.0001;
          IppL = (Vpp-Vbb)/pwm1.L*Tp*Tp/32/Tt;
          Ipp=pvModel.current(Vpp);
        }
      }
  return Vpp;
}

void unitTestPwmPower (bool flag, unsigned long & Time){
// test of pwm1.power(Vbb, Vpp, Ipp)
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    if (testingPwmPower){
      Serial.print (F("\n\npwm1.power_Test:Time="));
      Serial.print ((float)millis()/1000,3);
      Serial.print (F(" battery soc=")); Serial.print (battery.readSoc());
      Serial.print (F(" pv illumination=")); Serial.print (pvModel.getIllumination());
    }
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
      pwm1.setDcm();
      pvModel.setIllumination(0.8);
      battery.setSoc(0.1);
    }
    
    if(pwm1.mode==3) IppL = ((Vpp-Vbb)*Vbb)/Vpp*Tp/(2.4 *pwm1.L)/16; // ccm, includes f=1.0
    else IppL = (Vpp-Vbb)/pwm1.L*Tp*Tp/32/Tt; // dcm
    Ipp=pvModel.current(Vpp);
    if (testingPwmPower){
      Serial.print (F("\n Vpp="));   Serial.print(Vpp,3);
      Serial.print (F(" Ipp="));   Serial.print(Ipp,4);
      Serial.print (F(" IppL="));   Serial.print(IppL,4);
      Serial.print (F(" Ipp delta="));   Serial.print(Ipp-IppL,4);
      //  Serial.print (F("\n Mode=")); Serial.print (pwm1.readMode());
    }
    if (pwm1.readMode()==2) { // dcm
      // applicable to dcm only  
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, Tp, Tt);
      Ipp = pvModel.current(Vpp);
      
    } else if (pwm1.readMode()==3) { // ccm
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
    pwm1.Tt=Tt;
    pwm1.Tp=Tp;
    pwm1.Tpe=Tpe;
//    if (Tt<320) pwm1.setDcm();
    // calculate Ipp based on Tp and Tt
    // Ip mean=(Vpp-Vbb)/L*Tp^2/2/Tt
    
    if (testingPwmPower){
      Serial.print (F("\n Vbb=")); Serial.print(Vbb,1);
      Serial.print (F(" Vpp="));   Serial.print(Vpp,3);
      Serial.print (F(" Ipp="));   Serial.print(Ipp,4);
      Serial.print (F(" Ipp delta="));   Serial.print(Ipp-IppL,4);
      Serial.print(F("       Tt/16=")); Serial.print((float)Tt/16,4);
      Serial.print(F(" Tt=")); Serial.print(Tt);
      Serial.print(F(" Tp/16=")); Serial.print((float)Tp/16,4);
      Serial.print(F(" Tp="));    Serial.print(Tp);
      Serial.print(F(" Tpe/16=")); Serial.print((float)Tpe/16,4);
      Serial.print(F(" Tpe="));    Serial.println(Tpe);
    }
    if (Vbb>=charger.VbbStartMin-1&&Vbb<=charger.VbbStartMax+3 && \
        Vpp>=charger.VppStartMin-4&&Vpp<=charger.VppStartMax){

//    Ipp = pvModel.current(Vpp); // adjust Ipp

    pwm1.power(Vbb, Vpp, Ipp);
    Tt=pwm1.Tt; // times after pwm1 has run power()
    Tp=pwm1.Tp;
    Tpe=pwm1.Tpe;
//    Vpp=Vbb*Tt*8/Tp/10; // adjust Vpp to correspond to new Timer values
    
    } else {
      if (testingPwmPower){
        Serial.print (" Values_outside_range allowed");
        Serial.print(F(" Tt/16="));
        Serial.print((float)pwm1.Tt/16,4);
        // Serial.print(F(" pwm1.Tp="));
        // Serial.print(pwm1.Tp);
        Serial.print(F(" Tp/16="));
        Serial.print((float)pwm1.Tp/16,4);
        Serial.print(F(" Tpe/16="));
        Serial.print((float)pwm1.Tpe/16,4);
      }
    }
  }
  Time = lastTime;
}

void printVIIdelta(float Vpp, float Ipp, float IppL){
  Serial.print (F("\n Vpp="));   Serial.print(Vpp,3);
  Serial.print (F(" Ipp="));   Serial.print(Ipp,4);
  Serial.print (F(" IppL="));   Serial.print(IppL,4);
  Serial.print (F(" Ipp delta="));   Serial.print(Ipp-IppL,4);
  Serial.print (F(" soc="));   Serial.print(battery.readSoc(),4);
  //  Serial.print (F("\n Mode=")); Serial.print (pwm1.readMode());
}

void printVVIIdelta(float Vbb, float Vpp, float Ipp, float IppL){
  Serial.print (F("\n Vbb=")); Serial.print(Vbb,4);
  Serial.print (F(" Vpp="));   Serial.print(Vpp,3);
  Serial.print (F(" Ipp="));   Serial.print(Ipp,4);
  Serial.print (F(" Ipp delta="));   Serial.print(Ipp-IppL,4);
//  Serial.print (F(" soc="));   Serial.print(battery.readSoc(),4);
}

void printTTT(int Tt, int Tp, int Tpe){
      Serial.print(F(" Tt/16=")); Serial.print((float)Tt/16,4);
      Serial.print(F(" Tt=")); Serial.print(Tt);
      Serial.print(F(" Tp/16=")); Serial.print((float)Tp/16,4);
      Serial.print(F(" Tp="));    Serial.print(Tp);
      Serial.print(F(" Tpe/16=")); Serial.print((float)Tpe/16,4);
      Serial.print(F(" Tpe="));    Serial.println(Tpe);
}


void unitTestPwmCurrent (bool flag, unsigned long & Time){
// test of pwm1.current(Vbb, Vpp, Ipp)
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    float target=2; // Amps
    if (testingPwmCurrent){
      Serial.print (F("\n\npwm1.current_Test:Time="));
      Serial.print ((float)millis()/1000,3);
      Serial.print (F(" target=")); Serial.print (target);
      Serial.print (F(" battery soc=")); Serial.print (battery.readSoc());
    }
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
      pwm1.setDcm();
      pvModel.setIllumination(1);
      battery.setSoc(0);
      IppL = (Vpp-Vbb)/pwm1.L*Tp*Tp/32/Tt;
      Ipp=pvModel.current(Vpp);
    }
    if (testingPwmCurrent){
      printVIIdelta(Vpp, Ipp, IppL);
    }
    if (pwm1.readMode()==2) { // dcm
      
      IppL = (Vpp-Vbb)/pwm1.L*Tp*Tp/32/Tt; // load line for dcm
      Ipp=pvModel.current(Vpp);
      if (testingPwmVoltage) printVIIdelta(Vpp, Ipp, IppL);
      // match dcm load line to pv output  
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, Tp, Tt);
      Ipp = pvModel.current(Vpp);
      
    } else if (pwm1.readMode()==3) { // ccm
      Vpp = Vbb*Tt/Tp;
      Ipp=pvModel.current(Vpp);
      IppL=Ipp; // no meaning,
    }
    Ibb = Ipp * Vpp / Vbb;
    Vbb = battery.voltage(Ibb);
    battery.incrementSoc(Ibb);
    pwm1.Tt=Tt;
    pwm1.Tp=Tp;
    pwm1.Tpe=Tpe;
    if (testingPwmCurrent){
      printVVIIdelta(Vbb, Vpp, Ipp, IppL);
      printTTT(Tt, Tp, Tpe);
    }
    if (Vbb>=charger.VbbStartMin-1&&Vbb<=charger.VbbStartMax+3 && \
        Vpp>=charger.VppStartMin-4&&Vpp<=charger.VppStartMax+3){

    pwm1.current(Vbb, Vpp, Ipp, target); // test target
    
    Tt=pwm1.Tt; // times after pwm1 has run power()
    Tp=pwm1.Tp;
    Tpe=pwm1.Tpe;
    
    } else {
      if (testingPwmCurrent){
        Serial.print (F(" Values_outside allowed_range"));
        printTTT(Tt, Tp, Tpe);
      }
    }
  }
  Time = lastTime;
}


void unitTestPwmVoltage (bool flag, unsigned long & Time){
// test of pwm1.voltage(Vbb, Vpp, Ipp, target)
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    float target=charger.VbbStartMax+0.2;
    if (testingPwmVoltage){
      Serial.print (F("\n\npwm1.voltage_Test:Time="));
      Serial.print ((float)millis()/1000,3);
      Serial.print (F(" target=")); Serial.print (target);
      Serial.print (F(" battery soc=")); Serial.print (battery.readSoc());
    }
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
      pwm1.setDcm();
      battery.setSoc(0.1);
    }
    if (pwm1.readMode()==2) { // dcm
      IppL = (Vpp-Vbb)/pwm1.L*Tp*Tp/32/Tt; // load line for dcm
      Ipp=pvModel.current(Vpp);
      if (testingPwmVoltage) printVIIdelta(Vpp, Ipp, IppL);
      // match dcm load line to pv output  
      Vpp = matchDcmToPv(Ipp, IppL, Vbb, Vpp, Tp, Tt);
      Ipp = pvModel.current(Vpp);

    } else if (pwm1.readMode()==3) { // ccm
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
    pwm1.Tt=Tt;
    pwm1.Tp=Tp;
    pwm1.Tpe=Tpe;
    // calculate Ipp based on Tp and Tt
    // Ip mean=(Vpp-Vbb)/L*Tp^2/2/Tt
    
    if (testingPwmVoltage){
      printVVIIdelta(Vbb, Vpp, Ipp, IppL);
      printTTT(Tt, Tp, Tpe);
    }
    if (Vbb>=charger.VbbStartMin&&Vbb<=charger.VbbStartMax+3 && \
        Vpp>=charger.VppStartMin-4&&Vpp<=charger.VppStartMax){

    pwm1.voltage(Vbb, Vpp, Ipp, target); // test target
    
    Tt=pwm1.Tt; // pwm times after pwm1 has run voltage()
    Tp=pwm1.Tp;
    Tpe=pwm1.Tpe;
    
    } else {
      if (testingPwmVoltage){
        Serial.print (F(" Values_outside allowed_range"));
        printTTT(Tt, Tp, Tpe);
      }
    }
  }
  Time = lastTime;
}




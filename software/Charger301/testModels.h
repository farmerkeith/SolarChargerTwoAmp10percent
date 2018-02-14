// file created 30 Jan 2018
// contains definitions of pvModel and batteryModel used in testing
// battery model class
// pv panel model class

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
  
}  battery(initialSoc);

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
  soc += Ibb*socChargeFactor;
  soc -= socDischargeFactor; 
  if (soc>1) soc=1;
  if (soc<0) soc=0;
  
}

class pvModel {
  // simple modelling of a "12V" solar panel
  const float Voc100=21.28; // 100% illumination, Voc
  const float Voc0=19;      // 0% illumination, Voc
  const float Vmpp100=18.28; // 100% illumination, Vmpp
  const float Vmpp0=15.5;    // 0% illumination, Vmpp
  const float Capacity=150; // watts 
  float illumination, Voc, Vmpp, maxPwr; // current state
  
  public:
  pvModel (float illu);
  void setIllumination (float illu);
  float current (float volts);
  float getVoc (){return Voc;} 
  float getIllumination (){return illumination;}
  
} pvModel(pvIlluminationFactor);

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
  if (testingPvModel) {
    if (testingOneLine) Serial.print("\n");
    Serial.print(" pvModel");
  }
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

void printChargerHeader(long boostTime){
    Serial.print (F(" pv illumination=")); Serial.print(pvModel.getIllumination());
    Serial.print (F(" battery SOC=")); Serial.print(battery.readSoc());
    Serial.print (F(" boost time=")); Serial.print((float)boostTime/1000);
}

void printVVIIdelta(float Vbb, float Vpp, float Ipp, float IppL){
  if (testingOneLine) Serial.print ("\n");
  Serial.print (F(" Vbb=")); Serial.print(Vbb,4);
  Serial.print (F(" Vpp="));   Serial.print(Vpp,3);
  Serial.print (F(" Ipp="));   Serial.print(Ipp,4);
  Serial.print (F(" Ipp_delta="));   Serial.print(Ipp-IppL,4);
  Serial.print (F(" Ibb="));   Serial.print(Ipp*Vpp/Vbb,3);
//  Serial.print (F(" soc="));   Serial.print(battery.readSoc(),4);
}


void printTTT(int Tt, int Tp, int Tpe, byte mode){
//      Serial.print(F(" Tt/16=")); Serial.print((float)Tt/16,4);
      Serial.print(F(" Tt=")); Serial.print(Tt);
//      Serial.print(F(" Tp/16=")); Serial.print((float)Tp/16,4);
      Serial.print(F(" Tp="));    Serial.print(Tp);
//      Serial.print(F(" Tpe/16=")); Serial.print((float)Tpe/16,4);
      Serial.print(F(" Tpe="));    Serial.print(Tpe);
      Serial.print(F(" mode="));    Serial.print(mode);
}


float matchDcmToPv(float Ipp, float IppL, float Vbb, float Vpp, int Tp, int Tt){ // function in unitTestPwmVoltage
      // match load line to pv output  
      if (IppL>Ipp){
        while(IppL>Ipp){
          Vpp -= 0.0001;
          IppL = (Vpp-Vbb)/pwm.L*Tp*Tp/32/Tt;
          Ipp=pvModel.current(Vpp);
        }
      } else if (Ipp>IppL){
        while(Ipp>IppL){
          Vpp += 0.0001;
          IppL = (Vpp-Vbb)/pwm.L*Tp*Tp/32/Tt;
          Ipp=pvModel.current(Vpp);
        }
      }
  return Vpp;
}


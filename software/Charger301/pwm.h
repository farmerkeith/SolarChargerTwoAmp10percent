// file PWM.h created 21 Jan 2018

// libraries
#include "Timer1Fast.h"

class pwm1 {
  const float IppStart=0.5;     // mA
  const float TeStart=1;        // microseconds
  const int minTp = 16;
  const int maxTt = 1280;
  const int ccmTt = 320;
  float oldPower=0;
  bool direction=1; // 0 for current down, 1 for current up
  int track=16; // filtered memory of direction changes
  byte filter=4; // filter constant for track
  
  public: // changed for unit testing
  float L=20;             // microHenries
  enum Mode {
    off,
    start,
    dcm, // discontinuous current mode
    ccm  // continuous current mode
  } mode=off;
  Mode lastMode=off;
  void printTTTL(bool upDown, int dutyChange, Mode mode);
  int setDutyChange(bool upDown, Mode mode, float Vbb, float Vpp);
  int Tp, Tpe, Tt; // times in clock cycles (us * 16)
  public:
  bool startup(float Vbb, float Vpp, float Ipp); // creates pwm for start state. Unit tested
  bool voltage(float Vbb, float Vpp, float Ipp, float target); // manage pwm to maintain Vbb at target
  bool current(float Vbb, float Vpp, float Ipp, float target); // manage pwm to maintain Ipp at target
  bool initPower(float Vbb, float Vpp, float Ipp); // initiate pwm to maximise power Vpp * Ipp
  bool power(float Vbb, float Vpp, float Ipp); // manage pwm to maximise power Vpp * Ipp Unit tested
  void setDcm(){mode=dcm;}  
  void setCcm(){mode=ccm;}  
  Mode readMode(){return mode;}
  void setInductance(float Vbb, float Vpp, float Ipp); // Unit tested
  bool currentDelta(float Vbb,float Vpp,float Ipp, bool upDown); // unit tested
  void setPeriod(int period); // period in clock cycles, takes any integer value
  void setAtime(unsigned long Atime, int period); // clock cycles, takes any integer values
  void setBtime(unsigned long Btime, int period); // clock cycles, takes any integer values
  float readAtime(){return (float)Tp/16;}
  float readBtime(){return (float)Tpe/16;}
  float readPeriod(){return (float)Tt/16;}
  void enableDriver();
  
} pwm1;

bool pwm1::startup(float Vbb, float Vpp, float Ipp){ // 
  mode = start;
  // Tp = (Ipp mean)*(2.4*L*Vpp)/((Vpp-Vbb)*Vbb) microseconds
  // Tt = 1.2 * Tp*Vpp/Vbb microseconds
  Tp  = IppStart*2.4*L*Vpp/((Vpp-Vbb)*Vbb)*16; // clock cycles
  Tpe = Tp+TeStart*16;       // clock cycles // 16 clock cycles per microsecond extension for Te pulse
  Tt  = Tp*Vpp/Vbb * 1.2;    // clock cycles
  setPeriod (Tt);   // 
  setAtime(Tp, Tt); // 
  setBtime(Tpe, Tt); //
  // Lm = (Vpp-Vbb)*Tp^2/(2*Tt)/(Ipp mean) 
  setInductance(Vbb,Vpp,Ipp);
//  L = (Vpp-Vbb)*Tp*Tp/(2*Tt)/Ipp; 

  if (testing){
    // printouts to go with unit test of this function
    Serial.print(F(" startup result: Tt/16="));
    Serial.print((float)Tt/16,4);
    Serial.print(" Tp/16="); Serial.print((float)Tp/16,4);
    Serial.print(" Tpe/16="); Serial.print((float)Tpe/16,4);
    Serial.print(" L="); Serial.print(L);
    Serial.print(" IppStart="); Serial.print(IppStart);
  }
}

void pwm1::setPeriod(int period){
  Timer1Fast.setPeriodMicroseconds(period/16);
  while (period%16) {
    Timer1Fast.incrementPeriod();
    -- period;
  }
}

void pwm1::setAtime(unsigned long Atime, int period){ // clock cycles, takes any integer values
  unsigned long duty = (Atime<<16)/period;
  Timer1Fast.setPwmDuty(INpin, duty);
}

void pwm1::setBtime(unsigned long Btime, int period){ // clock cycles, takes any integer values
  unsigned long duty = (Btime<<16)/period;
  Timer1Fast.setPwmDuty(SDpin, duty);
}

void pwm1::enableDriver(){
  digitalWrite (SDpin, HIGH);
}

void pwm1::printTTTL(bool upDown, int dutyChange, Mode mode){
  String ud;
  if(upDown) ud="up"; else ud="dn";
  String md;
  if(mode==dcm) md="dcm"; 
  else if (mode==ccm) md="ccm";
  else md="unk";
  Serial.print(" current " + ud + ", " + md + ": dutyChange=");
  Serial.print(dutyChange);
  Serial.print(F("      Tt/16=")); Serial.print((float)Tt/16,4);
  Serial.print(F(" Tt=")); Serial.print(Tt);
  Serial.print(F(" Tp/16=")); Serial.print((float)Tp/16,4);
  Serial.print(F(" Tp=")); Serial.print(Tp);
  Serial.print(F(" Tpe/16=")); Serial.print((float)Tpe/16,4);
  Serial.print(F(" Tpe=")); Serial.print(Tpe);
  Serial.print(" L="); Serial.print(L);
}

int pwm1::setDutyChange(bool upDown, Mode mode, float Vbb, float Vpp){
  // simplified version for testing other functions
  int dutyChange=1; // reduce this when close to MPP
//  int dutyChange=16; // reduce this when close to MPP
/*
  // following line added to deal with ccm overshoot
  
  if (mode==dcm&&Tp+dutyChange > ccmTt*Vbb/Vpp){
    dutyChange = 4;
    Serial.println("\n new duty change");
  }
  
  if (upDown==0) dutyChange = -dutyChange;
  track = (track * (filter-1)+ dutyChange)/filter;
  if (track<8&&track>-8) {
    dutyChange=1;
    if (upDown==0) dutyChange = -dutyChange;
  } else if (track<16&&track>-16){
    dutyChange=4;
    if (upDown==0) dutyChange = -dutyChange;
  }
*/  
  if (upDown==0) dutyChange = -dutyChange;
  return dutyChange;
}

bool pwm1::currentDelta(float Vbb,float Vpp,float Ipp, bool upDown){
  // ccm:
  // In ccm, to increase current we have to decrease voltage which is Vbb*duty.
  // decrease Tp relative to Tt to increase current
  // calculate pwm change required to increase measured current by 1 step
  // voltage step size is fullScale/1024, ie a0fullScale/1024.
  // current step size is fullScale/512, ie a1fullScale/512.
  // Change in duty = -Vbb/(Vpp*Ipp)*dI
  // from ccm, change to dcm when Ipp < IppL; that is, the ccm current
  // is less than the current that would be carried in dcm.
  // dcm:
  // In dcm, to increase current we have to increase Tp, Tpe and Tt
  // because IppL = ((Vpp-Vbb)*Vbb)/Vpp*Tp/(2.4 *L)

  int dutyChange = setDutyChange(upDown, mode, Vbb, Vpp);
  
  if (testing){
    Serial.print (F(" track=")); Serial.print(track);
  }
//  int dutyChange=-(float)a1fullScale*Vbb/(Vpp*Ipp)/512;  // should be negative

  if (mode==dcm){
    Tp += dutyChange; // clock cycles 
    if (Tp<=minTp) { // lower limit for low currents
      Tp = minTp;
      Tt -= dutyChange; 
      if (Tt>=maxTt) Tt=maxTt ;
    }
    Tpe = Tp*Vpp/Vbb; // clock cycles 
    if(Tt < Tpe*10/8) Tt=Tpe*10/8 ;    // clock cycles 
    if (Tp>=ccmTt*Vbb/Vpp) { // change to ccm
        mode=ccm;
        Tt=ccmTt;
        setPeriod (Tt);   // 
    } else { // execute dcm
        setPeriod (Tt);   // 
        setBtime(Tpe, Tt); //
    }
      setAtime(Tp, Tt); // 
    
    // upper Tp limit to change to ccm
    // change to ccm when Tp is the correct value to make Tt=320
    // since Tp==Tt*Vbb/Vpp (in ccm) the change point is:
    
      
//    Serial.print ("\n line 165 mode="); Serial.println (mode);
    
    // printouts to go with unit test of this function
    if (testing){
      printTTTL(upDown, dutyChange, dcm);
    }
  } else if (mode==ccm){
    // SDpin is continuously ON 
    // Change in duty = -Vbb/(Vpp*Ipp)*dI
    Tp += dutyChange;     // clock cycles 
//      Serial.print("\n Tp="); Serial.print(Tp); 
//      Serial.print("\n ccmTt*Vbb/Vpp*8/10="); Serial.println(ccmTt*Vbb/Vpp*8/10); 
    float IppL = ((Vpp-Vbb)*Vbb)/Vpp*Tp/(2.4 *L)/20;
    Serial.print("\n Ipp="); Serial.print(Ipp,4); 
    Serial.print(" IppL="); Serial.println(IppL,4); 
    if (Ipp < IppL) { // // change to dcm
//    if (Tp<ccmTt*Vbb/Vpp) { // change to dcm
//    if (Tp<ccmTt*Vbb/Vpp*8/10) { // change to dcm
      mode=dcm;
      Tpe = Tp*Vpp/Vbb; // clock cycles 
      if(Tt < Tpe*10/8) Tt=Tpe*10/8 ;    // clock cycles 
      setPeriod (Tt);   // 
      setBtime(Tpe, Tt); //
      }
    setAtime(Tp, Tt); // 
    if (testing){
      printTTTL(upDown, dutyChange, ccm);
    }
  }
}

bool pwm1::power(float Vbb, float Vpp, float Ipp){
  // maximise power
  // if (newPower >= oldPower) continue in same direction
  // else reverse direction
  float newPower= Vpp*Ipp;
  if (newPower<oldPower) direction = !direction;
  if (testing){
    Serial.print(F(" new<old="));Serial.print(newPower<oldPower); 
    Serial.print(F(" oldPower="));Serial.print(oldPower,10); 
    Serial.print(F(" newPower="));Serial.print(newPower,10); 
    Serial.print(F("\n dir="));Serial.print(direction); 
  }
  currentDelta(Vbb,Vpp,Ipp,direction);
  oldPower=newPower;
}

bool pwm1::initPower(float Vbb, float Vpp, float Ipp){
  // coming from startup
  // set up pwm in dcm
  float margin = 1.0;
  switch (mode){
    case start:
      mode=dcm; lastMode=start; 
      margin = 1.2; break;
    case dcm:
      margin = 1.2; break;
    case ccm:
      margin = 1.0; break;
    default: // presumaby mode=off
      Serial.println(F("Error in pwm.h pwm1::initPower"));
      break;
  }
  // Tp = (Ipp mean)*(2.4*L*Vpp)/((Vpp-Vbb)*Vbb) microseconds
  // Tt = 1.2 * Tp*Vpp/Vbb microseconds
  Tp = Ipp*2.4*L*Vpp/((Vpp-Vbb)*Vbb)*16; // clock cycles
  Tpe = Tp*Vpp/Vbb;          // clock cycles 
  Tt = (Tp+Tpe) * margin;    // clock cycles 
  setPeriod (Tt);   // 
  setAtime(Tp, Tt); // 
  setBtime(Tpe, Tt); //
}

void pwm1::setInductance(float Vbb, float Vpp, float Ipp){
  // works provided mode==dcm
  if (Ipp>0.1) L = (Vpp-Vbb)*Tp*Tp/Tt/Ipp/32; 
  if (L>100) L=100;
  if (L<20) L=20;
}

bool pwm1::voltage(float Vbb, float Vpp, float Ipp, float target){
  // manage pwm to maintain Vbb at target
  // keep Vbb at the target
  // if Vbb is too high, reduce current 
  currentDelta(Vbb,Vpp,Ipp, Vbb<target); 
  // Vbb<target is 1 to increase current, 0 to reduce it
/*  
  if (Vbb<target){
    // increase current
    currentDelta(Vbb,Vpp,Ipp,1);   
  } else {
    currentDelta(Vbb,Vpp,Ipp,0);
  }
*/  
}

bool pwm1::current(float Vbb, float Vpp, float Ipp, float target){
  // manage pwm to maintain Ipp at target
  currentDelta(Vbb,Vpp,Ipp, Ipp<target); 
  // Ipp<target is 1 to increase current, 0 to reduce it
/*  
  if (Ipp<target){
    // increase current
    currentDelta(Vbb,Vpp,Ipp, 1);   
  } else {
    currentDelta(Vbb,Vpp,Ipp,0);
  }
*/  
}



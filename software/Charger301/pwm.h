// file PWM.h created 21 Jan 2018

// libraries
#include "Timer1Fast.h"

class pwm {
  const float IppStart=0.5;     // mA
  const float TeStart=1;        // microseconds
  const int minTp = 16;
  const int maxTt = 1280;
  const int ccmTt = 320;
  float oldPower=0;
  float oldIbb=0;
  bool direction=1; // 0 for current down, 1 for current up
  int track=8; // filtered memory of direction changes
  byte filter=4; // filter constant for track
  
  public: // changed for unit testing
  float L=33;  // microHenries
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
  bool IppDelta(float Vbb,float Vpp,float Ipp, bool upDown); // 
//  bool IbbDelta(float Vbb,float Vpp,float Ipp, bool upDown); // 
  void setPeriod(int period); // period in clock cycles, takes any integer value
  void setAtime(unsigned long Atime, int period); // clock cycles, takes any integer values
  void setBtime(unsigned long Btime, int period); // clock cycles, takes any integer values
  float readAtime(){return (float)Tp/16;}
  float readBtime(){return (float)Tpe/16;}
  float readPeriod(){return (float)Tt/16;}
  void enableDriver();
  
} pwm;

bool pwm::startup(float Vbb, float Vpp, float Ipp){ // 
  mode = start;
  // Tp = (Ipp mean)*(2.4*L*Vpp)/((Vpp-Vbb)*Vbb) microseconds
  // Tt = 1.2 * Tp*Vpp/Vbb microseconds
  Tp  = IppStart*2.5*L*Vpp/((Vpp-Vbb)*Vbb)*16; // clock cycles
  Tpe = Tp+TeStart*16;       // clock cycles // 16 clock cycles per microsecond extension for Te pulse
  Tt  = Tp*Vpp/Vbb * 1.25;    // clock cycles
  Timer1Fast.initializeFastCycles(Tt);
//  setPeriod (Tt);   // 
  setAtime(Tp, Tt); // 
  setBtime(Tpe, Tt); //
  float IppL = (Vpp-Vbb)*Tp*Tp/32/L/Tt;
  float Lm = (Vpp-Vbb)*Tp*Tp/32/IppL/Tt;
//  Serial.print(F("\n pwm line 63 IppL=")); Serial.print(IppL);
//  Serial.print(" Lm="); Serial.print(Lm);
  // Lm = (Vpp-Vbb)*Tp^2/(2*Tt)/(Ipp mean) 
//  setInductance(Vbb,Vpp,Ipp);
  //  L = (Vpp-Vbb)*Tp*Tp/(2*Tt)/Ipp; 

  if (pwm1testing){
    // printouts to go with unit test of this function
    Serial.print(F("\n startup result: "));
    printTTTL(1 , 0, mode);
/*    
    Serial.print((float)Tt/16,4);
    Serial.print(" Tt="); Serial.print(Tt);
    Serial.print(" Tp/16="); Serial.print((float)Tp/16,4);
    Serial.print(" Tpe/16="); Serial.print((float)Tpe/16,4);
    Serial.print(" L="); Serial.print(L);
    Serial.print(" IppStart="); Serial.print(IppStart);
*/
  }
}

void pwm::setPeriod(int period){
  Timer1Fast.setPeriodClockCycles(period);
//  while (period%16) {
//    Timer1Fast.incrementPeriod();
//    -- period;
//  }
}

void pwm::setAtime(unsigned long Atime, int period){ // clock cycles, takes any integer values
  unsigned long duty = (Atime<<16)/period;
  Timer1Fast.setPwmDuty(INpin, duty);
}

void pwm::setBtime(unsigned long Btime, int period){ // clock cycles, takes any integer values
  unsigned long duty = (Btime<<16)/period;
  Timer1Fast.setPwmDuty(SDpin, duty);
}

void pwm::enableDriver(){
  digitalWrite (SDpin, HIGH);
}

void pwm::printTTTL(bool upDown, int dutyChange, Mode mode){
  String ud;
  if(upDown) ud="up"; else ud="dn";
  String md;
  if(mode==dcm) md="dcm"; 
  else if (mode==ccm) md="ccm";
  else md="unk";
  if (testingOneLine) Serial.print("\n");
  Serial.print(" current " + ud + ", " + md + ": dutyChange=");
  Serial.print(dutyChange);
  if (testingFormatSpacing) Serial.print(F("     "));
  Serial.print(F(" Tt/16=")); Serial.print((float)Tt/16,4);
  Serial.print(F(" Tt=")); Serial.print(Tt);
  Serial.print(F(" Tp/16=")); Serial.print((float)Tp/16,4);
  Serial.print(F(" Tp=")); Serial.print(Tp);
  Serial.print(F(" Tpe/16=")); Serial.print((float)Tpe/16,4);
  Serial.print(F(" Tpe=")); Serial.print(Tpe);
  Serial.print(" L="); Serial.print(L);
}

int pwm::setDutyChange(bool upDown, Mode mode, float Vbb, float Vpp){
  //  int dutyChange=1; // minimum value for initial testing
  //  if (upDown==0) dutyChange = -dutyChange;
  int dutyChange=8; // reduce this when close to MPP
/*
  // following line added to deal with ccm overshoot
  if (mode==dcm&&Tp+dutyChange > ccmTt*Vbb/Vpp){
    dutyChange = 4;
    Serial.println("\n new duty change");
  }
*/
  if (upDown==0) dutyChange = -dutyChange;
  track = (track * (filter-1)+ dutyChange)/filter;
  if (track<5&&track>-5) {
    dutyChange=1;
    if (upDown==0) dutyChange = -dutyChange;
  } else if (track<7&&track>-7){
    dutyChange=4;
    if (upDown==0) dutyChange = -dutyChange;
  }
  return dutyChange;
}

bool pwm::IppDelta(float Vbb,float Vpp,float Ipp, bool upDown){
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
  
  if (pwm1testing==1){
    if (testingOneLine) Serial.print ("\n");
    Serial.print (F(" track=")); Serial.print(track);
  }
//  int dutyChange=-(float)a1fullScale*Vbb/(Vpp*Ipp)/512;  // should be negative

//  Serial.print (F("\n pwm line 171 mode=")); Serial.println(mode);
  if (mode==dcm){
    Tp += dutyChange; // clock cycles 
    if (Tp<=minTp) { // lower limit for low currents
      Tp = minTp;
      Tt -= dutyChange; 
      if (Tt>=maxTt) Tt=maxTt ;
    }
    Tpe = Tp*Vpp/Vbb; // clock cycles 
    if(Tt < Tpe*10/8) Tt=Tpe*10/8 ; // increase Tt if necessary to maintain the margin between Tpe and Tt 
    // has Tp reached its upper limit to change to ccm?
    // change to ccm when Tp is the correct value to make Tt=320 (ccmTt) in ccm
    // since Tp==Tt*Vbb/Vpp (in ccm) the change point is:
    if (Tp>=ccmTt*Vbb/Vpp) { // change to ccm
        mode=ccm;
        Tt=ccmTt;
        setPeriod (Tt);   // 
    } else { // execute dcm
        setPeriod (Tt);   // 
        setBtime(Tpe, Tt); //
    }
    setAtime(Tp, Tt); // 
//    Serial.print("\n pwm line 193 mode="); Serial.println(mode);
    
    // printouts to go with unit test of this function
    if (pwm1testing) printTTTL(upDown, dutyChange, dcm); 
  } else if (mode==ccm){
    // SDpin is continuously ON 
    // Change in duty = -Vbb/(Vpp*Ipp)*dI
    Tp += dutyChange;     // clock cycles 
//    Serial.print("\n pwm line 201 Tp="); Serial.print(Tp); 
//      Serial.print("\n ccmTt*Vbb/Vpp*8/10="); Serial.println(ccmTt*Vbb/Vpp*8/10); 
    float IppL = ((Vpp-Vbb)*Vbb)/Vpp*Tp/L/40; // Ipp that would occur if we change to dcm
//    Serial.print("\n Ipp="); Serial.print(Ipp,4); 
//    Serial.print(" IppL="); Serial.println(IppL,4); 
    if (Ipp < IppL) { // change to dcm if the ccm current is lower than dcm current
      mode=dcm;
      Tpe = Tp*Vpp/Vbb; // clock cycles 
      if(Tt < Tpe*10/8) Tt=Tpe*10/8 ; // increase Tt if necessary to maintain the margin between Tpe and Tt 
      setPeriod (Tt);   // 
      setBtime(Tpe, Tt); //
      }
    setAtime(Tp, Tt); // 
  }
//  Serial.print("\n pwm line 215 mode="); Serial.println(mode); 
  if (pwm1testing) printTTTL(upDown, dutyChange, mode); 
}

bool pwm::power(float Vbb, float Vpp, float Ipp){
  // maximise power
  // if (newPower >= oldPower) continue in same direction
  // else reverse direction
  float newPower= Vpp*Ipp;
  if (newPower<oldPower) direction = !direction;
  if (pwm1testing){
    if (testingOneLine) Serial.print ("\n");
    Serial.print(F(" new<old="));Serial.print(newPower<oldPower); 
    Serial.print(F(" oldPower="));Serial.print(oldPower,10); 
    Serial.print(F(" newPower="));Serial.print(newPower,10); 
    Serial.print(F(" dir="));Serial.print(direction); 
  }
  IppDelta(Vbb,Vpp,Ipp,direction);
  oldPower=newPower;
//  Serial.print("\n pwm line 231 power, Vpp="); Serial.println(Vpp);
}

bool pwm::initPower(float Vbb, float Vpp, float Ipp){
  //  Serial.println(F("\n init power function"));
  // coming from startup
  // set up pwm in dcm
  float margin = 1.0;
  switch (mode){
    case start:
      mode=dcm; lastMode=start; 
      margin = 1.25; break;
    case dcm:
      margin = 1.25; break;
    case ccm:
      margin = 1.0; break;
    default: // presumaby mode=off
      Serial.println(F("Error in pwm.h pwm1::initPower"));
      break;
  }
  if (mode != ccm){
    // Tp = (Ipp mean)*(2.4*L*Vpp)/((Vpp-Vbb)*Vbb) microseconds
    // Tt = 1.25 * Tp*Vpp/Vbb microseconds
//    Tp = Ipp*2.4*L*Vpp/((Vpp-Vbb)*Vbb)*16; // clock cycles
// keep previous Tp
    Tpe = Tp*Vpp/Vbb;          // clock cycles 
    Tt = (Tpe) * margin;    // clock cycles 
  }
  direction = 0; // reduce current
/*  
  Serial.print("\n pwm1.initPower line 257 Tt=");  Serial.print(Tt);
  Serial.print(" Tp=");  Serial.print(Tp);
  Serial.print(" Tpe=");  Serial.print(Tpe);
  Serial.print(" Vbb=");  Serial.print(Vbb);
  Serial.print(" Vpp=");  Serial.print(Vpp);
  Serial.print(" Ipp=");  Serial.print(Ipp);
*/  
  setPeriod (Tt);   // 
  setAtime(Tp, Tt); // 
  setBtime(Tpe, Tt); //
}

void pwm::setInductance(float Vbb, float Vpp, float Ipp){
  // works provided mode==dcm
  if (Ipp>0.1) L = (Vpp-Vbb)*Tp*Tp/Tt/Ipp/32; 
  if (L>100) L=100;
  if (L<20) L=20;
//  Serial.print(F("\n pwm line 280 Vbb=")); Serial.print(Vbb);
//  Serial.print(" Vpp="); Serial.print(Vpp);
//  Serial.print(" Ipp="); Serial.print(Ipp,3);
//  Lm = (Vpp-Vbb)*pwm1.Tp*pwm1.Tp/32/Ipp/pwm1.Tt;
//  Serial.print(" L="); Serial.print(L);
}

bool pwm::voltage(float Vbb, float Vpp, float Ipp, float target){
  // manage pwm to maintain Vbb at target
  // keep Vbb at the target
  // if Vbb is too high, reduce Ibb;
  // if Vbb is too low, increase Ibb. 
  // direction is 1 to increase Ipp, 0 to reduce it
//  Serial.print(F("\n pwm line 286 Vbb=")); Serial.print(Vbb);
//  Serial.print(F(" target=")); Serial.print(target);
  if (Vbb<target) { // increase Ibb
    float newIbb = Ipp * Vpp / Vbb;
    if(newIbb<oldIbb) direction = !direction;
    IppDelta(Vbb,Vpp,Ipp,direction);
    oldIbb=newIbb;
//    Serial.println("\n Line 270 pwm1::voltage");
  } else { // reduce Ipp
    IppDelta(Vbb,Vpp,Ipp, 0); 
//    Serial.println("\n Line 273 pwm1::voltage");
  }
/*  
  if (Vbb<target){
    // increase current
    currentDelta(Vbb,Vpp,Ipp,1);   
  } else {
    currentDelta(Vbb,Vpp,Ipp,0);
  }
*/  
}

bool pwm::current(float Vbb, float Vpp, float Ipp, float target){
  // manage pwm to maintain Ipp at target
  IppDelta(Vbb,Vpp,Ipp, Ipp<target); 
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



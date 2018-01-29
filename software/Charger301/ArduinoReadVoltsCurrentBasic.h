// File created 15 Jan 2018
// On command the ADC measures a number of times, 
// readVoltage(1) does a single measurement with no filtering
// readVoltage(2) or readVoltage(n) does a series of measurements lasting n milliseconds
// and returns the average
// 15 Jan 2018 adding current measuring for Hall effect sensors

class readVoltsAmps {
  public:
  readVoltsAmps(byte p); // p=pin. Constructor
  readVoltsAmps(byte p, byte refType); //p=pin. refType=voltage reference internal or Vcc. Constructor
  // functions
  void init();
  void calibrateZero(long adc);
  void calibrateScale(unsigned long mV);
  float getVolts(byte timeAllowed); // returns Volts
  float getVolts(){return getVolts(timeAllowed);} // returns Volts
  unsigned long getMilliVolts(byte timeAllowed); // returns milli volts
  unsigned long getMilliVolts(){return getMilliVolts(timeAllowed);} // returns milli volts
  unsigned long getVoltCode(byte timeAllowed); // returns voltCode
  unsigned long getVoltCode(){return getVoltCode(timeAllowed);} // returns voltCode
  
  void calibrateZeroAmps(long adc);
  void calibrateAmps(unsigned long mA);
  float getAmps(byte timeAllowed); // returns Amps
  float getAmps(){return getAmps(timeAllowed);} // returns Amps
  long getMilliAmps(byte timeAllowed); // returns milli Amps
  long getMilliAmps(){return getMilliAmps(timeAllowed);} // returns milli Amps
  
  // configuration variables
  byte pin=0; // selects pin to read
  byte ARef = 0; // 0 for 5V Vcc (default); 1 for 1.1V internal reference
  unsigned long fullScale = 6000;  // mV, max 2^16-1 = 65,535
  long currentFullScale = 13500;    // mA for ACS712, max 2^15-1 = 32,767
  // ACS712 nominal sensitivity is 185 mV/Amp. If Vcc is 5.00V the voltage change is 2500 mV for a voltCode change of 512
  // 2500 mV/185mV = 13.514 Amps for 512 codes, so each code is 13514/512= 26 mA. 
  //  int taskPeriod = 20; // interval between measurements (default: 20 ms)
  //  byte filter = 4; // exponential decay filter parameter 2^n; 0 for no filtering (default 16, can be 0 up to 10(for 1024) 
  //  byte filterLevel = 4; // No. of filter stages in series; max is 4 (ToDo: default 4, can be 1 up to 8).
  //  int ignoreThreshold = 5; // adc Code :discard criterion (0 for no discard; 1,2,3 etc for allowable distance from mean; 
  byte timeAllowed=20; // 0 for Mode 1, >0 for Mode 2

  // private functions
  private:
  long stabiliseReading(); // needed after change of ARef
  // working variables
  private:
  long zeroOffset=200; // ADC output code * 100 for zero voltage 
  long currentOffset=512; // adc code for zero current
  unsigned long voltsTime=0; // timer for regular execution of run()
  unsigned long counter = 0, oldCounter = 0;
  unsigned long adcCode = 0;
};

// constructors
readVoltsAmps::readVoltsAmps(byte p, byte refType){
  pin = p;
  ARef = refType;
}

readVoltsAmps::readVoltsAmps(byte p){
  pin = p;
  ARef = 0;
}

// functions
// _____________________________
void readVoltsAmps::init(){
  if (ARef) analogReference(INTERNAL); else analogReference(DEFAULT);
//  adcCode = stabiliseReading()*100; // multiply by 100 to increase calculation accuracy
//  filteredAdcCode = filterAdc(adcCode, 0); // initialise filter variables
  // increment start time to just after now
//  while ((long)(millis()-voltsTime)>=0) voltsTime += taskPeriod; 
}

// _____________________________
unsigned long readVoltsAmps::getVoltCode(byte timeAllowed){ 
   // returns voltCode, averaged value of analogRead(A0) * 100
//  if (timeAllowed==0&&mode1==1) return filteredAdcCode; // immediate return for mode 1
//  else if (timeAllowed==1 || timeAllowed==0&&mode1==0) { // return a single reading
  if (timeAllowed<=1) { // return a single reading
    if (ARef) analogReference(INTERNAL); else analogReference(DEFAULT);
    return stabiliseReading() * 100; // multiply by 100 to increase calculation accuracy
    
  } else { // timeAllowed >=2 // return average of readings over timeAllowed milliSeconds
    unsigned long adcTotal=0;
    unsigned long startMillis=millis();
    unsigned long counter=0;
    if (ARef) analogReference(INTERNAL); else analogReference(DEFAULT);
    stabiliseReading(); // wait for readings to stabilise

    while (millis()-startMillis<timeAllowed){
      counter++;
      adcTotal += analogRead(pin);
      yield();
    }
    // time is expired
    if (adcTotal>2^32/100) return adcTotal/counter*100;
    else return (adcTotal*100)/counter;
  }
}

// _____________________________
unsigned long readVoltsAmps::getMilliVolts(byte timeAllowed){ // returns milli volts
  unsigned long vc = getVoltCode(timeAllowed); // max is 102400
  if ((long)(vc-zeroOffset)<0) zeroOffset=vc; // in case of input connected to GND returning a higher value
  unsigned long ww = (vc -zeroOffset)/2 ; 
  return ((ww*fullScale) / (1024-zeroOffset/100))/50; // millivolts
}

// _____________________________
void readVoltsAmps::calibrateZero(long adc){ 
  zeroOffset=adc;
}

void readVoltsAmps::calibrateScale(unsigned long mV){
  fullScale = mV;    
}

// _____________________________
float readVoltsAmps::getVolts(byte timeAllowed){ // returns Volts
  return (float)getMilliVolts(timeAllowed)/1000;
}

// _____________________________
long readVoltsAmps::stabiliseReading(){
    long tt=0, ttold=0, flag=0;
    do {
      tt = analogRead(pin); // reading
      flag = tt - ttold;
      ttold = tt;
    } while (flag>1||flag<-1);
    return tt;
}

// _____________________________
float readVoltsAmps::getAmps(byte timeAllowed){ // returns Amps
  return (float)getMilliAmps(timeAllowed)/1000;
}

// _____________________________
long readVoltsAmps::getMilliAmps(byte timeAllowed){ // returns milli Amps
  unsigned long vc = getVoltCode(timeAllowed); // max is 102400
  long ww = (vc - currentOffset*100)/2 ; 
//  Serial.print(F("adc code for Ip=")); Serial.println(vc);
  return ((ww*currentFullScale) / (1024-currentOffset))/50; // milli Amps
}
// _____________________________
void readVoltsAmps::calibrateZeroAmps(long adc){ 
  currentOffset=adc;
}

void readVoltsAmps::calibrateAmps(unsigned long mA){
  currentFullScale = mA;    
}


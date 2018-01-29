
void readVoltsAndAmps (bool flag, unsigned long & Time){
  static unsigned long lastTime;
  if (flag) {
    lastTime=Time;
    Serial.print ("Performing readVoltsAndAmps function at time ");
    Serial.print((float)millis()/1000,3);
    float A0voltage = A0Volts.getVolts(); // returns Volts
    float A1current = A1Amps.getAmps(); // returns Amps
    float A2voltage = A2Volts.getVolts(); // returns Volts
    lcd1602.solarVoltage(A0voltage);
    lcd1602.solarCurrent(A1current);
    lcd1602.batteryVoltage(A2voltage);

    Serial.print (" A0Voltage= ");
    Serial.print(A0voltage,3);
    Serial.print (" A1Current= ");
    Serial.print(A1current,3);
    Serial.print (" A2Voltage= ");
    Serial.println(A2voltage,3);
    
  }
  Time = lastTime;
}

unsigned long countLoops (bool flag, unsigned long & Time){
  // counts the total executions of loops() between printouts
  static unsigned long lastTime;
  static unsigned long loopCounter=0;
  if (flag) {
    lastTime=Time;
    Serial.print ("\nPerforming countLoops printout function at time ");
    Serial.print((float)millis()/1000,3);
    Serial.print (" loop counter= ");
    Serial.print(loopCounter);
    loopCounter=0;
    return loopCounter;
  }
  ++loopCounter;
  Time = lastTime;
}



void loop() {
  /*
  // put your main code here, to run repeatedly:
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  //Serial.print("VBat: " ); Serial.println(measuredvbat);
*/
  frameCounter ++;
  //Serial.println(bFirstRun);

  if (bFirstRun){
    //sendMine(frameCounter,"bFirst Run is true");
    Serial.println("bFirst Run is true");
    bFirstRun = false;
    checkLength(); 
    announceSelf();
    sRunning = 0;
  } else {
    justListen();
  }
      
  strip.begin();

  if (FadeIn) {
    doFadeIn();
  }
  
  if (ledRunning) {
    doLEDrun();
  }
  
  if (FadeOut) {
    doFadeOut();
  }
}

void resetStrip(){
  FadeOut = false;
  FadeIn = false;
  ledRunning = false;
  InitCounter = 0;
  bFirstRun = false;
}

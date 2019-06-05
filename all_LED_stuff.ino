void checkLength(){
  clearStrip();
  int postLight = analogRead(BRIGHTNESS); //get the base value
  float thisLight = 0;
  strip.begin();
  for (int i=0; i<192; i++){
    strip.setPixelColor(i-1, 0, 0, 0);
    strip.setPixelColor(i, 255,255,255);
    strip.show();
    thisLight = analogRead(BRIGHTNESS);
    //Serial.print(thisLight); Serial.print("  "); Serial.print(postLight); Serial.print("  "); Serial.println((postLight-thisLight) );
    if ( (postLight-thisLight) > 500){
      //Serial.print("The total number of LED's are "); Serial.println(i-1);
      NUMPIXELS =  i;
      break;
    }
    //delay(5);
    postLight = thisLight;
  }
}

void doFadeIn(){
  InitCounter = InitCounter + 5;
  if (InitCounter > 253)
  {
    FadeIn = false;
    ledRunning = true;
    Serial.print(listenString);
    Serial.println(" is done fading in");
    head = 0;
  } 
  strip.setPixelColor(0, InitCounter, InitCounter, InitCounter);
  strip.show();
  //delay(5);
}

void doLEDrun(){
  strip.setPixelColor(head, 255, 255, 255); // color); // 'On' pixel at head
  // strip.setPixelColor(head+ledDir,colorDim);
  strip.setPixelColor(tail, 0); // 'Off' pixel at tail
  // strip.setPixelColor(tail-ledDir, 0);     // 'Off' pixel at tail
  strip.show(); // Refresh strip
  //delay(135); // Pause 20 milliseconds (~50 FPS)
  //Serial.println(head);
  tail = head;
  head += ledDir;
  if (head > (NUMPIXELS-1))
  {
    Serial.print("done now. fade out. ");
    head = NUMPIXELS;
    //ledDir *= -1;
    ledRunning = false;
    FadeOut = true;
    // sendStartCommand();
    InitCounter = 254;
    
    if (bChoreographer){          // am I responsible for sending command?
      //sendMessage(myNumber,"I am the choreographer",00);
      if (sTotal> 1){              // if more one suitcase tell next one to start here
        Serial.print(myNumber); Serial.print(" is telling this one to start: "); Serial.println(nextNumber);
        //Serial.print(" there are "); Serial.print(sTotal); Serial.println(" suitcases.");
        sendMessage(myNumber,"start",2); //choreographer always starts number two
       } else {                   // if I am the only suitcase fade out and restart
          Serial.println("Fading out before restarting");
          sendMessage(myNumber," restarts ",sTotal);
       }
    } else {                      // if I am NOT the choreographer
      Serial.print(nextNumber); Serial.print(" starting of "); Serial.print(sTotal); Serial.println(" suitcases.");
      sendMessage(myNumber,"start",nextNumber);
    }
  }
  if (head < 0)
  {
    ledDir *= -1;
  }
}

void doFadeOut(){
  InitCounter = InitCounter - 5;
  if (InitCounter < 0)
  {
    
    FadeOut = false;
    FadeIn = false;
    ledRunning = false;
    InitCounter = 0;
    
    if (bChoreographer){            // if the choreographer then do these
      if (sTotal>1){                // if more suitcases tell the next to start
        Serial.println(" another suitcase should be running now!");
        FadeOut = false;
        FadeIn = false;
        ledRunning = false;
        ledDir = 1;
        head = 0;
        InitCounter = 0;
        sendMessage(myNumber,"the next is",nextNumber);
      } else {
        FadeOut = false;
        FadeIn = true;
        ledRunning = false;
        ledDir = 1;
        head = 0;
        InitCounter = 0;
        //sendMessage(myNumber,"only me",sTotal);
      }
    } 
    /*else {
      //Serial.print(listenString);Serial.println(" is done fading out");
      sendMessage(myNumber,"start",nextNumber);
    }*/
  
  }
  // color = CRGB(InitCounter, InitCounter, InitCounter);
  strip.setPixelColor(NUMPIXELS - 1, InitCounter, InitCounter, InitCounter);
  strip.show();
}

/*
 * clear the LED strip completely
 */
void clearStrip(){
  strip.begin(); // Initialize pins for output
  for (int i=0; i<NUMPIXELS; i++){
    strip.setPixelColor(i, 0); // clear all LED's
  }
  strip.show();  // Turn all LEDs off ASAP
}

/*
 * this routine will flash an LED in the middle of the strip
 * the same number of times as the suitcases designation
 */
void initStrip(int thisNumber){
  clearStrip();
  for (int i=0; i<(myNumber+1); i++){
    strip.setPixelColor(NUMPIXELS/2, 255,0,0);
    strip.show();
    delay(250);
    strip.setPixelColor(NUMPIXELS/2, 0,0,0);
    strip.show();
    delay(250);
  }
  delay(2);
}

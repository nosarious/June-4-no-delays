void justListen(){
  message ="";
  //digitalWrite(RFM95_RST, LOW);
  //digitalWrite(RFM95_RST, HIGH);

  
  if (rf95.waitAvailableTimeout(10)){
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    // Should be a reply message for us now

  if (rf95.recv(buf, &len)){
      //Serial.println(String((char*)buf));
      message = String((char*)buf);
      Serial.print("I got: "); Serial.println(message);
      /*
       * only do the following if the choreographer
       */
      if (bChoreographer){
        //Serial.print("I just got: ");Serial.println(message);
        /*
         * did I just hear a new suitcase?!?
         */
        if (message.indexOf("newSuitcase")>-1){
          sTotal +=1;
          sendMessage(myNumber, "you_are_", sTotal);     
          nextNumber = 2;                             //choreographer always talkst to #2
          Serial.print("I jsut enumerated suitcase"); Serial.println(sTotal);
          /*
           * if there are more than 2 tell previous end suitcase to point to new end suitcase
           */
          if (sTotal>2){//delay (20);
            Serial.print("increasing the nextNumber for "); Serial.println(sTotal-1);
            sendMessage(myNumber, "increase", sTotal-1);
          }
        }
      }
     
      parseMessage(message);
      /*
       * only do things if this is for your number
       */
      if (toWhom.toInt() == myNumber){
       // sendMessage(myNumber, "has a message ",0);
        //Serial.println("this message was for me");
        if (newCommand == "start"){
          FadeIn = true;
          FadeOut = false;
          ledRunning = false;
          ledDir = 1;
          head = 0;
          InitCounter = 0;
          Serial.println(" I got a command to start!");
          if (bChoreographer){
            sendMessage(01, "is starting from", fromWhom.toInt());
          } else {
            sendMessage(myNumber, " beginning", 00);
          }
        }
        if (newCommand == "increase"){
          // if nextNumber is choreographer, change it
          //if (nextNumber == 1){
          nextNumber = myNumber +1;
          //}
          sTotal += 1;
          Serial.print("my next number is "); Serial.print(nextNumber);Serial.print(" of "); Serial.println(sTotal);
          sendMessage(myNumber, "updated to", nextNumber); 
        }
      }
    }
  }
}

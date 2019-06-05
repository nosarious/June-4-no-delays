/*
 * this is a routine just to announce yourself to the world. 
 * As such it does not use any of the associated function
 */

void announceSelf(){
  
  char radiopacket[20] = "00newSuitcase00";
  itoa (packetnum++, radiopacket+13, 10);
  
  radiopacket[19] = 0;
  rf95.send((uint8_t*)radiopacket,20);
  
  //sendThis(announceString);
  Serial.println("waiting for packet to complete...");
  
  rf95.waitPacketSent();
  //delay(20);
  
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  
  if (rf95.waitAvailableTimeout(1000)){
    Serial.println("checking messages");
  
    if(rf95.recv(buf, &len)){
      String message = String((char*)buf);
      String text = " got: ";
      String newMessage = text + message;

      //sendMessage(myNumber,message,sTotal);
      
      Serial.print(" I got this message: ");
      Serial.println(newMessage);
  
      if (message.indexOf("you_are_")>=0){
        resetStrip();
        bChoreographer = false;
        bFirstRun = false;
        
        parseMessage(message);
      
        nextNumber = 1;               // the most recent suitcase will always point to choreographer

        myNumber = toWhom.toInt();    // the number to wait for when checking messages
        sTotal = toWhom.toInt();      // the current total number of suitcases
        
        resetStrings(myNumber);

        //sendMessage(myNumber," of ", sTotal);

        sendConfirm("confirm");

        Serial.print("I am number "); Serial.print(myNumber); Serial.print(" of "); Serial.println(sTotal);
      }
    }
  } else {
    // no other suitcases then I am the only one
    Serial.println("no reply, I am the choreographer");
    bChoreographer = true;
    bFirstRun = false;
    sendMessage(myNumber, " out of a total ",sTotal);
  }
}

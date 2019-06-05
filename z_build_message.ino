void sendMessage(int myNumber, String thisCommand, int toWhom){

  bConfirm = false;
  
  //Serial.print(" beginning to send:");
  //Serial.print(myNumber);Serial.print(thisCommand);Serial.println(toWhom);
  
  sprintf (prefixNum,"%02d",myNumber);
  String prefix = prefixNum;
  //Serial.print("prefix: ");Serial.println(prefix);
  sprintf (suffixNum,"%02d",toWhom);
  String suffix = suffixNum;
  //Serial.print("suffix: ");Serial.println(suffix);
  /*
  String prefix = createStringFromNumber(myNumber);
  String suffix = createStringFromNumber(toWhom);
  */
  sendText = prefix + thisCommand + suffix;
  Serial.print("troubleshouting: "); Serial.println(sendText);   //troubleshouting
  
  int sendLength = sendText.length()+2;
  char thisMessage[sendLength];
  sendText.toCharArray(thisMessage,sendLength);

  //Serial.print("thisMessage: "); Serial.println(sendText);//troubleshouting
  
  itoa(packetnum++, thisMessage+sendText.length(), 10);
  
  thisMessage[sendText.length()] = 0;
  //sendText[sendLength-1] = 0;

  rf95.send((uint8_t *)thisMessage, sendLength);
  rf95.waitPacketSent();
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  /*
   * only check for my number if I sent "newsuitcase"
   */
  if (thisCommand == "newSuitcase"){ 
    Serial.println(" I sent newSuitcase");
    //Serial.println("Waiting for reply...");
    if (rf95.waitAvailableTimeout(1000))
    { 
      // Should be a reply message for us now   
      if (rf95.recv(buf, &len))
      {
        String reply = String((char*)buf);
        String test = "I got: ";
        String newMessage = test + reply;
  
        //Serial.print(reply);Serial.println("_is_the_reply_I_got");
        //test to see if the message contains "you are" and make a "suitcase#" name
        
        reply.remove(0,reply.length()-2);
        
        // these may change as I am building the strings completely on my own.
        listenString = "start";// + message;       // set my listen string
        endString = "end";// + message;            // set my end string
        hereString = "here"; // + message;            // set my confirmation string
        myNumber = reply.toInt();
      }
    }
  } 
 /*else {
    Serial.print("I sent: ");Serial.println(sendText);
  }
  */
}

String createStringFromNumber(int thisNumber){
  char bufNum[2]; sprintf (bufNum,"%02d",thisNumber);
  String thisNumberText = bufNum;
  return thisNumberText;
}

boolean isThisForMe(String thisString){
  int sentLength = thisString.length();
  thisString.remove(0,sentLength-2);
  boolean confirmation = false;
  if (thisString.toInt() == myNumber) confirmation = true;
  return confirmation;
}

void sendConfirm(String thisCommand){


  
  sendText = thisCommand;
  Serial.print("troubleshouting: "); Serial.println(sendText);   //troubleshouting
  
  int sendLength = sendText.length()+2;
  char thisMessage[sendLength];
  sendText.toCharArray(thisMessage,sendLength);

  //Serial.print("thisMessage: "); Serial.println(sendText);//troubleshouting
  
  itoa(packetnum++, thisMessage+sendText.length(), 10);
  
  thisMessage[sendText.length()] = 0;
  //sendText[sendLength-1] = 0;

  rf95.send((uint8_t *)thisMessage, sendLength);
  rf95.waitPacketSent();
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
}

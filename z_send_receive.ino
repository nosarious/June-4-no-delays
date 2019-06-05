/*
 * this strips the prefix and suffix from the string
 * that was recieved
 */
String parseMessage(String thisMessage){
  int thisLength = thisMessage.length();
  fromWhom = thisMessage;
  newCommand = thisMessage;
  toWhom = thisMessage;
  fromWhom.remove(2,thisLength-2);
  toWhom.remove(0,thisLength-2);
  newCommand.remove(0,2);
  newCommand.remove(newCommand.length()-2,2);
}




/*
 * basic send/recieve for given string 
 */
 /*
void sendThis(String thisString, int thisNumber){
  char bufNum[2]; sprintf (bufNum,"%02d",thisNumber);
  String thisNumberText = bufNum;
  String sendText = thisString + thisNumberText;
  int sendLength = sendText.length()+2;
  char thisMessage[sendLength];
  sendText.toCharArray(thisMessage,sendLength);
  
  itoa(packetnum++, thisMessage+sendText.length(), 10);
  
  thisMessage[sendText.length()] = 0;
  Serial.print(frameCounter);
  Serial.print(" sendThis String and Number is sending: "); Serial.println(thisMessage);
  //sendText[sendLength-1] = 0;

  rf95.send((uint8_t *)thisMessage, sendLength);
  
  rf95.waitPacketSent();

  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  
  //Serial.println("Waiting for reply...");
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    } else {
      Serial.println("Receive failed");
    }
  } else {
    Serial.print(frameCounter);
    Serial.println(" send-this-number: No reply, is there a listener around?");
  }
}
*/


/*
 * this is for sending JUST a string.
 */
 /*
void sendThis(String thisString){

  char bufNum[2]; sprintf (bufNum,"%02d",myNumber);
  String thisNumberText = bufNum;
  String sendText = thisString;// + thisNumberText;
  int sendLength = sendText.length()+2;
  char thisMessage[sendLength];
  sendText.toCharArray(thisMessage,sendLength);
/*
  Serial.print(" trying to build "); Serial.print(sendText); 
  Serial.print(" which has "); Serial.print(sendLength); Serial.println(" characters");
  * /

  //Serial.print("sending "); Serial.print(sendText); Serial.println(".");
  
  itoa(packetnum++, thisMessage+sendText.length(), 10);
  
  thisMessage[sendText.length()] = 0;
  Serial.print("sendThis String is sending: "); Serial.println(thisMessage);
  //sendText[sendLength-1] = 0;

  rf95.send((uint8_t *)thisMessage, sendLength);
  
  rf95.waitPacketSent();

  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  
  //Serial.println("Waiting for reply...");
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      String message = String((char*)buf);
      String test = "I got: ";
      String newMessage = test+message;

      //sendThis(newMessage);

      Serial.print(message);Serial.println("_is_the_message_I_got");
      //test to see if the message contains "you are" and make a "suitcase#" name
      
      if (message.indexOf("you_are_")>-1){
        sRunning = 0;
        FadeOut = false;
        FadeIn = false;
        ledRunning = false;
        InitCounter = 0;
        bFirstRun = false;
        message.remove(0,8);
        listenString = "start" + message;       // set my listen string
        endString = "end" + message;            // set my end string
        hereString = "here"+message;
        announceString = "";
        Serial.println("this is an od dplace to put this..."); 
        Serial.print("I have made a name for myself: "); Serial.println(listenString);
        Serial.print("my finish message is "); Serial.println(endString);

        sendThis("I am number ",message.toInt());
      }
    } else {
      Serial.println("send-this-string: Receive failed");
    }
  } else {
    Serial.println("send-this-only-string: No reply, is there a listener around?");
  }
}
*/



/*
 * this sends a message with prefix and suffix number (from, to)
 */
 /*
void sendMine(int thisNumber, String thisString){

  char bufNum[2]; sprintf (bufNum,"%02d",thisNumber);
  String thisNumberText = bufNum;
  String sendText = thisNumber + thisString;
  int sendLength = sendText.length()+2;
  char thisMessage[sendLength];
  sendText.toCharArray(thisMessage,sendLength);
  
  //Serial.print("sending "); Serial.print(sendText); Serial.println(".");
  
  itoa(packetnum++, thisMessage+sendText.length(), 10);
  
  thisMessage[sendText.length()] = 0;
  Serial.print("sendThis String is sending: "); Serial.println(thisMessage);
  //sendText[sendLength-1] = 0;

  rf95.send((uint8_t *)thisMessage, sendLength);
  
  rf95.waitPacketSent();
}
*/

/*
 * strings that are default but will be reset
 * if not the only suitcase
 */
String endString = "end";
String hereString = "here";
String listenString = "Start";
String nextString = "Start01";          //used to start the next suitcase
String resetString = "reset01";
String announceString = "newSuitcase";

/*
 * used for parsing messages
 */
String fromWhom;
String newCommand;
String toWhom;

String message;

  int NUMPIXELS = 30;

int fromNumber;
int toNumber;

char prefixNum[2]; 
char suffixNum[2]; 
String  sendText;

boolean bConfirm;

int delay1, delay2, delay4;   // counters for delay alternatives

/*
 * intergers used for enumeration
 */
int myNumber = 1;             // my number among all suitcases
int sTotal = 1;               // total number of suitcases
int nextNumber = 1;           // used to tell the next suitcase to start
int sRunning = 1;             // which suitcase is running at this time

/*
 * This is for deciding which LED will start/stop
 */
boolean ledRunning = false;
boolean FadeIn = true;
boolean FadeOut = false;

int InitCounter = 0;          // used for fadeIn/fadeOut

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0;
int  tail = -1; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFFFFFF;      // 'On' color (starts red)
uint32_t colorDim = 0x111111;

float ledDir = 1; //direction of LED

boolean bFirstRun = true;
boolean bChoreographer = false;

int frameCounter = 0;

void resetStrings(int thisNumber){
  char bufNum[2]; sprintf (bufNum,"%02d",thisNumber);
  String thisNumberText = bufNum;
  listenString = "start"+thisNumberText;       // set listen string
  endString = "end"+thisNumberText;           // set end string
  hereString = "here"+thisNumberText;        // set begin string
  
  //sendMessage(myNumber, "thanks ", sTotal);
}

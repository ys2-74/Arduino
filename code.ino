// April 18, 2024
// Final Project

// declare variables
int bRed=6;
int bBlue=5;
int bGreen=4;
int bYellow=3;
int redLED=13;
int blueLED=12;
int greenLED=8;
int yellowLED=7;
int redRGB=9;
int blueRGB=10;
int greenRGB=11;
int colourNumbers[10];
int count;
int clearCount=5;
int colours;
int duration;
int light;
bool playGame=false;
bool clear = false;
bool isRedPressed=false;
bool isBluePressed=false;
bool isGreenPressed=false;
bool isYellowPressed=false;

// arrays for messages to show on serial monitor
char *firstMessage[]={"Please press the button1 to play!"};
char *settingColourMsg[3]={"How many colours?", "3 -> press the button1", "4 -> press the button2"};
char *settingSpeedMsg[3]={"Which speed?", "Slow -> press button1", "Fast -> press button2"};
char *settingLightMsg[3]={"LED or RGB?", "LED -> press the button1", "RGB -> press the button2"};
char *countDownMsg[8]={ "Your settings:", "", "", "", "3", "2", "1", "Start!!"};
char *completedMsg[1]={"Congratulation You Cleared!"};
// arrays for settings
int colourValues[]={3,4};
char *colourStrings[]={"Colours: 3", "Colours: 4"};
int durationValues[]={400, 200};
char *durationStrings[]={"Speed: Slow", "Speed: Fast"};
int lightValues[]={1, 2};
char *lightStrings[]={"Light: LED", "Light: RGB"};

void setup()
{
  pinMode(bRed, INPUT);
  pinMode(bBlue, INPUT);
  pinMode(bGreen, INPUT);
  pinMode(bYellow, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redRGB, OUTPUT);
  pinMode(greenRGB, OUTPUT);
  pinMode(blueRGB, OUTPUT);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

// the function to display message
void printLines(int line, char *message[], int duration=0)
{
  for(int i=0; i<line; i++){
    Serial.println(message[i]);
    delay(duration);
  }
}

void loop()
{
  // initialize variable
  count=2;
  // show first massage
  printLines(1, firstMessage);
  
  while(digitalRead(bRed)==LOW){
  }
  // ser 3 settings
  setPlayerSetting(1, settingColourMsg, colourValues, colourStrings);  
  setPlayerSetting(2, settingSpeedMsg, durationValues, durationStrings);
  setPlayerSetting(3, settingLightMsg, lightValues, lightStrings);
  
  // set first colours
  for (int i=0; i<count; i++){
    // add a random number to the array
    colourNumbers[i]=random(0, colours);
  }
  // show comfirming and starting message
  printLines(8, countDownMsg, 1000);

  while(playGame){
    // add a random number to colour array
    colourNumbers[count]=random(0, colours);
    count++;
    // show pattern
    for (int i =0; i<count; i++){
      //delay(300);
      showPattern(colourNumbers[i], duration);
    }
	
    // check player input
    for(int i =0; i<count;i++){
      delay(300);
      while(digitalRead(bRed)==LOW &&digitalRead(bBlue)==LOW && digitalRead(bGreen)==LOW && digitalRead(bYellow)==LOW){
      }
      checkButtonState();
      if(isRedPressed && colourNumbers[i] != 0){
        playGame=false;
      }else if(isBluePressed && colourNumbers[i] != 1){
        playGame=false;
      }else if(isGreenPressed && colourNumbers[i] != 2){
        playGame=false;
      }else if(isYellowPressed && colourNumbers[i] != 3){
        playGame=false;
      }
      if(!playGame) break;
      delay(200);
    }
 	// check if player complete the level
    if(count > clearCount) {
      clear=true;
      break;
    }
    delay(500);
  }  
  if(playGame && clear){
    // show complete massage
    Serial.println("***Congratulation You Cleared!***");
    showWarningLight();
    for (int i =0; i<count;i++){
      showCompleteLight(colourNumbers[i]);
    }
  }else{
    // show message when player press unmatched button
    Serial.println("Ahame! You Mistaked.");
    showWarningLight();
    // show player's record before the mistake
    Serial.print("Your Record: ");
    if(count == 3) Serial.println(0);
    else Serial.println(count-1);
  }
}

// the function to check if any buttons were pressed
void checkButtonState()
{
  isRedPressed = digitalRead(bRed)==HIGH;
  isBluePressed = digitalRead(bBlue)==HIGH;
  isGreenPressed = digitalRead(bGreen)==HIGH;
  isYellowPressed = digitalRead(bYellow)==HIGH;
}

// the function for settings
void setPlayerSetting(int type, char *message[], int intValues[], char *strValues[])
{
  // show setting message
  printLines(3, message);
  delay(300);
  while(digitalRead(bRed)==LOW && digitalRead(bBlue)==LOW){
  }
  
  // check which button was pressed and set array
  checkButtonState();
  if(isRedPressed){
    countDownMsg[type]=strValues[0];
    if(type == 1){ // colour
      colours=intValues[0];
    }else if (type == 2){ // speed
      duration=intValues[0];
    }else{ // light
      light=intValues[0];
      playGame = true;
    }
  }else if(isBluePressed){
    countDownMsg[type]=strValues[1];
    if(type == 1){ 
      colours=intValues[1];
    }else if (type == 2){
      duration=intValues[1];
    }else{
      light=intValues[1];
      playGame = true;
    }
  }
}

// the function to show the colour pattern
void showPattern(int colourNum, int duration)
{
  if(light == 2){// RGB
    switch(colourNum){
      case 0: // red
        digitalWrite(redRGB, HIGH);
        break;
      case 1: // blue
        digitalWrite(blueRGB, HIGH);
        break;
      case 2: // green
        digitalWrite(greenRGB, HIGH);
        break;
      case 3: // yellow
        digitalWrite(redRGB, HIGH);
        digitalWrite(greenRGB, HIGH);
        break;
    }
    delay(duration);
    // reset
    digitalWrite(redRGB, LOW);
    digitalWrite(greenRGB, LOW);
    digitalWrite(blueRGB, LOW);
  }else{// LED
    switch(colourNum){
      case 0: // red
        digitalWrite(redLED, HIGH);
      	break;
      case 1: // blue
        digitalWrite(blueLED, HIGH);
      	break;
      case 2: // green
        digitalWrite(greenLED, HIGH);
        break;
      case 3: // yellow
        digitalWrite(yellowLED, HIGH);
      	break;
    }
    delay(duration);
    // reset
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
  }
  delay(duration);
}

// the function to show the colour pattern
void showCompleteLight(int colourNum)
{
  switch(colourNum){
    case 0: // red
      digitalWrite(redLED, HIGH);
      digitalWrite(redRGB, HIGH);
      break;
    case 1: // blue
      digitalWrite(blueLED, HIGH);
      digitalWrite(blueRGB, HIGH);
      break;
    case 2: // green
      digitalWrite(greenLED, HIGH);
      digitalWrite(greenRGB, HIGH);
      break;
    case 3: // yellow
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redRGB, HIGH);
      digitalWrite(greenRGB, HIGH);
      break;
  }
  delay(200);
  // reset
  digitalWrite(redRGB, LOW);
  digitalWrite(greenRGB, LOW);
  digitalWrite(blueRGB, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  delay(200);
}

// the function show the light when user make mistake
void showWarningLight()
{
  for(int i=0; i<4; i++){
    // RGB
    switch(i){
      case 0: // red
        digitalWrite(redRGB, HIGH);
        break;
      case 1: // blue
      	digitalWrite(blueRGB, HIGH);
      	break;
      case 2: // green
        digitalWrite(greenRGB, HIGH);
        break;
      case 3: // yellow
      	digitalWrite(redRGB, HIGH);
      	digitalWrite(greenRGB, HIGH);
      	break;
    }
    // turn all LED lights on
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    delay(200);
    // rest
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redRGB, LOW);
    digitalWrite(greenRGB, LOW);
  	digitalWrite(blueRGB, LOW);
    delay(200);
  }
}
  
#include <TimerOne.h>

const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
String dictionary[10];
int gameTime;
String inputString = "";
boolean stringComplete = false;
int startTime = 3;

bool start = false; 
bool finishGame = false;
bool finishStart = false;
int retroTime=0;




void setup() {
     
  Serial.begin(9600);   
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  dictionary[0]="0000";
  dictionary[1]="0001";
  dictionary[2]="0010";
  dictionary[3]="0011";
  dictionary[4]="0100";
  dictionary[5]="0101";  
  dictionary[6]="0110";
  dictionary[7]="0111"; 
  dictionary[8]="1000";
  dictionary[9]="1001";

 /*
  for(int i=0;i<10;i++){
    //Serial.println(i);
    transmitir(i);
    delay(1000);
    
  }
  */

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timerIsr );

  //retroTime=8;
  //transmitir(retroTime);
  //start = true;
   
};


void loop() {
  if(stringComplete){
    gameTime = inputString.toInt();
    Serial.println(gameTime);
    retroTime = startTime;
    transmitir(startTime);
    start = true;
    stringComplete=false;
    inputString="";
  }
  
}	

void transmitir(int value){
    String bcd = dictionary[value];
    //Serial.println(bcd);
    if(bcd[0]=='0'){
      digitalWrite(D, 0);
    }else{
      digitalWrite(D, 1);
    }
    if(bcd[1]=='0'){
      digitalWrite(C, 0);
    }else{
      digitalWrite(C, 1);
    }
    if(bcd[2]=='0'){
      digitalWrite(B, 0);
    }else{
      digitalWrite(B, 1);
    }
    if(bcd[3]=='0'){
      digitalWrite(A, 0);
    }else{
      digitalWrite(A, 1);
    }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void timerIsr() {
  if(start){
    retroTime--;
    transmitir(retroTime);
    if(retroTime==0){
      if(finishStart){
        stopGame();
      }else{
        finishStart = true;
        transmitir(gameTime);
        retroTime = gameTime;
      }
       
    }
  }
}

void stopGame(){
  Serial.println("Finish Game");
}


#include <TimerOne.h>

const int A = 3;
const int B = 4;
const int C = 5;
const int D = 6;
String dictionary[10];
int gameTime;
String inputString = "";
boolean stringComplete = false;
int startTime = 3;

bool start = false; 
bool finishGame = false;
bool finishStart = false;
int retroTime=0;
int amountPlayer1;
int amountPlayer2;


const int tiempoAntirebote =10;
const int tiempoAntirebote2 =10;

int estadoBoton;
int estadoBotonAnterior;

int estadoBoton2;
int estadoBotonAnterior2;


int led1 = 1;
int led2 = 7;
int led3 = 9;
int led4 = 10;
int led5 = 11;
int led6 = 12;
int led7 = 13;






void setup() {
     
  Serial.begin(9600);   
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  pinMode(8,INPUT);
  

  pinMode(1,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

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
  //attachInterrupt(digitalPinToInterrupt(2), addPlayer1, RISING );
  

  //retroTime=8;
  //transmitir(retroTime);
  //start = true;
  encenderLed(0,0,0,1,0,0,0);
   
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

  if(!finishGame && finishStart){

    
   estadoBoton =digitalRead (2);              //leemos el estado del boton
    if (estadoBoton  != estadoBotonAnterior) {     //si hay cambio con respeto al estado 
      if (antirebote (2)){                    //checamos  si esta preionado y si lo esta
        amountPlayer1++;                                //aumentamos la cuenta
        //Serial.println (amountPlayer1);  
        updateLed();     
      }
    }
    estadoBotonAnterior = estadoBoton;

    
    estadoBoton2 =digitalRead (8);              //leemos el estado del boton
    if (estadoBoton2  != estadoBotonAnterior2) {     //si hay cambio con respeto al estado 
      if (antirebote2 (8)){                    //checamos  si esta preionado y si lo esta
        amountPlayer2++;                                //aumentamos la cuenta
        //Serial.println (amountPlayer2);      
        updateLed(); 
      }
    }
    estadoBotonAnterior2 = estadoBoton2;
    
    
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
        finishGame = true;
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

void addPlayer1(){
  
}

boolean antirebote  (int pin ) {
  int  contador =0;
  boolean estado;            // guarda el estado del boton 
  boolean estadoAnterior;    // guarda el ultimo estado del boton 

  do {
    estado = digitalRead (pin);
    if (estado != estadoAnterior ){  // comparamos el estado actual 
      contador = 0;                   // reiniciamos el contador 
      estadoAnterior = estado;
    }
    else{
      contador = contador +1;       // aumentamos el contador en 1
    }
    delay (1);
  }
  while (contador < tiempoAntirebote);
  return estado;
}

boolean antirebote2  (int pin ) {
  int  contador2 =0;
  boolean estado2;            // guarda el estado del boton 
  boolean estadoAnterior2;    // guarda el ultimo estado del boton 

  do {
    estado2 = digitalRead (pin);
    if (estado2 != estadoAnterior2 ){  // comparamos el estado actual 
      contador2 = 0;                   // reiniciamos el contador 
      estadoAnterior2 = estado2;
    }
    else{
      contador2 = contador2 +1;       // aumentamos el contador en 1
    }
    delay (1);
  }
  while (contador2 < tiempoAntirebote2);
  return estado2;
}

void updateLed(){
  int diference = amountPlayer1 - amountPlayer2;
  if(diference == 0){
    Serial.println("Empate");
    encenderLed(0,0,0,1,0,0,0);
  }else if(diference == 1){
    Serial.println("Diferencia de 1 Player 1");
    encenderLed(0,0,1,0,0,0,0);
  }else if(diference == 2){
    encenderLed(0,1,0,0,0,0,0);
    Serial.println("Diferencia de 2 Player 1");
  }else if(diference >2){
    encenderLed(1,0,0,0,0,0,0);
    Serial.println("Diferencia mayor Player 1");
  }else if(diference == -1){
    encenderLed(0,0,0,0,1,0,0);
    Serial.println("Diferencia de 1 Player 2");
  }else if(diference == -2){
    encenderLed(0,0,0,0,0,1,0);
    Serial.println("Diferencia de 2 Player 2");
  }else if(diference <-2){
    encenderLed(0,0,0,0,0,0,1);
    Serial.println("Diferencia mayor Player 2");
  }
  
}

void encenderLed(int L1,int L2,int L3,int L4,int L5,int L6,int L7){
  digitalWrite(led1, L1);
  digitalWrite(led2, L2);
  digitalWrite(led3, L3);
  digitalWrite(led4, L4);
  digitalWrite(led5, L5);
  digitalWrite(led6, L6);
  digitalWrite(led7, L7);
}



//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// micsolar
// 
// Made by Frederico Wu
// License: CC-BY-SA 3.0
// Downloaded from: https://circuits.io/circuits/3843751-micsolar

#include <Servo.h>

Servo horizontal;
int servoh = 90;

Servo vertical;
int servov = 90;

int ldrES = A3;
int ldrDS = A2;
int ldrEI = A1;
int ldrDI = A0;

int tolV = 0;
int tolH = 0;

void setup() {
  
  Serial.begin(9600);

  horizontal.attach(5); 
  vertical.attach(6);
}

void loop() {
  
  int ES = analogRead(ldrES);
  int DS = analogRead(ldrDS);
  int EI = analogRead(ldrEI);
  int DI = analogRead(ldrDI);
  
  
  int mS = (ES + DS) / 2;
  int mI = (EI + DI) / 2;
  int mD = (DS + DI) / 2;
  int mE = (ES + EI) / 2;
  
  
  int difV = mS - mI;
  int difH = mE - mD;
    
   //refinar tolerancia - deve ser pequena (LDRs não são lineares)
   // sleep ou outro comando pro arduino não gastar energia 
    
    if (mS < mI) { // 0 graus no superior e 180 graus no inferior
    tolV=mI*0.05;
    difV=-difV;
      if (difV>tolV){  
    	servov = ++servov;
  
      if (servov >= 180) {
    
    		servov = 180;
  
  		}

      }
    }

	if (mI < mS) {
 	tolV=mS*0.05;
      if (difV>tolV)  {
  		servov = --servov;
      
        if (servov <= 0) {
          
          servov = 0;
      
      }
    }

}



    if (mD > mE) { // 0 graus na direita e 180 graus na esquerda
    tolH=mD*0.05;
    difH=-difH;
     if (difH>tolH){
      servoh = ++servoh;
     
      	if (servoh >= 180){
    
    		servoh = 180;
        }
  	  }
	}

	if (mE > mD) {
     tolH=mE*0.05; 
  	if (difH>tolH){
  		servoh = --servoh;
      
      if (servoh <= 0){
          
          servoh = 0;
      }
    }

}

vertical.write(servov);
horizontal.write(servoh);
  Serial.print ("tolV");
  Serial.print (tolV);
  Serial.print (" ");
  Serial.print ("DifV");
  Serial.print (difV);
  //Serial.print ("H");		// prints para conferir entradas e saídas do programa
  //Serial.print (servoh);
  Serial.print (" ");
  Serial.print ("V");
  Serial.print (servov);
  //Serial.print ("ES");
  //Serial.print (ES);
  Serial.println ();
delay (20); // para teste

}    

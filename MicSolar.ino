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

int ldrEI = A3;
int ldrDI = A2;
int ldrES = A1;
int ldrDS = A0;

int tolV = 0;
int tolH = 0;

void setup() {
  
  Serial.begin(9600);

  horizontal.attach(6); 
  vertical.attach(5);
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
    tolV=mI*0.05; // tolerancia escolhida baseda na variacao do cosseno de acordo com variacao de angulo
    difV=-difV;
      if (difV>tolV){  
    	servov = ++servov;
  
      if (servov >= 150) { // angulo selecionado para a plataforma nao inclinar demais e correr o risco de tombar
    
    		servov = 150;
  
  		}

      }
    }

	if (mI < mS) {
 	tolV=mS*0.05;
      if (difV>tolV)  {
  		servov = --servov;
      
        if (servov <= 30) {
          
          servov = 30;
      
      }
    }

}



    if (mD > mE) { // 0 graus na direita e 180 graus na esquerda
    tolH=mD*0.05;
    difH=-difH;
     if (difH>tolH){
      servoh = ++servoh;
     
      	if (servoh >= 140){ // angulos limitados pelos cabos e montagem da plataforma
    
    		servoh = 140;
        }
  	  }
	}

	if (mE > mD) {
     tolH=mE*0.05; 
  	if (difH>tolH){
  		servoh = --servoh;
      
      if (servoh <= 40){
          
          servoh = 40;
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

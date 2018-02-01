#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

int xPin = A4;
int yPin = A3;
int JoystickPosX = 0;
int JoystickPosY = 0;
int posX = 0;
int posY = 7;
int figure = 1;
int pos = 0;
int DrawPosX = 0;
int DrawPosY = 0;

boolean Positions[32*16];
boolean canMove = true;
int cube = 1;

  DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD() { 
  dmd.scanDisplayBySPI();
}
void setup() {
   Timer1.initialize( 1000 );          
   Timer1.attachInterrupt( ScanDMD );  
   dmd.clearScreen( true );
   pinMode(xPin, INPUT);
   pinMode(yPin, INPUT);
   Serial.begin(9600);  
   for(int i = 0; i == 32 * 16; i++){
       Positions[i] = false;
   }

}
void loop() { 

   figure = cube;
   logik();
}
void logik(){
   dmd.clearScreen( true );
   control();
   MOVE();
   Draw();
   Stop();
   delay(100);
   
}
void control(){
     JoystickPosX = analogRead(xPin);
   JoystickPosY = analogRead(yPin);
}
void MOVE(){
  if(canMove = true){ 
  if(posX != 33){
  posX++;
  }else{
    posX = 0;
  }
  if(JoystickPosX > 900 && posY !=14){
      posY++;
      delay(10);
    }
   if(JoystickPosX <100 && posY != 1){
      posY--;
      delay(10);
    }
  }
}
void Draw(){
    Serial.println(posY);
  dmd.drawBox( posX, posY ,posX-1,posY-1 , GRAPHICS_NORMAL);
    for(int i = 0; i < 32*16; i++){
        if(Positions[i] == true){       
          DrawPosY = (i / 32);
          DrawPosX = i + (DrawPosY * 32);    
          //Serial.println(DrawPosX);
          //Serial.println(DrawPosY);
          dmd.drawBox(DrawPosX,DrawPosY,DrawPosX,DrawPosY , GRAPHICS_NORMAL);
      }
  }
    }
  

void Stop(){
  pos = (32 * (posY+2)) + posX-1;

  if(posX == 31){
  Positions[pos-1] = true;
  Positions[pos] = true;
  Positions[pos-31] = true;
  Positions[pos-32] = true;

  }

        if(Positions[pos] == true){
        switch (figure){
          case 1:
            Positions[pos-1] = true;
            Positions[pos] = true;
            Positions[pos-31] = true;
            Positions[pos-32] = true;
          break;       
        }
      } 
    }



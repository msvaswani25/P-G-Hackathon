// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>

// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>
#include <string.h>
#include "InternetButton/InternetButton.h"
#include "math.h"

/*Did you know that the InternetButton can detect if it's moving? It's true!
Specifically it can read when it's being accelerated. Recall that gravity
is a constant acceleration and this becomes very useful- you know the orientation!*/
char Position[40];
char publishString[40];
int f[7]={0};
int f1=-1;
int firstAvailable =0;
bool wifiReady = WiFi.ready();
bool sta=true;
InternetButton b = InternetButton();

void setup() {
    //Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
    song();
}

void loop(){

    //How much are you moving in the x direction? (look at the white text on the board)
    int xValue = b.readX();
    int yValue = b.readY();
    int zValue = b.readZ();
    //Particle.publish("VedP checks value", "xValue", xValue, 60,PUBLIC);
    
    if(b.buttonOn(3))
    {
        song();
        lights();
        delay(5000);
        Particle.publish("status", "Going to sleep");
        sta =false;
        b.allLedsOff();
    }
     if(b.buttonOn(1))
     {
         sta=true;
         Particle.publish("status", "Woken Up");
         song();
     }
    if(b.buttonOn(2))
    {
        sta=false;
        Particle.publish("status", "Going to sleep");
        }
        if(sta==false){
            
   b.allLedsOff();
   sta = false;
   
    }
    if(sta==true)
    {
         sprintf(publishString, "%d,%d,%d", xValue,yValue,zValue);
         Spark.publish("Value", publishString);
         b.allLedsOn(abs(xValue), abs(yValue), abs(zValue));	
if (xValue>=-65 && xValue <=-55 && yValue>=-15 && yValue<=15 && zValue>=-10 && zValue<=10)
{sprintf(Position,"Front"); f[0]=1;} 
else if(xValue>=-75 && xValue <=-25 && yValue>=10 && yValue<=40 && zValue>=-50 && zValue<=-20)
{sprintf(Position,"RightUpper"); f[1]=1;}
else if(xValue>=5 && xValue <=30 && yValue>=10 && yValue<=40 && zValue>=-65 && zValue<=-25)
{sprintf(Position,"LeftUpper"); f[2]=1;}
else if(xValue>=45 && xValue <=70 && yValue>=-10 && yValue<=15 && zValue>=-30&& zValue<=10)
{sprintf(Position,"RightNormal"); f[3]=1;}
else if(xValue>=-75 && xValue <=-50 && yValue>=-5 && yValue<=20 && zValue>=-15 && zValue<=15)
{sprintf(Position,"LeftNormal"); f[4]=1;}
else if(xValue>=-40 && xValue <=0 && yValue>=-5 && yValue<=35 && zValue>=45 && zValue<=71)
{sprintf(Position,"LeftLower"); f[5]=1;}
else if(xValue>=-30 && xValue <=20 && yValue>=6 && yValue<=40 && zValue>=45 && zValue<=80)
{sprintf(Position,"RightLower"); f[6]=1;}
Spark.publish("Position", Position);

if(f[0]==1&&f[1]==1&&f[2]==1&&f[3]==1&&f[4]==1&&f[5]==1&&f[6]==1&&f1==-1)
{song();
lights();
 f1=1;
 delay(5000);
 Particle.publish("status", "Going to sleep");
 b.allLedsOff();
}
       

    
    }
    delay(1000);
}

void song()
{
     // playSong takes a string in the format
    // "NOTE,TYPE,NOTE,TYPE..."
    // Types are note types that define duration so 
    // 8 is a 1/8th note and 4 is a 1/4 note
     b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
      b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
       b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8"); b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8"); b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
    //b.playSong("B5,1,B6,1,B6,1,B6,1,D5,1,B5,1,B6,1,B6,1,D6,1,D5,1,D6,1,B7,1,D6,1,B6,1");
}
void lights()
{
        b.rainbow(5);
       
    }

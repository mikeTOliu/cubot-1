#include <Stepper.h>
//#include <String.h>
using namespace std;
//R1L3F2B2R1L3U1L1R3B2F2L1R3=D
/*

All the parameters below are well-adjusted. Please don't change anything except time.

*/
const int STEPS = 208;              // 360/1.8
const int stepperSpeed = 180;       // rpm  15.8V 
const int timeBetweenMoves = 5;     // ms    between U2 R2 or U R etc.
const int timeBetweenComs = 1000*3; // ms    between commands
const int steps_90 = 3*STEPS/4 ;     
const int steps_180 = STEPS/2;
const int steps_270 = STEPS/4;   

const int _angle[4]={0,steps_90,steps_180,steps_270};
// U2 -> stepperU.step(_angle[2]);

String command = "";

// adjust them according to your wiring
Stepper FF(211,28,29,30,31);
Stepper DD(212,22,23,24,25);
Stepper BB(206,34,35,36,37);
Stepper LL(206,38,39,40,41);
Stepper UU(205,44,45,46,47);
Stepper RR(208,50,51,52,53);

void Getcom();
void Solve();

void setup()
{
    FF.setSpeed(stepperSpeed);
    UU.setSpeed(stepperSpeed);
    RR.setSpeed(stepperSpeed);
    LL.setSpeed(stepperSpeed);
    DD.setSpeed(stepperSpeed);
    BB.setSpeed(stepperSpeed);

    pinMode(13,OUTPUT);
}
int i = 1;
void loop()
{
  if(i){
    i = 0;
    delay(timeBetweenComs);
    command = "";
    Getcom();
  }
}

// I was going to implement a funtion to receive solutions from serial monitor but did not manage to do so.
// I just simply paste the solution here and upload the code.
void Getcom() 
{    
    command = "U1D3F1L1B3R3B2U1D1B2R2D3L3R2U2B2U3R2U1L2F2U2F2R2D2F2L2U2F2R2U2";
    
    Solve();
}

void Solve()
{
    int com_len=command.length();
    for(int i=0;i<com_len;i+=2)
    //for(int i=com_len-2;i>=0;i-=2)
    {
        char ch=command[i];
        int n=command[i+1]-'0';
        
        //FULRDB
        switch(ch)
        {
            case 'F':FF.step(_angle[n]); for(int i=FF.motor_pin_1;i<FF.motor_pin_1+4;i++) digitalWrite(i,LOW); break;
            case 'U':UU.step(_angle[n]); for(int i=UU.motor_pin_1;i<UU.motor_pin_1+4;i++) digitalWrite(i,LOW); break;
            case 'L':LL.step(_angle[n]); for(int i=LL.motor_pin_1;i<LL.motor_pin_1+4;i++) digitalWrite(i,LOW); break;
            case 'R':RR.step(_angle[n]); for(int i=RR.motor_pin_1;i<RR.motor_pin_1+4;i++) digitalWrite(i,LOW); break;
            case 'D':DD.step(_angle[n]); for(int i=DD.motor_pin_1;i<DD.motor_pin_1+4;i++) digitalWrite(i,LOW); break;
            case 'B':BB.step(_angle[n]); for(int i=BB.motor_pin_1;i<BB.motor_pin_1+4;i++) digitalWrite(i,LOW); break;            
        }
        // Turning off the digital output of every pin after steps are made is crutial; otherwise, the current will be too large. 
        // To do so, motor_pin_i in Stepper.h must be removed from private to public. 
        
        digitalWrite(13,HIGH);
        delay(timeBetweenMoves);
        digitalWrite(13,LOW);
        // These scope is to determine whether the chip is executing the solution.
    }
    
}

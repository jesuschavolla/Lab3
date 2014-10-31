// ******************************************************************************************* //

#include "p24fj64ga002.h"

#include "lcd.h"

#include "PWM.h"

// ******************************************************************************************* //


void InPWM(){
            RPOR0bits.RP0R= 0;
            RPOR0bits.RP1R = 0;
            RPOR5bits.RP10R = 0;
            RPOR5bits.RP11R = 0;

    PR3 = 512;
    T3CON = 0x8000;
    PR2 = 512;
    T2CON = 0x8000;

    OC1CON = 0x000E;
    OC1R= 0;
    OC1RS = 0;

    OC2CON = 0x0006;
    OC2R = 0;
    OC2RS = 0;
    

}


// ******************************************************************************************* //


void MoveRobot(int state, int checking){
    //19 output compare 2
    //18 output compare 1
    //0  output  "NULL"

    //idle mode
    if(state ==0)
    {
            RPOR1bits.RP3R= 0;
            RPOR1bits.RP2R = 0;
            RPOR0bits.RP0R = 0;
            RPOR0bits.RP1R = 0;

    }
    else if(state== 1)
    {
    //forward 
        state = 2;
           RPOR1bits.RP3R= 0;//input 1
            RPOR1bits.RP2R = 18;//connected to input 2
            RPOR0bits.RP0R = 0;//input 4
            RPOR0bits.RP1R = 19;//input 3

        
    }
      //idle mode
    if(state ==2)
    {
            RPOR1bits.RP3R= 0;
            RPOR1bits.RP2R = 0;
            RPOR0bits.RP0R = 0;
            RPOR0bits.RP1R = 0;

    }
   
    //backward
    else if(state == 3)
    {
            RPOR1bits.RP3R= 18;//input 1
            RPOR1bits.RP2R = 0;//input 2
            RPOR0bits.RP0R = 19;//input 4
            RPOR0bits.RP1R = 0;//input 3

    }


}




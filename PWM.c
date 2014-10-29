// ******************************************************************************************* //

#include "p24fj64ga002.h"

#include "lcd.h"

#include "PWM.h"

// ******************************************************************************************* //


void InPWM(){

    RPOR1bits.RP2R = 0; //  output pins
    RPOR1bits.RP3R = 0;

    PR3 = 1474;
    T3CON = 0x8000;

    OC1CON = 0x000E;
    OC1R= 0;
    OC1RS = 0;

    OC2CON = 0x000E;
    OC2R = 0;
    OC2RS = 0;
    return 0;
}


// ******************************************************************************************* //
//void InPWM(void){ //  pulse width modulation
//
//    RPOR1bits.RP2R = 18; //
//    RPOR1bits.RP3R = 19;
//    T3CON = 0x8020; //  binary=1000000000000000 enable TMR2, prescale 1:64
//    PR3=512; // set the period for the given bitrate  econds
//
//    OC1CON = 0x0008;//0b 0110   //activate the PWM module
//    OC1R = OC1RS = 0; //seting initial duty cycles (master and slave)
//    OC2CON = 0x0008;//0b1110 activate the PWM module
//    OC2R = OC2RS = 0; //seting initial duty cycles (master and slave)
//
//}

void MoveRobot(int state, int checking){
    //19 : set as output >> compare 1 output >> Null=1
    //18 : set as output >> compare 1 output >> Null=0

    //idle mode
    if(state ==0)
    {
        if (checking==0)
        {
            state=1;
            RPOR0bits.RP0R= 0;
            RPOR0bits.RP1R = 0;
            RPOR5bits.RP10R = 0;
            RPOR5bits.RP11R = 0;
        }
        else if(checking==1){
            RPOR0bits.RP0R= 0;
            RPOR0bits.RP1R = 0;
            RPOR5bits.RP10R = 0;
            RPOR5bits.RP11R = 0;
            state=2;

        }
    }
    else if(state== 1)
    {
    //forward 
        state = 2;
        RPOR0bits.RP0R= 19;//pot >> left
        RPOR0bits.RP1R = 18;//pot >> right
        RPOR5bits.RP10R = 0;
        RPOR5bits.RP11R = 0;
        
        checking=1;
    }
   
    //backward
    else if(state == 2)
    {
        state = 0;
        RPOR0bits.RP0R= 0;
        RPOR0bits.RP1R = 0;
        RPOR5bits.RP10R = 19;//pot >> right
        RPOR5bits.RP11R = 18;//pot >> left
        checking=0;
    }
}




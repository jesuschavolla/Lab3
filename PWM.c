// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "PWM.h"
// ******************************************************************************************* //
void InPWM(void){ //  pulse width modulation

    RPOR1bits.RP2R = 0; //
    RPOR1bits.RP3R = 0;
    T2CON = 0x8000; //  binary=1000000000000000 enable TMR2, prescale 1:1
    PR3=1474; // set the period for the given bitrate  econds

    OC1CON = 0x0006;//0b 0110   //activate the PWM module
    OC1R = OC1RS = 0; //seting initial duty cycles (master and slave)
    OC2CON = 0x0006;//0b1110 activate the PWM module
    OC2R = OC2RS = 0; //seting initial duty cycles (master and slave)

}

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




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




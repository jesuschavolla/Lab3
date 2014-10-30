// ******************************************************************************************* //

// BY : Team 205: Jesus Chavolla, Uriel Garcia , Joshua Hurley

///////////////////////////////////////////////////////////////////////////////////////////////
// Include file for PIC24FJ64GA002 microcontroller. This include file defines
// MACROS for special function registers (SFR) and control bits within those
// registers.

#include "p24fj64ga002.h"
#include <stdio.h>
#include "lcd.h"
#include "ADC.h"
#include "PWM.h"


// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// Make sure "Configuration Bits set in code." option is checked in MPLAB.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.


_CONFIG1(WDTPS_PS32768 & FWPSA_PR128 & WINDIS_ON & FWDTEN_ON & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_ON);

// ******************************************************************************************* //
// Configuration bits for CONFIG2 settings.
// Make sure "Configuration Bits set in code." option is checked in MPLAB.

_CONFIG2(POSCMOD_NONE & I2C1SEL_PRI & IOL1WAY_ON & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_FRCDIV & SOSCSEL_SOSC & WUTSEL_LEG & IESO_ON);

// ******************************************************************************************* //

// ******************************************************************************************* //
int main(void)
{
    TRISBbits.TRISB5=1;
//    TRISBbits.TRISB8 = 0;
   
//    TRISBbits.TRISB10 = 0;
//    TRISBbits.TRISB3 = 0;
////
//    LATBbits.LATB10 = 1;
//    LATBbits.LATB3 = 1;

    int i=0;
    int state=0;
    int checking=0;
    int value=0;
    char ADV[4];
    char ADV2[4];
    char ADV3[4];
//    float percentage;
//    char duty[8];
     LCDInitialize();
    InADC();
    InPWM();



     RPOR1bits.RP2R= 0;
     RPOR2bits.RP5R = 0;
     RPOR1bits.RP3R = 18;//pot >> right
     RPOR5bits.RP10R = 19;//pot >> left

    
   
    while(1){

        // if(PORTBbits.RB5 == 0){
        //   }

        LCDClear();

      value = AnalogtoDigital();
      LCDMoveCursor(0,0);
      sprintf(ADV,"%4d", value);
       //LCDClear();
      //while(PORTBbits.RB5==0)
      //{
      
       LCDPrintString(ADV);
      // OC1RS = (1474 - (1474*(value-511)/511));
      // OC2RS = ((1474*value)/511);
       
       OC1RS = 1023- value;

       
       sprintf(ADV2,"%4d", OC1RS);
       LCDMoveCursor(1,0);

       LCDPrintString(ADV2);

       OC2RS = value;
      
       sprintf(ADV3,"%4d",OC2RS);
        LCDMoveCursor(1,4);
       LCDPrintString(ADV3);

       for(i=0;i<20000; i++);
    

      
    }
}

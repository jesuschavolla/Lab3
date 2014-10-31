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
volatile unsigned int state;
int main(void)
{
    TRISBbits.TRISB5=1;
CNEN2bits.CN27IE = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;


    int i=0;
    state=0;

   
   int value=0;
    double convert=0;
    char ADV[4];
    char ADV2[4];
    

     LCDInitialize();
    InADC();
    InPWM();
 
   
    while(1){

      

          MoveRobot(state);
        
       LCDClear();
         value = AnalogtoDigital();
         LCDMoveCursor(0,0);
          sprintf(ADV,"%4d", value);
          LCDPrintString(ADV);

        if(state==0 | state==2){
        
          LCDMoveCursor(1,0);
          LCDPrintString("0");
        LCDMoveCursor(1,4);
       LCDPrintString("0");

        }
        else if((state==1) |(state==2)){
       OC1RS = 1023- value;
       OC2RS = value;

            if(OC1RS>513 && OC2RS<511){

            convert=(OC2RS*100)/511;
           
            sprintf(ADV2,"%3.0f",convert);
            LCDMoveCursor(1,0);
            LCDPrintString(ADV2);


             LCDMoveCursor(1,4);
            LCDPrintString("100");
            }

            else if(OC1RS<510 && OC2RS>513){

            LCDMoveCursor(1,0);
            LCDPrintString("100");

            convert=(OC1RS*100)/511;
         

            sprintf(ADV2,"%3.0f",convert);
            
            LCDMoveCursor(1,4);
            LCDPrintString(ADV2);
            }

            else{
            LCDMoveCursor(1,0);
            LCDPrintString("100");
            LCDMoveCursor(1,4);
            LCDPrintString("100");
            }


       }

      

       for(i=0;i<20000; i++);
    

      
    }
}
    void __attribute__((interrupt, auto_psv)) _CNInterrupt(void) {
        while(PORTBbits.RB5==0);
        if(PORTBbits.RB5==1)
            state++;

        if(state==4)
            state=0;

//        MoveRobot(state);




        IFS1bits.CNIF = 0;

    }


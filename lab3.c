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
    int i=0;
    int state=0;
    int checking=0;
    int value=0;
    char ADV[8];
    float percentage;
    char duty[8];
     LCDInitialize();
    InADC();
    InPWM();

   
    while(1){

        LCDClear();

      value = AnalogtoDigital();
      sprintf(ADV,"%6d", value);
       LCDClear();
      //while(PORTBbits.RB5==0)
      //{
        LCDMoveCursor(0,0);
       LCDPrintString(ADV);
      // OC1RS = (1474 - (1474*(value-511)/511));
      // OC2RS = ((1474*value)/511);
       
       OC1RS = 1023 - value;
       OC2RS = value;
//       if(value >= 506 && value <= 516){
//           OC1RS = 1474;
//           OC2RS = 1474;
//           percentage=OC1RS/1474;
//       }
      //}
       
    }
}

// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "ADC.h"
#include "LCD.h"
// ******************************************************************************************* //

void InADC(){//intializes ADC

    AD1PCFG&= 0xFFFE;// select analog input AN0 to be connected to Jp 5
     
      AD1CON1 =0x20E4;  //  Auto converting after end of sampling
      AD1CON2 = 0x003C;//configures A/D voltage reference
      AD1CON3 = 0x0D01;
     

    AD1CSSL = 0x0000;        // no scanning
    AD1CHS = 0x0000;             //Configure input channels,

        
        AD1CON1bits.ADON = 1; // Turn on A/D

};

int AnalogtoDigital(){//function that returns the digital value
   
    AD1CHS = 0x0000;    // select analog input channel-AN0
    AD1CON1bits.SAMP = 1;// start sampling, automatic conversion will follow

   
    while(!AD1CON1bits.DONE);   // wait to complete the sampling
    AD1CON1bits.DONE = 0; // reset flag


    return(ADC1BUF0);//returns the ADC value



};
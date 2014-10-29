// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "ADC.h"
#include "LCD.h"
// ******************************************************************************************* //

void InADC(){

    AD1PCFG&= 0xFFFE;// select analog input pins//0b1111111111011111 ch5 Jp 5 is connected internally
    //AD1CON1 = 0x00E0;   //111 = Internal counter ends sampling and starts conversion (auto-convert)
      AD1CON1 =0x20E4;                  //  Auto converting after end of sampling
      AD1CON2 = 0x003C;
      AD1CON3 = 0x0D01;
      //AD1CON2 = 0x0000;
    //AD1CON3 = 0x1F01;  // sample time = 31Tad, Tad = 2*Tcy = 125 ns

    AD1CSSL = 0x0000;        // no scanning
    AD1CHS = 0x0000;             //Configure input channels,

        
        AD1CON1bits.ADON = 1; // Turn on A/D

};

int AnalogtoDigital(){//function that returns the digital value
   // int ADC=0;
   // int i=0;
    AD1CHS = 0x0000;    // select analog input channel-AN0
    AD1CON1bits.SAMP = 1;// start sampling, automatic conversion will follow

// wait to complete the sampling and then return value
// while(!AD1CON1bits.DONE);
//
//    AD1CON1bits.DONE=0;
//    AD1CON1bits.ASAM=0;
     AD1CON1bits.SAMP = 1;
    while(!AD1CON1bits.DONE);   // wait to complete the sampling
    AD1CON1bits.DONE = 0; // reset flag


    return(ADC1BUF0);



};
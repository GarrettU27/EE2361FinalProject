#include "xc.h"
#include "ADC.h"

void initADC(void) {
    AD1PCFGbits.PCFG2 = 0; //set AN2 to analog (leave AN0 and AN1 for possible analog reference)
    TRISBbits.TRISB0 = 1; //set AN2(RB0) as an input, not sure if needed yet
    AD1CHSbits.CH0SA = 0b00010; //set AN2 to positive input
    AD1CHSbits.CH0NA = 0b000; //leave negative input as V_REFL
    AD1CON2bits.VCFG = 0b000; //setting voltage reference to be V_DD and V_SS on chip for now, the output of the amp is a max of 2V and as it says it can easily be used with an ADC of 3.3V which this would be
    AD1CON3bits.ADCS = 0x00; //setting AD Conversion Clock to = TCY, but this is where prescaler is set
    AD1CON1bits.SSRC = 0b0111; //set so setting the SAMP starts sampling, and an internal counter ends sampling and starts conversion
    AD1CON3bits.SAMC = 0b11111; //this will determine how long we sample for currently. Set to 31 T_AD (ADC clock cycle, which is set equal to the internal clock cycle at the moment) at the moment
    AD1CON1bits.FORM = 0b01; //how the output is given. currently set to give an integer
    AD1CON2bits.SMPI = 0b0000; //how often a sample/convert should fire, current set for each sample/convert sequence
    //this also determines how many buffers are written to, the buffers are only written to right BEFORE the interrupt is called, and they are all written together. So if this is set to call an interrupt every 8th completion, 8 buffers will be written to.
    AD1CON1bits.ASAM = 1; //automatic sampling, which will be continuous
    AD1CON1bits.ADON = 1; //turn on A/D Converter

    _AD1IF = 0; //clear interrupt bit
    //this is where priiority of A/D would be set
}

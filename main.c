#include "xc.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled,
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

//this interrupt will be called after each sample/conversion completes
void __attribute__((interrupt, auto_psv)) _AD1Interrupt() {
    _AD1IF = 0;
    int result = ADC1BUF0; //this will capture the input
}

void initPic24(void) {
    //initializing A/D converter
    AD1PCFG = 0x0000; //setting all to analog for now, will change later
    AD1CON2bits.VCFG = 0b000; //setting voltage reference to be V_DD and V_SS on chip for now
    AD1CON3bits.ADCS = 0x00; //setting AD Conversion Clock to = TCY, but this is where prescaler is set
    AD1CON1bits.SSRC = 0b0111; //set so setting the SAMP starts sampling, and an internal counter ends sampling and starts conversion
    AD1CON3bits.SAMC = 0b11111; //this will determine how long we sample for currently. Set to 31 T_AD (ADC clock cycle, which is set equal to the internal clock cycle at the moment) at the moment
    AD1CON1bits.FORM = 0b01; //how the output is given. currently set to give an integer
    AD1CON2bits.SMPI = 0b0000; //how often a sample/convert should fire, current set for each sample/convert sequence
    //this also determines how many buffers are written to, the buffers are only written to right BEFORE the interrupt is called, and they are all written together. So if this is set to call an interrupt every 8th completion, 8 buffers will be written to.
    AD1CON1bits.ADON = 1; //turn on A/D Converter
}

void setup(void) {
    initPic24();
}

int main(void) {
    setup();

    while(1) {
        AD1CON1bits.SAMP = 1; //start sampling
    }
}
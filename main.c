#include "xc.h"
#include "projectLibrary.h"
#include "stdlib.h"

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
void __attribute__((interrupt, auto_psv)) _ADC1Interrupt() {
    _AD1IF = 0;
    putVal(ADC1BUF0); //this will capture the input
}

//ADC has higher priority than timer, so this should not be an issue
void __attribute__((interrupt, auto_psv)) _T1Interrupt() {
    _T1IF = 0;
//    volatile float write = ((255/1.23)*(3.3/1024)*getAvg())-(255/1.23)*1.22; //120;//((255/0.04)*(3.3/1024)*result)-160;
    volatile float write = abs((255/0.01)*((3.3/1024)*getAvg()-1.2246));
    writeColor((int)write, 0, 0);
}

void initPic24(void) {
    _RCDIV = 0;
    AD1PCFG = 0x9fff; //all digital
    TRISA = 0b1111111111111110;
    LATA = 0x0001;
}

void initTimer1(void) {
    T1CONbits.TON = 0;
    T1CONbits.TCKPS = 0b10; //1:64 prescaler
    PR1 = 24999; //100 ms
    _T1IE = 1;
    _T1IF = 0;
    T1CONbits.TON = 1;
}

void setup(void) {
    initPic24();
    initADC();
    initTimer1();
}

int main(void) {
    setup();

    while(1) {
        //sampling is automatic
    }
}
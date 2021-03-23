#include "xc.h"
#include "iLEDSource.h"
#include "iLED.h"

void readBits(int value) {
    int index = 8;
    int read_bit;

    while (index > 0) {
        read_bit = value & (1 << (index-1));
        if (read_bit) {
            write_1();
        }
        else {
            write_0();
        }
        index--;
    }
}

void writeColor(int r, int g, int b) {
    //the solution is just to mask along each in the correct order and
    //write out the streams. by far the easiest way to solve this

    readBits(r);
    readBits(g);
    readBits(b);

    LATA = 0x0000;
    delay_100us();
}
#include "circular_buffer.h"

#define BUFFER_SIZE 128

int avg = 0;
int tail = 0;
int buffer[BUFFER_SIZE];

void initBuffer(void) {
    //this is not required as a buffer initializes with 0s but whatever
    int index = 0;
    while (index < BUFFER_SIZE) {
        buffer[index] = 0;
        index++;
    }
}

void updateAvg() {
    int index = 0;
    unsigned long int sum = 0;
    while (index < BUFFER_SIZE) {
        sum += buffer[index];
        index++;
    }
    avg = sum/BUFFER_SIZE;
}

int getAvg() {
    return avg;
}

void putVal(int newValue) {
    buffer[tail] = newValue;
    updateAvg();
    tail = (tail+1) % BUFFER_SIZE;
}


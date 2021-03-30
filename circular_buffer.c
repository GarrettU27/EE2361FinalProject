#include "circular_buffer.h"

#define BUFFER_SIZE 1024

int avg = 0;
int tail = 0;
unsigned long int sum = 0;
int buffer[BUFFER_SIZE];

void initBuffer(void) {
    //this is not required as a buffer initializes with 0s but whatever
    int index = 0;
    while (index < BUFFER_SIZE) {
        buffer[index] = 0;
        index++;
    }
}

int getAvg() {
    return avg;
}

void putVal(int newValue) {
    //remove old value, add in new value and update the average
    sum -= buffer[tail];
    sum += newValue;
    avg = sum/BUFFER_SIZE;
    buffer[tail] = newValue;
    tail = (tail+1) % BUFFER_SIZE;
}


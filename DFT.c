#define _USE_MATH_DEFINES
#include <math.h>
#include "complex.h"

struct complex recentDFT;

float exponentValue(int k, int currentSample, int N) {
    return -(2*M_PI*k*currentSample)/N;
}

//k: frequency we are interested in
//N: # of samples
//samples: the actual samples
//freq: sample frequency
//NOTE: k must be LESS THAN freq/2
void DFT(int k, int N, float samples[], float freq) {
    struct complex sum = {0.0, 0.0};

    for (int i = 0; i < N; i++) {
        float angle = exponentValue(k, i, N);
        struct complex value = {samples[i]*cosf(angle), samples[i]*sinf(angle)};
        sum = add(sum, value);
    }

    sum.a *= 2;
    sum.b *= 2;

    recentDFT.a = sum.a/freq;
    recentDFT.b = sum.b/freq;
}

float returnDFTMag() {
    return magnitude(recentDFT);
}

float returnDFTPhase() {
    return phase(recentDFT);
}


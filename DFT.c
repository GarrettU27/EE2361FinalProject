#define _USE_MATH_DEFINES
#include <complex.h>
#include <math.h>

float _Complex recentDFT;

float exponentValue(int k, int currentSample, int N) {
    return -(2*M_PI*k*currentSample)/N;
}

//k: frequency we are interested in
//N: # of samples
//samples: the actual samples
//freq: sample frequency
//NOTE: k must be LESS THAN freq/2
void DFT(int k, int N, float samples[], float freq) {
    float _Complex sum = 0.0 + 0.0*I;

    for (int i = 0; i < N; i++) {
        float angle = exponentValue(k, i, N);
        float _Complex value = samples[i]*cosf(angle)+samples[i]*sinf(angle)*I;
        sum = sum + value;
    }

    sum = 2*sum;
    recentDFT = sum/freq;
}

float returnDFTMag() {
    return cabsf(recentDFT);
}

float returnDFTPhase() {
    return atan2f(cimagf(recentDFT), crealf(recentDFT));
}


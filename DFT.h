#ifndef DFT_H
#define	DFT_H

#ifdef	__cplusplus
extern "C" {
#endif

void DFT(int k, int N, float samples[], float freq);
double exponentValue(int k, int currentSample, int N);
float returnDFTMag();
float returnDFTPhase();

#ifdef	__cplusplus
}
#endif

#endif	/* ILED_H */

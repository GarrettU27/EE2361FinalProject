/* 
 * File:   iLED.h
 * Author: garre
 *
 * Created on March 23, 2021, 9:31 AM
 */

#ifndef ILED_H
#define	ILED_H

#ifdef	__cplusplus
extern "C" {
#endif

void readBits(int value);
void writeColor(int r, int g, int b);


#ifdef	__cplusplus
}
#endif

#endif	/* ILED_H */


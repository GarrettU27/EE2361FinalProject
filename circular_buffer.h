/*
 * File:   circular_buffer.h
 * Author: garre
 *
 * Created on March 26, 2021, 12:10 PM
 */

#ifndef CIRCULAR_BUFFER_H
#define	CIRCULAR_BUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

void initBuffer(void);
void updateAvg();
int getAvg();
void putVal(int newValue);


#ifdef	__cplusplus
}
#endif

#endif	/* CIRCULAR_BUFFER_H */


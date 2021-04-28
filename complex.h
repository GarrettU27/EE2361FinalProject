#ifndef COMPLEX_H
#define	COMPLEX_H

#ifdef	__cplusplus
extern "C" {
#endif

struct complex
{
    float a;
    float b;
};
void print(struct complex c);
float magnitude(struct complex c);
float phase(struct complex c);
struct complex add(struct complex c, struct complex d);


#ifdef	__cplusplus
}
#endif

#endif	/* ILED_H */

#include <math.h>
#include <stdio.h>

struct complex {
    float a;
    float b;
};

void print(struct complex c) {
    if (c.b >= 0) {
        printf("%f + %fj", c.a, c.b);
    }
    else {
        printf("%f - %fj", c.a, fabs(c.b));
    }
}

float magnitude(struct complex c) {
    return sqrtf(c.a*c.a + c.b*c.b);
}

float phase(struct complex c) {
    return atan2f(c.b, c.a);
}

struct complex add (struct complex c, struct complex d) {
    struct complex e = {c.a+d.a, c.b+d.b};
    return e;
}

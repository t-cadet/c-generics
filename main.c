#include <assert.h>
#include <stdio.h>

// could not find a way to simplify this
// because the preprocessor does not allow
// macros that contain preprocessor directives
// (cannot make a macro that contains includes etc)
#define vectype vecint
#define elemtype int
#include "vec.c"

#define vectype vecfloat
#define elemtype float
#include "vec.c"

typedef struct {
    int a;
    int b;
} pair;

#define vectype vecpair
#define elemtype pair
#include "vec.c"

int main() {

    // vec of int
    vecint v = vecintmake();
    assert(vecintisempty(&v));

    vecintpush(&v, 0);
    vecintpush(&v, 1);
    // vecintpush(&v, 1.5); // warning: implicit conversion from double to int
    assert(v.len == 2);

    assert(vecintpop(&v) == 1);
    assert(vecintpop(&v) == 0);
    assert(vecintisempty(&v));

    // vec of float
    vecfloat vf = vecfloatmake();
    vecfloatpush(&vf, 1.5);
    assert(vecfloatpop(&vf) == 1.5);

    // vec of custom type
    pair p = {};
    p.a = -5;
    p.b = 5;
    vecpair vp = vecpairmake();
    vecpairpush(&vp, p);
    pair poppedp = vecpairpop(&vp);
    assert(poppedp.a == p.a);
    assert(poppedp.b == p.b);
}

#ifdef vectype
#ifdef elemtype

#include <assert.h>
#include <stdlib.h>

#define concat_nx(a, b) a##b
#define concat(a, b) concat_nx(a, b)
// Note: C does not support overloads
// so we need to make function names
// unique for each type
#define fn(name) concat(vectype, name)

typedef struct {
    elemtype* data;
    int len;
    int cap;
} vectype;

vectype fn(make)() {
    vectype v;
    v.data = 0;
    v.len = 0;
    v.cap = 0;

    return v;
}

void fn(ensurecap)(vectype* v, int mincap) {
    if (v->cap < mincap) {
        int newcap = 2 * v->cap > mincap ? 2 * v->cap : mincap;
        
        elemtype* newdata = (elemtype*)malloc(newcap * sizeof(elemtype));
        assert(newdata);
        for (int i = 0; i < v->len; ++i) {
            newdata[i] = v->data[i];
        }        
        free(v->data);

        v->data = newdata;
        v->cap = newcap;
    }
}

int fn(isempty)(vectype* v) {
    return v->len == 0;
}

void fn(push)(vectype* v, elemtype value) {
    fn(ensurecap)(v, v->len+1);
    *(v->data+v->len) = value;
    ++v->len;
}

elemtype fn(pop)(vectype* v) {
    assert(!fn(isempty)(v));
    --v->len;
    return v->data[v->len];
}

#undef fn
#undef concat
#undef concat_nx
#undef elemtype
#undef vectype
#endif
#endif


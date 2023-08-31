#ifndef MACRO_H
#define MACRO_H

#define likely(x)       __builtin_expect((x), 1)
#define unlikely(x)     __builtin_expect((x), 0)
#define deref(type)     * (type *)
#define to0(x, type)    deref(type) x = (type) {0}  

#endif
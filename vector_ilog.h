#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CHUNK_SIZE 4

/* vector with small buffer optimization */

#define STRUCT_BODY(type)                                                  \
    struct {                                                               \
        size_t size : 54, on_heap : 1, capacity : 6, flag1 : 1, flag2 : 1, \
            flag3 : 1;                                                     \
        type *ptr;                                                         \
    }

#define NEXT_POWER_OF_2(s) \
    1 << (64 - __builtin_clzll(s)) //VV1

#define v(t, s, name, ...)                                              \
    (void) ((struct {                                                   \
        _Static_assert(s <= 8, "it is too big");                        \
        int dummy;                                                      \
    }){1});                                                             \
    union {                                                             \
        STRUCT_BODY(t);                                                 \
        struct {                                                        \
            size_t filler;                                              \
            t buf[NEXT_POWER_OF_2(s)];                                  \
        };                                                              \
    } name __attribute__((cleanup(vec_free))) = {.buf = {__VA_ARGS__}}; \
    name.size = sizeof((__typeof__(name.buf[0])[]){0, __VA_ARGS__}) /   \
                    sizeof(name.buf[0]) -                               \
                1;                                                      \
    name.capacity = sizeof(name.buf) / sizeof(name.buf[0])

#define vec_size(v) v.size
#define vec_capacity(v) __vec_capacity(&v)
static size_t inline __vec_capacity(void *vec)
{
    union {
        STRUCT_BODY(char);
        struct {
            size_t filler;
            char buf[];
        };
    } *v = vec;

    if (v->on_heap){
        if(v->capacity == 0) return 4;
        if(v->capacity == 1) return 6;
        if(v->capacity == 2) return 9;
        if(v->capacity == 3) return 13;
        if(v->capacity == 4) return 20;
        if(v->capacity == 5) return 30;
        if(v->capacity == 6) return 45;
        if(v->capacity == 7) return 68;
        if(v->capacity == 8) return 102;
        if(v->capacity == 9) return 153;
        if(v->capacity == 10) return 230;
        if(v->capacity == 11) return 345;
        if(v->capacity == 12) return 518;
        if(v->capacity == 13) return 778;
        if(v->capacity == 14) return 1167;
        return (size_t) (pow(1.5, v->capacity) * CHUNK_SIZE);
    }
    return CHUNK_SIZE;
}

#define vec_data(v) (v.on_heap ? v.ptr : v.buf) /* always contiguous buffer */

#define vec_elemsize(v) sizeof(v.buf[0])
#define vec_pos(v, n) vec_data(v)[n] /* lvalue */

#define vec_reserve(v, n) __vec_reserve(&v, n, vec_elemsize(v), vec_capacity(v))
#define vec_push_back(v, e)                                            \
    __vec_push_back(&v, &(__typeof__(v.buf[0])[]){e}, vec_elemsize(v), \
                    vec_capacity(v))

#define vec_pop_back(v) (void) (v.size -= 1) // VV2

/* This function attribute specifies function parameters that are not supposed
 * to be null pointers. This enables the compiler to generate a warning on
 * encountering such a parameter.
 */
#define NON_NULL __attribute__((nonnull))

static NON_NULL void vec_free(void *p)
{
    STRUCT_BODY(void) *s = p;
    if (s->on_heap)
        free(s->ptr);
}

static inline int ilog2(size_t n)
{
    return 64 - __builtin_clzll(n) - ((n & (n - 1)) == 0);
}

static int ilog_factor(size_t n){
    if (n <= 1) return 1;
    if (n <= 2) return 2;
    if (n <= 3) return 3;
    if (n <= 5) return 4;
	if (n <= 7) return 5;
	if (n <= 11) return 6;
	if (n <= 17) return 7;
	if (n <= 25) return 8;
	if (n <= 38) return 9;
	if (n <= 57) return 10;
	if (n <= 86) return 11;
	if (n <= 129) return 12;
	if (n <= 194) return 13;
	if (n <= 291) return 14;
	if (n <= 438) return 15;
	if (n <= 656) return 16;
	if (n <= 985) return 17;
	if (n <= 1167) return 18;
}

static NON_NULL void __vec_reserve(void *vec,
                                   size_t n,
                                   size_t elemsize,
                                   size_t capacity)
{
    union {
        STRUCT_BODY(void);
        struct {
            size_t filler;
            char buf[];
        };
    } *v = vec;

    if (n > capacity) {
        if (v->on_heap) {
            v->ptr = realloc(v->ptr,
                             elemsize * (size_t) ((pow(1.5,(v->capacity = ilog_factor(n/4))))* CHUNK_SIZE));
        } else {
            void *tmp =
                malloc(elemsize * (size_t) ((pow(1.5,(v->capacity = ilog_factor(n/4))))* CHUNK_SIZE));
            memcpy(tmp, v->buf, elemsize * v->size);
            v->ptr = tmp;
            v->on_heap = 1;
        }
    }
}

static NON_NULL void __vec_push_back(void *restrict vec,
                                     void *restrict e,
                                     size_t elemsize,
                                     size_t capacity)
{
    union {
        STRUCT_BODY(char);
        struct {
            size_t filler;
            char buf[];
        };
    } *v = vec;

    if (v->on_heap) {
        if (v->size == capacity)
            v->ptr = realloc(v->ptr, elemsize * (size_t) (pow(1.5,  ++v->capacity)*CHUNK_SIZE)); //VV3
        memcpy(&v->ptr[v->size++ * elemsize], e, elemsize);
    } else {
        if (v->size == capacity) {
            void *tmp =
                malloc(elemsize * (size_t)  (pow(1.5,v->capacity =  ilog_factor(v->size/4))*CHUNK_SIZE));
            memcpy(tmp, v->buf, elemsize * v->size);
            v->ptr = tmp;
            v->on_heap = 1;
            memcpy(&v->ptr[v->size++ * elemsize], e, elemsize);
        } else
            memcpy(&v->buf[v->size++ * elemsize], e, elemsize);
    }
}


#endif // VECTOR_H_INCLUDED

#ifndef PK_ARRAY_H
#define PK_ARRAY_H

#include "pk_defines.h"

enum {
    ARRAY_CAPACITY,
    ARRAY_LENGTH,
    ARRAY_STRIDE,
    ARRAY_FIELD_LENGTH
};

PK_API void* _array_create(u64 length, u64 stride);
PK_API void _array_destroy(void* array);

PK_API u64 _array_field_get(void* array, u64 field);
PK_API void _array_field_set(void* array, u64 field, u64 value);
PK_API void* _array_resize(void* array);
PK_API void* _array_push(void* array, const void* value_ptr);
PK_API void _array_pop(void* array, void* dest);
PK_API void* _array_pop_at(void* array, u64 index, void* dest);
PK_API void* _array_insert_at(void* array, u64 index, void* value_ptr);

#define ARRAY_DEFAULT_CAPACITY 1
#define ARRAY_RESIZE_FACTOR 2

#define ARRAY_CREATE(type) \
    _array_create(ARRAY_DEFAULT_CAPACITY, sizeof(type))

#define ARRAY_RESERVE(type, capacity) \
    _array_create(capacity, sizeof(type))

#define ARRAY_DESTROY(array) _array_destroy(array)

#define ARRAY_PUSH(array, value)           \
    {                                      \
        typeof(value) temp = value;        \
        array = _array_push(array, &temp); \
    }

#define ARRAY_POP(array, value_ptr) \
    _array_pop(array, value_ptr)

#define ARRAY_INSERT_AT(array, index, value)           \
    {                                                  \
        typeof(value) temp = value;                    \
        array = _array_insert_at(array, index, &temp); \
    }

#define ARRAY_POP_AT(array, index, value_ptr) \
    _array_pop_at(array, index, value_ptr)

#define ARRAY_CLEAR(array) \
    _array_field_set(array, ARRAY_LENGTH, 0)

#define ARRAY_CAPACITY(array) \
    _array_field_get(array, ARRAY_CAPACITY)

#define ARRAY_LENGHT(array) \
    _array_field_get(array, ARRAY_LENGTH)

#define ARRAY_STRIDE(array) \
    _array_field_get(array, ARRAY_STRIDE)

#define ARRAY_LENGTH_SET(array, value) \
    _array_field_set(array, ARRAY_LENGTH, value)

#endif // PK_ARRAY_H

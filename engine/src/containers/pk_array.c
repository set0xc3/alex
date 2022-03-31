#include "pk_array.h"

#include "core/pk_logger.h"
#include "core/pk_memory.h"

void* _array_create(u64 length, u64 stride) {
    u64 header_size = ARRAY_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* new_array = memory_allocate(header_size + array_size, MEMORY_TAG_ARRAY);
    memory_set(new_array, 0, header_size + array_size);
    new_array[ARRAY_CAPACITY] = length;
    new_array[ARRAY_LENGTH] = 0;
    new_array[ARRAY_STRIDE] = stride;
    return (void*)(new_array + ARRAY_FIELD_LENGTH);
}

void _array_destroy(void* array) {
    u64* header = (u64*)array - ARRAY_FIELD_LENGTH;
    u64 header_size = ARRAY_FIELD_LENGTH * sizeof(u64);
    u64 total_size = header_size + header[ARRAY_CAPACITY] * header[ARRAY_STRIDE];
    memory_free(header, total_size, MEMORY_TAG_ARRAY);
}

u64 _array_field_get(void* array, u64 field) {
    u64* header = (u64*)array - ARRAY_FIELD_LENGTH;
    return header[field];
}

void _array_field_set(void* array, u64 field, u64 value) {
    u64* header = (u64*)array - ARRAY_FIELD_LENGTH;
    header[field] = value;
}

void* _array_resize(void* array) {
    u64 length = ARRAY_LENGHT(array);
    u64 stride = ARRAY_STRIDE(array);
    void* temp = _array_create(
        (ARRAY_RESIZE_FACTOR * ARRAY_CAPACITY(array)),
        stride);
    memory_copy(temp, array, length * stride);

    _array_field_set(temp, ARRAY_LENGTH, length);
    _array_destroy(array);
    return temp;
}

void* _array_push(void* array, const void* value_ptr) {
    u64 length = ARRAY_LENGHT(array);
    u64 stride = ARRAY_STRIDE(array);
    if (length >= ARRAY_CAPACITY(array)) {
        array = _array_resize(array);
    }

    u64 addr = (u64)array;
    addr += (length * stride);
    memory_copy((void*)addr, value_ptr, stride);
    _array_field_set(array, ARRAY_LENGTH, length + 1);
    return array;
}

void _array_pop(void* array, void* dest) {
    u64 length = ARRAY_LENGHT(array);
    u64 stride = ARRAY_STRIDE(array);
    u64 addr = (u64)array;
    addr += ((length - 1) * stride);
    memory_copy(dest, (void*)addr, stride);
    _array_field_set(array, ARRAY_LENGTH, length - 1);
}

void* _array_pop_at(void* array, u64 index, void* dest) {
    u64 length = ARRAY_LENGHT(array);
    u64 stride = ARRAY_STRIDE(array);
    if (index >= length) {
        LOG_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }

    u64 addr = (u64)array;
    memory_copy(dest, (void*)(addr + (index * stride)), stride);

    // If not on the last element, snip out the entry and copy the rest inward.
    if (index != length - 1) {
        memory_copy(
            (void*)(addr + (index * stride)),
            (void*)(addr + ((index + 1) * stride)),
            stride * (length - index));
    }

    _array_field_set(array, ARRAY_LENGTH, length - 1);
    return array;
}

void* _array_insert_at(void* array, u64 index, void* value_ptr) {
    u64 length = ARRAY_LENGHT(array);
    u64 stride = ARRAY_STRIDE(array);
    if (index >= length) {
        LOG_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }
    if (length >= ARRAY_CAPACITY(array)) {
        array = _array_resize(array);
    }

    u64 addr = (u64)array;

    // If not on the last element, copy the rest outward.
    if (index != length - 1) {
        memory_copy(
            (void*)(addr + ((index + 1) * stride)),
            (void*)(addr + (index * stride)),
            stride * (length - index));
    }

    // Set the value at the index
    memory_copy((void*)(addr + (index * stride)), value_ptr, stride);

    _array_field_set(array, ARRAY_LENGTH, length + 1);
    return array;
}
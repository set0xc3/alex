#ifndef PK_MEMORY_H
#define PK_MEMORY_H

#include "pk_defines.h"

typedef enum memory_tag {
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

PK_API void memory_initialize();
PK_API void memory_shutdown();

PK_API void* memory_allocate(u64 size, memory_tag tag);
PK_API void memory_free(void* block, u64 size, memory_tag tag);
PK_API void* memory_zero(void* block, u64 size);
PK_API void* memory_copy(void* dest, const void* source, u64 size);
PK_API void* memory_set(void* dest, i32 value, u64 size);
PK_API char* get_memory_usage_str();

#endif  // PK_MEMORY_H

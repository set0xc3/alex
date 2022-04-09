#ifndef PK_MEMORY_H
#define PK_MEMORY_H

#include "pk_defines.h"

enum Memory_Tag
{
    MemoryTag_Unknown,
    MemoryTag_Array,
    MemoryTag_String,
    MemoryTag_Application,
    MemoryTag_Job,
    MemoryTag_Texture,
    MemoryTag_Material,
    MemoryTag_Renderer,
    MemoryTag_Game,
    MemoryTag_Transform,
    MemoryTag_Entity,
    MemoryTag_EntityNode,
    MemoryTag_Scene,
    
    MemoryTag_MaxTags
};

PK_API void memory_init();
PK_API void memory_shutdown();

PK_API void *memory_allocate(u64 size, Memory_Tag tag);
PK_API void memory_free(void *block, u64 size, Memory_Tag tag);
PK_API void *memory_copy(void *dest, const void *source, u64 size);
PK_API void *memory_set(void *dest, i32 value, u64 size);
PK_API char *get_memory_usage_str();

#endif

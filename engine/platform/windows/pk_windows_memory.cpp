#include "core/pk_logger.h"
#include "core/pk_memory.h"

#if PK_PLATFORM_WINDOWS

// TODO(parsecffo): Custom string lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Memory_Stats {
    u64 total_allocated;
    u64 tagged_allocations[MemoryTag_MaxTags];
};

global const char *memory_tag_strings[MemoryTag_MaxTags] = 
{
    "Unknown    ", "Array      ",  "String     ", "Applicaton", "Job        ",
    "Texture    ", "Material   ", "Renderer   ", "Game       ",
    "Transform  ", "Entity     ", "EntityNode", "Scene      "
};

global Memory_Stats stats;

void 
memory_init() 
{ 
    memory_set(&stats, 0, sizeof(stats)); 
}

void 
memory_shutdown() 
{
    
}

void 
*memory_allocate(u64 size, Memory_Tag tag) 
{
    if (tag == MemoryTag_Unknown) 
    {
        LOG_WARN("memory_allocate called using MemoryTag_Unknown. Re-class  this allocation.");
    }
    
    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;
    
    // TODO(parsecffo): Memory alignment
    void *block = malloc(size);
    memory_set(block, 0, size);
    return block;
}

void 
memory_free(void *block, u64 size, Memory_Tag tag) 
{
    if (tag == MemoryTag_Unknown) 
    {
        LOG_WARN("memory_free called using MemoryTag_Unknown. Re-class this allocation.");
    }
    
    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;
    
    // TODO(parsecffo): Memory alignment
    free(block);
}

void 
*memory_copy(void *dest, const void *source, u64 size) 
{
    return memcpy(dest, source, size);
}

void 
*memory_set(void *dest, i32 value, u64 size) 
{
    return memset(dest, value, size);
}

char *get_memory_usage_str() 
{
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;
    
    char buffer[8000] = "System memory use (tagged):\n";
    u64 offset = strlen(buffer);
    for (u32 i = 0; i < MemoryTag_MaxTags; ++i) 
    {
        char unit[4] = "XiB";
        f32 amount = 1.0f;
        if (stats.tagged_allocations[i] >= gib) 
        {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (float)gib;
        } 
        else if (stats.tagged_allocations[i] >= mib) 
        {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (float)mib;
        } 
        else if (stats.tagged_allocations[i] >= kib) 
        {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (float)kib;
        } 
        else 
        {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)stats.tagged_allocations[i];
        }
        
        i32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }
    char *out_string = _strdup(buffer);
    return out_string;
}

#endif
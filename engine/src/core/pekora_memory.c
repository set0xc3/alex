#include "pekora_memory.h"

// TODO(parsecffo): Custom string lib
#include <stdio.h>
#include <string.h>

#include "core/pekora_logger.h"
#include "platform/pekora_platform.h"

struct memory_stats {
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

global const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "};

global struct memory_stats stats;

void initialize_memory() {
    platform_zero_memory(&stats, sizeof(stats));
}

void shutdown_memory() {
}

void* pekora_allocate(u64 size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("pekora_allocate called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
    }

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    // TODO(parsecffo): Memory alignment
    void* block = platform_allocate(size, false);
    platform_zero_memory(block, size);
    return block;
}

void pekora_free(void* block, u64 size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("pekora_free called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    // TODO(parsecffo): Memory alignment
    platform_free(block, false);
}

void* pekora_zero_memory(void* block, u64 size) {
    return platform_zero_memory(block, size);
}

void* pekora_copy_memory(void* dest, const void* source, u64 size) {
    return platform_copy_memory(dest, source, size);
}

void* pekora_set_memory(void* dest, i32 value, u64 size) {
    return platform_set_memory(dest, value, size);
}

char* get_memory_usage_str() {
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    char buffer[8000] = "System memory use (tagged):\n";
    u64 offset = strlen(buffer);
    for (u32 i = 0; i < MEMORY_TAG_MAX_TAGS; ++i) {
        char unit[4] = "XiB";
        f32 amount = 1.0f;
        if (stats.tagged_allocations[i] >= gib) {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (float)gib;
        } else if (stats.tagged_allocations[i] >= mib) {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (float)mib;
        } else if (stats.tagged_allocations[i] >= kib) {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (float)kib;
        } else {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }
    char* out_string = _strdup(buffer);
    return out_string;
}
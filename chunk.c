#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk *chunk) {
        chunk->count = 0;
        chunk->capacity = 0;
        chunk->code = NULL;
        chunk->lines = NULL;
        init_varray(&chunk->constants);
}

void free_chunk(Chunk *chunk) {
        reallocate(chunk->code, sizeof(uint8_t)*chunk->capacity, 0);
        reallocate(chunk->lines, sizeof(int)*chunk->capacity, 0);
        free_varray(&chunk->constants);
        init_chunk(chunk);
}

void write_chunk(Chunk *chunk, uint8_t byte, int line) {
        if (chunk->capacity == chunk->count) {
                int old_capacity = chunk->capacity;
                chunk->capacity = (old_capacity < 8) ? 8 : old_capacity * 2;
                chunk->code = (uint8_t*)reallocate(chunk->code,
                                                   sizeof(uint8_t) * old_capacity,
                                                   sizeof(uint8_t) * chunk->capacity);
                chunk->lines = (int*)reallocate(chunk->lines,
                                                sizeof(int) * old_capacity,
                                                sizeof(int) * chunk->capacity);
        }

        chunk->code[chunk->count] = byte;
        chunk->lines[chunk->count] = line;
        chunk->count++;
}

int add_constant(Chunk *chunk, Value value) {
        write_varray(&chunk->constants, value);
        return chunk->constants.count - 1;
}

#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

typedef struct {
        Chunk *chunk;
        uint8_t *ip; /* instruction pointer */
        Value stack[256];
        Value *stack_top;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void init_VM();
void free_VM();
static void reset_stack();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif

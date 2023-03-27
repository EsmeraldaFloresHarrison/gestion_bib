#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    STACK_INT,
    STACK_CHAR,
    STACK_FLOAT
} DataType;
typedef struct Stack {
    DataType type;
    size_t size;
    void* data;
    void* top;
} Stack;

Stack stackCreate(size_t size, DataType type){
    size_t EffectiveSize = 0;
    if(type == STACK_INT) EffectiveSize = size * sizeof(int);
    else if(type == STACK_CHAR) EffectiveSize = size * sizeof(char);
    else if(type == STACK_FLOAT) EffectiveSize = size * sizeof(float);
    Stack s = {
        .type = type,
        .size = size,
        .data = malloc(EffectiveSize),
        .top = NULL
    };
    return s;
}
void stackFree(Stack* s, void* elem) {
    free(s->data);
    s->data = NULL;
}
int main(int argc, char* argv[]) {
    Stack s = stackCreate(10,STACK_INT);
    ((int*)s.data)[0] = 64;
    s.top = ((int*)s.data) + 0;

    ((int*) s.data)[1] = 128;
    s.top = ((int*)s.data) + 1;
    return 0;
}
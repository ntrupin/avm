//
// Created by Noah Trupin on 9/21/20.
//

#ifndef GIANT_STACK_H
#define GIANT_STACK_H

#include <stdlib.h>

#include "value.h"

typedef struct {
    uint64_t size;
    uint64_t count;
    avm_value **stack;
} avm_stack;

avm_stack *avm_stack_make();
void avm_stack_free(avm_stack *);
void avm_stack_push(avm_stack *, avm_value *);
avm_value *avm_stack_pop(avm_stack *);

#endif //GIANT_STACK_H

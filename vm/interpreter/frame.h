//
// Created by Noah Trupin on 9/21/20.
//

#ifndef GIANT_FRAME_H
#define GIANT_FRAME_H

#include <stdio.h>
#include <stdlib.h>

#include "../loader/class.h"
#include "vars.h"
#include "stack.h"

typedef struct {
    avm_class *class;
    uint32_t ip;
    avm_method_attribute *code;
    avm_vars *locals;
    avm_stack *stack;
} avm_frame;

avm_frame *avm_frame_make(avm_class *, char *);
void avm_frame_free(avm_frame *);
void avm_frame_exec(avm_frame *);

#endif //GIANT_FRAME_H

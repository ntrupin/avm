//
// Created by Noah Trupin on 9/21/20.
//

#ifndef GIANT_FRAME_H
#define GIANT_FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../loader/class.h"
#include "vars.h"
#include "value.h"
#include "stack.h"

typedef struct {
    avm_class *class;
    uint32_t ip;
    avm_method *method;
    avm_vars *locals;
    avm_stack *stack;
} avm_frame;

avm_frame *avm_frame_make(avm_class *, char *);
void avm_frame_free(avm_frame *);
avm_value *avm_frame_exec(avm_frame *, uint8_t argc, ...);

#endif //GIANT_FRAME_H

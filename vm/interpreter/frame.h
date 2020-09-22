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

enum {
    AOP_NOP=0x00,
    AOP_RETURN=0x01, AOP_IRETURN=0x02, AOP_DRETURN=0x03, AOP_SRETURN=0x04, AOP_ARETURN=0x05, AOP_RRETURN=0x06, AOP_RETURN2=0x07, AOP_RETURN3=0x08,
    AOP_LOAD=0x0A, AOP_ILOAD=0x0B, AOP_DLOAD=0x0C,
};
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

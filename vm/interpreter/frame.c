//
// Created by Noah Trupin on 9/21/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "frame.h"
#include "vars.h"
#include "stack.h"
#include "../loader/class.h"
#include "../loader/methods/methods.h"
#include "../loader/methods/attributes.h"

avm_value *avm_frame_exec_return(avm_frame *frame, avm_method_attribute *code)
{
    uint8_t op = code->data[frame->ip];
    switch (op) {
        case AOP_RETURN: {
            avm_value *a = avm_value_make(AVM_VOID);
            if (frame->stack->count > 0) {
                printf("error: misaligned stack in function %s", frame->method->name->value);
                exit(1);
            }
#if DEBUG
            printf("RETURN VOID\n");
#endif
            return a;
        }
        case AOP_IRETURN: {
            avm_value *a = avm_stack_pop(frame->stack);
            if (a->tag != AVM_INT) {
                printf("error: expected int\n");
                exit(1);
            }
            if (frame->stack->count > 0) {
                printf("error: misaligned stack in function %s\n", frame->method->name->value);
                exit(1);
            }
#if DEBUG
            printf("RETURN %d\n", a->avm_int);
#endif
            return a;
        }
        default:
            printf("error: invalid return byte 0x%02x\n", op);
            exit(1);
    }
}

avm_value *avm_frame_exec_load(avm_frame *frame, avm_method_attribute *code)
{
    uint8_t op = code->data[frame->ip];
    switch (op) {
        case AOP_ILOAD: {
            uint16_t index = (
                    ((uint16_t)code->data[++frame->ip] << 8) |
                    ((uint16_t)code->data[++frame->ip])
            );
            avm_constpool_utf8 *name = avm_constpool_resolve(frame->class->constpool, index);
            avm_value *a = avm_vars_read(frame->locals, name->value);
            if (a->tag != AVM_INT) {
                printf("error: expected int\n");
                exit(1);
            }
            avm_stack_push(frame->stack, a);
#if DEBUG
            printf("ILOAD %d\n", a->avm_int);
#endif
            break;
        }
        default:
            printf("error: invalid load byte 0x%02x\n", op);
            exit(1);
    }
}

avm_value *avm_frame_exec(avm_frame *frame, uint8_t argc, ...)
{
    va_list args;
    va_start(args, argc);
    uint8_t i;
    for (i=0;i<argc;i++) {
        avm_vars_insert(
            frame->locals,
            va_arg(args, char *),
            va_arg(args, avm_value *)
            );
    }
    va_end(args);
    avm_method_attribute *code = avm_method_attributes_resolve(frame->method->attrs, "code");
    for (;frame->ip<code->len;frame->ip++) {
        uint8_t op = code->data[frame->ip];
#if DEBUG
        printf("\t | 0x%04x => ", frame->ip);
#endif
        switch (op) {
            case AOP_NOP: {
#if DEBUG
                printf("NOP\n");
#endif
                break;
            }
            case AOP_RETURN ... AOP_RETURN3:
                return avm_frame_exec_return(frame, code);
            case AOP_LOAD ... AOP_DLOAD:
                avm_frame_exec_load(frame, code);
                break;
            default: {
                printf("error: invalid byte 0x%02x\n", op);
                exit(1);
            }
        }
    }
    printf("Code execution should not reach here. Please file an issue at <https://github.com/ntrupin/avm/issues>\n");
    exit(1);
}

avm_frame *avm_frame_make(avm_class *class, char *method)
{
    avm_frame *f = malloc(sizeof(avm_frame));
    if (!f) {
        printf("error allocating avm_frame");
        exit(1);
    }
    f->ip = 0;
    f->class = class;
    f->method = avm_methods_resolve(class->methods, method);
    f->stack = avm_stack_make();
    f->locals = avm_vars_make();
    return f;
}

void avm_frame_free(avm_frame *f)
{
    avm_vars_free(f->locals);
    avm_stack_free(f->stack);
    if (f) free(f);
}
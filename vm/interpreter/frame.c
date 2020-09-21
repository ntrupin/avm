//
// Created by Noah Trupin on 9/21/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "frame.h"
#include "vars.h"
#include "stack.h"
#include "../loader/class.h"
#include "../loader/methods/methods.h"
#include "../loader/methods/attributes.h"

void avm_frame_exec(avm_frame *frame)
{
#if DEBUG
    printf("| trace\n");
#endif
    for (;frame->ip<frame->code->len;frame->ip++) {
        uint8_t op = frame->code->data[frame->ip];
#if DEBUG
        printf("\t | 0x%04x => ", frame->ip);
#endif
        switch (op) {
            case 0x00: {
#if DEBUG
                printf("NOP\n");
#endif
                break;
            }
            case 0x01: {
                avm_value *a = avm_value_make(AVM_INT);
                a->avm_int = frame->code->data[++frame->ip];
#if DEBUG
                printf("PUSH 0x%04x\n", a->avm_int);
#endif
                avm_stack_push(frame->stack, a);
                break;
            }
            case 0x02: {
                avm_value *a = avm_stack_pop(frame->stack);
                avm_value *b = avm_stack_pop(frame->stack);
                avm_value *c = avm_value_make(AVM_INT);
                c->avm_int = a->avm_int + b->avm_int;
                avm_stack_push(frame->stack, c);
#if DEBUG
                printf("ADD 0x%04x, 0x%04x -> 0x%04x\n", a->avm_int, b->avm_int, c->avm_int);
#endif
                avm_value_free(a);
                avm_value_free(b);
                break;
            }
            default: break;
        }
    }
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
    avm_method *main = avm_methods_resolve(class->methods, method);
    f->code = avm_method_attributes_resolve(main->attrs, "code");
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
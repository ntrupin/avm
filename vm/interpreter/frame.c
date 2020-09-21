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
    for (;frame->ip<frame->code->len;frame->ip++) {
        uint8_t op = frame->code->data[frame->ip];
#if DEBUG
        printf("OP: 0x%02x\n", op);
#endif
        switch (op) {
            case 0x00:
                printf("NOP\n");
                break;
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
    if (f->locals) free(f->locals);
    if (f->stack) free(f->stack);
    if (f) free(f);
}
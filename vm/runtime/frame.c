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
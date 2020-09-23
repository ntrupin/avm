//
// Created by Noah Trupin on 9/21/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

void avm_stack_push(avm_stack *s, avm_value *v)
{
    if (s->count + 1 >= s->size) {
        s->size *= 2;
        s->stack = realloc(s->stack, s->size * sizeof(avm_value *));
        if (!s->stack) {
            printf("error reallocating avm_stack");
            exit(1);
        }
    }
    s->stack[s->count++] = v;
}

avm_value *avm_stack_pop(avm_stack *s)
{
    avm_value *r = s->stack[--s->count];
    if (!r) {
        printf("error popping from avm_stack");
        exit(1);
    }
    if (s->count < s->size / 2) {
        s->size /= 2;
        s->stack = realloc(s->stack, s->size+1);
        if (!s->size) {
            printf("error reallocating avm_stack");
            exit(1);
        }
    }
    return r;
}

avm_stack *avm_stack_make()
{
    avm_stack *s = malloc(sizeof(avm_stack));
    if (!s) {
        printf("error allocating avm_stack");
        exit(1);
    }
    s->size = 8;
    s->count = 0;
    s->stack = malloc(sizeof(avm_value *) * 8);
    if (!s->stack) {
        printf("error allocating avm_stack");
        exit(1);
    }
    return s;
}

void avm_stack_free(avm_stack *s)
{
#if DEBUG
    printf("| stack\n");
#endif
    while (s->count>0) {
        avm_value *a = avm_stack_pop(s);
#if DEBUG
        printf("\t| => ");
        switch (a->tag) {
            case AVM_VOID:
                printf("void\n");
                break;
            case AVM_INT:
                printf("%d\n", a->avm_int);
                break;
            case AVM_DOUBLE:
                printf("%f\n", a->avm_double);
                break;
            default: break;
        }
#endif
        avm_value_free(a);
    }
    if (s) free(s);
}
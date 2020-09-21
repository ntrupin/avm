//
// Created by Noah Trupin on 9/21/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "value.h"

avm_value *avm_value_make(uint8_t tag)
{
    avm_value *v = malloc(sizeof(avm_value *));
    if (!v) {
        printf("error allocating avm_value");
        exit(1);
    }
    v->tag = tag;
    return v;
}

void avm_value_free(avm_value *v)
{
    if (v) free(v);
}
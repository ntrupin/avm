//
// Created by Noah Trupin on 9/19/20.
//

#ifndef GIANT_METHODPOOL_METHOD_H
#define GIANT_METHODPOOL_METHOD_H

#include <stdlib.h>
#include <stdio.h>

#include "../constpool/constpool.h"
#include "../constpool/utf8.h"
#include "attributes.h"

typedef struct {
    uint16_t flags;
    avm_constpool_utf8 *name;
    avm_constpool_utf8 *desc;
    avm_method_attributes *attrs;
    uint8_t arity;
    uint8_t *args;
    uint8_t ret;
} avm_method;

avm_method *avm_method_make(FILE *, avm_constpool *);
void avm_method_free(avm_method *, uint16_t);

#endif //GIANT_METHOD_H

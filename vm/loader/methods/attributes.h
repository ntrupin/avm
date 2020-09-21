//
// Created by Noah Trupin on 9/19/20.
//

#ifndef GIANT_ATTRIBUTES_H
#define GIANT_ATTRIBUTES_H

#include <stdlib.h>
#include <stdio.h>

#include "attribute.h"
#include "../constpool/constpool.h"

typedef struct {
    uint16_t len;
    avm_method_attribute **attrs;
} avm_method_attributes;

avm_method_attributes *avm_method_attributes_make(FILE *, avm_constpool *);
void avm_method_attributes_free(avm_method_attributes *);
avm_method_attribute *avm_method_attributes_resolve(avm_method_attributes *, char *);

#endif //GIANT_ATTRIBUTES_H

//
// Created by Noah Trupin on 9/19/20.
//

#ifndef GIANT_ATTRIBUTE_H
#define GIANT_ATTRIBUTE_H

#include <stdlib.h>
#include <stdio.h>

#include "../constpool/utf8.h"
#include "../constpool/constpool.h"

typedef struct {
    avm_constpool_utf8 *name;
    uint64_t len;
    uint8_t *data;
} avm_method_attribute;

avm_method_attribute *avm_method_attribute_make(FILE *, avm_constpool *);
void avm_method_attribute_free(avm_method_attribute *);

#endif //GIANT_ATTRIBUTE_H

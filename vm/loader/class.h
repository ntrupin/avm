//
// Created by Noah Trupin on 9/14/20.
//

#ifndef GIANT_CLASS_H
#define GIANT_CLASS_H

#include <stdio.h>

#include "constpool/constpool.h"
#include "methods/methods.h"
#include "constpool/utf8.h"

typedef struct {
    uint16_t flags;
    avm_constpool_utf8 *name;
    avm_constpool_utf8 *super;
    avm_constpool *constpool;
    avm_methods *methods;
} avm_class;

avm_class *avm_class_make(FILE *);
void avm_class_free(avm_class *c);

#endif //GIANT_CLASS_H

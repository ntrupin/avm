//
// Created by Noah Trupin on 9/19/20.
//

#ifndef GIANT_METHODS_H
#define GIANT_METHODS_H

#include <stdlib.h>
#include <stdio.h>

#include "method.h"
#include "../constpool/constpool.h"

typedef struct {
    uint16_t len;
    avm_method **methods;
} avm_methods;

avm_methods *avm_methods_make(FILE *, avm_constpool *);
void avm_methods_free(avm_methods *);

#endif //GIANT_METHODS_H

//
// Created by Noah Trupin on 9/17/20.
//

#ifndef GIANT_CONSTPOOL_METHOD_H
#define GIANT_CONSTPOOL_METHOD_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    uint16_t class;
    uint16_t nametype;
} avm_constpool_method;

avm_constpool_method *avm_constpool_method_make(FILE *);
void avm_constpool_method_free(avm_constpool_method *);

#endif //GIANT_METHOD_H

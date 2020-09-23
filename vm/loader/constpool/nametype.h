//
// Created by Noah Trupin on 9/18/20.
//

#ifndef GIANT_NAMETYPE_H
#define GIANT_NAMETYPE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    uint16_t name;
    uint16_t type;
    uint8_t arity;
} avm_constpool_nametype;

avm_constpool_nametype *avm_constpool_nametype_make(FILE *);
void avm_constpool_nametype_free(avm_constpool_nametype *);

#endif //GIANT_NAMETYPE_H

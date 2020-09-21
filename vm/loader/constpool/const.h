//
// Created by Noah Trupin on 9/14/20.
//

#ifndef GIANT_CONST_H
#define GIANT_CONST_H

#include "utf8.h"
#include "string.h"
#include "method.h"
#include "nametype.h"

typedef struct {
    uint8_t tag;
    union {
        avm_constpool_utf8 *utf8;
        avm_constpool_string *string;
        avm_constpool_method *method;
        avm_constpool_nametype *nametype;
    };
} avm_constpool_const;

avm_constpool_const *avm_constpool_const_make(FILE *);
void avm_constpool_const_free(avm_constpool_const *, uint16_t);

#endif //GIANT_CONST_H

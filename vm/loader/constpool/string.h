//
// Created by Noah Trupin on 9/14/20.
//

#ifndef GIANT_STRING_H
#define GIANT_STRING_H

#include "utf8.h"

typedef struct {
    uint16_t index;
} avm_constpool_string;

avm_constpool_string *avm_constpool_string_make(FILE *);
void avm_constpool_string_free(avm_constpool_string *s);

#endif //GIANT_STRING_H

//
// Created by Noah Trupin on 9/21/20.
//

#ifndef GIANT_VALUE_H
#define GIANT_VALUE_H

#include <stdlib.h>

enum {
    AVM_VOID=0,
    AVM_INT=1,
    AVM_DOUBLE=2,
};

typedef struct {
    uint8_t tag;
    union {
        int avm_int;
        double avm_double;
    };
} avm_value;

avm_value *avm_value_make(uint8_t);
void avm_value_free(avm_value *);

#endif //GIANT_VALUE_H

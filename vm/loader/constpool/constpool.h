//
// Created by Noah Trupin on 9/14/20.
//

#ifndef GIANT_CONSTPOOL_H
#define GIANT_CONSTPOOL_H

#include "const.h"
#include "utf8.h"

typedef struct {
    uint16_t len;
    avm_constpool_const **consts;
} avm_constpool;

avm_constpool *avm_constpool_make(FILE *);
void avm_constpool_free(avm_constpool *);
avm_constpool_utf8 *avm_constpool_resolve(avm_constpool *, uint16_t);

#endif //GIANT_CONSTPOOL_H

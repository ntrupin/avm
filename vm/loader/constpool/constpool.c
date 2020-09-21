//
// Created by Noah Trupin on 9/14/20.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "constpool.h"
#include "utf8.h"
#include "const.h"
#include "../loader.h"

avm_constpool *avm_constpool_make(FILE *f)
{
    avm_constpool *cp = malloc(sizeof(avm_constpool));
    uint16_t len = lod2(f);
    avm_constpool_const **consts = malloc(len * sizeof(avm_constpool_const *));
    if (!cp || !consts) {
        printf("Error allocating avm_constpool");
        exit(1);
    }
    uint16_t i;
    for (i=0;i<len;i++) {
        consts[i] = avm_constpool_const_make(f);
    }
    cp->len = len;
    cp->consts = consts;
    return cp;
}

void avm_constpool_free(avm_constpool *cp)
{
#if DEBUG
    printf("\t| constpool \n");
#endif
    uint16_t i;
    for (i=0;i<cp->len;i++) {
        avm_constpool_const_free(cp->consts[i], i);
    }
    if (cp) free(cp);
}

avm_constpool_utf8 *avm_constpool_resolve(avm_constpool *cp, uint16_t index)
{
    if (cp->consts[index]->tag == 0x01) {
        return cp->consts[index]->utf8;
    }
    printf("Error resolving string at index %d", index);
    exit(1);
}
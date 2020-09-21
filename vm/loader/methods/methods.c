//
// Created by Noah Trupin on 9/19/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "method.h"
#include "methods.h"
#include "../constpool/constpool.h"
#include "../loader.h"

avm_methods *avm_methods_make(FILE *f, avm_constpool *cp)
{
    avm_methods *mp = malloc(sizeof(avm_methods));
    uint16_t len = lod2(f);
    avm_method **methods = malloc(len * sizeof(avm_method *));
    if (!mp || !methods) {
        printf("Error allocating avm_methods");
        exit(1);
    }
    uint16_t i;
    for (i=0;i<len;i++) {
        methods[i] = avm_method_make(f, cp);
    }
    mp->len = len;
    mp->methods = methods;
    return mp;
}

void avm_methods_free(avm_methods *mp)
{
#if DEBUG
    printf("\t| methods \n");
#endif
    uint16_t i;
    for (i=0;i<mp->len;i++) {
        avm_method_free(mp->methods[i], i);
    }
    if (mp) free(mp);
}
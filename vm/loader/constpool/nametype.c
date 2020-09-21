//
// Created by Noah Trupin on 9/18/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "nametype.h"
#include "../loader.h"

avm_constpool_nametype *avm_constpool_nametype_make(FILE *f)
{
    avm_constpool_nametype *n = malloc(sizeof(avm_constpool_nametype));
    if (!n) {
        printf("Error allocating string");
        exit(1);
    }
    n->name = lod2(f);
    n->type = lod2(f);
    return n;
}

void avm_constpool_nametype_free(avm_constpool_nametype *n)
{
#if DEBUG
    printf("nametype[name at: 0x%02x, type at: 0x%02x]\n", n->name, n->type);
#endif
    if (n) free(n);
}
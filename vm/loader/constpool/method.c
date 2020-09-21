//
// Created by Noah Trupin on 9/17/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "method.h"
#include "constpool.h"
#include "../loader.h"

avm_constpool_method *avm_constpool_method_make(FILE *f)
{
    avm_constpool_method *m = malloc(sizeof(avm_constpool_method));
    if (!m) {
        printf("Error allocating string");
        exit(1);
    }
    m->class = lod2(f);
    m->nametype = lod2(f);
    return m;
}

void avm_constpool_method_free(avm_constpool_method *m)
{
#if DEBUG
    printf("method[class at: 0x%02x, name+type at: 0x%02x]\n", m->class, m->nametype);
#endif
    if (m) free(m);
}
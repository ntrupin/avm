//
// Created by Noah Trupin on 9/14/20.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "class.h"
#include "loader.h"
#include "constpool/constpool.h"
#include "methods/methods.h"

avm_class *avm_class_make(FILE *f)
{
    avm_class *c = malloc(sizeof(avm_class));
    if (!c) {
        printf("Error allocating avm_class");
        exit(1);
    }
    c->constpool = avm_constpool_make(f);
    c->flags = lod2(f);
    c->name = avm_constpool_resolve(c->constpool, lod2(f));
    c->super = avm_constpool_resolve(c->constpool, lod2(f));
    c->methods = avm_methods_make(f, c->constpool);
    return c;
}

void avm_class_free(avm_class *c)
{
#if DEBUG
    printf("| class %s: %s\n",
           c->name->value,
           c->super->value
    );
#endif
    avm_methods_free(c->methods);
    avm_constpool_free(c->constpool);
    if (c) free(c);
}
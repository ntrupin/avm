//
// Created by Noah Trupin on 9/19/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "method.h"
#include "attributes.h"
#include "../loader.h"
#include "../constpool/constpool.h"
#include "../constpool/method.h"
#include "../constpool/nametype.h"
#include "../../runtime/value.h"

uint8_t avm_method_type(uint8_t value)
{
    switch (value) {
        case 'I':
            return AVM_INT;
        default: return 0;
    }
}

avm_method *avm_method_make(FILE *f, avm_constpool *cp)
{
    avm_method *m = malloc(sizeof(avm_method));
    if (!m) {
        printf("Error allocating method");
        exit(1);
    }
    m->flags = lod2(f);
    avm_constpool_method *cpm = cp->consts[lod2(f)]->method;
    avm_constpool_nametype *nt = cp->consts[cpm->nametype]->nametype;
    m->name = avm_constpool_resolve(cp, nt->name);
    m->desc = avm_constpool_resolve(cp, nt->type);
    m->attrs = avm_method_attributes_make(f, cp);
    m->arity = nt->arity;
    uint8_t i;
    m->args = malloc(sizeof(uint8_t) * m->arity);
    if (!m->args) {
        printf("Error allocating method types");
        exit(1);
    }
    for (i=0;i<m->arity;i++) {
        m->args[i] = avm_method_type(m->desc->value[i]);
    }
    m->ret = m->desc->value[i] == '-'
            ? avm_method_type(m->desc->value[++i])
            : AVM_VOID;
    return m;
}

void avm_method_free(avm_method *m, uint16_t i)
{
#if DEBUG
    printf("\t\t| 0x%04x => method[name: \"%s\", type: \"%s\"]\n", i, m->name->value, m->desc->value);
#endif
    avm_method_attributes_free(m->attrs);
    if (m) free(m);
}
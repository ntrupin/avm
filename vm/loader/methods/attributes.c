//
// Created by Noah Trupin on 9/19/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "attributes.h"
#include "attribute.h"
#include "../constpool/constpool.h"
#include "../loader.h"

avm_method_attributes *avm_method_attributes_make(FILE *f, avm_constpool *cp)
{
    avm_method_attributes *ats = malloc(sizeof(avm_method_attributes));
    uint16_t len = lod2(f);
    avm_method_attribute **attrs = malloc(len * sizeof(avm_method_attribute *));
    if (!ats || !attrs) {
        printf("Error allocating avm_method_attributes");
        exit(1);
    }
    uint16_t i;
    for (i=0;i<len;i++) {
        attrs[i] = avm_method_attribute_make(f, cp);
    }
    ats->len = len;
    ats->attrs = attrs;
    return ats;
}

void avm_method_attributes_free(avm_method_attributes *ats)
{
    uint16_t i;
    for (i=0;i<ats->len;i++) {
        avm_method_attribute_free(ats->attrs[i]);
    }
    if (ats) free(ats);
}

avm_method_attribute *avm_method_attributes_resolve(avm_method_attributes *ats, char *name)
{

}
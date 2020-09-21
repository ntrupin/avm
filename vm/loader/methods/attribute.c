//
// Created by Noah Trupin on 9/19/20.
//

#include <stdlib.h>
#include <stdio.h>

#include "attribute.h"
#include "../constpool/const.h"
#include "../loader.h"

avm_method_attribute *avm_method_attribute_make(FILE *f, avm_constpool *cp)
{
    avm_method_attribute *a = malloc(sizeof(avm_method_attribute));
    //printf("%d\n", cp->consts[lod2(f)]->utf8->len);
    avm_constpool_utf8 *name = cp->consts[lod2(f)]->utf8;
    uint64_t len = lod4(f);
    uint8_t *data = malloc(sizeof(uint8_t) * len);
    if (!a || !data) {
        printf("Error allocating attribute");
        exit(1);
    }
    a->name = name;
    a->len = len;
    uint64_t i;
    for (i=0;i<len;i++) {
        data[i] = lod1(f);
    }
    a->data = data;
    return a;
}

void avm_method_attribute_free(avm_method_attribute *a)
{
#if DEBUG
    printf("\t\t\t| %s => ", a->name->value);
    uint64_t i;
    for (i=0;i<a->len;i++) {
        printf("0x%02x%s", a->data[i], i+1<a->len ? ", " : " ");
    }
    printf("\n");
#endif
    if (a->data) free(a->data);
    if (a) free(a);
}

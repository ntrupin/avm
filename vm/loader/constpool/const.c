//
// Created by Noah Trupin on 9/14/20.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "const.h"
#include "utf8.h"
#include "string.h"
#include "method.h"
#include "nametype.h"
#include "../loader.h"
#include "../class.h"

avm_constpool_const *avm_constpool_const_make(FILE *f)
{
    avm_constpool_const *c = malloc(sizeof(avm_constpool_const));
    if (!c) {
        printf("Error allocating const");
        exit(1);
    }
    uint8_t tag = lod1(f);
    switch (tag) {
        case 0x01:
            c->utf8 = avm_constpool_utf8_make(f);
            break;
        case 0x02:
            c->string = avm_constpool_string_make(f);
            break;
        case 0x03:
            c->method = avm_constpool_method_make(f);
            break;
        case 0x04:
            c->nametype = avm_constpool_nametype_make(f);
            break;
        default:
            printf("Error: invalid Const tag %x", tag);
            break;
    }
    c->tag = tag;
    return c;
}

void avm_constpool_const_free(avm_constpool_const *c, uint16_t index)
{
#if DEBUG
    printf("\t\t| 0x%04x => ", index);
#endif
    switch (c->tag) {
        case 0x01:
            avm_constpool_utf8_free(c->utf8);
            break;
        case 0x02:
            avm_constpool_string_free(c->string);
            break;
        case 0x03:
            avm_constpool_method_free(c->method);
            break;
        case 0x04:
            avm_constpool_nametype_free(c->nametype);
            break;
        default:
            printf("Error: invalid Const tag %x", c->tag);
            if (c) free(c);
            exit(1);
    }
    if (c) free(c);
}
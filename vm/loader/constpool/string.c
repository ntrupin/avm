//
// Created by Noah Trupin on 9/14/20.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "string.h"
#include "utf8.h"
#include "../loader.h"

avm_constpool_string *avm_constpool_string_make(FILE *f)
{
    avm_constpool_string *s = malloc(sizeof(avm_constpool_string));
    if (!s) {
        printf("Error allocating string");
        exit(1);
    }
    s->index = lod2(f);
    return s;
}

void avm_constpool_string_free(avm_constpool_string *s)
{
#if DEBUG
    printf("string[utf8 at: 0x%x]\n", s->index);
#endif
    if (s) free(s);
}
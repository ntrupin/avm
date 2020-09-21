//
// Created by Noah Trupin on 9/14/20.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "utf8.h"
#include "../loader.h"

avm_constpool_utf8 *avm_constpool_utf8_make(FILE *f)
{
    avm_constpool_utf8 *s = malloc(sizeof(avm_constpool_utf8));
    if (!s) {
        printf("Error allocating string");
        exit(1);
    }
    s->len = lod2(f);
    s->value = lodbytes(f, s->len);
    return s;
}

void avm_constpool_utf8_free(avm_constpool_utf8 *s)
{
#if DEBUG
    printf("utf8[len: %d, value: \"%s\"]\n", s->len, s->value);
#endif
    if (s->value) free(s->value);
    if (s) free(s);
}
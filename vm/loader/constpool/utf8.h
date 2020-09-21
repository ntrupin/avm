//
// Created by Noah Trupin on 9/14/20.
//

#ifndef GIANT_UTF8_H
#define GIANT_UTF8_H

typedef struct {
    uint16_t len;
    uint8_t *value;
} avm_constpool_utf8;

avm_constpool_utf8 *avm_constpool_utf8_make(FILE *);
void avm_constpool_utf8_free(avm_constpool_utf8 *);

#endif //GIANT_UTF8_H

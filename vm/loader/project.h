//
// Created by Noah Trupin on 9/20/20.
//

#ifndef GIANT_PROJECT_H
#define GIANT_PROJECT_H

#include <stdint.h>
#include <stdlib.h>

#include "class.h"
#include "constpool/utf8.h"
#include "constpool/constpool.h"

typedef struct {
    uint16_t major;
    uint16_t minor;
    avm_constpool_utf8 *name;
    avm_constpool *constpool;
    uint8_t count;
    avm_class **classes;
} avm_project;

avm_project *avm_project_make(char *);
void avm_project_free(avm_project *);
avm_class *avm_project_resolve(avm_project *, char *);

#endif //GIANT_PROJECT_H

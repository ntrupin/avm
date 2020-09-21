//
// Created by Noah Trupin on 9/21/20.
//

#ifndef GIANT_VARS_H
#define GIANT_VARS_H

#include <stdlib.h>
#include <stdio.h>

#include "value.h"

typedef struct {
    char *name;
    avm_value *value;
} avm_vars_entry;

typedef struct {
   uint64_t size;
   uint64_t full;
   avm_vars_entry **entries;
} avm_vars;

avm_vars *avm_vars_make();
void avm_vars_free(avm_vars *);
avm_vars_entry *avm_vars_entry_make(char *, avm_value *);
void avm_vars_entry_free(avm_vars_entry *);
void avm_vars_insert(avm_vars *, char *, avm_value *);
avm_value *avm_vars_read(avm_vars *, char *);
void avm_vars_delete(avm_vars *, char *);

#endif //GIANT_VARS_H

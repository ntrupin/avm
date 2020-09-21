//
// Created by Noah Trupin on 9/21/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vars.h"

uint64_t fnv1a(char *name)
{
    uint64_t prime = 0x100000001b3;
    uint64_t hash = 0xcbf29ce484222325;
    uint64_t i;
    for (i=0;name[i]!='\0';i++) {
        hash ^= name[i];
        hash *= prime;
    }
    return hash;
}

avm_vars_entry *avm_vars_entry_make(char *name, avm_value *value)
{
    avm_vars_entry *e = malloc(sizeof(avm_vars_entry));
    if (!e) {
        printf("error allocating avm_vars_entry");
        exit(1);
    }
    e->name = name;
    e->value = value;
    return e;
}

void avm_vars_entry_free(avm_vars_entry *e)
{
    if (!e) return;
    avm_value_free(e->value);
    if (e->name) free(e->name);
    free(e);
}

void avm_vars_insert(avm_vars *v, char *name, avm_value *value)
{
    if (v->full == v->size) {
        v->size *= 2;
        v->entries = realloc(v->entries, v->size * sizeof(avm_vars_entry *));
        if (!v->entries) {
            printf("error reallocating avm_vars_entry");
            exit(1);
        }
    }
    //printf("\n%d\n", fnv1a(name) % v->size);
    uint64_t hash = fnv1a(name) % v->size;
    while (v->entries[hash]) {
        hash += 1;
    }
    v->entries[hash] = avm_vars_entry_make(name, value);
    v->full += 1;
}

avm_value *avm_vars_read(avm_vars *v, char *name)
{
    uint64_t hash = fnv1a(name) % v->size;
    for (;;hash++) {
        if (!v->entries[hash]) {
            continue;
        }
        if (strcmp(v->entries[hash]->name, name) == 0) {
            continue;
        }
        return v->entries[hash]->value;
    }
}

void avm_vars_delete(avm_vars *v, char *name)
{
    uint64_t hash = fnv1a(name) % v->size;
    for (;;hash++) {
        if (!v->entries[hash]) {
            continue;
        } else if (strcmp(v->entries[hash]->name, name) != 0) {
            continue;
        }
        avm_vars_entry_free(v->entries[hash]);
        v->full -= 1;
        break;
    }
}

avm_vars *avm_vars_make()
{
    avm_vars *v = malloc(sizeof(avm_vars));
    if (!v) {
        printf("error allocating avm_vars");
        exit(1);
    }
    v->size = 8;
    v->entries = malloc(v->size * sizeof(avm_vars_entry *));
    return v;
}

void avm_vars_free(avm_vars *v)
{
    uint64_t i;
    for (i=0;i<v->size;i++) {
        avm_vars_entry_free(v->entries[i]);
    }
    if (v) free(v);
}

//
// Created by Noah Trupin on 9/20/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "project.h"
#include "class.h"
#include "loader.h"

avm_project *avm_project_make(char *name)
{
    FILE *f;
    f = fopen(name, "rb");
    if (!f) {
        printf("Error opening file.");
        exit(1);
    }
    uint32_t magic = lod4(f);
    if (magic != 0xCAFEBABE) {
        printf("Error: invalid magic.");
        exit(1);
    }
    avm_project *p = malloc(sizeof(avm_project));
    if (!p) {
        printf("Error allocating avm_project");
        exit(1);
    }
    p->major = lod2(f);
    p->minor = lod2(f);
    p->constpool = avm_constpool_make(f);
    p->name = avm_constpool_resolve(p->constpool, lod2(f));
    p->count = lod1(f);
    avm_class **cs = malloc(sizeof(avm_class *) * p->count);
    uint8_t i;
    for (i=0;i<p->count;i++) {
        cs[i] = avm_class_make(f);
    }
    p->classes = cs;
    fclose(f);
    return p;
}

void avm_project_free(avm_project *p)
{
#if DEBUG
    printf("\nAVM v%d.%d\nProject %s\n",
           p->major,
           p->minor,
           p->name->value
    );
#endif
    uint8_t i;
    avm_constpool_free(p->constpool);
    for (i=0;i<p->count;i++) {
        avm_class_free(p->classes[i]);
    }
    if (p) free(p);
}

avm_class *avm_project_resolve(avm_project *p, char *name)
{
    uint8_t i;
    for (i=0;i<p->count;i++) {
        if (strcmp(p->classes[i]->name->value, name) == 0) {
            return p->classes[i];
        }
    }
    printf("Error resolving class with name %s", name);
    exit(1);
}
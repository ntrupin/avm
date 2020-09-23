//
// Created by Noah Trupin on 9/20/20.
//

#ifndef GIANT_VM_H
#define GIANT_VM_H

#include <stdio.h>

#include "./loader/project.h"

enum {
    AOP_NOP=0x00,
    AOP_RETURN=0x01, AOP_LOAD=0x02, AOP_STORE=0x03, AOP_ADD=0x04
};

typedef struct {
    avm_project *project;
    //avm_vars *globals;
} avm_vm;

int vm(int, char **);

#endif //GIANT_VM_H
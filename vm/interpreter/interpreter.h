//
// Created by Noah Trupin on 9/21/20.
//

#ifndef GIANT_INTERPRETER_H
#define GIANT_INTERPRETER_H

#include <stdlib.h>

#include "../loader/project.h"
#include "vars.h"

typedef struct {
   avm_project *project;
   //avm_vars *globals;
} avm_interpreter;

avm_interpreter *avm_interpreter_make(char *);
void avm_interpreter_run(avm_interpreter *);
void avm_interpreter_free(avm_interpreter *);

#endif //GIANT_INTERPRETER_H

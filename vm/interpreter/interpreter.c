//
// Created by Noah Trupin on 9/21/20.
//

#include <stdlib.h>

#include "interpreter.h"
#include "frame.h"
#include "../loader/project.h"
#include "../loader/class.h"
#include "vars.h"

void avm_interpreter_run(avm_interpreter *ai)
{
    avm_class *class = avm_project_resolve(ai->project, ai->project->name->value);
    avm_frame *frame = avm_frame_make(class, "main");
    avm_frame_exec(frame);
    avm_frame_free(frame);
}

avm_interpreter *avm_interpreter_make(char *name)
{
    avm_interpreter *ai = malloc(sizeof(avm_interpreter));
    if (!ai) {
        printf("error allocating avm_interpreter");
        exit(1);
    }
    ai->project = avm_project_make(name);
    return ai;
}

void avm_interpreter_free(avm_interpreter *ai)
{
    if (ai->project) avm_project_free(ai->project);
    if (ai) free(ai);
}

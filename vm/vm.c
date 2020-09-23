#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "vm.h"
#include "loader/project.h"
#include "runtime/frame.h"

avm_value *avm_vm_return(avm_frame *frame, avm_method_attribute *code)
{
    uint8_t op = code->data[frame->ip];
    avm_value *a;
    if (frame->method->ret == AVM_VOID) {
        a = avm_value_make(AVM_VOID);
    } else {
        a = avm_stack_pop(frame->stack);
    }
    if (a->tag != frame->method->ret) {
        printf("error: wrong return type %d, expected %d\n", a->tag, frame->method->ret);
        exit(1);
    }
    if (frame->stack->count > 0) {
        printf("error: misaligned stack in function %s", frame->method->name->value);
        exit(1);
    }
#if DEBUG
    printf("RETURN\n");
#endif
    return a;
}

void avm_vm_load(avm_frame *frame, avm_method_attribute *code)
{
    uint8_t op = code->data[frame->ip];
    uint16_t index = (
            ((uint16_t)code->data[++frame->ip] << 8) |
            ((uint16_t)code->data[++frame->ip])
    );
    avm_constpool_utf8 *name = avm_constpool_resolve(frame->class->constpool, index);
    avm_value *a = avm_vars_read(frame->locals, name->value);
    avm_stack_push(frame->stack, a);
#if DEBUG
    printf("LOAD %d\n", a->avm_int);
#endif
    return;
}

void avm_vm_add(avm_frame *frame, avm_method_attribute *code)
{
    uint8_t op = code->data[frame->ip];
    avm_value *a = avm_stack_pop(frame->stack);
    avm_value *b = avm_stack_pop(frame->stack);
    avm_value *c = avm_value_make(AVM_INT);
    c->avm_int = a->avm_int + b->avm_int;
    avm_stack_push(frame->stack, c);
#if DEBUG
    printf("ADD\n");
#endif
}

avm_value *avm_vm_class(avm_frame *frame, uint8_t argc, ...)
{
    va_list args;
    va_start(args, argc);
    uint8_t i;
    for (i=0;i<argc;i++) {
        char *name = va_arg(args, char *);
        avm_value *value = va_arg(args, avm_value *);
        avm_vars_insert(frame->locals, name, value);
        if (value->tag != frame->method->args[i]) {
            printf("error: wrong argument type %d, expected %d\n", value->tag, frame->method->args[i]);
            exit(1);
        }
    }
    va_end(args);

    avm_method_attribute *code = avm_method_attributes_resolve(frame->method->attrs, "code");
    for (;frame->ip<code->len;frame->ip++) {
        uint8_t op = code->data[frame->ip];
#if DEBUG
        printf("\t | 0x%04x => ", frame->ip);
#endif
        switch (op) {
            case AOP_NOP: {
#if DEBUG
                printf("NOP\n");
#endif
                break;
            }
            case AOP_RETURN:
                return avm_vm_return(frame, code);
            case AOP_LOAD:
                avm_vm_load(frame, code);
                break;
            case AOP_ADD:
                avm_vm_add(frame, code);
                break;
            default: {
                printf("error: invalid byte 0x%02x\n", op);
                exit(1);
            }
        }
    }
    printf("Code execution should not reach here. Please file an issue at <https://github.com/ntrupin/avm/issues>\n");
    exit(1);
}

avm_vm *avm_vm_make(char *name)
{
    avm_vm *v = malloc(sizeof(avm_vm));
    if (!v) {
        printf("error allocating avm_vm");
        exit(1);
    }
    v->project = avm_project_make(name);
    return v;
}

void avm_vm_free(avm_vm *v)
{
    if (v->project) avm_project_free(v->project);
    if (v) free(v);
}

void avm_vm_run(avm_vm *v)
{
    avm_class *class = avm_project_resolve(v->project, v->project->name->value);
    avm_frame *frame = avm_frame_make(class, "main");
#if DEBUG
    printf("| trace\n");
#endif
    avm_value *x = avm_value_make(AVM_INT);
    x->avm_int = 15;
    avm_value *y = avm_value_make(AVM_INT);
    y->avm_int = 1000;
    avm_value *result = avm_vm_class(frame, 2, "x", x, "y", y);
    printf("Program Returned %d\n", result->avm_int);
    avm_frame_free(frame);
}

int vm(int argc, char **argv)
{
#if GENERATE
    uint8_t test_set[] = {
        // Magic
        0xCA, 0xFE, 0xBA, 0xBE,
        // Version
        0x00, 0x00, 0x00, 0x01,
        // constpool Len
        0x00, 0x01,
        // constpool Projectname: "Base" Tag + Len + Val
        0x01, 0x00, 0x04, 0x42, 0x61, 0x73, 0x65,
        // Projectname index
        0x00, 0x00,
        // AVM Classes Len
        0x01,
        // constpool Len
        0x00, 0x0B,
        // constpool Classname: "Base" Tag + Len + Val
        0x01, 0x00, 0x04, 0x42, 0x61, 0x73, 0x65,
        // constpool Superclass: "Super" Tag + Len + Val
        0x01, 0x00, 0x05, 0x53, 0x75, 0x70, 0x65, 0x72,
        // constpool String: "Hello, world!" Tag + Len + Val
        0x01, 0x00, 0x0C, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64,
        // constpool String: Pointing to entry index 2
        0x02, 0x00, 0x02,
        // constpool String: "main"
        0x01, 0x00, 0x04, 0x6d, 0x61, 0x69, 0x6e,
        // constpool String: "II-I"
        0x01, 0x00, 0x04, 0x49, 0x49, 0x2d, 0x49,
        // constpool Method
        0x03, 0x00, 0x00, 0x00, 0x07,
        // constpool nametype
        0x04, 0x02, 0x00, 0x04, 0x00, 0x05,
        // constpool String: "code" Tag + Len + Val
        0x01, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65,
        // constpool String: "x" Tag + Len + Val
        0x01, 0x00, 0x01, 0x78,
        // constpool String: "y" Tag + Len + Val
        0x01, 0x00, 0x01, 0x79,
        // Flags
        0x00, 0x01,
        // Classname index
        0x00, 0x00,
        // Superclass index
        0x00, 0x01,
        // methods len
        0x00, 0x01,
        // methods Method Class + NaT + Attr Len + Attr Name
        0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x08,
        // Attr Data Len + Attr Data (Code)
        0x00, 0x00, 0x00, 0x09,
        AOP_NOP, AOP_LOAD, 0x00, 0x09, AOP_LOAD, 0x00, 0x0A, AOP_ADD, AOP_RETURN, //0x01, 0x03, 0x01, 0x05, 0x02
    };
    FILE *f;
    f = fopen("test.avm", "wb");
    uint32_t i;
    for (i=0;i<sizeof(test_set);i++) {
        putc(test_set[i], f);
#if DEBUG
       printf("0x%02x ", test_set[i]);
#endif
    }
    fclose(f);
#if DEBUG
    printf("\n\n");
#endif
#endif
    avm_vm *v = avm_vm_make("test.avm");
    avm_vm_run(v);
    avm_vm_free(v);
    return 0;
}

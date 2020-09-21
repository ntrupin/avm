//
// Created by Noah Trupin on 8/27/20.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "loader.h"

uint8_t *lodbytes(FILE *f, uint32_t n)
{
    uint8_t *bytes = malloc(n * sizeof(uint8_t));
    if (!bytes) {
        printf("Error loading bytes from file.");
        exit(0);
    }
    uint32_t i;
    uint8_t c;
    for (i=0;i<n&&(c=getc(f))>=0&&c<=UINT8_MAX;i++) {
        bytes[i] = c;
    }
    return bytes;
}

uint8_t lod1(FILE *f)
{
    uint8_t *byte = lodbytes(f, 1);
    uint8_t val = byte[0];
    free(byte);
    return val;
}

uint16_t lod2(FILE *f)
{
    uint8_t *bytes = lodbytes(f, 2);
    uint16_t val = (
            ((uint16_t)bytes[0] << 8) |
            ((uint16_t)bytes[1])
    );
    return val;
}

uint32_t lod4(FILE *f)
{
    uint8_t *bytes = lodbytes(f, 4);
    uint32_t val = (
            ((uint32_t)bytes[0] << 24) |
            ((uint32_t)bytes[1] << 16) |
            ((uint32_t)bytes[2] << 8) |
            ((uint32_t)bytes[3])
    );
    return val;
}

uint64_t lod8(FILE* f)
{
    uint8_t *bytes = lodbytes(f, 8);
    uint8_t i;
    uint64_t val;
    for (i=56;i>=0;i-=8) {
        if (i == 56) {
            val = (bytes[7 % (i / 8)] << i);
            continue;
        }
        val |= (bytes[7 % (i / 8)] << i);
    }
    return val;
}
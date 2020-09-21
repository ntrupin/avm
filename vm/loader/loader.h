//
// Created by Noah Trupin on 8/27/20.
//

#ifndef GIANT_LOADER_H
#define GIANT_LOADER_H

#include <stdint.h>
#include <stdio.h>

#include "constpool/constpool.h"

uint8_t *lodbytes(FILE *, uint32_t);
uint8_t lod1(FILE *);
uint16_t lod2(FILE *);
uint32_t lod4(FILE *);
uint64_t lod8(FILE *);

#endif //GIANT_LOADER_H

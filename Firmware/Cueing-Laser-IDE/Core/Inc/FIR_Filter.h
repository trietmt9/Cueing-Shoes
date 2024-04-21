#ifndef __FIR__FILTER__H
#define __FIR__FILTER__H
#include "stdint.h"

#define FIR_FILTER_LENGTH                       8

typedef struct
{
    float buffer[FIR_FILTER_LENGTH];
    uint8_t buffer_index;
    float output; 
}FIR_Filter;

void Filter_init(FIR_Filter* fir);
float Filter_update(FIR_Filter* fir, float input);
#endif
#include "FIR_Filter.h"

static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {0.3 ,0.2,0.1,0.09,0.08,0.07,0.09,0.08, 0.3, 0.2,0.1,0.09,0.08,0.07,0.09,0.08}; // Impulse response h(j)

void Filter_init(FIR_Filter *fir)
{
    /* Clear filter buffer */
    for(uint8_t n = 0; n < FIR_FILTER_LENGTH; n++)
    {
        fir->buffer[n] = 0.0f;
    }

    /* Reset buffer index */
    fir->buffer_index = 0; // input index of the buffer x(n)

    /* Clear filter output */

    fir->output = 0.0f; // output y(n)
}

float Filter_update(FIR_Filter* fir, float input)
{
    /* Store latest sample in buffer */
    fir->buffer[fir->buffer_index] = input;

    /* Increment the buffer index */
    fir->buffer_index++;

    // Check if buffer index equal to FIR_FILTER_LENGTH 
    if (fir->buffer_index == FIR_FILTER_LENGTH)
    {
        fir->buffer_index = 0;
    }
    /* Compute new output sample (use convolution) */
    fir->output = 0.0f; 
    uint8_t sumIndex = fir->buffer_index;
    for(uint8_t n = 0; n < FIR_FILTER_LENGTH; n++)
    {
        /* Decrement index and wrap it necessary */
        if (sumIndex > 0)
        {
            sumIndex--;
        }
        // Shift Impulse response index
        else 
        {
            sumIndex = FIR_FILTER_LENGTH - 1;
        }

    /* Multiply Impulse response with shifted input sample and add to output */
        // y[n] += h[j]*x[n-j]
        fir->output += FIR_IMPULSE_RESPONSE[n] * fir->buffer[sumIndex];
    }
    return fir->output;  
}
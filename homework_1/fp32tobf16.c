#include <stdio.h>

float fp32_to_bf16(float x)                 
{
    float y = x;
    int *p = (int *) &y;
    unsigned int exp = *p & 0x7F800000;
    unsigned int man = *p & 0x007FFFFF;

    if (exp == 0 && man == 0) /* zero */
        {
            printf("exp==0 && man==0\n");
            return x;
        }
    if (exp == 0x7F800000) /* infinity or NaN */
        {
            printf("exp==255");
            return x;
        }

    /* Normalized number */
    /* round to nearest */
    float r = x;
    int *pr = (int *) &r;
    *pr &= 0xFF800000;  /* r has the same exp as x */
    r /= 0x100;
    y = x + r;
    
    *p &= 0xFFFF0000;

    return y;
}
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>

// Define the structure for IEEE 754 single-precision floating-point numbers
struct IEEE754_single {
    uint32_t mantissa : 23; // 23 bits for the mantissa
    uint32_t exponent : 8;  // 8 bits for the exponent
    uint32_t sign : 1;      // 1 bit for the sign
};

struct IEEE754_half {
    uint16_t mantissa : 10; // 10 bits for the mantissa
    uint16_t exponent : 5;  // 5 bits for the exponent
    uint16_t sign : 1;      // 1 bit for the sign
};

// Function to round a floating-point number to the nearest integer
int round_to_nearest_integer(float x)
{

    // Create a union for IEEE 754 single-precision floating-point numbers
    union {
        float f;
        struct IEEE754_single bits;
    } ieee754;

    ieee754.f = x; // Assign the floating-point number to the union
    // printf("ieee754.bits: %x\n", ieee754.bits);
    // printf("ieee754.bits.sign: %x\n", ieee754.bits.sign);
    // printf("ieee754.bits.exponent: %x\n", ieee754.bits.exponent);
    // printf("ieee754.bits.mantissa: %x\n", ieee754.bits.mantissa);
    
    // Extract the sign, exponent, and mantissa parts
    int sign = ieee754.bits.sign;
    int exponent = ieee754.bits.exponent - 127; // Offset of the exponent is 127
    uint32_t mantissa = ieee754.bits.mantissa | 0x800000; // Add the hidden 1
    // printf("sign: %x\n", sign);
    // printf("exponent: %x\n", exponent);
    // printf("mantissa: %x\n", mantissa);
    
    // Handle the case when the input value is 0
    if (ieee754.bits.exponent == 0 && ieee754.bits.mantissa  == 0)
    {
        return 0;
    }

    if (ieee754.bits.exponent == 255 && ieee754.bits.mantissa  == 0) 
    {
        if (sign) {
            printf("the input value is too small\n");
            return INT_MIN; // Negative infinity
        } else {
            printf("the input value is too large\n");
            return INT_MAX; // Positive infinity
        }
    }

    // Check if the input value is too large or too small
    if (exponent > 31) {
        if (sign) {
            printf("the input value is too small\n");
            return INT_MIN; // Negative infinity
        } else {
            printf("the input value is too large\n");
            return INT_MAX; // Positive infinity
        }
    }

    // Check if the input value is NaN
    if (ieee754.bits.exponent == 255 && ieee754.bits.mantissa != 0) {
        // NaN value detected
        if (mantissa & (1 << 22)) {
            printf("This is a signaling NaN (sNaN)\n");
            // Handle sNaN (signaling NaN) as needed
            // For example, you can raise a floating-point exception here
        } else {
            printf("This is a quiet NaN (qNaN)\n");
            // Handle qNaN (quiet NaN) as needed
            // For example, you can simply return an error code here
            return INT_MIN; // or return another appropriate error value
        }
    }

    // Perform rounding
    int int_value; // Integer part (before the decimal point)
    int float_value; // Fractional part (after the decimal point)
    if (exponent >= 23) {
        int_value = mantissa << (exponent - 23);
        float_value = 0; // No fractional part
        
    } else {
        int_value = mantissa >> (23 - exponent);
        float_value = mantissa & ((1 << (23 - exponent)) - 1); // Get the fractional part
    }

    // Perform rounding by adding the last fractional bit to the integer part
    if ((float_value & (1 << (22 - exponent))) != 0) {
        int_value += 1;
    }

    // Determine the final sign of the result based on the sign bit
    if (sign) {
        int_value = -int_value;
    }

    return int_value;
}

int round_to_nearest_integer_half(float x)
{
    union {
        float f;
        struct IEEE754_half bits;
    } ieee754;
    ieee754.f = x;

    int sign = ieee754.bits.sign;
    int exponent = ieee754.bits.exponent - 15; // Offset of the exponent is 15
    uint32_t mantissa = ieee754.bits.mantissa | (ieee754.bits.exponent > 0 ? 0x400 : 0);

    if (ieee754.bits.exponent == 0 && ieee754.bits.mantissa  == 0)
    {
        return 0;
    }

    if (ieee754.bits.exponent == 31 && ieee754.bits.mantissa  == 0) 
    {
        if (sign) {
            printf("the input value is too small\n");
            return INT_MIN; // Negative infinity
        } else {
            printf("the input value is too large\n");
            return INT_MAX; // Positive infinity
        }
    }
    // Perform rounding
    int int_value; // Integer part (before the decimal point)
    int float_value; // Fractional part (after the decimal point)
    if (exponent >= 10) {
        int_value = mantissa << (exponent - 10);
        float_value = 0; // No fractional part
        
    } else {
        int_value = mantissa >> (10 - exponent);
        float_value = mantissa & ((1 << (10 - exponent)) - 1); // Get the fractional part
    }

    // Perform rounding by adding the last fractional bit to the integer part
    if ((float_value & (1 << (9 - exponent))) != 0) {
        int_value += 1;
    }

    // Determine the final sign of the result based on the sign bit
    if (sign) {
        int_value = -int_value;
    }

    return int_value;
}
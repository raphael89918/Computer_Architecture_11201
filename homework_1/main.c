#include "round_function.c"
#include "fp32tobf16.c"

int main() {
    float floatValue;
    
    printf("enter a float value: ");
    scanf("%f", &floatValue);
    float bf16 = fp32_to_bf16(floatValue);
    printf("bf16 = %f\n", bf16);

    int result = round_to_nearest_integer(bf16);
    printf("bf16 to integer %d\n", result);
    return 0;
}
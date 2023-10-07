#include "round_function.c"
int main() {
    float floatValue;
    
    printf("enter a float value: ");
    scanf("%f", &floatValue);
    
    int intValue = round_to_nearest_integer_half(floatValue);

    printf("float: %f\nround to integer(half precision): %d\n", floatValue, intValue);

    return 0;
}
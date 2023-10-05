#include "round_function.c"
int main() {
    float floatValue;
    
    printf("enter a float value: ");
    scanf("%f", &floatValue);
    printf("====%lf\n", floatValue);
    int intValue = round_to_nearest_integer(floatValue);

    printf("float: %f\nround to integer(single precision): %d\n", floatValue, intValue);

    return 0;
}
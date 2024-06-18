#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long uint32_t;
typedef union {
    uint32_t i;
    float f;
} FloatIntUnion;

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#define NAN (float)(FloatIntUnion){ .i = 0x7FC00000 }.f

float my_fabs(float x, float y);
float my_log(float x, float n);
float my_fact(float x, int y);
float my_pow(float x, int y);
float my_sqrt(float x, float y);
float my_nrt(float x, float y);
float calculator(char* op, float x, float y);

float my_fabs(float x, float y) { // It worky :D
    return (y < 0 ? -y : y) * x;
}

float my_abs(float x, float y) { // It worky :D
    return (int)(y < 0 ? -y : y) * x;
}

float my_fact(float x, int y) { // It worky :D
    float result = y;
    result = (y == 0) ? 1.0 : y;
    result = (y != 1) ? result : 1;
    for (int i = (y - 1); i != 1; --i) { result *= i; } 

    return result *= x;
}

float my_log(float x, float y) { // It worky :D
    if (y <= 0.0) {
        fprintf(stderr, "Error: Logarithm is only defined for x > 0.\n");
        return -1.0;
    }

    float result = 0.0;
    float delta = (y - 1.0) / (y + 1.0);
    float delta_squared = delta * delta;
    float numerator = delta;
    int n = 1;

    while (my_pow(delta, n) / n >= 1e-6) {
        result += 2.0 * numerator / n;
        numerator *= delta_squared;
        n += 2;
    }

    return result *= x;
}

float my_pow(float x, int y) { // It worky :D
    float result = 1.0;
    if (y == 0) {
        result = 1.0;
    } else if (y < 0) {
        result = 1.0 / my_pow(x, -y);
    }
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

float nrt(float x, float y) { // It worky :D
    if (x <= 0.0) {
        fprintf(stderr, "Error: x must be greater than 0.\n");
        return -1.0;
    }

    float guess = y / x;
    float epsilon = 1e-6;

    while (my_pow(guess, x) - y > epsilon || y - my_pow(guess, x) > epsilon) {
        guess = guess - (my_pow(guess, x) - y) / (x * my_pow(guess, x - 1));
    }

    return guess;
}


float my_sqrt(float x, float y) { // It worky :D
    if (y < 0.0) {
        fprintf(stderr, "Error: Square root of negative number.\n");
        return NAN;
    }
    if (y == 0.0 || y == 1.0) {
        return y;
    }
    float theta = y / 2.0;
    float gamma;
    float delta;

    do {
        gamma = theta;
        theta = (theta + y / theta) / 2.0;
        delta = my_fabs(1, theta - gamma);
    } while (delta > 1e-10);

    return theta *= x;
}

float calculator(char* op, float x, float y) { // It worky :D
    system("clear");
    float result = 0.0;

    if (strcmp(op, "+") == 0) {
        result = x + y;
    } else if (strcmp(op, "-") == 0) {
        result = x - y;
    } else if (strcmp(op, "*") == 0) {
        result = x * y;
    } else if (strcmp(op, "/") == 0) {
        result = (y == 0.0) ? NAN : x / y;
    } else if (strcmp(op, "!") == 0) {
        result = my_fact(x, (int)y);
    } else if (strcmp(op, "sq") == 0) {
        result = x * (y * y);
    } else if (strcmp(op, "nrt") == 0) {
        result = nrt(x, y);
    } else if (strcmp(op, "log") == 0) {
        result = my_log(x, y);
    } else if (strcmp(op, "sqrt") == 0) {
        result = my_sqrt(x, y);
    } else if (strcmp(op, "pow") == 0) {
        result = my_pow(x, (int)y);
    } else if (strcmp(op, "fabs") == 0){
        result = my_fabs(x, y);
    } else if (strcmp(op, "abs") == 0){
        result = my_abs(x, y);
    } else {
        printf("Unknown operation.\n");
        result = NAN;
    }

    printf("Result: %f\n", result);

    return result;
}

int main() { // It worky :D
    system("clear");
    char *op = (char *)malloc(6 * sizeof(char));
    float x, y;
    int yn;

    printf("How many variables: ");
    scanf("%d", &yn);

    system("clear");
    if (yn == 2) {
        printf("(format: op x y): ");
        scanf("%s %f %f", op, &x, &y);
        calculator(op, x, y);
    } else {
        printf("(format: op x): ");
        scanf("%s %f", op, &y);
        calculator(op, 1, y);
    }

    free(op);

    return 0;
}

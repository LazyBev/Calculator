#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long uint32_t;
typedef union {
    uint32_t i;
    float f;
} FloatIntUnion;

#define PI 3.14159265358979323846
#define NAN (float)(FloatIntUnion){ .i = 0x7FC00000 }.f

float my_fabs(float x, float y);
float my_factorial(float x, int y);
float my_pow(float x, int y);
float my_sqrt(float x, float y);
float my_sin(float x, float y);
float my_asin(float x, float y);
float calculator(char* op, float x, float y);

float my_fabs(float x, float y) {
    float result = y < 0 ? -y : y;
    return result *= x;
}

float my_factorial(float x, int y) {
    if (y == 0 || y == 1) {
        return 1.0;
    }
    float result = 1.0;
    for (int i = 2; i <= y; i++) {
        result *= i;
    }

    result *= x;
    return result;
}

float my_pow(float x, int y) {
    float result = 1.0;
    if (y == 0) {
        return 1.0;
    } else if (y < 0) {
        return 1.0 / my_pow(x, -y);
    }
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

float my_sqrt(float x, float y) {
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

    return theta;
}

float my_sin(float x, float y) { // is completely brocken :'C
    float result = y;
    int sign = -1;
    float term = y - sign * my_pow(y, 3) / my_factorial(1, 3);;

    for (int i = 5; my_fabs(1, term) > 1e-100; i += 2) {
        term = sign * my_pow(y, i) / my_factorial(1, i);
        result += term;
        sign *= -1;
    }

    result *= x; 
    return result;
}

float my_asin(float x, float y) { // is slightly brocken :'C
    if (y < -0.5) {
        return -PI / 2 + 2 * my_asin(x, my_sqrt(1, (1 + -y) / 2));
    } else if (y > 0.5) {
        return PI / 2 - 2 * my_asin(x, my_sqrt(1, (1 - y) / 2));
    }

    float result = y;
    float term = y;
    int n = 1;

    while (my_fabs(1, term) > 1e-100) {
        term *= (y * y * (2 * n - 1) * (2 * n - 1)) / ((2 * n) * (2 * n + 1));
        result += term / (2 * n + 1);
        n++;
    }

    result *= x;

    return result;
}

float calculator(char* op, float x, float y) {
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
        result = my_factorial(x, (int)y);
    } else if (strcmp(op, "sq") == 0) {
        result = x * (y * y);
    } else if (strcmp(op, "sqrt") == 0) {
        result = my_sqrt(x, y);
    } else if (strcmp(op, "pow") == 0) {
        result = my_pow(x, (int)y);
    } else if (strcmp(op, "sin") == 0) {
        result = my_sin(x, y);
    } else if (strcmp(op, "asin") == 0) {
        result = my_asin(x, y);
    } else {
        printf("Unknown operation.\n");
        result = NAN;
    }

    printf("Result: %f\n", result);

    return result;
}

int main() {
    system("clear");
    char *op = (char *)malloc(6 * sizeof(char)); // Allocate memory for operation string
    float x, y;
    int yn;

    printf("How many variables: ");
    scanf("%d", &yn);

    system("clear");
    if (yn == 2) {
        printf("(op x y): ");
        scanf("%s %f %f", op, &x, &y);
        calculator(op, x, y);
    } else {
        printf("(op x): ");
        scanf("%s %f", op, &y);
        calculator(op, 1, y);
    }

    free(op);

    return 0;
}

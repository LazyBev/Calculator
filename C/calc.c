#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double calculator(double a, double b) {
    system("clear");
    double result = 0.0;
    char op[4];

    printf("operation: ");
    scanf("%3s", op);

    if (strcmp(op, "add") == 0) {
        result = a + b;
    } else if (strcmp(op, "min") == 0) {
        result = a - b;
    } else if (strcmp(op, "mul") == 0) {
        result = a * b;
    } else if (strcmp(op, "div") == 0) {
        if (b != 0) {
            result = a / b;
        } else {
            printf("Error: Division by zero.\n");
            result = NAN;
        }
    } else if (strcmp(op, "sqr") == 0) {
        result = sqrt(a * b);
    } else if (strcmp(op, "pow") == 0) {
        result = pow(a, b);
    } else {
        printf("Unknown operation.\n");
        result = NAN;
    }

    return result;
}

int main() {
    system("clear");
    double a, b, prod;

    printf("1st num: ");
    scanf("%lf", &a);
    printf("2nd num: ");
    scanf("%lf", &b);

    prod = calculator(a, b);

    if (!isnan(prod)) {
        printf("Result: %lf\n", prod);
    }

    return 0;
}

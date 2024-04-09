#include "calculator.h"

double add(double a, double b) {
    return a + b;
}

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

double divine(double a, double b) {
    if (b == 0) {
        return 0; 
    }
    return a / b;
}

double modulo(double a, double b) {
    if (b == 0) {
        return 0;
    }
    return ((int)a) % ((int)b);
}

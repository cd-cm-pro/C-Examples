#include <math.h>
#include <stdio.h>
#define PI 3.14159265358979

int main(void) {
    double RADIAN = (PI / 180);
    double floor1 = 1.8;
    double ceil1 = 2.5;
    double round1 = 12.34;
    double round2 = 56.78;
    printf("floor(1.8) = %.1f\n", floor(floor1));
    printf("ceil(2.5) = %.1f\n", ceil(ceil1));
    printf("round(12.34) = %.1f\n", round(round1));
    printf("round(56.78) = %.1f\n", round(round2));
    printf("sqrt(9) = %f\n", sqrt(9));
    printf("abs(-123) = %f\n", abs(-123));
    printf("2 squared 3 = %f\n", pow(2, 3));
    printf("90 degress = %f radian\n", RADIAN * 90);
    printf("cos(90 degress) = %f\n", cos(RADIAN * 90));
    printf("sin(180 degress) = %f\n", cos(RADIAN * 180));
    printf("tan(60 degress) = %f\n", tan(RADIAN * 60));
    printf("e squared 2 = %f\n", exp(2));
    printf("log_e(10) = %f\n", log(10));
    printf("log_10(100) = %f\n", log10(100));
    return 0;
}
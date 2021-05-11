#include <stdio.h>
#include <stdlib.h>

void perevodInt(int);
void perevodD(double, int);

char sign = '+';
int base;
/*
int main() {

    int accuracy;
    double number;

    printf("Enter number\n");
    scanf_s("%lf", &number);

    number < 0 ? sign = '-', number *= -1 : number; // тернарная условная операция

    printf("Enter base (2 <= base <= 16)\n");
    scanf_s("%d", &base);

    printf("Enter accuracy\n");
    scanf_s("%d", &accuracy);

    perevodInt((int)number);
    printf(".");
    perevodD(number - (int)number, accuracy);

    return 0;
}

void perevodInt(int number) {
    int i;
    if (number >= base) {
        i = number % base;
        number = number / base;
        perevodInt(number);
        printf("%c", i > 9 ? i - 10 + 'a' : i + '0');
    }
    else {
        printf("%c %c", sign, number > 9 ? number - 10 + 'A' : number + '0');
    }
}

void perevodD(double number, int accuracy) {
    static short n;
    int i;
    if (number != 0 && n++ < accuracy) {
        i = number *= base;
        printf("%c", i > 9 ? i - 10 + 'a' : i + '0');
        perevodD(number - (int)number, accuracy);
    }
    else {
        printf("%c", number > 9 ? (int)number - 10 + 'A' : (int)number + '0');
    }
}

*/

int ss;
char ms[200];
char znak = '+';

int main()
{
    int t, i, num1, k1 = 10, k2 = 11;

    double num;
    printf("Enter number: ");
    scanf_s("%lf", &num);

    printf("Enter accarsity: ");
    scanf_s("%d", &t);

    printf("Enter cc: ");
    scanf_s("%d", &ss);

    num < 0 ? znak = '-', num *= -1 : num;
    num1 = num;
    num -= num1;

    while (num1 >= ss)
    {
       i = num1 % ss;
       num1 /= ss;
       ms[k1--] = i > 9 ? i - 10 + 'A' : i + '0';
    }
    ms[k1--] = num1 > 9 ? num1 - 10 + 'A' : num1 + '0';
    ms[k1] = znak;
    ms[k2++] = '.';

    while (num != 0 && k2 - 11 <= t)
    {
        num *= ss;
        i = num * ss;
        num -= i;
        ms[k2++] = i > 9 ? i - 10 + 'A' : i + '0';
    }

    for (i = k1; i < k2; i++)
        printf("%c", ms[i]);

    return 0;

}

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <locale.h>

enum Types { Int, Float };

void summa( int kl, ...)
{
    void* p = &kl;
    int sumI = 0;
    float sumF = 0;
    p = (int*)p + 1;
    for (int i = 0; i < kl; i++)
        switch (*(Types*)p)
        {
            case Int:
                p = (Types*)p + 1;
                sumI += *(int*)p;
                p = (int*)p + 1;
                break;
            case Float:
                p = (Types*)p + 1;
                sumF += *(double*)p;
                p = (double*)p + 1;
                break;
        }
printf("sum of integer numbers is %d\nsum of float numbers is %f\n", sumI, sumF);
return;
}
int main()
{
    int a = 1, b = 2, c = 3;
    float aa = 11.1, bb = 22.2, cc = 33.3;
    summa(6, Int, a, Float, aa, Int, b, Int, c, Float, bb, Float, cc);
    return 0;
}

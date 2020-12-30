#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <locale.h>

enum Types{Int,Float};

void summa(enum Types typ,int kl,...)
{
    void *p = &kl;
    int sumI = 0;
    float sumF = 0;
    p = (int*)p + 1;
    for (int i = 0; i < kl; i++)
    switch (*(type*)p)
    {
        case intt:
            p = (type*)p + 1;
            sumi += *(int*)p;
            p = (int*)p + 1;
            break;
        case floatt:
            p = (type*)p + 1;
            sumf += *(double*)p;
            p = (double*)p + 1;
            break;
    }
}
int main() {
    setlocale(LC_ALL, "");
    int sumInt;
    float sumFloat;
    summa(Int,4,1,2,3,4,&sumInt);
    summa(Float,3,1.2,1.7,3.6,&sumFloat);
    printf("%d %3f",sumInt,sumFloat);
    return 0;
}

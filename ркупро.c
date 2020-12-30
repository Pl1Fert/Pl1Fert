#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdarg.h>

enum Types {Int,Float};
void sum(enum Types typ,int kl, ...)
{
    int sumI = 0;
    float sumF = 0;
    switch(typ)
    {
        case Int:
            va_list p;
            va_start(p, kl);
            for (int i = 0; i < kl; i++)
            {
                sumI += va_arg(p,int);
            }
            *va_arg(p, int*) = sumI;
            va_end(p)
            break;
        case Float:
            va_list pp;
            va_start(pp, double);
            for (int i = 0; i < kl; i++)
            {
                sumF += va_arg(pp,double);
            }
            *va_arg(p, double*) = sumF;
            va_end(pp);
            break;
    }
}

int main()
{
    setlocale(LC_ALL,"");
    int summaInt;
    double summaFloat;
    sum(Int, 3, 54, 45, 56, &summaInt);
    sum(Float, 3, (double)54.23, (double)466.4,(double)1.4, &summaFloat);
    printf("%d  %.3lf\n", summaInt, summaFloat);
    
    return 0;
}

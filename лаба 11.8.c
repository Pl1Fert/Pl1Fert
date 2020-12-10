
//  лаба 11.8


#include <stdio.h>
#include <locale.h>

double factorial(double n)
{
    if(n == 0)
        return 1;
    return factorial (n-1)*n;
}

int ClearStdin()
{
    int rv = 1;
    int ch;
    while (1)
    {
        ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            break;
        }
        rv = 0;
    }
    return rv;
}

int main()
{
    setlocale(LC_ALL,"");
    
    double n;
    int readCount, isEmpty;
    
    printf("Введите число: ");
    
    while (1)
    {
        readCount = scanf("%lf", &n);
        isEmpty = ClearStdin();
        if (readCount == 1 && isEmpty != 0 && n >= 0)
        {
            break;
        }
        printf("Неверный формат числа. Введите целое положительное число\n");
    }
    
    printf("Факториал числа %.1lf = %.1lf\n",n,factorial(n));
    return 0;
}

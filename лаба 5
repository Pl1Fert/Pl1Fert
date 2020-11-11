#include<stdio.h>
#include<locale.h>
#include<math.h>
#include<stdlib.h>

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
    setlocale(LC_ALL, "");
    int otr = 0, pol = 0, zero = 0, a, n, sump = 0, sumo = 0,isEmpty, readCount;

    //Ввод кол-во чисел
    printf("Введите целое число n: ");
    //Проверка
    while (1)
    {
        readCount = scanf("%d", &n);
        isEmpty = ClearStdin();
        if (readCount == 1 && isEmpty != 0 && n>0) 
        {
            break;
        }
        printf("Неверный формат числа. Введите целое положительное число\n");
    }

    //Ввод чисел
    for (int i = 1; i <= n; i++) 
    {
        printf("Введите целое a: ");
        //Проверка
        while (1)
        {
            readCount = scanf("%d", &a);
            isEmpty = ClearStdin();
            if (readCount == 1 && isEmpty != 0) 
            {
                break;
            }
            printf("Неверный формат числа. Введите целое число\n");
        }

        if (a < 0) 
        {                               //подсчет количества и суммы отрицательных чисел
            otr++; sumo = a + sumo;
        }
        else if (a > 0)
        {                               //подсчет количества и суммы положительных чисел
            pol++; sump = a + sump;
        }
        else if (a == 0) 
        {                               //подсчет количества и суммы 0
            zero++;
        }
    }
    printf("Количество положительных: %d\nСумма положительных: %d\nКоличество отрицательных: %d\nСумма отрицательных: %d\nКоличество равных нулю: %d\n", pol, sump, otr, sumo, zero);
}

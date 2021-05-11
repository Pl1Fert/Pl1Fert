Лаба 7.1
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

// Возвращает rv
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

    int readCount, isEmpty;
    int min,n;

    printf("Введите размерность матрицы.  ");
    // Проверка ввода n
    while (1)
    {
        readCount = scanf("%d", &n);
        isEmpty = ClearStdin();
        if (readCount == 1 && isEmpty != 0 && n > 0)
        {
            break;
        }
        printf("Неверный формат числа. Введите целое положительное число\n");
    }

    int **array= (int**)malloc(n*sizeof(int));
    for(int i = 0;i < n;i++)
    {
        array[i] = (int*)malloc(n*sizeof(int));
    }
    //Заполнение матрицы
    printf("Заполните матрицу \n");

    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
        {
            while (1)
            {
                readCount = scanf("%d", &array[i][j]);
                isEmpty = ClearStdin();
                if (readCount == 1 && isEmpty != 0 )
                {
                    break;
                }
                printf("Неверный формат числа. Введите целое положительное число\n");
            }
        }
    }
    //Вывод исходной матрицы
    printf("Исходная матрица \n");

    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
        {
            printf("%3d",array[i][j]);
        }
        printf("\n");
    }
    
    //Сортировка
    for(int j = 0;j < n;j++)
    {
        min=array[0][j];
        for(int i = 0;i < n;i++)
        {
            for(int b = 0 ; b < n, (i + b) < n;b++)
            {
                if(array[i][j] < 0 && array[i+b][j] < 0)
                {
                    if(array[i][j] > array[i+b][j])
                    {
                        min = array[i][j];
                        array[i][j] = array[i+b][j];
                        array[i+b][j] = min;
                    }
                }
            }
        }
    }
    //Вывод преобразованной матрицы
    printf("Преобразованная матрица \n");
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
        {
            printf("%3d",array[i][j]);
        }
        printf("\n");
    }
       
    //Освобождение памяти
    for (int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}

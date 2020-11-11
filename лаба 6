
//  лаба6



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
    setlocale(LC_ALL, "");

    int readCount, isEmpty;
    int max=0, b=0,min=0,n;

    printf("Введите размерность матрицы.\nn = ");
    
    // ПРоверка ввода n
    
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
    
    // Cоздание динамической матрицы порядка n
    
    int **array = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        array[i] = (int*)malloc(n * sizeof(int));
    }

    printf("Заполните матрицу:\n");

    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("A[%d][%d] = ", i, j);
            
            // Проверка ввода элемента матрицы
            
            while (1)
            {
                readCount = scanf("%d", &array[i][j]);
                isEmpty = ClearStdin();
                if (readCount == 1 && isEmpty != 0 )
                {
                   break;
                }
                printf("Неверный формат числа. Введите целое число\n");
            }
        }
    }
    // Вывод матрицы
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        max = array[i][0];
        
        // Поиск максимального элемента в строке
        
        for (int j = 0; j < n; j++)
        {
            if (array[i][j] > max)
            {
                max = array[i][j];
                b = j;
            }
            min = max;
        }
        
        // Поиск минимального элемента в столбце
        
        for (int i = 0; i < n; i++)
        {
            if (array[i][b] < min)
            {
                min = array[i][b];
            }
        }
        
        // Проверка на совпадение чисел
        
        if (max == min)
        {
            printf("%d\n", min);
        }
    }
    
    // Освобождение памяти
    
    for(int i=0;i<n;i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}

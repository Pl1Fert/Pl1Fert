//  laba 10





#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int findmaximum(int** second_array, int n, int i);
void ins(int** first_array, int n, int** second_array);
void print(int** first_array, int n, int** second_array);
int multi(int** second_array, int n, int j);
int ClearStdin(void);

int main()
{
    setlocale(LC_ALL, "");
    int n;
    int readCount, isEmpty;

    printf("Введите размерность матриц: ");
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

    //Выделение памяти под матрицы

    int** first_array = (int**)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        first_array[i] = (int*)malloc(n * sizeof(int));
    }

    int** second_array = (int**)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        second_array[i] = (int*)malloc(n * sizeof(int));
    }

    //Ввод матриц

    ins(first_array, n, second_array);

    //Вывод матриц

    print(first_array, n, second_array);

    //Умножение элементов строки 1 матрицы на максимальный элемент строки второй матрицы

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            first_array[i][j] *= findmaximum(second_array, n, i);

        }
    }

    print(first_array, n, second_array);

    //Сложение элементов столбца новой матрицы на произведение элементов соответствующей строки 2 матрицы

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            first_array[i][j] += multi(second_array, n, j);
        }
    }
    print(first_array, n, second_array);

    //Освобождение памяти

    for (int i = 0; i < n; i++)
    {
        free(first_array[i]);
    }
    free(first_array);

    for (int i = 0; i < n; i++)
    {
        free(second_array[i]);
    }
    free(second_array);
    return 0;
}

//Ввод матриц

void ins(int** first_array, int n, int** second_array)
{
    int readCount, isEmpty;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("First_array[%d][%d] = ", i, j);

            // Проверка ввода элемента матрицы

            while (1)
            {
                readCount = scanf("%d", &first_array[i][j]);
                isEmpty = ClearStdin();
                if (readCount == 1 && isEmpty != 0)
                {
                    break;
                }
                printf("Неверный формат числа. Введите целое число\n");
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Second_array[%d][%d] = ", i, j);

            // Проверка ввода элемента матрицы

            while (1)
            {
                readCount = scanf("%d", &second_array[i][j]);
                isEmpty = ClearStdin();
                if (readCount == 1 && isEmpty != 0)
                {
                    break;
                }
                printf("Неверный формат числа. Введите целое число\n");
            }
        }
    }
}

//Вовзращает max(максимум строки второй матрицы)

int findmaximum(int** second_array, int n, int i)
{
    int max;
    max = second_array[i][0];
    for (int j = 0; j < n; j++)
    {
        if (second_array[i][j] > max)
        {
            max = second_array[i][j];
        }
    }
    return max;
}

//Перемножает элементы строки второй матрицы и вовзращает a

int multi(int** second_array, int n, int j)
{
    int a = 1;
  
    for (int jj = 0; jj < n; jj++)
    {
        a *= second_array[j][jj];
    }
    return a;
    
}

//Вывод матриц

void print(int** first_array, int n, int** second_array)
{
    printf("Первая матрица \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", first_array[i][j]);
        }
        printf("\n");
    }

    printf("Вторая матрица \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", second_array[i][j]);
        }
        printf("\n");
    }
}

// Возвращает rv

int ClearStdin(void)
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

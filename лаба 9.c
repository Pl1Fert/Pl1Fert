
//  лаба 9
//
//  Created by AlexeyRusel on 11/5/20.
//  Copyright © 2020 AlexeyRusel. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
    int max;
    int n; // количество строк
    int m; // количество символов в строке
    int readCount, isEmpty;
      
     
    
    printf("Введите количество строк: ");
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
    //Выделение памяти под массив
    char **str=(char **)malloc(n*sizeof(char *));
    printf("Введите количество символов в строке: ");
    while (1)
    {
        readCount = scanf("%d", &m);
        isEmpty = ClearStdin();
        if (readCount == 1 && isEmpty != 0 && m > 0)
        {
            break;
        }
        printf("Неверный формат числа. Введите целое положительное число\n");
    }
    
    //Выделение памяти под строки
    
    for(int i = 0; i < n; i++)
    {
        str[i] = (char *)malloc((m+1)*sizeof(char));

    }
    
    //Обьясвление второго массива
    
    int **array=(int**)malloc(n*sizeof(int*));
       for(int i = 0;i < n;i++)
       {
           array[i] = (int*)malloc(1*sizeof(int));
       }
    
    printf("Введите %3d строк длинной не более %3d символов\n",n,m);
    
    //Ввод строк
    
    rewind(stdin);
    for(int i = 0; i < n; i++)
    {
        gets(str[i]);
    }
    
    //Вывод строк
    
    printf("Матрица \n");
    
    for(int i = 0; i < n; i++)
    {
        printf("%s\n",str[i]);
    }
    
    //Перевод строк в числа
    
    for(int i = 0;i < n;i++)
    {
        array[i][0] = atoi(str[i]);
    }
    
    //Сортировка по убыванию
    
    max=array[0][0];
    for(int i = 0;i < n;i++)
    {
        for(int b = 0 ; b < n, (i + b) < n;b++)
        {
            if(array[i][0] < array[i+b][0])
            {
                max = array[i][0];
                array[i][0] = array[i+b][0];
                array[i+b][0] = max;
            }
        }
    }
    
    //Вывод отсортированной матрицы
    
    printf("Отсортированная матрица \n");
    for(int i = 0; i < n;i++)
    {
        printf("%3d\n",array[i][0]);
    }
    
    //Освобождение памяти
    
    for(int i = 0;i < n;i++)
    {
        free(str[i]);
    }
    free(str);
    
    for(int i = 0;i < n;i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}


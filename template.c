#include <stdio.h>
#include <locale.h>
#include <stdlib.h>



int main()
{
    setlocale(LC_ALL,"");

    
    int n;
//шаблон для матрицы динамической
    printf("Введите размерность матрицы.  ");
    
        scanf("%d", &n);
       

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
             scanf("%d", &array[i][j]);
                
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
    //Освобождение памяти
    for (int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}    

// шаблон для строки динамической
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
int main()
{
    setlocale(LC_ALL,"");
    int n;
    
    //Размерность строки
    printf("Введите размер строки: ");
    
     scanf("%d", &n);
        
    
    char *str = (char *)calloc(n+1, sizeof(char));
    //Заполнение строки
    /*for(int i = 0;i < n;i++)
    {
       scanf("%c",&str[i]);
    }*/
    rewind(stdin);
    gets(str);
    
   
    
   
    //Вывод строки
    printf("\nИсходная строка\n ");
    printf("\n%s\n", str);
    
    free(str);
    return 0;
}
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
//шаблон под массив строк
int main()
{
    setlocale(LC_ALL,"");
    int max,value = 0;
    int n; // количество строк
    int m; // количество символов в строке
      
    printf("Введите количество строк: ");
    scanf("%d", &n);
     
    //Выделение памяти под массив
    char **str=(char **)malloc(n*sizeof(char *));
    printf("Введите количество символов в строке: ");
    scanf("%d", &m);

    
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
        fgets(str[i],(m+1),stdin);
    }
    
    //Вывод строк
    
    printf("Матрица \n");
    
    for(int i = 0; i < n; i++)
    {
        printf("%s\n",str[i]);
    }

    //Перевод строк в числа
    int j,znak;
    
    for (int i = 0; i < n; i++)
    {
        for (j = 0; str[i][j]!= '\0'; j++)
        {
            znak = (str[i][j]=='-')? -1:1;
            if (str[i][j]=='+' || str[i][j]=='-') j++;
            if (str[i][j] >= '0' && str[i][j] <= '9')
            {
                value = value * 10 + str[i][j] - '0';
            }
            value*=znak;
        }
        array[i][0] = value;
        value = 0;
        j = 0;
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

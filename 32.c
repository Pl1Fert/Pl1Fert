#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    setlocale(LC_ALL, "");
    for (int i = 1; i < argc; i++)
        printf("%s\n", argv[i]);

    int** array = (int**)malloc(argc * sizeof(int*));
    for (int i = 0; i < argc; i++)
    {
        array[i] = (int*)malloc(1 * sizeof(int));
    }


    //Перевод строк в числа
    int j,value = 0,k = 0,sum = 0;

    for (int i = 1; i < argc; i++)
    {
        for (j = 0; argv[i][j] != '\0'; j++)
        {

            if (argv[i][j] >= '0' && argv[i][j] <= '9')
            {
                value = value * 10 + argv[i][j] - '0';
            }
        }
        array[k][0] = value;
        k++;
        value = 0;
    }
    for (int i = 0; i < argc; i++)
    {
        if (array[i][0] % 4 == 0)
            sum += array[i][0];
    }
    printf("\n%d", sum);
    for (int i = 0; i < argc; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int numberWords(char* string) {
    static int num, i, flag;
    if (!string[i]) {
        return 0;
    }
    if (string[i] != ' ' && flag == 0 && (string[i] >= 'A' && string[i] <= 'Z')) {
        num++;
        flag = 1;
    }

    if (string[i] == ' ') {
        flag = 0;
    }

    i++;
    numberWords(string);
    return num;
}

int main(int argc,char* argv[])
{
    int amount = 0,k = 0,max,index = 0;
    setlocale(LC_ALL, "");
    for (int i = 1; i < argc; i++)
        printf("%s\n", argv[i]);
    int* array = (int*)malloc(argc * sizeof(int));
    // дин. массив
    for (int i = 1; i < argc; i++)
    {
        amount = numberWords(argv[i]);
        array[k] = amount;
        k++;
    }
    max = array[0];
    for (int i = 1; i < argc; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
            index = i;
        }
    }
    printf("%s", argv[index + 1]);
    free(array);
    return 0;
}

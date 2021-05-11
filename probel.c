//удалить все лишниие пробелы перед словами после слов между словами по 1 оставить
#include <stdio.h>
#include <stdlib.h>   //подключение библеотек
int length(char* str); //прототип функции
int del_space(char* str);
int main()
{
	int i, j, lines;        //объявление переменных
	printf("Input the number of lines:");  //кол-во строк в тексте
	scanf_s("%d", &lines);
	rewind(stdin);      //очистка буфера ввода чтобы правильно ввести строки
	char** str = (char**)calloc(lines, sizeof(char*));
	if (str == nullptr)
	{
		printf("\nNo memmory allocated.");  //объявление 'текста' и проверка на выделение памяти
		free(str);
		return 0;
	}
	for (i = 0; i < lines; i++)
	{
		str[i] = (char*)malloc(255 * sizeof(char)); //объявление строк и проверка на
		if (str[i] == nullptr)                        //выделение памяти
		{
			printf("\nNo memmory allocated.");
			for (j = 0; j < i; j++)
			{
				free(str[j]);
			}
			free(str);
			return 0;
		}
	}
	for (i = 0; i < lines; i++)
	{
		fgets(str[i], 255, stdin);
		rewind(stdin);
	}
	system("CLS");
	puts("ur text:");     //ввод и вывод изначального текста
	for (i = 0; i < lines; i++)
		puts(str[i]);
	//ggg
	//for (i = 0; i < lines; i++)
		//str[i] = del_space(str[i]);
	for (i = 0; i < lines; i++)
	for (int j = del_space(str[i]); j < length(str[i]) - 1; j++)  //удаление до первого слова
		str[j] = str[j + 1];
	//ggg
	puts("Changed text:");
	for (i = 0; i < lines; i++)  //вывод получившегося текста и освобождение памяти
		puts(str[i]);
	for (i = 0; i < lines; i++)
		free(str[i]);
	free(str);
	return 0;
}
int length(char* str)  //функция для нахождения размера строки
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}
/*
char* del_space(char* str) //функция удаления лишних пробелов
{
	int i, n = length(str);
	for (i = 0; i < n - 1; i++)
	{
		if (str[i] == ' ')
		{
			if (i == 0)
			{
				for (int j = i; j < n - 1; j++)  //удаление до первого слова
					str[j] = str[j + 1];
				n--;
				str = (char*)realloc(str, n * sizeof(char));
				i--;
			}
			if (str[i + 1] == '\0')// удаление после всех слов
			{
				str[i] = str[i + 1];
				n--;
				str = (char*)realloc(str, n * sizeof(char));
				i--;
			}
			if (str[i + 1] == ' ')  // удаление пробелов между словами больше 1
			{
				for (int j = i + 1; j < n - 1; j++)
					str[j] = str[j + 1];
				n--;
				str = (char*)realloc(str, n * sizeof(char));
				i--;
			}

		}
	}
	return str;
}
*/

int del_space(char* str)
{
	static int i = 0, n = length(str),index;
	if (i == 0)
	{
		return index = i;
		i++;
		del_space(str);
	}
	if (str[i + 1] == '\0')// удаление после всех слов
	{
		return index = i;
		i++;
		del_space(str);
	}
	if (str[i + 1] == ' ')  // удаление пробелов между словами больше 1
	{
		return index = i;
		i++;
		del_space(str);
	}
	i++;
	del_space(str);
}

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
int function(int, int*, int, ...);
int main()
{
int firstArray[] = { 1, 2, 3 },
secondArray[] = { 4, 5, 6, 7 },
thirdArray[] = { 8, 9 },
firstArraySize,
secondArraySize,
thirdArraySize;
setlocale(LC_ALL, "Russian");
firstArraySize = sizeof(firstArray) / sizeof(int);
secondArraySize = sizeof(secondArray) / sizeof(int);
thirdArraySize = sizeof(thirdArray) / sizeof(int);
puts("Результат первого вызова функции:");
printf("%d", function(3, firstArray, firstArraySize, secondArray,
secondArraySize, thirdArray, thirdArraySize));
puts("\n\nРезультат второго вызова функции:");

97

printf("%d", function(2, firstArray, firstArraySize, thirdArray,
thirdArraySize));
_getch();
return 0;
}
/* Первый параметр, передаваемый в функцию – число массивов,
второй – указатель на массив, третий – размерность массива */
int function(int arraysNumber, int *array, int arraySize, ...)
{
int *pointer1 = &arraySize; // указатель на размерность массива
int **pointer2 = &array; // указатель на указатель в стеке на массив
int maxSum = 0, sum, i;
while (arraysNumber--) // k == 0, если все массивы обработаны
{
sum = 0; // сумма для накопления по очередному массиву
for (i = 0; i < *pointer1; i++)
sum += *(*pointer2 + i);
if (maxSum < sum) // сравнение с контрольной суммой
maxSum = sum;
pointer2 += 2; // pointer2 передвигается на очередной массив (указатель)
pointer1 += 2; // pointer1 передвигается на его размерность
}
return maxSum; // возврат найденной суммы
}

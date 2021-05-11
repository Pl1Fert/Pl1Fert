#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <locale.h>

enum Types { Int, Float  } typ;

void summa(int groups, int len, Types typ, ...)
{
	int sumI = 0;
	float sumF = 0;
	va_list p;
	va_start(p, typ);
	while (groups--)
	{
		switch (typ)
		{
		case Int:
			while (len--)
			{
				sumI += va_arg(p, int);
			}
			break;
		case Float:
			while (len--)
			{
				sumF += va_arg(p, double);
			}
			break;
		}
		len = va_arg(p, int);
		typ = va_arg(p, enum Types);
		
	}
	va_end(p);
	printf("%d %f", sumI, sumF);
}
int main()
{
	summa(3,2,Int, 2, 2, 3, Float, 1.2, 3.8, 1.5, 4,Int,3, 5, 6, 4);
	return 0;
}

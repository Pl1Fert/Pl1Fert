#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <locale.h>

enum data{Int,Float } typ;

void summa( int groups, int len, data typ, ...)
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
					sumF += va_arg(p, float);
				}
				break;
		}
		len = va_arg(p, int);
		typ = va_arg(p, enum data);
	}
	va_end(p);
	printf("%d %f", sumI, sumF);
}
int main()
{
	summa(3, 3, Int, 1, 2, 3, Float, 1.2, 3.8, 1.5, Int, 5, 6, 4);
	return 0;
}

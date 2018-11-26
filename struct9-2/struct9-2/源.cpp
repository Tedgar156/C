#include <stdio.h>
int LongFun(int g)
{
		if (g == 1||g==2)
		{
			return 1;
		}
		else
		return LongFun(g-2)+LongFun(g - 1);
}
int Fun(int g)
{
	static int a = -1;
	a++;
	if (g == 1)
		return a;
	else if (g % 2 == 1)//ÆæÊý
		{
			Fun(3 * g + 1);
		}
		else
		{
			Fun(g / 2);
		}
}
int Func()
{
	int son, money;
	if
}
int main()
{
	int a, b;
	/*printf("1:");
	scanf("%d", &a);
	printf("%d\n",LongFun(a));*/
	printf("2:");
	scanf("%d",&b);
	printf("%d\n", Fun(b));
	return 0;
}
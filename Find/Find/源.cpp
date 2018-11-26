//查找
#include <stdio.h>
#define PI 10
int Search_bin(int map[], int length, int key)//折半查找
{
	int low = 0, max = length,i=length/2;
	while (low <= max)
	{
		i = (low + max) / 2;
		if (map[i] == key)
		{
			return i;
		}
		else if (map[i] < key)
		{
			low = i + 1;
		}
		else
		{
			max = i - 1;
		}
	}
	return -1;
}
void InsertSort(int r[],int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
	{
		r[0] = r[i];
		j = i - 1;
		while (r[0] < r[j])
		{
			r[j + 1] = r[j];
			j--;
		}
		r[j + 1] = r[0];
	}
}
int main()
{
	int i;
	int map[PI] = { 0, 1, 2, 3, 4, 5, 6, 7,8, 9 };
	i = Search_bin(map, PI, 10);
	if (i >= 0)
	{
		printf("位序是%d\n", i+1);
	}
	else
	{
		printf("未查找到\n");
	}
	int a[PI+5] = { 2, 26, 5, 48, 15, 23, 52, 21, 23, 10 };
	InsertSort(a, PI);
	for (int i = 0; i < PI; i++)
	{
		printf("%d\t", a[i]);
	}
	return 0; 
}
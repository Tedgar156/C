//����˳��
#include<stdio.h>
#define N 4
#define M 7
void Invert(int map[N + M], int temp,int n)//��temp���뵽��n��
{
	int i;
	static int j = N + M;
	j++;
	for (i = j- 1; i >= n-1; i--)
	{
		map[i+1] = map[i];
	}
	map[n - 1] = temp;
}
void exchange(int a[N + M], int n, int m)//�õ�n�����뵽m����
{
	int temp = a[n - 1];
		for (int i = n-1; i >= m; i--)
	{
		a[i] = a[i-1];
	}
	a[m - 1] = temp;
}
void interval(int b[N + M],int n,int m)//��n��m֮��Ľ���
{
	int temp;
	for (int i = n; i <= (m+n )/ 2; i++)
	{
		temp = b[i];
		b[i] = b[n + m - i];
		b[n + m - i] = temp;
	}
}
int main()
{
	int map[N + M+N+M] = { 0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//���뷨
	//����Ҫ������������ǰ��
	for (int i = N-1; i>=0 ; i--)
	{
		Invert(map, map[i], N+M+1);
	}
	for (int i = N; i < N+N + M; i++){
		printf("%d\n", map[i]);
	}
	int a[N + M] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = N+M; i > N; i--)
	{
		exchange(a, N+M, 1);
	}
	for (int i = 0; i < N + M; i++)
	{
		printf("%d\t", a[i]);
	}
	printf("\n");
	int b[N + M] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	interval(b, 0, N + M-1);
	interval(b, 0, M-1);
	interval(b, M, M + N-1);
	for (int i = 0; i < N + M; i++)
	{
		printf("%d\t", b[i]);
	}
	return 0;
}
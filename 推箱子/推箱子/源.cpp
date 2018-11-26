/**********************************************
**********文件名称:推箱子**********************
*********制作人:糖衣***************************
**********时间:2017-1-30***********************/
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<graphics.h>
#include<stdlib.h>
/*#define long 14
#define  high 13
#define win 10
int map[high][long] = {
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 0, 0, 4, 4, 1, 1, 1, 1, 1 },
	{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 0, 1, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 1 },
	{ 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 4, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 4, 0, 1, 0, 0, 0, 5, 0, 0, 1 },
	{ 1, 0, 4, 0, 4, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 4, 0, 1, 0, 1, 3, 3, 3, 1, 0 },
	{ 0, 1, 0, 1, 1, 0, 0, 0, 0, 3, 3, 3, 1, 0 },
	{ 0, 1, 0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } };*/
#define high 8
#define long 8
#define win 4
//0 空地 1 墙 3 目的地 4箱子 5人 
//■墙  ◆箱子 ○目的地 ●箱子入目 ☆人 ★人入目
int map[high][long] = {
	{0,0,1,1,1,0,0,0},
	{0,0,1,3,1,0,0,0},
	{0,0,1,0,1,1,1,1},
	{1,1,1,4,0,4,3,1},
	{1,3,0,4,5,1,1,1},
	{1,1,1,1,4,1,0,0},
	{0,0,0,1,3,1,0,0},
	{0,0,0,1,1,1,0,0}
};
void welcome()
{
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < long; j++)
		{
			if (map[i][j] == 0)
				printf("  ");
			else if (map[i][j] == 1)
				printf("■");
			else if (map[i][j] == 3)
				printf("○");
			else if (map[i][j] == 4)
				printf("◆");
			else if (map[i][j] == 5)
				printf("☆");
			else if (map[i][j] == 7)
				printf("●");
			else if (map[i][j] == 8)
				printf("★");
		}
		printf("\n");
	}
}
void play()
{
	int p;
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < long; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)
				break;
		}
		if (map[i][j] == 5 || map[i][j] == 8)
			break;
	}
	p=getch();
	switch (p)
	{
	case 80:
		if (map[i+1][j] == 0 || map[i+1][j] == 3)
		{
			map[i][j] -= 5;
			map[i+1][j] += 5;
		}
		else if (map[i + 1][j] == 4 || map[i + 1][j] == 7)
		{
			if (map[i + 2][j] == 0 || map[i + 2][j] == 3)
			{
				map[i][j] -= 5;
				map[i + 1][j] += 1;
				map[i + 2][j] += 4;
			}
		}
		break;
	case 72:
		if (map[i - 1][j] == 0 || map[i - 1][j] == 3)
		{
			map[i][j] -= 5;
			map[i - 1][j] += 5;
		}
		else if (map[i - 1][j] == 4 || map[i - 1][j] == 7)
		{
			if (map[i - 2][j] == 0 || map[i - 2][j] == 3)
			{
				map[i][j] -= 5;
				map[i - 1][j] += 1;
				map[i - 2][j] += 4;
			}
		}
		break;
	case 75:
		if (map[i][j-1] == 0 || map[i][j-1] == 3)
		{
			map[i][j] -= 5;
			map[i][j-1] += 5;
		}
		else if (map[i][j-1] == 4 || map[i][j-1] == 7)
		{
			if (map[i][j-2] == 0 || map[i][j-2] == 3)
			{
				map[i][j] -= 5;
				map[i][j-1] += 1;
				map[i][j-2] += 4;
			}
		}
		break;
	case 77:
		if (map[i][j + 1] == 0 || map[i][j + 1] == 3)
		{
			map[i][j] -= 5;
			map[i][j + 1] += 5;
		}
		else if (map[i][j + 1] == 4 || map[i][j + 1] == 7)
		{
			if (map[i][j + 2] == 0 || map[i][j + 2] == 3)
			{
				map[i][j] -= 5;
				map[i][j + 1] += 1;
				map[i][j + 2] += 4;
			}
		}
		break;
	default:
		break;
	}
}
int dege()
{
	int i,j,d=0;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < long; j++)
		{
			if (map[i][j] == 7)
				d++;
		}
	}
	if (d == win)
		return 1;
	else
		return 0;
}
int main()
{
	HWND hwnd;
	hwnd = GetHWnd();
	while (1)
	{
		system("cls");
		welcome();
		play();
		system("cls");	
		welcome();
		if (dege() == 1)
		{
			int a=MessageBox(hwnd, L"恭喜你闯关成功" ,L"赢了",MB_OK);
			if (a == IDOK)
				return 0;
		}
	}
}
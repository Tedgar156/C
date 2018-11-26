/***********************************************************
*****************工程名称:扫雷******************************
*****************制作人：糖衣*******************************
*****************竣工时间：2017/3/23************************
************************************************************
************************************************************/

#include<stdio.h>
#include<graphics.h>
#include<time.h>
#pragma comment (lib,"winmm.lib")
#define N 10
#define M 50
int welcome()
{
	mciSendString(L"open 女孩.mp3 alias img", 0, 0, 0);
	mciSendString(L"play img ", 0, 0, 0);
	IMAGE img;
	MOUSEMSG msg_1;
	loadimage(&img, L"beijing.jpg", N*M, N*M);
	setbkmode(TRANSPARENT);//透明
	settextstyle(30, 30, L"宋体");
	putimage(0, 0, &img);
	settextcolor(RGB(113, 62, 247));
	outtextxy(180, 100, L"BEGAIN");
	do{
		msg_1 = GetMouseMsg();
		if (msg_1.x >= 180 && msg_1.x < 330 && msg_1.y >= 230 && msg_1.y < 260)
		{
			settextcolor(RGB(0, 255, 0));
			outtextxy(140, 260, L"DIFFICULT");
			settextcolor(RGB(135, 1, 0));
			outtextxy(180, 230, L"ESSAY");
			switch (msg_1.uMsg)
			{
			case WM_LBUTTONDOWN:return N;
			}
		}
		else if (msg_1.x >= 140 && msg_1.x < 410 && msg_1.y >= 260 && msg_1.y < 290)
		{
			settextcolor(RGB(0, 255, 0));
			outtextxy(180, 230, L"ESSAY");
			settextcolor(RGB(135, 1, 0));
			outtextxy(140, 260, L"DIFFICULT");
			switch (msg_1.uMsg)
			{
			case WM_LBUTTONDOWN:return 3*N;
			}
		}
		else 
		{
			settextcolor(RGB(0, 255, 0));
			outtextxy(180, 230, L"ESSAY");
			settextcolor(RGB(0, 255, 0));
			outtextxy(140, 260, L"DIFFICULT");
		}
	}while (1);
}
void drew(int map[][N + 2], IMAGE *img)//显示出图片
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			switch (map[i][j])
			{
			case 9:putimage((i - 1)*M, (j - 1)*M, &img[10]); break;
			case 10:putimage((i - 1)*M, (j - 1)*M, &img[0]); break;
			case 11:putimage((i - 1)*M, (j - 1)*M, &img[1]); break;
			case 12:putimage((i - 1)*M, (j - 1)*M, &img[2]); break;
			case 13:putimage((i - 1)*M, (j - 1)*M, &img[3]); break;
			case 14:putimage((i - 1)*M, (j - 1)*M, &img[4]); break;
			case 15:putimage((i - 1)*M, (j - 1)*M, &img[5]); break;
			case 16:putimage((i - 1)*M, (j - 1)*M, &img[6]); break;
			case 17:putimage((i - 1)*M, (j - 1)*M, &img[7]); break;
			case 18:putimage((i - 1)*M, (j - 1)*M, &img[8]); break;
			default:putimage((i - 1)*M, (j - 1)*M, &img[9]); break;
			}
		}
	}
}
void loadinggame(int x, int y, int map[][N + 2], int *pnumber)
{
	//x y 为0的坐标
	map[x][y] += 10;
	(*pnumber)--;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i <= 0 || i >= 11 || j <= 0 || j >= 11)continue;
			if (map[i][j] <= 8)
			{
				if (map[i][j] == 0)
				{
					loadinggame(i, j, map, pnumber);
				}
				else if (map[i][j] != -1)
				{
					map[i][j] += 10;
					(*pnumber)--;
				}
			}
		}
	}
}

int play(int map[][N + 2], int *pnumber, IMAGE *img)
{
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)//获取鼠标信息
		{
		case WM_LBUTTONDOWN:
			if (map[msg.x / M + 1][msg.y / M + 1] == 0)
			{
				loadinggame(msg.x / M + 1, msg.y / M + 1, map, pnumber);//将周围是0的全部点开
			}
			else if (map[msg.x / M + 1][msg.y / M + 1] <= 8)
			{
				map[msg.x / M + 1][msg.y / M + 1] += 10;
				(*pnumber)--;
			}
			else continue;
			if (map[msg.x / M + 1][msg.y / M + 1] == 9)
				return -1;
			else return 0;
			break;
		case WM_RBUTTONDOWN:putimage(msg.x / M*M, msg.y / M*M, img); break;
		}
	}
}
void game()
{
	int a = welcome();
	IMAGE img[12];
	loadimage(&img[0], L"0.jpg", M, M);
	loadimage(&img[1], L"1.jpg", M, M);
	loadimage(&img[2], L"2.jpg", M, M);
	loadimage(&img[3], L"3.jpg", M, M);
	loadimage(&img[4], L"4.jpg", M, M);
	loadimage(&img[5], L"5.jpg", M, M);
	loadimage(&img[6], L"6.jpg", M, M);
	loadimage(&img[7], L"7.jpg", M, M);
	loadimage(&img[8], L"8.jpg", M, M);
	loadimage(&img[9], L"空.jpg", M, M);
	loadimage(&img[10], L"雷.jpg", M, M);
	loadimage(&img[11], L"标记.jpg", M, M);
	int map[N + 2][N + 2] = { 0 };
	srand((unsigned)time(NULL));
	int x, y;
	//int num = rand() % N*N;
	for (int i = 0; i <a;)//埋雷
	{
		x = rand() % N;
		y = rand() % N;
		if (map[x + 1][y + 1] == 0)
		{
			map[x + 1][y + 1] = -1;
			i++;
		}
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] != -1)//对不是雷区进行修改值
			{
				for (x = i - 1; x <= i + 1; x++)//对周围九个数进行累加
				{
					for (y = j - 1; y <= j + 1; y++)
					{
						if (map[x][y] == -1)//map[i][j]是一个雷
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}
	int number = N*N - N/*num*/;
	int *pnumber = &number;
	HWND hwnd = GetHWnd();
	while (1)
	{
		drew(map, img);
		if (play(map, pnumber, &img[11]) == -1)
		{
			drew(map, img);
			MessageBox(hwnd, L"很遗憾", L"OK", MB_OK);
			int a = MessageBox(hwnd, L"是否重玩", L"OK", MB_OKCANCEL);
			if (a == IDOK)
			{
				game();
			}
			break;
		}
		if (number == 0)
		{
			drew(map, img);
			MessageBox(hwnd, L"恭喜你赢了", L"OK", MB_OK);
			int a = MessageBox(hwnd, L"是否重玩", L"OK", MB_OKCANCEL);
			if (a == IDOK)
			{
				game();
			}
			break;
		}

	}
}
int main()
{
	initgraph(N*M, N*M);
	game();
	closegraph();
	return 0;
}
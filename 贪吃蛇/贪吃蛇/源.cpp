/***************************************
*            工程名称：贪吃蛇          *
*            制作人：糖衣              *
*            时间：2017/4/17           *
****************************************/
#include<graphics.h>
#include<stdlib.h>//随机数
#include<time.h>
#include<conio.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib")//添加背景音乐
#define snake_max 100
void Break();
typedef struct
{
	int x;
	int y;
}COOR;
struct Food
{
	COOR FoodC;//蛇的坐标
	int flag;//判断食物是否被吃
}food;
typedef struct 
{
	COOR skc[snake_max];
	int n;//节点个数
	int ch;//蛇的方向
}SNACK;
SNACK snack;//定义一个蛇的结构体
void Welcome()
{
	//mciSendString(L"open D:\\音乐/女孩.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"open 女孩.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"play bgm repeat", 0, 0, 0);//播放音乐
	IMAGE image;//定义一个图片
	MOUSEMSG msg;//定义一个获取鼠标信息
	//roundrect(0, 220, 220, 0, 50, 500);
	loadimage(&image, L"1.jpg", 640, 480);//加载图片
	putimage(0, 0, &image);//输出图片
	settextstyle(50, 0, L"Ravie");//长 宽(0自动匹配)
	setbkmode(TRANSPARENT);//字体透明设置背景风格(transparent)透明
	do{
		msg = GetMouseMsg();//获取鼠标信息
		if (msg.x >= 255 && msg.x < 430 && msg.y >= 185 && msg.y <= 220)//更改BEGAIN的颜色
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(255, 180, L"BEGAIN");
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:return;
			}
		}
		else if (msg.x >= 250 && msg.x < 390 && msg.y >= 260 && msg.y < 290)
		{
			settextcolor(RGB(255, 0, 0));//设置字体颜色 red green black
			outtextxy(255, 250, L"OVER");//输出
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:exit(1);
			}
		}
		else
		{
			settextcolor(RGB(137, 57, 196));//设置字体颜色 red green black
			outtextxy(255, 180, L"BEGAIN");//输出
			outtextxy(255, 250, L"OVER");
		}
		
	} while (1);
	//mkCtrl判断是否按下ctrl
}
void GameInit()
{
	srand((unsigned int)time (NULL));//随机一个数  需要用到的头文件:stdlib.h time.h
	setbkcolor(RGB(50, 17, 50));//背景颜色
	cleardevice();//清屏
	setlinecolor(RED);//设置轮廓颜色
	setfillcolor(BLACK);//设置填充颜色
	snack.ch = 77;//蛇初始状态为向右
	snack.skc[0].x = 10;
	snack.skc[0].y = 0;//初始蛇的第一节位置
	snack.skc[1].x = 0;
	snack.skc[1].y = 0;//初始蛇的第二节位置
	snack.n = 8;//初始蛇的节数
	food.flag = 0;//被吃掉的
}
void MoveGame()
{
	for (int i = snack.n - 1; i > 0; i--)
	{
		snack.skc[i].x = snack.skc[i - 1].x;
		snack.skc[i].y = snack.skc[i - 1].y;
	}
	switch (snack.ch)
	{
	case 72://向上走
		snack.skc[0].y -= 10;
		setfillcolor(BLACK);
		break;
	case 80://想下走
		snack.skc[0].y += 10;
		setfillcolor(BLACK);
		break;
	case 77://想右走
		snack.skc[0].x += 10;
		setlinecolor(RED);
		break;
	case 75://向左走
		snack.skc[0].x -= 10; 
		setlinecolor(RED);
		break;
	default:break;
	}
	Break();
	for (int i = 0; i <snack.n ; i++)
	{
		fillrectangle(snack.skc[i].x, snack.skc[i].y,
			snack.skc[i].x + 10, snack.skc[i].y + 10);
	}
}
void ChangeDriction()
{
	int movech;
	movech = getch();
	switch (movech)
	{
	case 72:if (snack.ch!=80)
		snack.ch = 72; break;
	case 80:if (snack.ch!=72)
		snack.ch = 80; break;
	case 75:if (snack.ch!=77)
		snack.ch = 75; break;
	case 77:if (snack.ch!=75)
		snack.ch = 77; break;
	default:break;
	}
}
void FoodInit()
{
	food.FoodC.x = (rand() % 640 / 10) * 10;
	food.FoodC.y = (rand() % 480 / 10) * 10;
	food.flag = 1;
}
void DrawFood()
{
	setfillcolor(RED);
	fillroundrect(food.FoodC.x, food.FoodC.y, food.FoodC.x + 10, food.FoodC.y + 10, 10, 10);
}
void EatFood()
{
	if (snack.skc[0].x == food.FoodC.x&&snack.skc[0].y == food.FoodC.y)
	{
		snack.n++;
		food.flag = 0;
	}
}
int Judge()
{
	int a = rand() % 2;
	if (a > 0)
	{
		if (snack.skc[0].x < 0)
		{
			snack.skc[0].x += 640;
		}
		else if (snack.skc[0].y < 0)
		{
			snack.skc[0].y += 480;
		}
		else if (snack.skc[0].x>630)
		{
			snack.skc[0].x -= 640;
		}
		else if (snack.skc[0].y > 470)
		{
			snack.skc[0].y -= 480;
		}
	}
	else
	{
		if (snack.skc[0].x < 0 || snack.skc[0].y < 0 || snack.skc[0].x>630 || snack.skc[0].y > 470)
		{
			return 1;
		}
	}
	for (int i = 1; i < snack.n; i++)
	{
		if (snack.skc[0].x == snack.skc[i].x&&snack.skc[0].y == snack.skc[i].y)
			return 1;
	}
	return 0;
}
void Game()
{
	Welcome();
	GameInit();
	while (1)
	{

		while (!_kbhit())
		{
			if (food.flag == 0)
				FoodInit();
			cleardevice();
			MoveGame();
			DrawFood();
			EatFood();
			Sleep(100);
		}
		ChangeDriction();
	}
}
void Break()
{
	HWND Hwnd;
	Hwnd = GetHWnd();
	if (Judge()>0)
	{
		if (MessageBox(Hwnd, L"游戏结束", L"GAME OVER", MB_OK) == IDOK)
		{
			if (MessageBox(Hwnd, L"游戏结束", L"是否重玩", MB_OKCANCEL) == IDOK)
			{
				Game();
			}
			else
			{
				exit(1);
			}
		}
		
	}
	else return;
}
int main()
{
	initgraph(640,480);
	int flag=1;
	Game();
	getchar();  
	closegraph();
}
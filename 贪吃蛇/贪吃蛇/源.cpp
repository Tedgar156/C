/***************************************
*            �������ƣ�̰����          *
*            �����ˣ�����              *
*            ʱ�䣺2017/4/17           *
****************************************/
#include<graphics.h>
#include<stdlib.h>//�����
#include<time.h>
#include<conio.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib")//��ӱ�������
#define snake_max 100
void Break();
typedef struct
{
	int x;
	int y;
}COOR;
struct Food
{
	COOR FoodC;//�ߵ�����
	int flag;//�ж�ʳ���Ƿ񱻳�
}food;
typedef struct 
{
	COOR skc[snake_max];
	int n;//�ڵ����
	int ch;//�ߵķ���
}SNACK;
SNACK snack;//����һ���ߵĽṹ��
void Welcome()
{
	//mciSendString(L"open D:\\����/Ů��.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"open Ů��.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"play bgm repeat", 0, 0, 0);//��������
	IMAGE image;//����һ��ͼƬ
	MOUSEMSG msg;//����һ����ȡ�����Ϣ
	//roundrect(0, 220, 220, 0, 50, 500);
	loadimage(&image, L"1.jpg", 640, 480);//����ͼƬ
	putimage(0, 0, &image);//���ͼƬ
	settextstyle(50, 0, L"Ravie");//�� ��(0�Զ�ƥ��)
	setbkmode(TRANSPARENT);//����͸�����ñ������(transparent)͸��
	do{
		msg = GetMouseMsg();//��ȡ�����Ϣ
		if (msg.x >= 255 && msg.x < 430 && msg.y >= 185 && msg.y <= 220)//����BEGAIN����ɫ
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
			settextcolor(RGB(255, 0, 0));//����������ɫ red green black
			outtextxy(255, 250, L"OVER");//���
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:exit(1);
			}
		}
		else
		{
			settextcolor(RGB(137, 57, 196));//����������ɫ red green black
			outtextxy(255, 180, L"BEGAIN");//���
			outtextxy(255, 250, L"OVER");
		}
		
	} while (1);
	//mkCtrl�ж��Ƿ���ctrl
}
void GameInit()
{
	srand((unsigned int)time (NULL));//���һ����  ��Ҫ�õ���ͷ�ļ�:stdlib.h time.h
	setbkcolor(RGB(50, 17, 50));//������ɫ
	cleardevice();//����
	setlinecolor(RED);//����������ɫ
	setfillcolor(BLACK);//���������ɫ
	snack.ch = 77;//�߳�ʼ״̬Ϊ����
	snack.skc[0].x = 10;
	snack.skc[0].y = 0;//��ʼ�ߵĵ�һ��λ��
	snack.skc[1].x = 0;
	snack.skc[1].y = 0;//��ʼ�ߵĵڶ���λ��
	snack.n = 8;//��ʼ�ߵĽ���
	food.flag = 0;//���Ե���
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
	case 72://������
		snack.skc[0].y -= 10;
		setfillcolor(BLACK);
		break;
	case 80://������
		snack.skc[0].y += 10;
		setfillcolor(BLACK);
		break;
	case 77://������
		snack.skc[0].x += 10;
		setlinecolor(RED);
		break;
	case 75://������
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
		if (MessageBox(Hwnd, L"��Ϸ����", L"GAME OVER", MB_OK) == IDOK)
		{
			if (MessageBox(Hwnd, L"��Ϸ����", L"�Ƿ�����", MB_OKCANCEL) == IDOK)
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
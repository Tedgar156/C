/****************************************
*              ���̣��Թ�               *
*              �����ˣ�����             *
*              ʱ�䣺2017/4/23          *
*****************************************/
/*#include<stdio.h>
#include<Windows.h>
#include<time.h>
#define HIGHT 47
#define WIDTH 47
#define WALL 1
#define ROAD 0
#define START 2
#define END 3
int map[WIDTH + 2][HIGHT + 2];
//void gotoxy(int x, int y)
//{
//	COORD pos;//��ȡ���
//	pos.X = x;
//	pos.Y= y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}
void Paint(int x, int y)
{
	//gotoxy(2 * y , x - 1);
	switch (map[x][y])
	{
	case ROAD:printf("  ");
		break;
	case WALL:printf("��");
		break;
	case START:printf("��");
		break;
	case END:printf("��");
		break;
	}
}
void CreatMaze(int x,int y)
{
	int dir[4][2] = { 0, 1,//�������ϼ��������Ϊ����
		1, 0,//�������ϼ��������Ϊ����
		0, -1,//�������ϼ��������Ϊ����
		-1, 0 };//�������ϼ��������Ϊ����
	int j, temp;
	for (int i = 0; i < 4; i++)//�������˳��
	{
		j = rand() % 4;//map[j][0] map[j][1]
		temp = dir[j][0];
		dir[j][0] = dir[i][0];
		dir[i][0] = temp;
		temp = dir[j][1];
		dir[j][1] = dir[i][1];
		dir[i][1] = temp;
	}
	map[x][y] = ROAD;
	for (int i = 0; i < 4; i++)
	{
		if (map[x + 2 * dir[i][0]][y + 2 * dir[i][1]]==WALL)
		{
			map[x + dir[i][0]][y + dir[i][1]] = ROAD;
			CreatMaze(x + 2 * dir[i][0],y + 2 * dir[i][1]);
		}
	}
}
int main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < WIDTH + 2; i++)
	{
		for (int j = 0; j < HIGHT + 2; j++)
		{
			if (i == 0 || i == HIGHT + 1 || j == 0 || j == WIDTH + 1)
			{
				map[i][j] = ROAD;
			}
			else
			{
				map[i][j] = WALL;
			}
		}
	}
	CreatMaze(2 * (rand() % (HIGHT / 2) + 1), 2 * (rand() % (WIDTH / 2) + 1));//�������һ����
	map[2][1] = START;
	map[HIGHT-1][WIDTH] = END;
	for (int i = 1; i < HIGHT+1; i++)
	{
		for (int j = 1; j < WIDTH+1; j++)
		{
			Paint(i, j);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}*/
#include<stdio.h>
#include<graphics.h>
#define	WINDWIDTH 640//���ڿ�
#define WINDWEIGHT 480//���ڸ�
#define WIDTH 480//�Թ���
#define HEIGHT 480//�Թ���
#define WALL 1//ǽ
#define ROAD 0//·
#define UNIT 20
const SIZE g_utMap = { 23, 23 };
const POINT g_uiExit = { 21, 22 };
IMAGE g_imgMap(WIDTH, HEIGHT);
DWORD *g_bufMap;//�Թ��Դ� 
IMAGE g_imgRender(WIDTH, HEIGHT);
DWORD *g_bufRender;//
DWORD *g_bufScreen;//������Ļ�Դ�
void WELCOME();
int main()
{
	initgraph(WINDWIDTH, WINDWEIGHT);
	WELCOME();
	getchar();
	closegraph();
	return 0;
}
void WELCOME()
{
	setfillcolor(DARKGRAY);
	solidrectangle(WIDTH, 0, WINDWIDTH, WINDWEIGHT);
	setbkmode(TRANSPARENT);
	outtextxy(490, 100, L"�ٺ�");
}
void Ready()
{
	InitGame();
}
void InitGame()
{
	g_bufRender = GetImageBuffer(&g_imgRender);
	g_bufMap = GetImageBuffer(&g_imgMap);
	g_bufScreen = GetImageBuffer(NULL);
	SetWorkingImage(&g_imgRender);
	setbkmode(TRANSPARENT);
	SetWorkingImage(NULL);
}
void CreatMap(int width, int height)
{
	int x, y;
	BYTE**arymap=new BYTE*[width+2];
	for (x = 0; x < width + 2; x++)
	{
		arymap[x] = new BYTE[height + 2];
		memset(arymap[x], WALL, height + 2);
	}
	for (x = 0; x <= width + 1; x++)
	{
		arymap[x][0] = arymap[x][height + 1] = ROAD;
	}
	for (y = 0; y <= height + 1; y++)
	{
		arymap[0][y] = arymap[width + 1][y] = ROAD;
	}
}
void TraveMap(int x, int y, BYTE **arymap)
{
	int j, temp;
	int dir[4][2] = { 0, 1, 0, -1, 1, 0, -1, 0 };
	for (int i = 0; i < 4; i++)
	{
		j = rand() % 4;
		temp = dir[j][0];
		dir[j][0] = dir[i][0];
		dir[i][0] = temp;
		temp = dir[j][1];
		dir[j][1] = dir[i][1];
		dir[i][1] = temp;
	}
	arymap[x][y] = ROAD;
	for (int i = 0; i < 4; i++)
	{
		if (arymap[x + 2*dir[i][0]][y +2*dir[i][1]] == WALL)
		{
			arymap[x + dir[i][0]][y + dir[i][1]] = ROAD;
			TraveMap(x + dir[i][0], y + dir[i][1],arymap);
		}
	}
}
void DrawWall(int x, int y, bool left, bool right, bool up, bool down)
{
	int cx, cy;
	cx = x*UNIT - UNIT / 2 - 2 + 10;
	cy = y*UNIT - UNIT / 2 - 2 + 10;
	if (left) solidrectangle(x*UNIT - UNIT + 10, cy, cx + 4, cy + 4);
	if (right)solidrectangle(cx, cy, x*UNIT + 9, cy + 4);
	if (up)solidrectangle(cy, x*UNIT - UNIT + 10, cx + 4, cy + 4);
	if (down)solidrectangle(cx, cy, x*UNIT + 9, cy + 4);
}
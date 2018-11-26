// 流星雨.cpp : Defines the entry point for the console application.
//

/////////////////////////////////////////////////// 
// 程序名称：数字流星雨 
// 最后修改：2006-10-15
/////////////////////////////////////////////////// 
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

/***********************宏定义**********************/
#define PI 3.1415926										//圆周率
#define WIDTH 200											//屏幕宽度，流星出生区域
#define HEIGHT 150											//屏幕高度，流星出生区域
#define V 20												//流星速度，单次移动的像素数
#define LENGTH	20											//流星字符数
#define DELAY 30											//延时
#define NUM 45												//流星个数


/******************定义流星结构体*******************/
struct meteor
{
	int x0;
	int y0;
	int yh;
	char str[LENGTH];
}me[NUM] = { 0 };

/*********************函数声明**********************/
char AsciiRand();
void Move(char *p);
void InitMeteor(struct meteor *me);
int color(int y, int y0, int yh);
void Meteors(struct meteor me[]);

/***********************主函数**********************/
///int main(void)

int _tmain(int argc, _TCHAR* argv[]){

	char c = '\0'; //接收键盘输入的变量	
	initgraph(WIDTH, HEIGHT); //初始化 WIDTH * HEIGHT的绘图窗口


	HWND hwnd = GetHWnd(); //获得窗口句柄
	SetWindowText(hwnd, "Gavin Liu 数字流星雨"); 	//修改窗口名称
	ShowWindow(hwnd, SW_SHOWMAXIMIZED); 	//最大化显示窗口	
	MessageBox(hwnd, TEXT("点击【确定】开始演示流星雨效果，Esc键退出"), TEXT("提示"), MB_OK | MB_ICONWARNING); //弹出提示


	srand((unsigned)time(NULL)); 	//设置随机种子

	for (int i = 0; i < NUM; i++){ 	//对NUM个流星体初始化
		InitMeteor(&me[i]);
	}

	while (c != 27){
		BeginBatchDraw(); 		//开始批量绘图
		Meteors(me); 		//绘制一帧动画

		FlushBatchDraw(); 		//执行未完成的绘制任务


		Sleep(DELAY);  		//延时
		cleardevice(); 		//清屏

		for (int i = 0; i < NUM; i++){

			me[i].yh += V;
			Move(me[i].str);
			if (me[i].yh > HEIGHT + LENGTH * V){
				InitMeteor(&me[i]);
			}
		}

		if (kbhit())	{
			c = getch();
		}
	}

	EndBatchDraw();  	//结束批量绘图
	closegraph(); 	//结束绘图环境
	return 0;
}

/***********************函数体**********************/


char AsciiRand(){  //产生随机可见ASCII码
	return ((char)(rand() % (126 - 33) + 33));
}


void Move(char *p){  //字符后移，可以使显示时字符相对屏幕位置不变
	char *pt = p + LENGTH;
	while (pt > p){
		*(--pt) = *(pt - 1);
	}
	*p = AsciiRand();
}


void InitMeteor(struct meteor *me){ //对一颗流星初始化
	me->x0 = rand() % WIDTH;
	me->yh = me->y0 = rand() % HEIGHT;

	for (int i = 0; i < LENGTH; i++)
	{
		*(me->str + i) = AsciiRand();
	}
}


int color(int y, int y0, int yh) {//确定流星的颜色
	int color;

	//出生点之前的流星体置成黑色
	if (y < y0)	{
		color = 0;
	}

	//流星颜色自头至尾按照余弦函数递减
	else{
		//尾迹消失
		color = (int)(255 * cos((yh - y) * PI / (2 * LENGTH * V)));
	}
	return color;
}


//打印一帧流星的画面
void Meteors(struct meteor me[]){
	//设置格式：背景透明，字符高度，字体粗细，字体
	setbkmode(TRANSPARENT);
	setfont(12, 12, "宋体");

	//开始打印一帧图像
	int y;
	for (int n = 0; n < NUM; n++){
		for (int j = 0; j < LENGTH; j++)	{
			//流星中第j个字符的纵坐标
			y = me[n].yh - j * V;

			//设置颜色，流星的头部是白色的
			setcolor(RGB(255 * (0 == j), color(y, me[n].y0, me[n].yh), 255 * (0 == j)));

			//打印字符
			outtextxy(me[n].x0, y, me[n].str[j]);
		}
	}
}

#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>//播放音频
#pragma comment(lib,"WINMM.LIB")//WINMM.LIB预处理
#define NumOfColumn 25
/*
1.创建wind32工程
2.注册窗口
3.窗口处理函数
4.创建窗口
5.显示窗口
6.消息循环
*/




typedef struct charList
{

	struct charList *prev;
	TCHAR ch;
	struct charList *next;

}CharList;





typedef struct tegcharColum
{
	CharList *head,*cur,*front;
	int x, y;
	int iStrNum;//记录总共显示的字符数
	int iShowLen;//记录需要的个数
}CharQueue;
//这个结构体用来保存所有需要显示的字符

struct showChar{
	TCHAR myChar[60];//显示60个字符
	int iNum;//字符个数
}charArry[5] = {//戴望舒 《雨巷》
	{ TEXT("撑着油纸伞，独自彷徨在雨巷"),13 },//加TEXT 这个一个宽字节 unicode
	{ TEXT("我想"),2 },
	{ TEXT("和你"),2 },
	{ TEXT("在一"),2 },
	{ TEXT("一起"),2 }
};






LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,LPARAM LParam);//窗口处理

int WINAPI WinMain(HINSTANCE hInstance//实列句柄
	, HINSTANCE hPrevInstance//上一个句柄
	, PSTR szCmdLine//命令行
	, int iCmdShow)//显示方式
{
	TCHAR szClassName[] = L"love";//加L 是unicode编码宽字节
	//窗口注册
	WNDCLASS wndClass;//注册窗口类
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//窗口风格 窗口大小发生改变进行重绘
	wndClass.cbClsExtra = 0;//附加信息
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;//处理窗口消息 WndProc处理函数
	wndClass.hInstance = hInstance;
	wndClass.hCursor = NULL;//光标
	wndClass.hIcon = NULL;//图标
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//处理背景 得到画刷
	wndClass.lpszMenuName = NULL;//菜单
	wndClass.lpszClassName = szClassName;//类名
	//窗口注册
	PlaySound(L"LoveStory.mp4",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);


	if (!RegisterClass(&wndClass)){
		MessageBox(NULL, TEXT("注册失败！"), TEXT("错误信息"),MB_ICONERROR);
		return -1;
	}


	HWND hwnd = CreateWindow(szClassName, NULL, WS_POPUP | WS_THICKFRAME, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);//创建窗口:窗口名字，窗口风格，窗口大小（长度、宽度),实例句柄，附加消息
	
	


	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


void CreateQueue(CharQueue *cc,int cyScreen,int x)//创建队列
{

	cc->head = NULL;
	cc->iShowLen = 1;
	cc->x = x;
	cc->y = rand() % 10 ? rand() % cyScreen : 0;
	int NumTemp = rand() % 6;
	cc->iStrNum = charArry[NumTemp].iNum;

	charList *front;

	cc->head=cc->cur=cc->front=(CharList*)calloc(cc->iStrNum,sizeof(CharList));//calloc与malloc功能相同，calloc能自动初始化
	
	
	
	
	
	int i;
	for (i = 0; i < cc->iStrNum - 1; i++)
	{
		cc->cur->prev = front;
		cc->cur->ch = charArry[NumTemp].myChar[i];
		front = cc->cur++;
		front->next = cc->cur;
	}
	cc->cur->prev = front;
	cc->cur->ch = charArry[NumTemp].myChar[i];
	cc->cur->next = cc->head;
	cc->head->prev = cc->cur;
	cc->cur = cc->head;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM LParam)

{
	HDC hdc;
	static HDC hdcMem;
	static HBITMAP hBitemp;
	static CharQueue *AllChar;
	HFONT hFont;
	static int cxScreen, cyScreen;
	static int iFontWidth = 20, iFontHeight = 20;
	int i, j, y, greenToblack;
	CharQueue *ccElem;
	CharList *temp;

	switch (message)
	{
	case WM_CREATE:
		cxScreen = GetSystemMetrics(SM_CXSCREEN);
		cyScreen = GetSystemMetrics(SM_CYSCREEN);
		SetTimer(hwnd, 1, 70, NULL);

		hdc = GetDC(hwnd);
		hdcMem = CreateCompatibleDC(hdc);
		hBitemp = CreateCompatibleBitmap(hdc, cxScreen, cyScreen);
		SelectObject(hdcMem, hBitemp);
		ReleaseDC(hwnd, hdc);

		hFont = CreateFont(iFontHeight, iFontWidth, 0,0,400,FALSE,FALSE,0,/*角度设置*/
			DEFAULT_CHARSET/*字符集*/, OUT_DEFAULT_PRECIS,/*指定输出*/CLIP_DEFAULT_PRECIS,
			DRAFT_QUALITY/*指向输出质量*/,FIXED_PITCH|FF_SWISS,L"微软雅黑");
		SelectObject(hdcMem, hFont);
		DeleteObject(hFont);

		SetBkMode(hdcMem, TRANSPARENT);



		AllChar = (CharQueue*)calloc(NumOfColumn, sizeof(CharQueue));
		for (i = 0; i < NumOfColumn; i++)
		{
			CreateQueue(AllChar + i, cyScreen, 50 * i + 20);
		}
		return 0;
	case WM_TIMER:
		PatBlt(hdcMem, 0, 0, cxScreen, cyScreen, BLACKNESS);

		for (i = 0; i < NumOfColumn; i++)
		{
			ccElem = AllChar + i;

			temp = ccElem->head;
			SetTextColor(hdcMem, RGB(255, 255, 255));
			TextOut(hdc, ccElem->x, ccElem->y, &temp->ch, 1);

			y = ccElem->y;
			greenToblack = 0;
			ccElem->head = ccElem->head->next;

			for (j = 1; j < ccElem->iShowLen; j++)
			{
				SetTextColor(hdcMem, RGB(255, 255, 255));
				TextOut(hdcMem, ccElem->x, y -= iFontHeight, &temp->ch, 1);
				temp = temp->prev;
			}

			if (ccElem->iShowLen < ccElem->iStrNum)
			{
				ccElem->iShowLen++;
			}

			ccElem->y += iFontHeight;
			if (ccElem->y - ccElem->iStrNum*iFontHeight>cyScreen)
			{
				free(ccElem->cur);
				CreateQueue(ccElem, cyScreen, 128 * i + 17);
			}

		}
		hdc = GetDC(hwnd);
		BitBlt(hdc, 0, 0, cxScreen, cyScreen, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(hwnd, hdc);
		return 0;
		//
	}
	return DefWindowProc(hwnd, message, wParam, LParam);
}
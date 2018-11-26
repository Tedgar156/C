#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>//������Ƶ
#pragma comment(lib,"WINMM.LIB")//WINMM.LIBԤ����
#define NumOfColumn 25
/*
1.����wind32����
2.ע�ᴰ��
3.���ڴ�����
4.��������
5.��ʾ����
6.��Ϣѭ��
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
	int iStrNum;//��¼�ܹ���ʾ���ַ���
	int iShowLen;//��¼��Ҫ�ĸ���
}CharQueue;
//����ṹ����������������Ҫ��ʾ���ַ�

struct showChar{
	TCHAR myChar[60];//��ʾ60���ַ�
	int iNum;//�ַ�����
}charArry[5] = {//������ �����
	{ TEXT("������ֽɡ����������������"),13 },//��TEXT ���һ�����ֽ� unicode
	{ TEXT("����"),2 },
	{ TEXT("����"),2 },
	{ TEXT("��һ"),2 },
	{ TEXT("һ��"),2 }
};






LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,LPARAM LParam);//���ڴ���

int WINAPI WinMain(HINSTANCE hInstance//ʵ�о��
	, HINSTANCE hPrevInstance//��һ�����
	, PSTR szCmdLine//������
	, int iCmdShow)//��ʾ��ʽ
{
	TCHAR szClassName[] = L"love";//��L ��unicode������ֽ�
	//����ע��
	WNDCLASS wndClass;//ע�ᴰ����
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//���ڷ�� ���ڴ�С�����ı�����ػ�
	wndClass.cbClsExtra = 0;//������Ϣ
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;//��������Ϣ WndProc������
	wndClass.hInstance = hInstance;
	wndClass.hCursor = NULL;//���
	wndClass.hIcon = NULL;//ͼ��
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//������ �õ���ˢ
	wndClass.lpszMenuName = NULL;//�˵�
	wndClass.lpszClassName = szClassName;//����
	//����ע��
	PlaySound(L"LoveStory.mp4",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);


	if (!RegisterClass(&wndClass)){
		MessageBox(NULL, TEXT("ע��ʧ�ܣ�"), TEXT("������Ϣ"),MB_ICONERROR);
		return -1;
	}


	HWND hwnd = CreateWindow(szClassName, NULL, WS_POPUP | WS_THICKFRAME, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);//��������:�������֣����ڷ�񣬴��ڴ�С�����ȡ����),ʵ�������������Ϣ
	
	


	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	//��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


void CreateQueue(CharQueue *cc,int cyScreen,int x)//��������
{

	cc->head = NULL;
	cc->iShowLen = 1;
	cc->x = x;
	cc->y = rand() % 10 ? rand() % cyScreen : 0;
	int NumTemp = rand() % 6;
	cc->iStrNum = charArry[NumTemp].iNum;

	charList *front;

	cc->head=cc->cur=cc->front=(CharList*)calloc(cc->iStrNum,sizeof(CharList));//calloc��malloc������ͬ��calloc���Զ���ʼ��
	
	
	
	
	
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

		hFont = CreateFont(iFontHeight, iFontWidth, 0,0,400,FALSE,FALSE,0,/*�Ƕ�����*/
			DEFAULT_CHARSET/*�ַ���*/, OUT_DEFAULT_PRECIS,/*ָ�����*/CLIP_DEFAULT_PRECIS,
			DRAFT_QUALITY/*ָ���������*/,FIXED_PITCH|FF_SWISS,L"΢���ź�");
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
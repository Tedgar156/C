#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
int main()
{
	
	mciSendString(L"open Ů��.mp3", 0, 0, 0);
	mciSendString(L"play Ů��.mp3", 0, 0, 0);
	int result;
	HWND hwnd;
	IMAGE image;
	initgraph(640, 480);
	loadimage(&image, L"1.j", 640, 480);
	hwnd = GetHWnd();
	putimage(0, 0, &image);
	setbkmode(TRANSPARENT);
	outtextxy(300, 240, L"����sb��");
	do{
		result = MessageBox(hwnd, TEXT("����SB"), TEXT("SB���ܿ���"), MB_OKCANCEL);
		putimage(0, 0, &image);
		switch (result)
		{
		case IDOK:MessageBox(hwnd, TEXT("��ȷʵ��SB"), TEXT("���Ǹ�SB"), MB_OK); putimage(0, 0, &image); break;
		case IDCANCEL:MessageBox(hwnd, TEXT("������Ǹ�SB��������ϵͳ"), TEXT("������������SB"), MB_OK); putimage(0, 0, &image); break;
		}
	} while (1);
	closegraph();
	return 0;
}
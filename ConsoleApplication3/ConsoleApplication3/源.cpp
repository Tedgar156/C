#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
int main()
{
	
	mciSendString(L"open 女孩.mp3", 0, 0, 0);
	mciSendString(L"play 女孩.mp3", 0, 0, 0);
	int result;
	HWND hwnd;
	IMAGE image;
	initgraph(640, 480);
	loadimage(&image, L"1.j", 640, 480);
	hwnd = GetHWnd();
	putimage(0, 0, &image);
	setbkmode(TRANSPARENT);
	outtextxy(300, 240, L"你是sb吗？");
	do{
		result = MessageBox(hwnd, TEXT("你是SB"), TEXT("SB才能看见"), MB_OKCANCEL);
		putimage(0, 0, &image);
		switch (result)
		{
		case IDOK:MessageBox(hwnd, TEXT("你确实是SB"), TEXT("真是个SB"), MB_OK); putimage(0, 0, &image); break;
		case IDCANCEL:MessageBox(hwnd, TEXT("你真的是个SB，请相信系统"), TEXT("还不相信你是SB"), MB_OK); putimage(0, 0, &image); break;
		}
	} while (1);
	closegraph();
	return 0;
}
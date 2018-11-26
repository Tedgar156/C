// ������.cpp : Defines the entry point for the console application.
//

/////////////////////////////////////////////////// 
// �������ƣ����������� 
// ����޸ģ�2006-10-15
/////////////////////////////////////////////////// 
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

/***********************�궨��**********************/
#define PI 3.1415926										//Բ����
#define WIDTH 200											//��Ļ��ȣ����ǳ�������
#define HEIGHT 150											//��Ļ�߶ȣ����ǳ�������
#define V 20												//�����ٶȣ������ƶ���������
#define LENGTH	20											//�����ַ���
#define DELAY 30											//��ʱ
#define NUM 45												//���Ǹ���


/******************�������ǽṹ��*******************/
struct meteor
{
	int x0;
	int y0;
	int yh;
	char str[LENGTH];
}me[NUM] = { 0 };

/*********************��������**********************/
char AsciiRand();
void Move(char *p);
void InitMeteor(struct meteor *me);
int color(int y, int y0, int yh);
void Meteors(struct meteor me[]);

/***********************������**********************/
///int main(void)

int _tmain(int argc, _TCHAR* argv[]){

	char c = '\0'; //���ռ�������ı���	
	initgraph(WIDTH, HEIGHT); //��ʼ�� WIDTH * HEIGHT�Ļ�ͼ����


	HWND hwnd = GetHWnd(); //��ô��ھ��
	SetWindowText(hwnd, "Gavin Liu ����������"); 	//�޸Ĵ�������
	ShowWindow(hwnd, SW_SHOWMAXIMIZED); 	//�����ʾ����	
	MessageBox(hwnd, TEXT("�����ȷ������ʼ��ʾ������Ч����Esc���˳�"), TEXT("��ʾ"), MB_OK | MB_ICONWARNING); //������ʾ


	srand((unsigned)time(NULL)); 	//�����������

	for (int i = 0; i < NUM; i++){ 	//��NUM���������ʼ��
		InitMeteor(&me[i]);
	}

	while (c != 27){
		BeginBatchDraw(); 		//��ʼ������ͼ
		Meteors(me); 		//����һ֡����

		FlushBatchDraw(); 		//ִ��δ��ɵĻ�������


		Sleep(DELAY);  		//��ʱ
		cleardevice(); 		//����

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

	EndBatchDraw();  	//����������ͼ
	closegraph(); 	//������ͼ����
	return 0;
}

/***********************������**********************/


char AsciiRand(){  //��������ɼ�ASCII��
	return ((char)(rand() % (126 - 33) + 33));
}


void Move(char *p){  //�ַ����ƣ�����ʹ��ʾʱ�ַ������Ļλ�ò���
	char *pt = p + LENGTH;
	while (pt > p){
		*(--pt) = *(pt - 1);
	}
	*p = AsciiRand();
}


void InitMeteor(struct meteor *me){ //��һ�����ǳ�ʼ��
	me->x0 = rand() % WIDTH;
	me->yh = me->y0 = rand() % HEIGHT;

	for (int i = 0; i < LENGTH; i++)
	{
		*(me->str + i) = AsciiRand();
	}
}


int color(int y, int y0, int yh) {//ȷ�����ǵ���ɫ
	int color;

	//������֮ǰ���������óɺ�ɫ
	if (y < y0)	{
		color = 0;
	}

	//������ɫ��ͷ��β�������Һ����ݼ�
	else{
		//β����ʧ
		color = (int)(255 * cos((yh - y) * PI / (2 * LENGTH * V)));
	}
	return color;
}


//��ӡһ֡���ǵĻ���
void Meteors(struct meteor me[]){
	//���ø�ʽ������͸�����ַ��߶ȣ������ϸ������
	setbkmode(TRANSPARENT);
	setfont(12, 12, "����");

	//��ʼ��ӡһ֡ͼ��
	int y;
	for (int n = 0; n < NUM; n++){
		for (int j = 0; j < LENGTH; j++)	{
			//�����е�j���ַ���������
			y = me[n].yh - j * V;

			//������ɫ�����ǵ�ͷ���ǰ�ɫ��
			setcolor(RGB(255 * (0 == j), color(y, me[n].y0, me[n].yh), 255 * (0 == j)));

			//��ӡ�ַ�
			outtextxy(me[n].x0, y, me[n].str[j]);
		}
	}
}

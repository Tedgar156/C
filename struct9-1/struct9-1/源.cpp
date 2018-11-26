//队
/*#include<stdio.h>
#include<stdlib.h>
typedef char Elemtype;
typedef struct Link
{
	Elemtype data;
	struct Link *next;
}Link;
typedef struct
{
	Link *rear;//定义尾指针；
	Link *front;//定义头指针；

}LinkQueue;
void QueueEmpty();
void InitLink(LinkQueue *T)//队初始化
{
	T->front = T->rear = (Link*)malloc(sizeof(Link));
	if (T->front == NULL)
	{
		printf("申请失败\n");
		return;
	}
	T->front->next = NULL;//易错点
}
void push(LinkQueue *T, Elemtype e)//压队
{
	Link *p;
	p = (Link*)malloc(sizeof(Link));
	if (p == NULL){ printf("无法申请空间\n"); return; }
	p->data = e;
	p->next = NULL;
	T->rear->next = p;//用尾指针指向p;
	T->rear = p;//移动尾指针；
}
void pop(LinkQueue *T, Elemtype *e)//出队
{

	if (T->front == T->rear){ printf("空指针无法出队\n"); return; }
	Link *p = T->front->next;
	*e = p->data;
	T->front->next = p->next;
	if (T->rear == p)//判断是否只有一个队
	{
		T->rear = T->front;
	}
	free(p);
}
int main()
{
	Elemtype e;
	LinkQueue T;
	InitLink(&T);
	push(&T, 'A');
	push(&T, 'B');
	push(&T, 'C');
	pop(&T, &e);
	printf("1:%c\n", e);
	pop(&T, &e);
	printf("2:%c\n", e);
	pop(&T, &e);
	printf("3:%c\n", e);
	pop(&T, &e);
	printf("4:%c\n", e);
	push(&T, 'c');
	pop(&T, &e);
	printf("5%c\n", e);
}*/
#include<stdio.h>
char tr[] = "#()+-*/";
char pre[7][8] = {//#()+-*/
	{ '>','*','*','<','<','<','<' },//#
	{'>','>','*','>','>','>','>'},//(
	{ '*','=','*','<','<','<','<' },//)
	{ '>', '>', '*', '<','<','<','<' },//+
	{'>','>','*','<','<','<','<'},//-
	{ '>','>','*','>','>','<','<'},//*
	{'>','>','*','>','>','<','<'}///
};
int Judge(char str)//判断是运算符还是操作符；运算符返回1，操作符返回0
{
	int i = 0;
	while (i<7)
	{
		if (str == tr[i])
		{
			return 1;
		}
		i++;
	}
	return 0;
}
char preority(char bon[],int top[],char str)
{
	int i = 0,j=0,k=0;
	for (k = 0; k < 7; k++)
	{
		if (bon[top[0] - 1] == tr[k])
		{
			j = k;
			break;
		}
	}
	for (k = 0; k < 7; k++)
	{
		if (str == tr[k])
		{
			i = k;
			break;
		}
	}
	return pre[i][j];
}
void input(char in[],int put[],int top[],char data,int num,int a)
{
	if (1 == a)
	{
		in[top[0]++] = data;
		in[top[0]] = '\0';
	}
	else if (2==a)
	{
		put[top[1]++] = num;
		put[top[1]] = '\0';
	}
	else
	{
		put[top[1]++] = data - '0';
		put[top[1]] = '\0';
	}
}
char outputch(char in[], int *top)
{
		return in[--(*top)];
}
int outputin(int in[], int *top)
{
	return in[--(*top)];
}
int main()
{
	int i=0;
	int top[2] = { 0 }, pon[20],a,b,d ;
	char str[20],bon[20], c;
	c = getchar();
	while (c!='\n')
	{
		str[i] = c;
		c = getchar();
		i++;
	}
	str[i] = '#';
	str[i + 1] = '\n';
	i = 0;
	bon[0] = '#';
	top[0] = 1;
	while (1)
	{
		if (Judge(str[i]) > 0)//判断是运算符
		{
			switch (preority(bon, top, str[i]))
			{
			case '>':input(bon,pon,top,str[i],0,1);
				break;
			case '<':
				b = outputin(pon, &top[1]);
				a = outputin(pon, &top[1]);
				switch (outputch(bon,&top[0]))
				{
				case '+':
					d = a + b;
					input(bon,pon,top,'a',d,2);
					break;
				case '-':d = a -b;
					input(bon, pon, top, 'a', d, 2);
					break;
				case'*':d = a * b;
					input(bon, pon, top, 'a', d, 2);
					break;
				case '/':d = a / b;
					input(bon, pon, top, 'a', d, 2);
					break;
				}
				i--;
				break;
			case '=':
			case '*':
				top[0]--;
				break;
			}
		}
		else
		{
			if (str[i] >= '0'&&str[i] <= '9')
			{
				input(bon, pon, top, str[i], 1, 0);
			}
			else
			{
				input(bon, pon, top, str[i], 0, 1);
			}
		}
		if (bon[0] != bon[1])
			i++;
		else
			break;
	}
	printf("结果为:%d\n",pon[0]);
	return 0;
}
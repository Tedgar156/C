#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
	int year;
	int month;
	int day;
}Data;
typedef struct
{
	int id; //图书编号
	char name[20];//图书名
	int price;//价格
	Data pubData;//出版日期
}Book;
typedef Book ElemType;
typedef struct LNode
{
	Book data;
	struct LNode *next;
}LNode;
int InsertList(LNode *L, int i, ElemType e)
{
	int j;
	LNode *p, *q;
	//初始化，指向头结点，并初始化计数器j=0
	p = L; j = 0;
	//循环：将指针指向第i-1个结点
	while (p != NULL&&j<i - 1)
	{
		p = p->next;
		j++;
	}
	//检果i是否正确(1<=i<=n+1)    j>i-1时，i<1
	if (p == NULL || j>i - 1)return 0;//p==NULL时，i>n+1
	//分配空间并插入
	q = (LNode*)malloc(sizeof(LNode));
	if (q == NULL)return 0;
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}
void disp(LNode *p)
{
	printf("\t书号\t%-16s价格\t出版日期\n", "书名");
	printf("\t%d\t%-16s%d\t%d-%d-%d\n"
		, p->data.id, p->data.name, p->data.price
		, p->data.pubData.year
		, p->data.pubData.month
		, p->data.pubData.day);
}
void display(LNode *L)
{
	LNode *p;
	p = L->next;
	printf("\t书号\t%-16s价格\t出版日期\n", "书名");
	while (p != NULL)
	{
		printf("\t%d\t%-16s%d\t%d-%d-%d\n"
			, p->data.id, p->data.name, p->data.price
			, p->data.pubData.year
			, p->data.pubData.month
			, p->data.pubData.day);
		p = p->next;
	}
}
void addinformation(LNode *L)
{
	int a=0,b;
	LNode *p;
	ElemType e;
	p = L->next;
	while (p != NULL)
	{
		p = p->next;
		a++;
	}
	e.id = a+1;
	printf("\t请输入书名:");
	scanf("%s", e.name);
	printf("\t请输入价格:");
	scanf("%d", &e.price);
	printf("\t请输入出版日期(年):");
	scanf("%d", &e.pubData.year);
	printf("\t请输入出版日期(月):");
	scanf("%d", &e.pubData.month);
	printf("\t请输入出版日期(日):");
	scanf("%d", &e.pubData.day);
	b = InsertList(L, a+1, e);
	if (b==0)
	{
		system("cls");
		printf("插入失败");
		return;
	}
	else if (b == 1)
	{
		system("cls");
		printf("插入成功！！！\n");
		return;
	}
}
void delet(LNode *L)
{
	char bookname[20],b;
	LNode *p = L->next,*q=L;
	printf("\t请输入要删除书名:");
	scanf("%s", bookname);
	while (p != NULL)
	{
		if (strcmp(p->data.name,bookname)==0)
		{
			disp(p);
			printf("是否删除(Y/N)?");
			getchar();
			scanf("%c", &b);
			if (b == 'Y' || b == 'y')
			{
				q->next = p->next;
				free(p);
				p = q->next;
				while (p != NULL)
				{
					(p->data.id)--;
					p = p->next;
				}
				system("cls");
				printf("删除成功！！！\n");
			}
			return;
		}
		q = q->next;
		p = p->next;
	}
	if (p == NULL)
	{
		printf("未查找到该书，删除失败\n");
		return;
	}
}
void find(LNode *L)
{
	LNode *p=L;
	char bookname[20];
	printf("\t请输入需要查找书名:");
	scanf("%s", bookname);
	while (p != NULL)
	{
		if (strcmp(p->data.name, bookname) == 0)
		{
			disp(p);
			return;
		}
		p = p->next;
	}
	printf("\t未找到该书\n");
}
//菜单
void modepy(LNode *L)
{
	int j = 1;
	ElemType e;
	char bookname[20], b;
	LNode *p = L->next, *q = L;
	printf("\t请输入要修改书名:");
	scanf("%s", bookname);
	while (p != NULL)
	{
		if (strcmp(p->data.name, bookname) == 0)
		{
			disp(p);
			printf("是否修改(Y/N)?");
			getchar();
			scanf("%c", &b);
			if (b == 'Y' || b == 'y')
			{
				q->next = p->next;
				free(p);
				e.id = j;
				printf("\t请输入书名:");
				scanf("%s", e.name);
				printf("\t请输入价格:");
				scanf("%d", &e.price);
				printf("\t请输入出版日期(年):");
				scanf("%d", &e.pubData.year);
				printf("\t请输入出版日期(月):");
				scanf("%d", &e.pubData.month);
				printf("\t请输入出版日期(日):");
				scanf("%d", &e.pubData.day);
				InsertList(L, j, e);
				system("cls");
				printf("修改成功！！！\n");
			}
			return;
		}
		q = q->next;
		p = p->next;
		j++;
	}
	if (p == NULL)
	{
		printf("未查找到该书，修改失败\n");
		return;
	}
}
void menu(LNode *L)
{

	int select;
	char a;
	do
	{
		system("cls");//清屏
		printf("\t****************************\n");
		printf("\t*1.添加新的图书            *\n");
		printf("\t*2.删除指定图书            *\n");
		printf("\t*3.查找指定图书(书名)      *\n");
		printf("\t*4.修改图书信息            *\n");
		printf("\t*5.显示所有的图书          *\n");
		printf("\t*0.退出                    *\n");
		printf("\t****************************\n");
		printf("\t请输入操和代码：");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			//插入一个元数到指定位置
			addinformation(L);
			system("pause");
			break;
		case 2:
			//删除指定位置的元素符号
			delet(L);
			system("pause");
			break;
		case 3:
			//查找指定元素的位序
			find(L);
			system("pause");
			break;
		case 4:
			//修改图书信息
			modepy(L);
			system("pause");
			break;
		case 5:
			//显示所有的元素
			display(L);

			system("pause");
			break;
		case 0:
			//退出
			printf("\t请问是否确定要退出程序！(Y/N)");
			//接收用户输入的选择并执行是否要退出的功能
			getchar();
			scanf("%c", &a);
			if (a == 'Y' || a == 'y')
			{
				exit(0);
			}
			break;
		}
	} while (select<0 || select>5);
}
int main()
{
	LNode H;
	Book book1 = { 1, "数据结构", 34, { 2014, 1, 25 } };
	Book book2 = { 2, "C语言程序设计", 31, { 2013, 11, 12 } };
	Book book3 = { 3, "Java面向对象", 42, { 2015, 8, 1 } };
	Book book4 = { 4, "Web应用开发", 68, { 2016, 10, 18 } };
	Book book5 = { 5, "Android开发基础", 75, { 2017, 3, 30 } };
	H.next = NULL;
	InsertList(&H, 1, book1);
	InsertList(&H, 2, book2);
	InsertList(&H, 3, book3);
	InsertList(&H, 4, book4);
	InsertList(&H, 5, book5);

	while (1)
	{
		menu(&H);
	}

}
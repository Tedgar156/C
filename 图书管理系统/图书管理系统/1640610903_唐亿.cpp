#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 5  //空间的增量
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
typedef struct
{
	ElemType *elem;//首地址
	int length;//元素个数
	int listSize;//容量
}sqList;
//初始化线表L,容量为size,成功返回1,失败返回0
int InitiList(sqList *L, int size)
{

	L->elem = (ElemType*)malloc(size*sizeof(ElemType));
	if (L->elem == NULL)return 0;
	L->listSize = size;
	L->length = 0;
	return 1;

}
//添加图书，若成果则返回1，失败则返回0。
int add(sqList *opbook)
{
	int loc, i;
	ElemType *p;
	printf("\t****************************\n");
	printf("\t*     添加新的图书         *\n");
	printf("\t****************************\n");
	printf("\t请输入添加图书的位置:");
	scanf("%d", &loc);
	//判断插入位置是否正确
	if (loc<1 || loc>opbook->length + 1)return 0;
	//判断空间是否满
	if (opbook->length >= opbook->listSize)
	{
		p = (ElemType*)realloc(opbook->elem, sizeof(ElemType)*(opbook->listSize + N));
		if (p == NULL)return 0;
		opbook->elem = p;
		opbook->listSize += N;
	}
	//将信息内容依次往后移动
	for (i = opbook->length; i >= loc; i--)
	{
		opbook->elem[i] = opbook->elem[i - 1];
	}
	//在设定的位置进行存储信息
	printf("\t请输入图书编号:");
	scanf("%d", &opbook->elem[loc - 1].id);
	printf("\t请输入图书名:");
	scanf("%s", opbook->elem[loc - 1].name);
	printf("\t请输入图书价格:");
	scanf("%d", &opbook->elem[loc - 1].price);
	printf("\t请输入出版日期(年/月/日):");
	scanf("%d/%d/%d", &opbook->elem[loc - 1].pubData.year, &opbook->elem[loc - 1].pubData.month, &opbook->elem[loc - 1].pubData.day);
	opbook->length++;
	return 1;
}
//删除信息成功返回1失败返回0
int dele(sqList *book)
{
	int elect,i;
	printf("\t****************************\n");
	printf("\t*      删除图书            *\n");
	printf("\t****************************\n");
	printf("请输入需要删除的位置:");
	scanf("%d", &elect);//确认删除的位置是否正确
	if (elect<1 || elect>book->length)return 0;
	for (i = elect; i < book->length; i++)//将位置从后往前移动
	{
		book->elem[i - 1] = book->elem[i];
	}
	book->length--;
	return 1;
}
//显示全部信息
void display(sqList *book)
{
	int i;
	printf("图书编号\t图书名\t图书价格\t出版日期:年\t月\t日\n");
	for (i = 0; i < book->length; i++)
	{
		printf("%d\t\t%s\t%d\t\t\t%d\t%d\t%d\n", book->elem[i].id, book->elem[i].name,
			book->elem[i].price, book->elem[i].pubData.year, book->elem[i].pubData.month, book->elem[i].pubData.day);
	}
}
//查找(书名指定图书信息)查找到了返回1失败返回0
int LocateList(sqList *book)
{
	char name_1[20];
	int i;
	printf("\t****************************\n");
	printf("\t*      查找图书            *\n");
	printf("\t****************************\n");
	printf("请输入书名:");
	scanf("%s", name_1);
	for (i = 0; i < book->length; i++){
		if (strcmp(name_1, book->elem[i].name) == 0)
		{
			printf("图书编号\t图书名\t图书价格\t出版日期:年\t月\t日\n");
			printf("%d\t\t%s\t%d\t\t\t%d\t%d\t%d\n", book->elem[i].id, book->elem[i].name,
				book->elem[i].price, book->elem[i].pubData.year, book->elem[i].pubData.month, book->elem[i].pubData.day);
			getchar();
			getchar();
			return 1;
		}
	}
	return 0;
}
//菜单
void menu(sqList *pbook)
{
	//pbook->elem[i].pubData.day

	int select,result;
	char a,choice;
	do
	{
		system("cls");//清屏
		printf("\t****************************\n");
		printf("\t*1.添加新的图书            *\n");
		printf("\t*2.删除指定图书            *\n");
		printf("\t*3.查找指定图书(书名)      *\n");
		printf("\t*4.显示所有的图书          *\n");
		printf("\t*0.退出                    *\n");
		printf("\t****************************\n");
		printf("\t请输入操和代码：");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			//插入一个元数到指定位置
			result = add(pbook);
			system("cls");
			if (result == 1)
				printf("\t存储信息成功!");
			else
				printf("\t存储信息失败!");
			system("pause");
			break;
		case 2:
			//删除指定位置的元素符号
			result = dele(pbook);
			system("cls");
			if (result == 1)
				printf("\t删除信息成功!");
			else
				printf("\t删除信息失败!");
			system("pause");
			break;
		case 3:
			//查找指定元素的位序
			result = LocateList(pbook);
			system("cls");
			if (result == 1)
				printf("\t查找信息成功!");
			else
				printf("\t查找信息失败!");
			system("pause");
			break;
		case 4:
			//显示所有的元素
			display(pbook);
			system("pause");
			break;
		case 0:
			//退出
			printf("\t请问是否确定要退出程序！(Y/N)");
			//接收用户输入的选择并执行是否要退出的功能
			scanf("%c", &a);
			scanf("%c", &choice);
			if (choice == 'Y' || choice == 'y'){
				exit(0);
			}
			break;
		}
	} while (select<0 || select>4);
}
int main()
{
	sqList books;
	InitiList(&books, 100);
	while (1)
	{
		menu(&books);
	}

}
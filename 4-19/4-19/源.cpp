#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
typedef struct 
{
	int no;
	char name[20];
	int math;
	int english;
	int computer;
	int score;
}student;
typedef student Elemtype;
typedef struct LNode
{
	student data;
	struct LNode *next;
}LNode;
void num()
{
	printf("*************************************\n");
	printf("*欢迎使用学生成绩管理系统           *\n");
	printf("*[1] 输入所有学生信息               *\n");
	printf("*[2] 输出所有学生成绩               *\n");
	printf("*[3] 按学号查找某个学生信息         *\n");
	printf("*[4] 按姓名查找某个学生信息         *\n");
	printf("*[5] 按学号对学生排序               *\n");
	printf("*[6] 按总成绩对学生排序             *\n");
	printf("*[7] 按姓名修改某个学生信息         *\n");
	printf("*[8] 按学号修改某个学生信息         *\n");
	printf("*[9] 按姓名删除某个学生信息         *\n");
	printf("*[10] 按学号删除某个学生信息        *\n");
	printf("*[0] 退出程序                       *\n");
	printf("**************************************\n");
}
void addinformation(LNode *L)
{
	LNode *p =L,*q=L->next;
	FILE *fp;
	fp = fopen("ST.M", "w+");
	char a;
	while (q != NULL)
	{
		p = p->next;
		q = q->next;
	}
	do{
		q = (LNode*)malloc(sizeof(Elemtype));
		if (q == NULL)
		{
			printf("存储失败！");
			return;
		}
		printf("请输入学号:");
		scanf("%d", &q->data.no);
		printf("请输入姓名:");
		scanf("%s", q->data.name);
		printf("请输入数学成绩:");
		scanf("%d", &q->data.math);
		printf("请输入英语成绩:");
		scanf("%d", &q->data.english);
		printf("请输入计算机成绩:");
		scanf("%d", &q->data.computer);
		q->data.score = q->data.math + q->data.english + q->data.computer;
		q->next = NULL;
		fwrite(&q->data, sizeof(student), 1, fp);
		p->next = q;
		p = p->next;
		system("cls");
		printf("保存成功!");
		printf("是否继续存储?(y/n)");
		getchar();
		scanf("%c", &a);
		system("cls");	
	} while (a=='y'||a=='Y');
	fclose(fp);
}
void display(LNode L)
{
	LNode *p;
	p= L.next;
	printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
	while (p != NULL)
	{
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		p = p->next;
	}
}
void findno(LNode L)
{
	int no;
	LNode *p = L.next;
	printf("请输入需要查找的学号:");
	scanf("%d", &no);
	while (p!=NULL&&p->data.no != no)
	{
	
		p = p->next;
	}
	if (p == NULL)
	{
		system("cls");
		printf("查找失败！");
		return;
	}
	else
	{
		printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		system("pause");
	}
	system("cls");
	printf("查找成功！");
}
void findname(LNode L)
{
	char name[20];
	LNode *p = L.next;
	printf("请输入需要查找的名字:");
	scanf("%s", name);
	while (p != NULL)
	{
		if (strcmp(name, p->data.name)==0)
		{
			break;
		}
		p = p->next;
	}
	if (p == NULL)
	{
		system("cls");
		printf("查找失败！");
		return;
	}
	else
	{
		printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		system("pause");
	}
	system("cls");
	printf("查找成功！");
}
void sortno(LNode L)
{
	LNode *p = L.next,*q=L.next;
	student ST;
	while (p!=NULL)
	{
		q = p;
		while (q != NULL)
		{
			if (p->data.no > q->data.no)
			{
				ST = p->data;
				p->data = q->data;
				q->data = ST;
			}
			q = q->next;
		}
		p = p->next;
	}
	display(L);
}
void sortscore(LNode L)
{
	LNode *p = L.next, *q = L.next;
	student ST;
	while (p != NULL)
	{
		q = p;
		while (q != NULL)
		{
			if (p->data.score < q->data.score)
			{
				ST = p->data;
				p->data = q->data;
				q->data = ST;
			}
			q = q->next;
		}
		p = p->next;
	}
	display(L);
}
int prove(int secret[6],int confirm[6])
{
	for (int i = 0; i < 6; i++)
	{
		if (secret[i] != confirm[i])
		{
			return 0;
		}
	}
	return 1;
}
void modefyname(LNode *L,int secret[6])
{
	printf("请确认密码:");
	int confirm[6];
	for (int i = 0; i < 6; i++)
	{
		confirm[i] = getch();
		printf("*");
	}
	printf("\n");
	if (prove(secret,confirm))
	{
		printf("\n欢迎您!\n");
		char name[20], sure;
		LNode *p = L->next;
		printf("请输入需要修改的名字:");
		scanf("%s", name);
		while (p != NULL)
		{
			if (strcmp(name, p->data.name) == 0)
			{
				break;
			}
			p = p->next;
		}
		if (p == NULL)
		{
			system("cls");
			printf("修改失败！");
			return;
		}
		else
		{
			printf("请确认信息:\n");
			printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
			printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		}
		printf("请确认是否修改(Y/N):");
		scanf("%c", &sure);
		if (sure == 'Y' || sure == 'y')
		{
			printf("是否全部修改:");
			getchar();
			scanf("%c", &sure);
			printf("\n");
			if (sure == 'Y' || sure == 'y')
			{
				printf("请输入学号:");
				scanf("%d", &p->data.no);
				printf("请输入姓名:");
				scanf("%s", p->data.name);
				printf("请输入数学成绩:");
				scanf("%d", &p->data.math);
				printf("请输入英语成绩:");
				scanf("%d", &p->data.english);
				printf("请输入计算机成绩:");
				scanf("%d", &p->data.computer);
				system("cls");
				printf("修改成功！");
				return;
			}
			else
			{
				int i = 0;
				printf("修改学号请输入1:\n");
				printf("修改名字请输入2:\n");
				printf("修改数学成绩请输入3:\n");
				printf("修改英语成绩请输入4:\n");
				printf("修改计算机成绩请输入5:\n");
				scanf("%d", &i);
				switch (i)
				{
				case 1:printf("请输入学号:");
					scanf("%d", &p->data.no);
					break;
				case 2:printf("请输入姓名:");
					scanf("%s", p->data.name);
					break;
				case 3:printf("请输入数学成绩:");
					scanf("%d", &p->data.math);
					break;
				case 4:printf("请输入英语成绩:");
					scanf("%d", &p->data.english);
					break;
				case 5:printf("请输入计算机成绩:");
					scanf("%d", &p->data.computer);
					break;
				}
			}
			p->data.score = p->data.math + p->data.english + p->data.computer;
		}
	}
	else {
		printf("密码失败\n");
		return;
	}
}
void modefyno(LNode *L, int secret[6])
{
	printf("请确认密码:");
	int confirm[6];
	for (int i = 0; i < 6; i++)
	{
		confirm[i] = getch();
		printf("*");
	}
	printf("\n");
	if (prove(secret, confirm))
	{
		char sure;
		int no;
		LNode *p = L->next;
		printf("\n欢迎您!\n");
		printf("请输入需要修改的学号:");
		scanf("%d", &no);
		while (p != NULL)
		{
			if (no == p->data.no)
			{
				break;
			}
			p = p->next;
		}
		if (p == NULL)
		{
			system("cls");
			printf("修改失败！");
			return;
		}
		else
		{
			printf("请确认信息:\n");
			printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
			printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		}
		printf("请确认是否修改(Y/N):");
		getchar();
		scanf("%c", &sure);
		if (sure == 'Y' || sure == 'y')
		{
			printf("是否全部修改:");
			getchar();
			scanf("%c", &sure);
			printf("\n");
			if (sure == 'Y' || sure == 'y')
			{
				printf("请输入学号:");
				scanf("%d", &p->data.no);
				printf("请输入姓名:");
				scanf("%s", p->data.name);
				printf("请输入数学成绩:");
				scanf("%d", &p->data.math);
				printf("请输入英语成绩:");
				scanf("%d", &p->data.english);
				printf("请输入计算机成绩:");
				scanf("%d", &p->data.computer);
				system("cls");
				printf("修改成功！");
				return;
			}
			else
			{
				int i = 0;
				printf("修改学号请输入1:\n");
				printf("修改名字请输入2:\n");
				printf("修改数学成绩请输入3:\n");
				printf("修改英语成绩请输入4:\n");
				printf("修改计算机成绩请输入5:\n");
				scanf("%d", &i);
				switch (i)
				{
				case 1:printf("请输入学号:");
					scanf("%d", &p->data.no);
					break;
				case 2:printf("请输入姓名:");
					scanf("%s", p->data.name);
					break;
				case 3:printf("请输入数学成绩:");
					scanf("%d", &p->data.math);
					break;
				case 4:printf("请输入英语成绩:");
					scanf("%d", &p->data.english);
					break;
				case 5:printf("请输入计算机成绩:");
					scanf("%d", &p->data.computer);
					break;
				}
			}
			p->data.score = p->data.math + p->data.english + p->data.computer;
		}
	}
	else { 
		printf("密码失败\n");
		return; 
	}
}
void deletname(LNode *L)
{
	char name[20], sure;
	LNode *p = L->next,*q=L;
	printf("请输入需要删除的名字:");
	scanf("%s", name);
	while (p != NULL)
	{
		if (strcmp(name, p->data.name) == 0)
		{
			break;
		}
		p = p->next;
		q = q->next;
	}
	if (p == NULL)
	{
		system("cls");
		printf("删除失败！");
		return;
	}
	else
	{
		printf("请确认信息:\n");
		printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
	}
	printf("请确认是否删除(Y/N):");
	getchar();
	scanf("%c", &sure);
	if (sure == 'Y' || sure == 'y')
	{
		if (p->next == NULL)
		{
			//free(p);
			q->next = NULL;
		}
		else
		{
			q->next = p->next;
			//free(p);
			system("cls");
			printf("删除成功！");
			return;
		}
	}
}
void deletno(LNode *H)
{
	LNode *p, *q;
	char sure;
	p = H->next;
	q = H;
	int  a;
	int j = 1, g = 0;
	while (p != NULL)
	{
		j++;
		p = p->next;
	}
	p = H->next;
	printf("请输入学号：");
	scanf("%d", &a);
	while (p != NULL)
	{
		if (a == p->data.no)
		{
			printf("请确认信息:\n");
			printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
			printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
			printf("请确认是否修改(Y/N):");
			getchar();
			scanf("%c", &sure);
			if (sure == 'Y' || sure == 'y')
			{
				if (p->next == NULL)
				{
					free(p);
					q->next = NULL;
					return;
				}
				else
				{
					q->next = p->next;
					free(p);
					return;
				}
			}
			else return;
		}
		if (p->next != NULL)
		{
			p = p->next;
			q = q->next;
		}
	}
}
void exict(LNode *L)
{
	char a;
	system("cls");
	getchar();
	printf("确认退出(Y/N)？");
	scanf("%c", &a);
	if (a == 'Y' || a == 'y')
	{
		exit(1);
	}
}
void load(LNode *H)
{
	FILE *fp;
	LNode *p,*q=H->next;
	if ((fp = fopen("ST.M", "r")) == NULL)
	{
		fp = fopen("ST.M", "w");
		return;
	}
	else
	{
		while (!feof(fp))
		{
			p = (LNode*)malloc(sizeof(LNode));
			fread(&p->data, sizeof(student),1,fp);
			p->next = NULL;
			q->next = p;
			q = q->next;
		}
		return;
	}
	fclose(fp);
}
int main()
{
	int choise;
	int secret[6];
	LNode L;
	L.next = NULL;
	LNode *p;
	p = (LNode*)malloc(sizeof(Elemtype));
	p->data = { 01, "游成威", 98, 84, 75,158 };
	L.next = p;
	p->next = NULL;
	printf("创建密码:");
	for (int i = 0; i < 6; i++)
	{
		secret[i] = getch();
		printf("*");
	}
	printf("\n创建成功！\n");
	system("pause");
	system("cls");
	load(&L);
	while (1)
	{
		system("cls");//清屏
		num();//选择框
		printf("请输入您的选择（0 - 10）:");
		scanf("%d", &choise);//根据输入选择不同的功能
		switch (choise)
		{
		case 1:addinformation(&L);//输入所有学生信息
			system("pause");
			break;
		case 2://输出所有学生成绩
			display(L);
			system("pause");
			break;
		case 3:// 按学号查找某个学生信息
			findno(L);
				system("pause");
			break;
		case 4://按姓名查找某个学生信息
			findname(L);
			system("pause");
			break;
		case 5://按学号对学生排序
			sortno(L);
			system("pause");
			break;
		case 6://按总成绩对学生排序
			sortscore(L);
			system("pause");
			break;
		case 7://按姓名修改某个学生信息
			modefyname(&L,secret);
			system("pause");
			break;
		case 8://按学号修改某个学生信息
			modefyno(&L,secret);
			system("pause");
			break;
		case 9://按姓名删除某个学生信息
			deletname(&L);
			system("pause");
			break;
		case 10://按学号删除某个学生信息
			deletno(&L);
			system("pause");
			break;
		case 0:
			exict(&L);//退出程序
			break;
		default:break;
		}
	}
}
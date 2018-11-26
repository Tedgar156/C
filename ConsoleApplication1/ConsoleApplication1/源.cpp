#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct result
{
	int  math;
	int english;
	int computer;
	int score;
}result;
typedef struct students
{
	int no;
	char name[20];
	result subject;
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
int insrtlist(LNode*L, students x)
{
	LNode *p, *q;
	p = L->next;
	q = L;
	while (p != NULL)
	{
		p = p->next;
		q = q->next;
	}
	p = (LNode*)malloc(sizeof(LNode));
	if (p == NULL)return 0;
	p->data = x;
	p->next = NULL;
	q->next = p; return 1;
}
void insert(LNode*L)
{
	students student;
	char a;
	do
	{
		system("cls");
		printf("输入学号:");
		scanf("%d", &student.no);
		printf("输入学生名字：");
		scanf("%s", &student.name);
		getchar();
		printf("输入数学成绩：");
		scanf("%d", &student.subject.math);
		printf("输入英语成绩：");
		scanf("%d", &student.subject.english);
		printf("输入计算机成绩：");
		scanf("%d", &student.subject.computer);
		student.subject.score = student.subject.computer + student.subject.english + student.subject.math;
		if (insrtlist(L, student) == 0)
		{
			system("cls");
			printf("存储失败！");
			return;
		}
		printf("是否还有存储学生信息(Y/N):");
		getchar();
		scanf("%c", &a);
	} while (a=='y'||a=='Y');
	system("cls");
	printf("保存成功!");
}
void display(LNode L)
{
	LNode *p;
	p = L.next;
	printf("学号\t姓名\t数学成绩\t英语成绩\t计算机成绩\t总成绩\n");
	while (p != NULL)
	{
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.subject.math, p->data.subject.english, p->data.subject.computer, p->data.subject.score);
		p = p->next;
	}
}
void findno(LNode L)
{
	int no;
	LNode *p = L.next;
	printf("请输入需要查找的学号:");
	scanf("%d", &no);
	while (p != NULL&&p->data.no != no)
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
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.subject.math, p->data.subject.english, p->data.subject.computer, p->data.subject.score);
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
		if (strcmp(name, p->data.name) == 0)
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
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.subject.math, p->data.subject.english, p->data.subject.computer, p->data.subject.score);
		system("pause");
	}
	system("cls");
	printf("查找成功！");
}
void sortno(LNode L)
{
	LNode *p = L.next, *q = L.next;
	student ST;
	while (p != NULL)
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
			if (p->data.subject.score < q->data.subject.score)
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
void modefyname(LNode *L)
{
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
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.subject.math, p->data.subject.english, p->data.subject.computer, p->data.subject.score);
	}
	printf("请确认是否修改(Y/N):");
	scanf("%c", &sure);
	if (sure == 'Y' || sure == 'y')
	{
		printf("请输入学号:");
		scanf("%d", &p->data.no);
		printf("请输入姓名:");
		scanf("%s", p->data.name);
		printf("请输入数学成绩:");
		scanf("%d", &p->data.subject.math);
		printf("请输入英语成绩:");
		scanf("%d", &p->data.subject.english);
		printf("请输入计算机成绩:");
		scanf("%d", &p->data.subject.computer);
		p->data.subject.score = p->data.subject.math + p->data.subject.english + p->data.subject.computer;
		system("cls");
		printf("修改成功！");
		return;
	}
}
void modefyno(LNode *L)
{
	char sure;
	int no;
	LNode *p = L->next;
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
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.subject.math, p->data.subject.english, p->data.subject.computer, p->data.subject.score);
	}
	printf("请确认是否修改(Y/N):");
	getchar();
	scanf("%c", &sure);
	if (sure == 'Y' || sure == 'y')
	{
		printf("请输入学号:");
		scanf("%d", &p->data.no);
		printf("请输入姓名:");
		scanf("%s", p->data.name);
		printf("请输入数学成绩:");
		scanf("%d", &p->data.subject.math);
		printf("请输入英语成绩:");
		scanf("%d", &p->data.subject.english);
		printf("请输入计算机成绩:");
		scanf("%d", &p->data.subject.computer);
		p->data.subject.score = p->data.subject.math + p->data.subject.english + p->data.subject.computer;
		system("cls");
		printf("修改成功！");
		return;
	}
}
void deletname(LNode *L)
{
	char name[20], sure;
	LNode *p = L->next, *q = L;
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
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.subject.math, p->data.subject.english, p->data.subject.computer, p->data.subject.score);
		printf("请确认是否删除(Y/N):");
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
				system("cls");
				printf("删除成功！");
				return;
			}
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
			printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.subject.math, p->data.subject.english, p->data.subject.computer, p->data.subject.score);
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
void exict()
{
	char a;
	system("cls");
	getchar();
	printf("确认退出(Y/N)？");
	scanf("%c", &a);
	if (a == 'Y' || a == 'y')
		exit(1);
}
int main()
{
	int choise;
	LNode L;
	L.next = NULL;
	while (1)
	{
		system("cls");//清屏
		num();//选择框
		printf("请输入您的选择（0 - 10）:");
		scanf("%d", &choise);//根据输入选择不同的功能
		switch (choise)
		{
		case 1:insert(&L);//输入所有学生信息
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
			modefyname(&L);
			system("pause");
			break;
		case 8://按学号修改某个学生信息
			modefyno(&L);
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
			exict();//退出程序
			break;
		default:break;
		}
	}
}
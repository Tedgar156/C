/********************************************************
**************文件名称:学生管理系统(结构体数组)**********
*************运用知识:结构体.数组************************
*************制作人:糖衣*********************************
*************时间:2017-1-30******************************
*********************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
typedef struct stu
{
	char name[15];
	int no;
	int score;
}ST;
void add(ST *stu)
{
	char a;
	printf("姓名:");
	scanf("%s", stu->name);
	scanf("%c", &a);
	printf("学号:");
	scanf("%d", &stu->no);
	printf("成绩:");
	scanf("%d", &stu->score);
	system("cls");
}
void allfind(int number, ST *stu)
{
	int i;
	printf("查找信息如下:\n");
	printf("\t\t姓名\t学号\t成绩\n");
	for (i = 0; i < number; i++)
	{
		printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
	}
	getchar();
}
void findname(int number, ST *stu)
{	
	int i,j=0;
	char name[15];
	char a;
	printf("╔═══════════════╗\n");
	printf("║          查找学生信息        ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入查找学生的姓名:");
	scanf("%s", name);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (!strcmp(name, stu[i].name))
		{
			printf("查找信息如下:\n");
			printf("\t\t姓名\t学号\t成绩\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			j++;
		}
	}
	if (j != 0)
	{
		getchar();
		return;
	}
	printf("输入错误!请按任意键退出---");
	getchar();
}
void findno(int number, ST *stu)
{
	int i,j=0;
	char a;
	int no;
	printf("╔═══════════════╗\n");
	printf("║          查找学生信息        ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入查找学生的学号:");
	scanf("%d", &no);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (no == stu[i].no)
		{
			printf("查找信息如下:\n");
			printf("\t\t姓名\t学号\t成绩\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			j++;
		}
	}
	if (j != 0)
	{
		getchar();
		return;
	}
	printf("输入错误!请按任意键退出---");
	getchar();
}
void find(int number, ST *stu)
{
	int choise;
	char a;
	while (1)
	{
		printf("╔═══════════════╗\n");
		printf("║          查找学生信息        ║\n");
		printf("╠═══════════════╣\n");
		printf("║       1:查看全部信息         ║\n");
		printf("║       2:按照姓名查找         ║\n");
		printf("║       3:按照学号查找         ║\n");
		printf("║       4:退出                 ║\n");
		printf("║═══════════════║\n");
		printf("请选择:");
		scanf("%d", &choise);
		scanf("%c", &a);
		system("cls");
		switch (choise)
		{
		case 1:
			allfind(number, stu);
			break;
		case 2:
			findname(number, stu);
			break;
		case 3:
			findno(number, stu);
			break;
		case 4:return;
			break;
		default:break;
		}
		system("cls");
	}
}
void revisename(int number,ST*stu)
{
	int i;
	char name[15];
	char confirm;
	char a;
	printf("╔═══════════════╗\n");
	printf("║          修改学生信息        ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入需要修改学生的名字:");
	scanf("%s", name);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (!strcmp(name, stu[i].name))
		{
			printf("请确认信息:\n");
			printf("\t\t姓名\t学号\t成绩\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("请确认是否修改(Y/N):");
			scanf("%c", &confirm);
			scanf("%c", &a);
			if (confirm == 'Y' || confirm == 'y')
			{
				char a;
				printf("姓名:");
				scanf("%s", stu[i].name);
				scanf("%c", &a);
				printf("学号:");
				scanf("%d", &stu[i].no);
				printf("成绩:");
				scanf("%d", &stu[i].score);
				system("cls");
				getchar();
				printf("保存信息成功!请按任意键退出---\n");
				getchar();
				return;
			}
			else
				return;
		}
	}
	printf("输入错误！请按任意键退出--");
	getchar();
}
void reviseno(int number,ST*stu)
{
	int no;
	int i;
	char confirm;
	char a;
	printf("╔═══════════════╗\n");
	printf("║          修改学生信息        ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入需要修改学生的学号:");
	scanf("%d", &no);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (no == stu[i].no)
		{
			printf("请确认信息:\n");
			printf("\t\t姓名\t学号\t成绩\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("请确认是否修改(Y/N):");
			scanf("%c", &confirm);
			scanf("%c", &a);
			if (confirm == 'Y' || confirm == 'y')
			{
				char a;
				printf("姓名:");
				scanf("%s", stu[i].name);
				scanf("%c", &a);
				printf("学号:");
				scanf("%d", &stu[i].no);
				printf("成绩:");
				scanf("%d", &stu[i].score);
				system("cls");
				getchar();
				printf("保存信息成功!请按任意键退出---\n");
				getchar();
				return;
			}
			else
				return;
		}
	}
	printf("输入错误！请按任意键退出--");
	getchar();
}
void revise(int number,ST*stu)
{
		int choise;
		char a;
		while (1)
		{
			system("cls");
			printf("╔═══════════════╗\n");
			printf("║          修改学生信息        ║\n");
			printf("╠═══════════════╣\n");
			printf("║       1:按照姓名修改         ║\n");
			printf("║       2:按照学号修改         ║\n");
			printf("║       3:退出                 ║\n");
			printf("║═══════════════║\n");
			printf("请选择:");
			scanf("%d", &choise);
			scanf("%c", &a);
			system("cls");
			switch (choise)
			{
			case 1:revisename(number, stu);
				break;
			case 2:reviseno(number, stu);
				break;
			case 3:return;
				break;
			default:
				break;
			}
		}
}
void welcome()
{
	printf("╔═══════════════╗\n");
	printf("║          学生管理系统        ║\n");
	printf("╠═══════════════╣\n");
	printf("║      1:添加信息              ║\n");
	printf("║      2:查看信息              ║\n");
	printf("║      3:修改信息              ║\n");
	printf("║      4:删除信息              ║\n");
	printf("║      5:排列信息              ║\n");
	printf("║      6:退出                  ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入您的选择:");
}
int deletname(int number, ST*stu)
{
	int i, j;
	char name[15];
	char confirm;
	char a;
	printf("╔═══════════════╗\n");
	printf("║          删除学生信息        ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入需要删除学生的名字:");
	scanf("%s", name);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (!strcmp(name, stu[i].name))
		{
			printf("请确认信息:\n");
			printf("\t\t姓名\t学号\t成绩\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("请确认是否修改(Y/N):");
			scanf("%c", &confirm);
			scanf("%c", &a);
			if (confirm == 'Y' || confirm == 'y')
			{
				for (j = i; j < number - 1; j++)
				{
					stu[j] = stu[j + 1];
				}
				number -= 1;
				system("cls");
				printf("删除信息成功!请按任意键退出---\n");
				getchar();
				return number;
			}
			else
				break;
		}
	}
	printf("输入错误！请按任意键退出--");
	getchar();
	return number;
}
int deletno(int number, ST*stu)
{
	int no;
	int i,j;
	char confirm;
	char a;
	printf("╔═══════════════╗\n");
	printf("║          删除学生信息        ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入需要删除学生的学号:");
	scanf("%d", &no);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (no == stu[i].no)
		{
			printf("请确认信息:\n");
			printf("\t\t姓名\t学号\t成绩\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("请确认是否修改(Y/N):");
			scanf("%c", &confirm);
			scanf("%c", &a);
			if (confirm == 'Y' || confirm == 'y')
			{
				for (j = i; j < number - 1; j++)
				{
					stu[j] = stu[j + 1];
				}
				number -= 1;
				system("cls");
				printf("删除信息成功!请按任意键退出---\n");
				getchar();
				return number;
			}
			else
				break;
		}
	}
	printf("输入错误！请按任意键退出--");
	getchar();
	return number;
}
int dele(int number,ST*stu)
{
	int choise;
	char a;
	while (1)
	{
		system("cls");
		printf("╔═══════════════╗\n");
		printf("║          删除学生信息        ║\n");
		printf("╠═══════════════╣\n");
		printf("║       1:按照姓名删除         ║\n");
		printf("║       2:按照学号删除         ║\n");
		printf("║       3:退出                 ║\n");
		printf("║═══════════════║\n");
		printf("请选择:");
		scanf("%d", &choise);
		scanf("%c", &a);
		system("cls");
		switch (choise)
		{
		case 1:number=deletname(number, stu);
			break;
		case 2:number=deletno(number, stu);
			break;
		case 3:return number;
			break;
		default:
			break;
		}
	}
}
void arrybig(int number, ST *stu)
{
	int i,j;
	printf("\t\t姓名\t学号\t成绩\n");
	for (i = 0; i < number; i++)
	{
		for (j = 0; j < number; j++)
		{
			if (stu[i].no<stu[j].no)
			{
				ST st;
				st = stu[j];
				stu[j] = stu[i];
				stu[i] = st;
			}
		}
	}
	for (i = 0; i < number; i++)
	{
		printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
	}
	printf("请按任意键退出--");
	getchar();
}
void arrysmall (int number, ST *stu)
{
	int i, j;
	printf("\t\t姓名\t学号\t成绩\n");
	for (i = 0; i < number; i++)
	{
		for (j = 0; j < number; j++)
		{
			if (stu[i].no>stu[j].no)
			{
				ST st;
				st = stu[j];
				stu[j] = stu[i];
				stu[i] = st;
			}
		}
	}
	for (i = 0; i < number; i++)
	{
		printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
	}
	printf("请按任意键退出--");
	getchar();
}
void arry(int number,ST *stu)
{
	int choise;
	char a;
	while (1)
	{
		system("cls");
		printf("╔═══════════════╗\n");
		printf("║          排列学生信息        ║\n");
		printf("╠═══════════════╣\n");
		printf("║       1:按学号从小到大       ║\n");
		printf("║       2:按学号从大到小       ║\n");
		printf("║       3:退出                 ║\n");
		printf("║═══════════════║\n");
		printf("请选择:");
		scanf("%d", &choise);
		scanf("%c", &a);
		system("cls");
		switch (choise)
		{
		case 1:
			arrybig(number, stu);
			break;
		case 2:
			arrysmall (number, stu);
			break;
		case 3:return;
			break;
		default:
			break;
		}
	}
}
void read(ST *stu)
{
	FILE *fp;
	int i;
	if ((fp = fopen("学生管理系统.text", "r")) == NULL)
	{
		printf("读取文件失败！\n");
		exit(1);
	}
	else
	{
		for (i = 0;stu==NULL; i++)
		{
			fscanf(fp,"\t\t%s\t%d\t%d\n", stu->name, stu->no, stu->score);
			stu++;
		}
	}
	fclose(fp);
}
void printf(int number,ST *stu)
{
	int i;
	FILE *fp;
	if ((fp = fopen("学生管理系统.text", "w")) == NULL)
	{
		printf("读取文件失败！\n");
	}
	for (i = 0; i < number; i++)
	{
		fprintf(fp, "\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
	}
	fclose(fp);
	printf("保存成功!");
}
int main()
{
	char a;
	int i,j=1,k = 0, b = 1, number = 0, secrea[6], secreat[6];
	ST stu[100];
	int chose;
	//read(stu);
	i = 0;
	printf("请创建6位密码:");
	while (k < 6)
	{
		secreat[k] = getch();
		printf("*");
		k++;
	}
	printf("保存密码成功!");
	getchar();
	system("cls");
	while (1)
	{
		welcome();
		scanf("%d", &chose);
		scanf("%c", &a);
		system("cls");
		switch (chose)
		{
		case 1:
			printf("╔═══════════════╗\n");
			printf("║          添加学生信息        ║\n");
			printf("╚═══════════════╝\n");
			printf("需要存储学生的个数:");
			scanf("%d", &i);
			if (b == 1)
			{
				number = i;
				i = 0;
			}
			else
			{
				int a;
				a = i;
				i = number;
				number += a;
			}
			for (i; i < number; i++)
			{
				add(&stu[i]);
				b++;
			}
			scanf("%c", &a);
			system("cls");
			printf("保存信息成功!请按任意键退出---");
			getchar();
			break;
		case 2:
			find(number, stu);
			break;
		case 3:
			printf("请输入密码:");
			for (k=0; k < 6; k++)
			{
				secrea[k] = getch();
				printf("*");
			}
			for (k = 0; k < 6; k++)
			{
				if (secrea[k] != secreat[k])
				{
					j = 0;
					break;
				}
			}
			if (j=1)
			{
				revise(number, stu);
			}
			else
			{
				printf("密码错误!!!");
  				getchar();
			}
			break;
		case 4:number=dele(number,stu);
			break;
		case 5:
			arry(number,stu);
			break;
		case 6:printf(number,stu);
			return 0;
		default:
			break;
		}
		system("cls");
	}
		return 0;
}
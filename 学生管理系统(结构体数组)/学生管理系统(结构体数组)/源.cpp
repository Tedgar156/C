/********************************************************
**************�ļ�����:ѧ������ϵͳ(�ṹ������)**********
*************����֪ʶ:�ṹ��.����************************
*************������:����*********************************
*************ʱ��:2017-1-30******************************
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
	printf("����:");
	scanf("%s", stu->name);
	scanf("%c", &a);
	printf("ѧ��:");
	scanf("%d", &stu->no);
	printf("�ɼ�:");
	scanf("%d", &stu->score);
	system("cls");
}
void allfind(int number, ST *stu)
{
	int i;
	printf("������Ϣ����:\n");
	printf("\t\t����\tѧ��\t�ɼ�\n");
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
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("�U          ����ѧ����Ϣ        �U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("���������ѧ��������:");
	scanf("%s", name);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (!strcmp(name, stu[i].name))
		{
			printf("������Ϣ����:\n");
			printf("\t\t����\tѧ��\t�ɼ�\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			j++;
		}
	}
	if (j != 0)
	{
		getchar();
		return;
	}
	printf("�������!�밴������˳�---");
	getchar();
}
void findno(int number, ST *stu)
{
	int i,j=0;
	char a;
	int no;
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("�U          ����ѧ����Ϣ        �U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("���������ѧ����ѧ��:");
	scanf("%d", &no);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (no == stu[i].no)
		{
			printf("������Ϣ����:\n");
			printf("\t\t����\tѧ��\t�ɼ�\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			j++;
		}
	}
	if (j != 0)
	{
		getchar();
		return;
	}
	printf("�������!�밴������˳�---");
	getchar();
}
void find(int number, ST *stu)
{
	int choise;
	char a;
	while (1)
	{
		printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("�U          ����ѧ����Ϣ        �U\n");
		printf("�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		printf("�U       1:�鿴ȫ����Ϣ         �U\n");
		printf("�U       2:������������         �U\n");
		printf("�U       3:����ѧ�Ų���         �U\n");
		printf("�U       4:�˳�                 �U\n");
		printf("�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
		printf("��ѡ��:");
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
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("�U          �޸�ѧ����Ϣ        �U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("��������Ҫ�޸�ѧ��������:");
	scanf("%s", name);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (!strcmp(name, stu[i].name))
		{
			printf("��ȷ����Ϣ:\n");
			printf("\t\t����\tѧ��\t�ɼ�\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("��ȷ���Ƿ��޸�(Y/N):");
			scanf("%c", &confirm);
			scanf("%c", &a);
			if (confirm == 'Y' || confirm == 'y')
			{
				char a;
				printf("����:");
				scanf("%s", stu[i].name);
				scanf("%c", &a);
				printf("ѧ��:");
				scanf("%d", &stu[i].no);
				printf("�ɼ�:");
				scanf("%d", &stu[i].score);
				system("cls");
				getchar();
				printf("������Ϣ�ɹ�!�밴������˳�---\n");
				getchar();
				return;
			}
			else
				return;
		}
	}
	printf("��������밴������˳�--");
	getchar();
}
void reviseno(int number,ST*stu)
{
	int no;
	int i;
	char confirm;
	char a;
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("�U          �޸�ѧ����Ϣ        �U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("��������Ҫ�޸�ѧ����ѧ��:");
	scanf("%d", &no);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (no == stu[i].no)
		{
			printf("��ȷ����Ϣ:\n");
			printf("\t\t����\tѧ��\t�ɼ�\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("��ȷ���Ƿ��޸�(Y/N):");
			scanf("%c", &confirm);
			scanf("%c", &a);
			if (confirm == 'Y' || confirm == 'y')
			{
				char a;
				printf("����:");
				scanf("%s", stu[i].name);
				scanf("%c", &a);
				printf("ѧ��:");
				scanf("%d", &stu[i].no);
				printf("�ɼ�:");
				scanf("%d", &stu[i].score);
				system("cls");
				getchar();
				printf("������Ϣ�ɹ�!�밴������˳�---\n");
				getchar();
				return;
			}
			else
				return;
		}
	}
	printf("��������밴������˳�--");
	getchar();
}
void revise(int number,ST*stu)
{
		int choise;
		char a;
		while (1)
		{
			system("cls");
			printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
			printf("�U          �޸�ѧ����Ϣ        �U\n");
			printf("�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
			printf("�U       1:���������޸�         �U\n");
			printf("�U       2:����ѧ���޸�         �U\n");
			printf("�U       3:�˳�                 �U\n");
			printf("�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
			printf("��ѡ��:");
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
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("�U          ѧ������ϵͳ        �U\n");
	printf("�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	printf("�U      1:�����Ϣ              �U\n");
	printf("�U      2:�鿴��Ϣ              �U\n");
	printf("�U      3:�޸���Ϣ              �U\n");
	printf("�U      4:ɾ����Ϣ              �U\n");
	printf("�U      5:������Ϣ              �U\n");
	printf("�U      6:�˳�                  �U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("����������ѡ��:");
}
int deletname(int number, ST*stu)
{
	int i, j;
	char name[15];
	char confirm;
	char a;
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("�U          ɾ��ѧ����Ϣ        �U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("��������Ҫɾ��ѧ��������:");
	scanf("%s", name);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (!strcmp(name, stu[i].name))
		{
			printf("��ȷ����Ϣ:\n");
			printf("\t\t����\tѧ��\t�ɼ�\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("��ȷ���Ƿ��޸�(Y/N):");
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
				printf("ɾ����Ϣ�ɹ�!�밴������˳�---\n");
				getchar();
				return number;
			}
			else
				break;
		}
	}
	printf("��������밴������˳�--");
	getchar();
	return number;
}
int deletno(int number, ST*stu)
{
	int no;
	int i,j;
	char confirm;
	char a;
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("�U          ɾ��ѧ����Ϣ        �U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("��������Ҫɾ��ѧ����ѧ��:");
	scanf("%d", &no);
	scanf("%c", &a);
	for (i = 0; i < number; i++)
	{
		if (no == stu[i].no)
		{
			printf("��ȷ����Ϣ:\n");
			printf("\t\t����\tѧ��\t�ɼ�\n");
			printf("\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
			printf("��ȷ���Ƿ��޸�(Y/N):");
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
				printf("ɾ����Ϣ�ɹ�!�밴������˳�---\n");
				getchar();
				return number;
			}
			else
				break;
		}
	}
	printf("��������밴������˳�--");
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
		printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("�U          ɾ��ѧ����Ϣ        �U\n");
		printf("�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		printf("�U       1:��������ɾ��         �U\n");
		printf("�U       2:����ѧ��ɾ��         �U\n");
		printf("�U       3:�˳�                 �U\n");
		printf("�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
		printf("��ѡ��:");
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
	printf("\t\t����\tѧ��\t�ɼ�\n");
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
	printf("�밴������˳�--");
	getchar();
}
void arrysmall (int number, ST *stu)
{
	int i, j;
	printf("\t\t����\tѧ��\t�ɼ�\n");
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
	printf("�밴������˳�--");
	getchar();
}
void arry(int number,ST *stu)
{
	int choise;
	char a;
	while (1)
	{
		system("cls");
		printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("�U          ����ѧ����Ϣ        �U\n");
		printf("�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
		printf("�U       1:��ѧ�Ŵ�С����       �U\n");
		printf("�U       2:��ѧ�ŴӴ�С       �U\n");
		printf("�U       3:�˳�                 �U\n");
		printf("�U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U\n");
		printf("��ѡ��:");
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
	if ((fp = fopen("ѧ������ϵͳ.text", "r")) == NULL)
	{
		printf("��ȡ�ļ�ʧ�ܣ�\n");
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
	if ((fp = fopen("ѧ������ϵͳ.text", "w")) == NULL)
	{
		printf("��ȡ�ļ�ʧ�ܣ�\n");
	}
	for (i = 0; i < number; i++)
	{
		fprintf(fp, "\t\t%s\t%d\t%d\n", stu[i].name, stu[i].no, stu[i].score);
	}
	fclose(fp);
	printf("����ɹ�!");
}
int main()
{
	char a;
	int i,j=1,k = 0, b = 1, number = 0, secrea[6], secreat[6];
	ST stu[100];
	int chose;
	//read(stu);
	i = 0;
	printf("�봴��6λ����:");
	while (k < 6)
	{
		secreat[k] = getch();
		printf("*");
		k++;
	}
	printf("��������ɹ�!");
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
			printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
			printf("�U          ���ѧ����Ϣ        �U\n");
			printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
			printf("��Ҫ�洢ѧ���ĸ���:");
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
			printf("������Ϣ�ɹ�!�밴������˳�---");
			getchar();
			break;
		case 2:
			find(number, stu);
			break;
		case 3:
			printf("����������:");
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
				printf("�������!!!");
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
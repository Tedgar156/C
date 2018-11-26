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
	printf("*��ӭʹ��ѧ���ɼ�����ϵͳ           *\n");
	printf("*[1] ��������ѧ����Ϣ               *\n");
	printf("*[2] �������ѧ���ɼ�               *\n");
	printf("*[3] ��ѧ�Ų���ĳ��ѧ����Ϣ         *\n");
	printf("*[4] ����������ĳ��ѧ����Ϣ         *\n");
	printf("*[5] ��ѧ�Ŷ�ѧ������               *\n");
	printf("*[6] ���ܳɼ���ѧ������             *\n");
	printf("*[7] �������޸�ĳ��ѧ����Ϣ         *\n");
	printf("*[8] ��ѧ���޸�ĳ��ѧ����Ϣ         *\n");
	printf("*[9] ������ɾ��ĳ��ѧ����Ϣ         *\n");
	printf("*[10] ��ѧ��ɾ��ĳ��ѧ����Ϣ        *\n");
	printf("*[0] �˳�����                       *\n");
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
			printf("�洢ʧ�ܣ�");
			return;
		}
		printf("������ѧ��:");
		scanf("%d", &q->data.no);
		printf("����������:");
		scanf("%s", q->data.name);
		printf("��������ѧ�ɼ�:");
		scanf("%d", &q->data.math);
		printf("������Ӣ��ɼ�:");
		scanf("%d", &q->data.english);
		printf("�����������ɼ�:");
		scanf("%d", &q->data.computer);
		q->data.score = q->data.math + q->data.english + q->data.computer;
		q->next = NULL;
		fwrite(&q->data, sizeof(student), 1, fp);
		p->next = q;
		p = p->next;
		system("cls");
		printf("����ɹ�!");
		printf("�Ƿ�����洢?(y/n)");
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
	printf("ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\t�ܳɼ�\n");
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
	printf("��������Ҫ���ҵ�ѧ��:");
	scanf("%d", &no);
	while (p!=NULL&&p->data.no != no)
	{
	
		p = p->next;
	}
	if (p == NULL)
	{
		system("cls");
		printf("����ʧ�ܣ�");
		return;
	}
	else
	{
		printf("ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\t�ܳɼ�\n");
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		system("pause");
	}
	system("cls");
	printf("���ҳɹ���");
}
void findname(LNode L)
{
	char name[20];
	LNode *p = L.next;
	printf("��������Ҫ���ҵ�����:");
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
		printf("����ʧ�ܣ�");
		return;
	}
	else
	{
		printf("ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\t�ܳɼ�\n");
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		system("pause");
	}
	system("cls");
	printf("���ҳɹ���");
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
	printf("��ȷ������:");
	int confirm[6];
	for (int i = 0; i < 6; i++)
	{
		confirm[i] = getch();
		printf("*");
	}
	printf("\n");
	if (prove(secret,confirm))
	{
		printf("\n��ӭ��!\n");
		char name[20], sure;
		LNode *p = L->next;
		printf("��������Ҫ�޸ĵ�����:");
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
			printf("�޸�ʧ�ܣ�");
			return;
		}
		else
		{
			printf("��ȷ����Ϣ:\n");
			printf("ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\t�ܳɼ�\n");
			printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		}
		printf("��ȷ���Ƿ��޸�(Y/N):");
		scanf("%c", &sure);
		if (sure == 'Y' || sure == 'y')
		{
			printf("�Ƿ�ȫ���޸�:");
			getchar();
			scanf("%c", &sure);
			printf("\n");
			if (sure == 'Y' || sure == 'y')
			{
				printf("������ѧ��:");
				scanf("%d", &p->data.no);
				printf("����������:");
				scanf("%s", p->data.name);
				printf("��������ѧ�ɼ�:");
				scanf("%d", &p->data.math);
				printf("������Ӣ��ɼ�:");
				scanf("%d", &p->data.english);
				printf("�����������ɼ�:");
				scanf("%d", &p->data.computer);
				system("cls");
				printf("�޸ĳɹ���");
				return;
			}
			else
			{
				int i = 0;
				printf("�޸�ѧ��������1:\n");
				printf("�޸�����������2:\n");
				printf("�޸���ѧ�ɼ�������3:\n");
				printf("�޸�Ӣ��ɼ�������4:\n");
				printf("�޸ļ�����ɼ�������5:\n");
				scanf("%d", &i);
				switch (i)
				{
				case 1:printf("������ѧ��:");
					scanf("%d", &p->data.no);
					break;
				case 2:printf("����������:");
					scanf("%s", p->data.name);
					break;
				case 3:printf("��������ѧ�ɼ�:");
					scanf("%d", &p->data.math);
					break;
				case 4:printf("������Ӣ��ɼ�:");
					scanf("%d", &p->data.english);
					break;
				case 5:printf("�����������ɼ�:");
					scanf("%d", &p->data.computer);
					break;
				}
			}
			p->data.score = p->data.math + p->data.english + p->data.computer;
		}
	}
	else {
		printf("����ʧ��\n");
		return;
	}
}
void modefyno(LNode *L, int secret[6])
{
	printf("��ȷ������:");
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
		printf("\n��ӭ��!\n");
		printf("��������Ҫ�޸ĵ�ѧ��:");
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
			printf("�޸�ʧ�ܣ�");
			return;
		}
		else
		{
			printf("��ȷ����Ϣ:\n");
			printf("ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\t�ܳɼ�\n");
			printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
		}
		printf("��ȷ���Ƿ��޸�(Y/N):");
		getchar();
		scanf("%c", &sure);
		if (sure == 'Y' || sure == 'y')
		{
			printf("�Ƿ�ȫ���޸�:");
			getchar();
			scanf("%c", &sure);
			printf("\n");
			if (sure == 'Y' || sure == 'y')
			{
				printf("������ѧ��:");
				scanf("%d", &p->data.no);
				printf("����������:");
				scanf("%s", p->data.name);
				printf("��������ѧ�ɼ�:");
				scanf("%d", &p->data.math);
				printf("������Ӣ��ɼ�:");
				scanf("%d", &p->data.english);
				printf("�����������ɼ�:");
				scanf("%d", &p->data.computer);
				system("cls");
				printf("�޸ĳɹ���");
				return;
			}
			else
			{
				int i = 0;
				printf("�޸�ѧ��������1:\n");
				printf("�޸�����������2:\n");
				printf("�޸���ѧ�ɼ�������3:\n");
				printf("�޸�Ӣ��ɼ�������4:\n");
				printf("�޸ļ�����ɼ�������5:\n");
				scanf("%d", &i);
				switch (i)
				{
				case 1:printf("������ѧ��:");
					scanf("%d", &p->data.no);
					break;
				case 2:printf("����������:");
					scanf("%s", p->data.name);
					break;
				case 3:printf("��������ѧ�ɼ�:");
					scanf("%d", &p->data.math);
					break;
				case 4:printf("������Ӣ��ɼ�:");
					scanf("%d", &p->data.english);
					break;
				case 5:printf("�����������ɼ�:");
					scanf("%d", &p->data.computer);
					break;
				}
			}
			p->data.score = p->data.math + p->data.english + p->data.computer;
		}
	}
	else { 
		printf("����ʧ��\n");
		return; 
	}
}
void deletname(LNode *L)
{
	char name[20], sure;
	LNode *p = L->next,*q=L;
	printf("��������Ҫɾ��������:");
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
		printf("ɾ��ʧ�ܣ�");
		return;
	}
	else
	{
		printf("��ȷ����Ϣ:\n");
		printf("ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\t�ܳɼ�\n");
		printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
	}
	printf("��ȷ���Ƿ�ɾ��(Y/N):");
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
			printf("ɾ���ɹ���");
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
	printf("������ѧ�ţ�");
	scanf("%d", &a);
	while (p != NULL)
	{
		if (a == p->data.no)
		{
			printf("��ȷ����Ϣ:\n");
			printf("ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\t�ܳɼ�\n");
			printf("%d\t%-8s%-8d\t%-8d\t%-8d\t%-8d\n", p->data.no, p->data.name, p->data.math, p->data.english, p->data.computer, p->data.score);
			printf("��ȷ���Ƿ��޸�(Y/N):");
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
	printf("ȷ���˳�(Y/N)��");
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
	p->data = { 01, "�γ���", 98, 84, 75,158 };
	L.next = p;
	p->next = NULL;
	printf("��������:");
	for (int i = 0; i < 6; i++)
	{
		secret[i] = getch();
		printf("*");
	}
	printf("\n�����ɹ���\n");
	system("pause");
	system("cls");
	load(&L);
	while (1)
	{
		system("cls");//����
		num();//ѡ���
		printf("����������ѡ��0 - 10��:");
		scanf("%d", &choise);//��������ѡ��ͬ�Ĺ���
		switch (choise)
		{
		case 1:addinformation(&L);//��������ѧ����Ϣ
			system("pause");
			break;
		case 2://�������ѧ���ɼ�
			display(L);
			system("pause");
			break;
		case 3:// ��ѧ�Ų���ĳ��ѧ����Ϣ
			findno(L);
				system("pause");
			break;
		case 4://����������ĳ��ѧ����Ϣ
			findname(L);
			system("pause");
			break;
		case 5://��ѧ�Ŷ�ѧ������
			sortno(L);
			system("pause");
			break;
		case 6://���ܳɼ���ѧ������
			sortscore(L);
			system("pause");
			break;
		case 7://�������޸�ĳ��ѧ����Ϣ
			modefyname(&L,secret);
			system("pause");
			break;
		case 8://��ѧ���޸�ĳ��ѧ����Ϣ
			modefyno(&L,secret);
			system("pause");
			break;
		case 9://������ɾ��ĳ��ѧ����Ϣ
			deletname(&L);
			system("pause");
			break;
		case 10://��ѧ��ɾ��ĳ��ѧ����Ϣ
			deletno(&L);
			system("pause");
			break;
		case 0:
			exict(&L);//�˳�����
			break;
		default:break;
		}
	}
}
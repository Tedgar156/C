#include <string.h> 
#include <stdio.h> 
#include <malloc.h>
#include <stdlib.h>
#define Max 20000
#define MAXSIZE 3 

typedef struct ArcCell
{
	int adj;  /* ���ڽӵĳ���֮���·�� */
}ArcCell;   /* ����ߵ����� */
typedef struct VertexType
{
	int number;  /* ���б�� */
	char sight[100];  /* �������� */
	char description[1000]; /* �������� */
}VertexType;   /* ���嶥������� */
typedef struct
{
	VertexType vex[20]; /* ͼ�еĶ��㣬���� */
	ArcCell arcs[20][20]; /* ͼ�еıߣ���Ϊ���м�ľ��� */
	int vexnum, arcnum; /* ������������ */
}MGraph;   /* ����ͼ������ */
MGraph G;   /* ��ͼ����Ϊȫ�ֱ��� */

typedef struct wat_ros
{
	char name[10];/*����*/
	int req_amt;/*��Ʊ��*/
	struct wat_ros *next;
}qnode, *qptr;

typedef struct pqueue
{
	qptr front;/*�Ⱥ��油�ͻ��������ͷָ��*/
	qptr rear;/*�Ⱥ��油�ͻ����������ָ��*/
}linkqueue;

typedef struct ord_ros
{
	char name[10];/*�ͻ�����*/
	int ord_amt;/*��Ʊ��*/
	int grade;/*��λ�ȼ�*/
	struct ord_ros *next;
}linklist;

typedef struct airline
{
	char str_name[10];
	char ter_name[10];/*�յ�վ�� */
	char air_num[10];/*�����*/
	char plane_num[10];/*�ɻ���*/
	char day[7];/*�������գ����ڼ���*/
	int tkt_amt;/*��Ա����*/
	int tkt_sur;/*��Ʊ��*/
	int money;
	linklist *order;/*��Ա������ָ���Ա���������ͷָ��*/
	linkqueue wait;/*�Ⱥ��油�Ŀͻ������򣬷ֱ�ָ���ŶӵȺ�������ͷ��β��ָ��*/
	struct airline *next;//��ֱ��ĳ���
}lineinfo;

struct airline *start;

void display(struct airline *info)
/*��ӡÿ�����ߵĻ�����Ϣ*/
{
	printf("%8s\t%8s\t%3s\t%s\t%4s\t\t%3d\t%10d\t%10d\n", info->str_name, info->ter_name, info->air_num, info->plane_num, info->day, info->tkt_amt, info->tkt_sur, info->money);
}

void list()/*��ӡȫ��������Ϣ*/
{
	struct airline *info;
	int i = 0;
	info = start;
	printf("���վ��\t�յ�վ��\t�����\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t      Ʊ��\n");
	while (i<MAXSIZE) {
		display(info);
		info++;
		i++;
	}
	printf("\n\n");
}

struct airline *find()
	/*����ϵͳ����ĺ���Ų�ѯ����ָ����ʽ����*/
{
	struct airline *info;
	char number[10];
	int i = 0;
	info = start;
	printf("�����뺽���:");
	scanf("%s", number);
	while (i<MAXSIZE) {
		if (!strcmp(number, info->air_num))
			return info;
		info++;
		i++;
	}
	printf("�Բ��𣬸ú���ĩ�ҵ�!\n");
	return NULL;
}

struct airline *fix_start(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("������Ҫ�޸ĵ�Ŀ�����վ��");
		scanf("%s", a);
		strcpy(p->ter_name, a);
	}
	else
		printf("���г˿ͣ��޷��޸ģ�");
	return p;
}
struct airline *fix_terminal(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("������Ҫ�޸ĵ�Ŀ���յ�վ��");
		scanf("%s", a);
		strcpy(p->ter_name, a);
	}
	else
		printf("���г˿ͣ��޷��޸ģ�");
	return p;
}
struct airline *fix_time(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("������Ҫ�޸����ʱ�䣨�������գ����ڼ�������");
		scanf("%s", a);
		strcpy(p->day, a);
	}
	else
		printf("���г˿ͣ��޷��޸ģ�");
	return p;
}
struct airline *fix_plane_num(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("������Ҫ�޸ĵķɻ��ţ�");
		scanf("%s", a);
		strcpy(p->day, a);
	}
	else
		printf("���г˿ͣ��޷��޸ģ�");
	return p;
}
struct airline *tkt_amt(struct airline *p)
{
	int a;
	if (p->order == NULL)
	{
		printf("������Ҫ�޸ĵĶ��Ա������");
		scanf("%d", &a);
		p->tkt_amt = a;
	}
	else
		printf("���г˿ͣ��޷��޸ģ�");
	return p;
}
struct airline *money(struct airline *p)
{
	int a;
	if (p->order == NULL)
	{
		printf("������Ҫ�޸ĵ�Ʊ��Ϊ��");
		scanf("%d", &a);
		p->tkt_amt = a;
	}
	else
		printf("���г˿ͣ��޷��޸ģ�");
	return p;
}


struct airline *fix()
{
	int choose;
	struct airline * p;
	p = find();
	while (1)
	{//��ʾ�˵�
		system("cls");//����
		printf("��ѡ��Ҫ�޸ĵ���Ϣ��\n");
		printf("*************************************\n");
		printf("[1] �޸����վ\n");
		printf("[2] �޸��յ�վ\n");
		printf("[3] �޸����ʱ��\n");
		printf("[4] �޸ķɻ��ͺ�\n");
		printf("[5] �޸�Ʊ��\n");
		printf("[6] �޸ĳ�Ա����\n");
		printf("[0] �˳�����\n");
		printf("����������ѡ��0 - 9����\n");
		printf("**************************************)\n");
		scanf("%d", &choose);
		if (choose == 0)
		{
			break;//���ڽ��������������ѭ��
		}
		switch (choose)
		{
		case 1:
			p = fix_start(p);
			break;
		case 2:
			p = fix_terminal(p);
			break;
		case 3:
			p = fix_time(p);
			break;
		case 4:
			p = fix_plane_num(p);
			break;
		case 5:
			p = money(p);
			break;
		case 6:
			p = tkt_amt(p);
			break;
		default:
			printf("�������� ���������");
		}
	}
	return p;
}
void Search()
/*���ݿͻ�������յ�վ�����������Ϣ*/
{
	struct airline *info, *find();
	char name[10], name1[10];
	int i = 0;
	info = start;
	printf("���������վ��:");
	scanf("%s", name);
	printf("�������յ�վ��:");
	scanf("%s", name1);
	while (i<MAXSIZE)
	{
		if (!strcmp(name, info->str_name))
		{
			if (!strcmp(name1, info->ter_name))
				break;
		}
		info++;
		i++;
	}
	if (i >= MAXSIZE)
		printf("�Բ����޸ú���!\n");
	else {
		printf("���վ��\t�յ�վ��\t�����\t�ɻ���\t��������\t��Ա����\t��Ʊ��\t      Ʊ��\n");
		display(info);
	}
}
void prtlink()
/*��ӡ��Ʊ��Ա������Ŀͻ�������Ϣ*/
{
	linklist *p;
	struct airline *info;
	info = find();
	p = info->order;
	if (p != NULL) {
		printf("�ͻ�����   ��Ʊ����   ��λ�ȼ�\n");
		while (p) {
			printf("%s\t\t%d\t%d\n", p->name, p->ord_amt, p->grade);
			p = p->next;
		}
	}
	else
		printf("�ú���û�пͻ���Ϣ!!\n");
}
linklist *insertlink(linklist *head, int amount, char name[], int grade)
/*���Ӷ�Ʊ��Ա������Ŀͻ���Ϣ*/
{
	linklist *p1, *new;
	p1 = head;
	new = (linklist *)malloc(sizeof(linklist));
	if (!new) { printf("\nOut of memory!!\n"); return NULL; }
	strcpy(new->name, name);
	new->ord_amt = amount;
	new->grade = grade;
	new->next = NULL;
	if (head == NULL)/*��ԭ�޶�Ʊ�ͻ���Ϣ*/
	{
		head = new; new->next = NULL;
	}
	else
		head = new;
	new->next = p1;
	return head;
}

linkqueue appendqueue(linkqueue q, char name[], int amount)
/*�����ŶӵȺ�Ŀͻ�������*/
{
	qptr new;
	new = (qptr)malloc(sizeof(qnode));
	strcpy(new->name, name);
	new->req_amt = amount;
	new->next = NULL;
	if (q.front == NULL)/*��ԭ�ŶӵȺ�ͻ�������Ϊ��*/
		q.front = new;
	else
		q.rear->next = new;
	q.rear = new;
	return q;
}

void order()
/*����Ʊҵ��*/
{
	struct airline *info;
	int amount, grade;
	char name[10];
	info = start;
	if (!(info = find())) return;/*���ݿͻ��ṩ�ĺ���Ž��в�ѯ����Ϊ�գ��˳���ģ��*/
	printf("�������㶩Ʊ����Ҫ������:");
	scanf("%d", &amount);
	if (amount>info->tkt_amt)/*���ͻ���Ʊ�����Ա��Ʊ�ܶ�˳�*/
	{
		printf("\n�Բ����������Ʊ�������Ѿ�������Ա����!");
		return;
	}
	if (amount <= info->tkt_sur)/*���ͻ���Ʊ��ĩ������Ʊ������Ʊ�ɹ����ȼ���Ϣ*/
	{
		int i;
		printf("������������������Ʊ�ͻ���:");
		scanf("%s", name);
		printf("������%sƱ�Ĳ�λ�ȼ�:", name);
		scanf("%d", &grade);
		info->order = insertlink(info->order, amount, name, grade);/*�ڶ�Ʊ��Ա����������ӿͻ���Ϣ*/
		for (i = 0; i<amount; i++)/*��������ö�Ʊ�ͻ�����λ��*/
			printf("%s����λ����:%d\n", name, info->tkt_amt - info->tkt_sur + i + 1);
		info->tkt_sur -= amount;/*�ú��ߵ���Ʊ��Ӧ�����ÿͻ��Ķ�Ʊ��*/
		printf("\nף��������죡\n");
	}
	else       /*����Ա����Ʊ�����ڶ�Ʊ�ѯ�ʿͻ��Ƿ���Ҫ�����ŶӵȺ�*/
	{
		char r;
		printf("\n�Ѿ�û�и����Ʊ������Ҫ�ŶӵȺ���?(Y/N)");
		r = getch();
		printf("%c", r);
		if (r == 'Y' || r == 'y')
		{
			printf("\n�����������������ŶӶ�Ʊ�ͻ���:");
			scanf("%s", name);
			info->wait = appendqueue(info->wait, name, amount);/*���ŶӵȺ��Ա����������ӿͻ���Ϣ*/
			printf("\nע��ɹ�!\n");
		}
		else printf("\n��ӭ���´��ٴζ�����\n");
	}
}
void return_tkt()
/*��Ʊģ��*/
{
	struct airline *info;
	qnode *t, *back, *f, *r;
	int grade;
	linklist *p1, *p2, *head;
	char cusname[10];
	if (!(info = find())) return;/*���ò�ѯ���������ݿͻ��ṩ�ĺ��߽�������*/
	head = info->order;
	p1 = head;
	printf("�����������������Ʊ�ͻ���:");
	scanf("%s", cusname);
	while (p1 != NULL) {/*���ݿͻ��ṩ����������Ʊ�ͻ���������в�ѯ*/
		if (!strcmp(cusname, p1->name)) break;
		p2 = p1; p1 = p1->next;
	}
	if (p1 == NULL) { printf("�Բ�����û�ж���Ʊ!\n"); return; }/*��δ�ҵ����˳���ģ��*/
	else {/*����Ϣ��ѯ�ɹ���ɾ����Ʊ�ͻ��������е���Ϣ*/
		if (p1 == head) head = p1->next;
		else p2->next = p1->next;
		info->tkt_sur += p1->ord_amt;
		grade = p1->grade;
		printf("%s�ɹ���Ʊ��\n", p1->name);
		free(p1);
	}
	info->order = head;/*���½�����������ָ��Ʊ�������ͷָ�� */
	f = (info->wait).front;/*fָ���ŶӵȺ��������е�ͷ���*/
	r = (info->wait).rear;/*rָ���ŶӵȺ��������е�β���*/
	t = f;/*tΪ��ǰ�����������ŶӺ�������*/
	while (t)
	{
		if (info->tkt_sur >= info->wait.front->req_amt) {/*������������Ϊͷ���*/
			int i;
			info->wait.front = t->next;
			printf("%s��Ʊ�ɹ���\n", t->name);
			for (i = 0; i<t->req_amt; i++)/*�����λ��*/
				printf("%s����λ����:%d\n", t->name, (info->tkt_sur) - i);
			info->tkt_sur -= t->req_amt;
			info->order = insertlink(info->order, t->req_amt, t->name, grade);/*���뵽��Ʊ�ͻ�����������*/
			free(t);
			break;
		}
		back = t; t = t->next;
		if ((info->tkt_sur) >= (t->req_amt) && t != NULL)/*�����������߲�Ϊͷ���*/
		{
			int i;
			back->next = t->next;
			printf("%s��Ʊ�ɹ���\n", t->name);
			for (i = 0; i<t->req_amt; i++)/*�����λ��*/
				printf("<%s>'s seat number is:%d\n", t->name, (info->tkt_sur) - i);
			info->tkt_sur -= t->req_amt;
			info->order = insertlink(info->order, t->req_amt, t->name, grade);/*���뵽��Ʊ�ͻ�����������*/
			free(t); break;
		}
		if (f == r) break;
	}
}

char nameofairplane[100];
int NUM = 10;
int P[20][20];  /*  */
int p[20];/*ȫ�����飬�������·���ϵĸ�����*/
int visited[20];/*ȫ�����飬������¼�����㱻���ʵ����*/
int a = 0;/*ȫ�ֱ�����������¼ÿ�Զ���֮�������·��������*/
long int D[20];  /* ���������洢���·������ */
int   x[20] = { 0 };
void CreateUDN(int v, int a); /* ��ͼ���� */
void narrate();   /*˵������*/
void ShortestPath(int num); /*���·������*/
void output(int sight1, int sight2); /*�������*/
char Menu();   /* ���˵� */
void search();   /* ��ѯ������Ϣ */
char SearchMenu();  /* ��ѯ�Ӳ˵� */
void HaMiTonian(int);   /* ͼ�ı��� */
void Searchpath1(MGraph g);/*��ѯ��������������·��*/
void disppath(MGraph g, int i, int j);
void path(MGraph g, int i, int j, int k);/*ȷ��·���ϵ�k+1����������*/
void NextValue(int);
void display(); /* ��ʾ������� */
int Addnewsight(int n); /*����µľ����·��*/
int Deletesight(int n); /*ɾ�������·��*/
void Changesight(); /*�޸ľ����·��*/
char Changemenu();  /*�޸�·���򶥵��ѡ��˵�*/
char Sightmenu();  /*ѡ����þ���Ĳ˵�*/
void narrate1();


void main() /* ������ */
{
	int v0, v1;
	int ck;
	CreateUDN(NUM, 11);
	int i = 0;
	struct airline * p;
	FILE *fp = NULL;
	struct airline air[MAXSIZE];
	char msg[1024] = { 0 };
	fp = fopen("��ʼ����.txt", "r");
	if (fp == NULL)
	{
		printf("��ȡʧ��");
	}
	else
	{
		while (fgets(msg, 1024, fp) != NULL)
		{
			air[i].order = NULL;
			air[i].wait.front = NULL;
			air[i].wait.rear = NULL;
			sscanf_s(msg, "%s %s %s %s %s %d %d %d", &air[i].str_name, 20, &air[i].ter_name, 20, &air[i].air_num, 20, &air[i].plane_num, 20, &air[i].day, 20, &air[i].tkt_amt, &air[i].tkt_sur, &air[i].money);
			i++;
		}
	}
	if (i == MAXSIZE)
		printf("��ȡ�ɹ�\n");
	system("pause");
	start = &air[0];					 /*  clrscr();*/
	do
	{
		ck = Menu();
		switch (ck)
		{
		case 1:
			search();
			break;
		case 2:
			system("cls");
			narrate1();
			printf("\n\n\t\t\t��ѡ�������У�0��%d����", NUM - 1);
			scanf("%d", &v0);
			printf("\t\t\t��ѡ���յ���У�0��%d����", NUM - 1);
			scanf("%d", &v1);
			ShortestPath(v0);  /* ������������֮������·�� */
			output(v0, v1);     /* ������ */
			printf("\n\n\t\t\t\t�밴���������...\n");
			getchar();
			getchar();
			break;
		case 3:
			system("cls");
			narrate1();
			x[0] = 1;
			Searchpath1(G);
			printf("\n\n\t\t\t\t�밴���������...\n");
			getchar();
			getchar();
			break;
		case 4:
			system("cls");
			narrate1();
			NUM = Addnewsight(NUM);
			system("cls");
			narrate();
			break;
		case 5:
			NUM = Deletesight(NUM);
			break;
		case 6:
			Changesight();
			break;
		case 7:
			order();
			system("pause");
			break;
		case 8:
			return_tkt();
			system("pause");
			break;
		case 9:
			list();
			system("pause");
			break;
		case 10:
			prtlink();
			system("pause");
			break;
		case 11:
			fix();
			system("pause");
			break;
		case 12:
			Search();
			system("pause");
			break;
		case 13:
			narrate();
			system("pause");
			break;
		};
	} while (ck != 14);
}
char Menu()  /* ���˵� */
{
	int c;
	int flag;
	do {
		flag = 1;
		system("cls");
		printf("\n--------------------weclome airplan manenagment-------------------\n");
		printf("\n                           �˵�ѡ��                             \n\n");
		printf("       1����ѯ������Ϣ               2����ѯ�����м����·��        \n");
		printf("       3����ѯ�����м�����·��       4�����뺽��ͼ                  \n");
		printf("       5��ɾ�����г��к�·��         6���޸����г��к�·��          \n");
		printf("       7.����Ʊҵ��                8.������Ʊҵ��                 \n");
		printf("       9.�鿴���к�����Ϣ            10.����Ѷ�Ʊ�ͻ���Ϣ          \n");
		printf("       11.�޸ĺ�����Ϣ               12 ��ѯ������Ϣ                \n");
		printf("       13 �鿴���г�����Ϣ           14�˳�		     			   \n");
		printf("--------------------------------------------------------------------\n");
		printf("\n ���������ѡ��");
		scanf("%d", &c);
		if (c == 1 || c == 2 || c == 3 || c == 4 || c == 5 || c == 6 || c == 7 || c == 8 || c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 14)
			flag = 0;
	} while (flag);
	return c;
}
char SearchMenu()  /* ��ѯ�Ӳ˵� */
{
	char c;
	int flag;
	do {
		flag = 1;
		system("cls");
		narrate1();
		printf("\n\t\t\t				                \n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t        1�����ճ��б�Ų�ѯ       \n");
		printf("\t\t\t        2�����ճ������Ʋ�ѯ       \n");
		printf("\t\t\t        e������                   \n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t									\n");
		printf("\t\t\t\t����������ѡ��");
		scanf("%c", &c);
		if (c == '1' || c == '2' || c == 'e')
			flag = 0;
	} while (flag);
	return c;
}

void search()  /* ��ѯ������Ϣ */
{
	int num;
	int i;
	char c;
	char name[20];
	do
	{
		system("cls");
		c = SearchMenu();
		switch (c)
		{
		case '1':
			system("cls");
			narrate();
			printf("\n\n\t\t��������Ҫ���ҵĳ��б�ţ�");
			scanf("%d", &num);
			for (i = 0; i<NUM; i++)
			{
				if (num == G.vex[i].number)
				{
					printf("\n\n\t\t\t��Ҫ���ҳ�����Ϣ����:");
					printf("\n\n\t\t\t%-25s\n\n", G.vex[i].description);
					printf("\n\t\t\t�����������...");
					getchar();
					getchar();
					break;
				}
			}
			if (i == NUM)
			{
				printf("\n\n\t\t\tû���ҵ���");
				printf("\n\n\t\t\t�����������...");
				getchar();
				getchar();
			}
			break;
		case '2':
			system("cls");
			narrate();
			printf("\n\n\t\t��������Ҫ���ҵĳ������ƣ�");
			scanf("%s", name);
			for (i = 0; i<NUM; i++)
			{
				if (!strcmp(name, G.vex[i].sight))
				{
					printf("\n\n\t\t\t��Ҫ���ҳ�����Ϣ����:");
					printf("\n\n\t\t\t%-25s\n\n", G.vex[i].description);
					printf("\n\t\t\t�����������...");
					getchar();
					getchar();
					break;
				}
			}
			if (i == NUM)
			{
				printf("\n\n\t\t\tû���ҵ���");
				printf("\n\n\t\t\t�����������...");
				getchar();
				getchar();
			}
			break;
		}
	} while (c != 'e');
}
void CreateUDN(int v, int a) /* ��ͼ���� */
{
	int i, j;
	strcpy(nameofairplane, "�й�����");
	G.vexnum = v;  /* ��ʼ���ṹ�еĳ������ͱ��� */
	G.arcnum = a;
	for (i = 0; i<20; ++i) G.vex[i].number = i; /* ��ʼ��ÿһ�����еı�� */
	/* ��ʼ��ÿһ������������������� */
	strcpy(G.vex[0].sight, "����");
	strcpy(G.vex[0].description, "����������������ʷ�Ļ����Ǻ�������ӵ�������Ļ��Ų������ĳ��У���ǧ�������ʷ�����˹ʹ�����̳���˴��볤�ǡ��ú�԰���ڶ���ʤ�ż�");
	strcpy(G.vex[1].sight, "�Ϻ�");
	strcpy(G.vex[1].description, "�Ϻ�����ơ��������ꡱ�����л����񹲺͹�ֱϽ�У��������ĳ��У�������У����й���һ����У��й��ľ��á���ͨ���Ƽ�����ҵ�����ڡ�ó�ס���չ�ͺ������ģ������غ����ų���");
	strcpy(G.vex[2].sight, "����");
	strcpy(G.vex[2].description, "�����ǹ㶫ʡʡ�ᡢ�������ĳ��С�������С��ϲ�ս��˾�פ�ء��ǹ���Ժ��λ�Ĺ��ʴ��С�������ó���ġ������ۺϽ�ͨ��Ŧ�������ۺ����Ż����С�������ʷ�Ļ�����");
	strcpy(G.vex[3].sight, "����");
	strcpy(G.vex[3].description, "���ڣ���ơ����������ǣ��й��Ĵ�һ�߳���֮һ[1]  ���㶫ʡʡϽ�С��ƻ������С���ʡ���С������������ĳ��С��������");
	strcpy(G.vex[4].sight, "���");
	strcpy(G.vex[4].description, "��ۣ���ƴ��hoeng1 gong2��Ӣ�ģ�Hong Kong����ͨ��ƴ����xi��ng g��ng����д��HK������ơ��ۡ���ȫ��Ϊ�л����񹲺͹�����ر���������HKSAR��");
	strcpy(G.vex[5].sight, "�ɶ�");
	strcpy(G.vex[5].description, "�ɶ�������أ��Ĵ�ʡʡ�ᡢ��ʡ���У��й����ϵ����ĿƼ�����ó���������ĺͽ�ͨ��Ŧ[1]  ��������Ҫ�ĸ��¼�����ҵ���ء���ó�������ĺ��ۺϽ�ͨ��Ŧ������������Ҫ�����ĳ���");
	strcpy(G.vex[6].sight, "����");
	strcpy(G.vex[6].description, "���죬��ưͻ��壬λ���й����ϲ������л����񹲺͹�ֱϽ�С��������ĳ���[1]  ��������С����ʴ��У��������ε������á����ڡ���ó�������Ƽ����ºͺ�������");
	strcpy(G.vex[7].sight, "����");
	strcpy(G.vex[7].description, "���ݣ���ơ��������㽭ʡʡ�ᡢ��ʡ���У�λ���й������غ����㽭ʡ������Ǯ�������Ρ��������˺��϶ˣ����㽭ʡ�����Ρ����á��Ļ�����������ͨ�ͽ������ģ����������޳���Ⱥ���ĳ���֮һ��������������̬���ô��ڵ����");
	strcpy(G.vex[8].sight, "�人");
	strcpy(G.vex[8].description, "�人����ơ���������ơ����ǡ����Ǻ���ʡʡ�ᡢ�в���ʡΨһ�ĸ�ʡ���к��ش���У��й��в��������ĳ��У�ȫ����Ҫ�Ĺ�ҵ���ء��ƽ̻��غ��ۺϽ�ͨ��Ŧ");
	strcpy(G.vex[9].sight, "���");
	strcpy(G.vex[9].description, "��򣬼�ƽ��л����񹲺͹�ֱϽ�С��������ĳ��С�������С�[1-2]  �����������������ġ������غ����ų��У�ȫ���Ƚ������з����ء��������ʺ��˺����������ڴ�����Ӫʾ�������ĸ￪��������");
	/* ��������еı߼ٶ�Ϊ20000������������������֮���ǲ��ɵ��� */
	for (i = 0; i<20; ++i)
	for (j = 0; j<20; ++j)
		G.arcs[i][j].adj = Max;
	/*
	�±��ǿ�ֱ�ӵ���ĳ��м�ľ��룬���������е������ǻ���ģ�
	����Ҫ��ͼ�жԳƵı�ͬʱ��ֵ��
	*/
	G.arcs[0][1].adj = G.arcs[1][0].adj = 500;
	G.arcs[1][3].adj = G.arcs[3][1].adj = 70;
	G.arcs[0][6].adj = G.arcs[3][0].adj = 250;
	G.arcs[1][4].adj = G.arcs[4][1].adj = 80;
	G.arcs[2][4].adj = G.arcs[4][2].adj = 100;
	G.arcs[3][5].adj = G.arcs[5][3].adj = 90;
	G.arcs[5][2].adj = G.arcs[2][5].adj = 100;
	G.arcs[4][6].adj = G.arcs[6][4].adj = 75;
	G.arcs[4][7].adj = G.arcs[7][4].adj = 300;
	G.arcs[2][7].adj = G.arcs[7][2].adj = 400;
	G.arcs[7][8].adj = G.arcs[8][7].adj = 40;
}
void narrate() /* ˵������ */
{
	int i, k = 0;
	printf("\n\t***************��ӭʹ��%s���ճ���**************\n", nameofairplane);
	printf("\t______________________________\n");
	printf("\t\t������������\t\t\t\n");
	printf("\t______________________________\n");
	for (i = 0; i<NUM; i++)
	{
		printf("\n%-10d%-25s\n\n%-80s\n", i, G.vex[i].sight, G.vex[i].description);

		/* ��������б� */
		k = k + 1;
	}
	printf("\t________________________________|_________________________________\n");
}
void narrate1() /* ˵������ */
{
	int i, k = 0;
	printf("\n\t***************��ӭʹ��%s���ճ���**************\n", nameofairplane);
	printf("\t______________________________\n");
	printf("\t\t��������\t\t\t\n");
	printf("\t______________________________\n");
	for (i = 0; i<NUM; i++)
	{
		printf("\n%-10d%-25s\n\n", i, G.vex[i].sight);

		/* ��������б� */
		k = k + 1;
	}
	printf("\t________________________________|_________________________________\n");
}
void ShortestPath(int num) /* �Ͻ�˹�����㷨���·������ numΪ��ڵ�ı�� */
{
	int v, w, i, t;  /* i��w��vΪ�������� */
	int final[20]; /*  */
	int min;
	for (v = 0; v<NUM; v++)
	{
		final[v] = 0;  /* ����Ӷ���num������vû�����·�� */
		D[v] = G.arcs[num][v].adj;/* ����֮��ص�Ȩֵ����D�д��
								  */
		for (w = 0; w<NUM; w++) /* ����Ϊ��·�� */
			P[v][w] = 0;
		if (D[v]<20000)  /* ����·�� */
		{
			P[v][num] = 1; /* ���ڱ�־��Ϊһ */
			P[v][v] = 1; /* �������� */
		}
	}
	D[num] = 0;
	final[num] = 1;      /* ��ʼ��num��������S���� */
	/* ��ʼ��ѭ����ÿһ�����num��ĳ����������·������������뵽S���� */
	for (i = 0; i<NUM; ++i)     /* ����G.vexnum-1������ */
	{
		min = Max;     /* ��ǰ��֪�붥��num��������� */
		for (w = 0; w<NUM; ++w)
		if (!final[w])    /* w������v-s�� */
		if (D[w]<min)   /* w������num������� */
		{
			v = w;
			min = D[w];
		}
		final[v] = 1;   /* ��num���������v���뵽s���� */
		for (w = 0; w<NUM; ++w)  /* ���µ�ǰ���·��������� */
		if (!final[w] && ((min + G.arcs[v][w].adj)<D[w]))/* ����s���ϣ����ұ���ǰ���ҵ���·�����̾͸��µ�ǰ·�� */
		{
			D[w] = min + G.arcs[v][w].adj;
			for (t = 0; t<NUM; t++)
				P[w][t] = P[v][t];
			P[w][w] = 1;
		}
	}
}
void output(int sight1, int sight2)    /* ������� */
{
	int a, b, c, d, q = 0;
	a = sight2;    /* �����ж���ֵ��a */
	if (a != sight1)    /* ������ж����ͳ���һ�����غϣ������... */
	{
		printf("\n\t��%s��%s�����·����", G.vex[sight1].sight, G.vex[sight2].sight);/* �����ʾ��Ϣ */
		printf("\t(��̾���Ϊ %dkm.)\n\n\t", D[a]);  /* ���sight1��sight2�����·�����ȣ������D[]������ */
		printf("\t%s", G.vex[sight1].sight);   /* �������һ������ */
		d = sight1;      /* ������һ�ı�Ÿ�ֵ��d */
		for (c = 0; c<NUM; ++c)
		{
		gate:;        /* ��ţ�������Ϊgoto�����ת��λ�� */
			P[a][sight1] = 0;
			for (b = 0; b<NUM; b++)
			{
				if (G.arcs[d][b].adj<20000 && P[a][b])  /* �������һ������һ���ٽ��֮�����·�������·�� */
				{
					printf("-->%s", G.vex[b].sight);  /* ����˽ڵ������ */
					q = q + 1;     /* ����������һ����8�������ʱ�Ļ��� */
					P[a][b] = 0;
					d = b;     /* ��b��Ϊ�����������һ��ѭ���������˷��� */
					if (q % 8 == 0) printf("\n");
					goto gate;
				}
			}
		}
	}
}
void Searchpath1(MGraph g)/*��ѯ�������м������·��*/
{
	int l = 0;
	int k = 0;
	int i, j;
	printf("ѡ��������㣺");
	scanf("%d", &i);
	printf("ѡ��Ŀ�ؾ��㣺");
	scanf("%d", &j);
	for (; k<g.vexnum; k++)/*g.vexnumber��ʾ���еĶ������*/
	if (i == g.vex[k].number) i = k;/*�������ҵ�����������ĳ������еı����ͬ�Ķ���*/
	for (; l<g.vexnum; l++)
	if (j == g.vex[l].number) j = l;/*�������ҵ������������Ŀ�س��еı����ͬ�Ķ���*/
	printf("\n��%s��%s����������·����:\n\n", g.vex[i].sight, g.vex[j].sight);/*����������к�Ŀ�س��е�����*/

	disppath(g, i, j);/*����disppath����,��������������м������·��*/
}
void disppath(MGraph g, int i, int j)
{
	int k;
	p[0] = i;
	for (k = 0; k<g.vexnum; k++)
		visited[i] = 0;/*��ʼ��������ķ��ʱ�־λ������Ϊδ���ʹ���*/
	a = 0;/*��ʼ��·��������*/
	path(g, i, j, 0);/*ͨ������path�������ҵ���vi��vj������·�������*/
}
void path(MGraph g, int i, int j, int k)
/*ȷ��·���ϵ�k+1����������*/
{
	int s;
	if (p[k] == j)/*�ҵ�һ��·��*/
	{
		a++;/*·��������ֵ��1*/
		printf("��%d��:\t", a);
		for (s = 0; s <= k - 1; s++)/*���һ��·��*/
		{
			printf("%s", g.vex[p[s]].sight);
			printf("->");
		}
		//cout<<g.vex[p[s]].sight;
		printf("%s\n", g.vex[p[s]].sight);
	}
	s = 0;
	while (s<g.vexnum)
	{
		if (s != i)/*��֤�ҵ����Ǽ�·��*/
		{
			if (g.arcs[p[k]][s].adj != Max&&visited[s] == 0)
				/*��vk��vs֮���бߴ�����vsδ�����ʹ�*/
			{
				visited[s] = 1;/*�÷��ʱ�־λΪ1,���ѷ��ʵ�*/
				p[k + 1] = s;/*������s���뵽p������*/
				path(g, i, j, k + 1);/*�ݹ����֮*/
				visited[s] = 0;/*���÷��ʱ�־λΪ0����δ���ʵģ��Ա�ö����ܱ�����ʹ��*/
			}
		}
		s++;
	}
}
int Addnewsight(int n)
{
	int i;
	char sight[100], description[1000];
	int length;
	printf("�������³��е����ƣ�\n");
	scanf("%s", &sight);
	printf("�������³��е������Ϣ��\n");
	scanf("%s", &description);
	strcpy(G.vex[n].sight, sight);
	strcpy(G.vex[n].description, description);
	G.vex[n].number = n;
	for (i = 0; i<n; i++)
	{
		system("cls");
		narrate();
		printf("������˳��е���%d�����еľ��루��λ��m����ͬһ���л򲻿ɵ�����20000��ʾ����\n", i);
		scanf("%d", &length);
		if (length != 20000)
			G.arcnum++;
		G.arcs[n][i].adj = G.arcs[i][n].adj = length;
	}
	n++;
	G.vexnum++;
	return n;
}
int Deletesight(int n)
{
	int i;
	int j;
	char c;
	int num;
	char name[20];
	system("cls");
	c = SearchMenu();
	switch (c)
	{
	case '1':
		system("cls");
		narrate();
		printf("\n\n\t\t��������Ҫɾ�����еı�ţ�");
		scanf("%d", &num);
		for (i = 0; i<NUM; i++)
		{
			if (num == G.vex[i].number)
			{
				for (j = 0; j<NUM; j++)
				{
					if (G.arcs[i][j].adj != 20000)
						G.arcnum--;
					G.arcs[i][j].adj = G.arcs[j][i].adj = 20000;
				}

			}
		}
		for (; num<NUM; num++)
		{
			strcpy(G.vex[num].sight, G.vex[num + 1].sight);
			strcpy(G.vex[num].description, G.vex[num + 1].description);
		}
		n--;
		printf("\n\t\t\t�����������...");
		getchar();
		getchar();
		break;
		if (i == NUM)
		{
			printf("\n\n\t\t\tû���ҵ���");
			printf("\n\n\t\t\t�����������...");
			getchar();
			getchar();
		}
		break;
	case '2':
		system("cls");
		narrate();
		printf("\n\n\t\t��������Ҫɾ�����е����ƣ�");
		scanf("%s", name);
		for (i = 0; i<NUM; i++)
		{
			if (!strcmp(name, G.vex[i].sight))
			{
				num = i;
				for (j = 0; j<NUM; j++)
				{
					if (G.arcs[i][j].adj != 20000)
						G.arcnum--;
					G.arcs[i][j].adj = G.arcs[j][i].adj = 20000;
				}
			}
		}
		for (; num<NUM; num++)
		{
			strcpy(G.vex[num].sight, G.vex[num + 1].sight);
			strcpy(G.vex[num].description, G.vex[num + 1].description);
		}
		n--;
		printf("\n\t\t\t�����������...");
		getchar();
		getchar();
		break;
		if (i == NUM)
		{
			printf("\n\n\t\t\tû���ҵ���");
			printf("\n\n\t\t\t�����������...");
			getchar();
			getchar();
		}
		break;
	}
	return n;
}
char Changemenu()
{
	char c;
	int flag;
	do {
		flag = 1;
		system("cls");
		narrate();
		printf("\n\t\t\t								\n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t        1���޸ĳ�����Ϣ           \n");
		printf("\t\t\t        2���޸ĺ�����Ϣ           \n");
		printf("\t\t\t         e������                  \n");
		printf("\t\t\t	                                \n");
		printf("\t\t\t									\n");
		printf("\t\t\t\t����������ѡ��");
		scanf("%c", &c);
		if (c == '1' || c == '2' || c == 'e')
			flag = 0;
	} while (flag);
	return c;
}
char Sightmenu()
{
	char c;
	int flag;
	do {
		flag = 1;
		system("cls");
		narrate();
		printf("\n\t\t\t								\n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t        1���޸ĳ�������           \n");
		printf("\t\t\t        2���޸ĳ�������           \n");
		printf("\t\t\t        e������                   \n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t									\n");
		printf("\t\t\t\t����������ѡ��");
		scanf("%c", &c);
		if (c == '1' || c == '2' || c == 'e')
			flag = 0;
	} while (flag);
	return c;
}
void Changesight()
{
	int a, b, length;
	char sight[100];
	char description[1000];
	char p;
	char q;
	int i;
	int num;
	p = Changemenu();
	switch (p)
	{
	case'1':
		system("cls");
		narrate();
		printf("\n\n\t\t��������Ҫ�޸ĵĳ��б�ţ�");
		scanf("%d", &num);
		for (i = 0; i < NUM; i++)
		{
			if (G.vex[i].number == num)
			{
				q = Sightmenu();
				if (q == '1')
				{
					printf("�������޸ĺ�ĳ������ƣ�\n");
					scanf("%s", &sight);
					strcpy(G.vex[num].sight, sight);
					printf("\t\t\t\t�޸ĳɹ���\n");
				}
				else if (q == '2')
				{
					printf("�������޸ĺ�ĳ�����Ϣ��\n");
					scanf("%s", &description);
					strcpy(G.vex[num].description, description);
					printf("\t\t\t\t�޸ĳɹ���\n");
				}
				else if (q == 'e')
					p = Changemenu();
			}
		}
		printf("\n\t\t�����������...");
		getchar();
		getchar();
		break;
		if (i == NUM)
		{
			printf("\n\n\t\t\t\tû���ҵ���");
			printf("\n\n\t\t\t�����������...");
			getchar();
			getchar();
		}
		break;
	case '2':
		printf("\t\t�������·һ��ĳ�����ţ�");
		scanf("%d", &a);
		printf("\t\t�������·��һ��ĳ�����ţ�");
		scanf("%d", &b);
		printf("\t\t�������޸ĺ�ĵ�·���ȣ�");
		scanf("%d", &length);
		G.arcs[a][b].adj = G.arcs[b][a].adj = length;
		printf("\t\t\t\t�޸ĳɹ���\n");
		printf("\t\t");
		getchar();
		system("PAUSE");
		break;
	}
}


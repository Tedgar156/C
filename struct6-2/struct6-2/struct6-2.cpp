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
	int id; //ͼ����
	char name[20];//ͼ����
	int price;//�۸�
	Data pubData;//��������
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
	//��ʼ����ָ��ͷ��㣬����ʼ��������j=0
	p = L; j = 0;
	//ѭ������ָ��ָ���i-1�����
	while (p != NULL&&j<i - 1)
	{
		p = p->next;
		j++;
	}
	//���i�Ƿ���ȷ(1<=i<=n+1)    j>i-1ʱ��i<1
	if (p == NULL || j>i - 1)return 0;//p==NULLʱ��i>n+1
	//����ռ䲢����
	q = (LNode*)malloc(sizeof(LNode));
	if (q == NULL)return 0;
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}
void disp(LNode *p)
{
	printf("\t���\t%-16s�۸�\t��������\n", "����");
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
	printf("\t���\t%-16s�۸�\t��������\n", "����");
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
	printf("\t����������:");
	scanf("%s", e.name);
	printf("\t������۸�:");
	scanf("%d", &e.price);
	printf("\t�������������(��):");
	scanf("%d", &e.pubData.year);
	printf("\t�������������(��):");
	scanf("%d", &e.pubData.month);
	printf("\t�������������(��):");
	scanf("%d", &e.pubData.day);
	b = InsertList(L, a+1, e);
	if (b==0)
	{
		system("cls");
		printf("����ʧ��");
		return;
	}
	else if (b == 1)
	{
		system("cls");
		printf("����ɹ�������\n");
		return;
	}
}
void delet(LNode *L)
{
	char bookname[20],b;
	LNode *p = L->next,*q=L;
	printf("\t������Ҫɾ������:");
	scanf("%s", bookname);
	while (p != NULL)
	{
		if (strcmp(p->data.name,bookname)==0)
		{
			disp(p);
			printf("�Ƿ�ɾ��(Y/N)?");
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
				printf("ɾ���ɹ�������\n");
			}
			return;
		}
		q = q->next;
		p = p->next;
	}
	if (p == NULL)
	{
		printf("δ���ҵ����飬ɾ��ʧ��\n");
		return;
	}
}
void find(LNode *L)
{
	LNode *p=L;
	char bookname[20];
	printf("\t��������Ҫ��������:");
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
	printf("\tδ�ҵ�����\n");
}
//�˵�
void modepy(LNode *L)
{
	int j = 1;
	ElemType e;
	char bookname[20], b;
	LNode *p = L->next, *q = L;
	printf("\t������Ҫ�޸�����:");
	scanf("%s", bookname);
	while (p != NULL)
	{
		if (strcmp(p->data.name, bookname) == 0)
		{
			disp(p);
			printf("�Ƿ��޸�(Y/N)?");
			getchar();
			scanf("%c", &b);
			if (b == 'Y' || b == 'y')
			{
				q->next = p->next;
				free(p);
				e.id = j;
				printf("\t����������:");
				scanf("%s", e.name);
				printf("\t������۸�:");
				scanf("%d", &e.price);
				printf("\t�������������(��):");
				scanf("%d", &e.pubData.year);
				printf("\t�������������(��):");
				scanf("%d", &e.pubData.month);
				printf("\t�������������(��):");
				scanf("%d", &e.pubData.day);
				InsertList(L, j, e);
				system("cls");
				printf("�޸ĳɹ�������\n");
			}
			return;
		}
		q = q->next;
		p = p->next;
		j++;
	}
	if (p == NULL)
	{
		printf("δ���ҵ����飬�޸�ʧ��\n");
		return;
	}
}
void menu(LNode *L)
{

	int select;
	char a;
	do
	{
		system("cls");//����
		printf("\t****************************\n");
		printf("\t*1.����µ�ͼ��            *\n");
		printf("\t*2.ɾ��ָ��ͼ��            *\n");
		printf("\t*3.����ָ��ͼ��(����)      *\n");
		printf("\t*4.�޸�ͼ����Ϣ            *\n");
		printf("\t*5.��ʾ���е�ͼ��          *\n");
		printf("\t*0.�˳�                    *\n");
		printf("\t****************************\n");
		printf("\t������ٺʹ��룺");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			//����һ��Ԫ����ָ��λ��
			addinformation(L);
			system("pause");
			break;
		case 2:
			//ɾ��ָ��λ�õ�Ԫ�ط���
			delet(L);
			system("pause");
			break;
		case 3:
			//����ָ��Ԫ�ص�λ��
			find(L);
			system("pause");
			break;
		case 4:
			//�޸�ͼ����Ϣ
			modepy(L);
			system("pause");
			break;
		case 5:
			//��ʾ���е�Ԫ��
			display(L);

			system("pause");
			break;
		case 0:
			//�˳�
			printf("\t�����Ƿ�ȷ��Ҫ�˳�����(Y/N)");
			//�����û������ѡ��ִ���Ƿ�Ҫ�˳��Ĺ���
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
	Book book1 = { 1, "���ݽṹ", 34, { 2014, 1, 25 } };
	Book book2 = { 2, "C���Գ������", 31, { 2013, 11, 12 } };
	Book book3 = { 3, "Java�������", 42, { 2015, 8, 1 } };
	Book book4 = { 4, "WebӦ�ÿ���", 68, { 2016, 10, 18 } };
	Book book5 = { 5, "Android��������", 75, { 2017, 3, 30 } };
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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
struct num{
	char name[20];
	struct num *next;
};
struct Data
{
	char name[20];
	char secret[20];
	struct num no;
};
typedef struct ID
{
	struct Data data;
	struct ID *next;
}id;

id *User=(id*)malloc(sizeof(id));
int compose(char a[],char b[])
{
	FILE *fp;
	id *p=User,*q;
	while (p->next != NULL)
	{
		p = p->next;
	}
	if ((fp = fopen("1.txt", "r")) == NULL)
	{
		printf("���ļ�ʧ��!\n");
		return 0;
	}
	while (!feof(fp))
	{
		q = (id*)malloc(sizeof(id));
		fread(&q->data, sizeof(struct Data), 1, fp);
		q->next = NULL;
		p->next = q;
		printf("%s\n", q->data.name);
		printf("%s\n", q->data.secret);
		if (strcmp(q->data.name, a) == 0)
		{
			printf("һ��\n");
			b=q->data.secret;
			fclose(fp);
			return 1;
		}
		p = p->next;
	}
	fclose(fp);
	return -1;
}
int main()
{
	FILE *fp;
	char secr[20];
	int i=0;
	char a = 'n';
	struct num k;
	k = User->data.no;
	strcpy(k.name, "����");
	k.next = NULL;
	struct num *o;
	o = (struct num*)malloc(sizeof(struct num));
	strcpy(o->name, "�г�ΰ");
	o->next = NULL;
	k.next = o;
	o = &k;
	while (o != NULL)
	{
		printf("����:%s\n", o->name);
		o = o->next;
	}
	User->next = NULL;
	fp = fopen("1.txt", "a+");
	id user,*q=User,*p=User->next;
	do{
	printf("�������û���:");
	fflush(stdin);
	scanf("%s", user.data.name);
	i = compose(user.data.name, secr);
	if (i == 1)
	{
		//printf("�û����ظ�\n");
		//printf("�Ƿ������");
		i = MessageBox(0, L"�û����ظ�", L"����", MB_OKCANCEL);
		switch (i)
		{
		case IDOK:a = 'y'; break;
		case IDCANCEL:fclose(fp); return 1; break;
		}
	}
	else if (i==-1)
	{
		printf("����:");
		fflush(stdin);
		scanf("%s", user.data.secret);
		while (q->next != NULL)
		{
			q = q->next;
		}
		p = (id*)malloc(sizeof(id));
		p->data = user.data;
		p->next = NULL;
		q->next = p;
		fwrite(&p->data, sizeof(struct Data), 1, fp);
		a = 'n';
	}
	} while (a == 'y' || a == 'Y');

	fclose(fp);
	int g = 0;
	id m;
	while (g<1)
	{
		fopen("1.txt", "r");
		fread(&m.data, sizeof(struct Data), 1, fp);
		printf("����%s\n", m.data.name);
		printf("����%s\n", m.data.secret);
		fclose(fp);
		g++;
	}
	a = 'n';
	do{
		printf("�û���:");
		fflush(stdin);
		scanf("%s", user.data.name);
		p = User;
		while (p != NULL)
		{
			if (strcmp(p->data.name, user.data.name) == 0)
			{
				break;
			}
			p = p->next;
		}
		
		if (p!=NULL)
		{
			printf("����:%s\n", p->data.secret);
			printf("����:");
			fflush(stdin);
			scanf("%s", user.data.secret);
			if (strcmp(user.data.secret, p->data.secret) == 0)
			{
				MessageBox(0, L"�û���¼�ɹ�", L"��ȷ", MB_OK);
			}
			else{
				i = MessageBox(0, L"�������!�Ƿ����?", L"����", MB_OKCANCEL);
				switch (i)
				{
				case IDOK:a = 'y'; break;
				case IDCANCEL:return 1; break;
				}
			}
		}
		else 
		{
			MessageBox(0, L"�޸��û�!", L"����", MB_OK);
		}
	} while (a == 'y' || a == 'Y');
	fclose(fp);
	return 0;
}

//
//#define MAXSIZE 10
//typedef char ElemType;
//typedef struct ArcNode
//{
//	int adjVex;//���vi �ڽ�����
//	struct ArcNode *nextArc;//ָ��VI��һ���ڽӵ�ı߽��
//	int weight;//Ȩֵ
//}ArcNode;
//typedef struct VNode
//{
//	ElemType data;//�洢��������
//	ArcNode *firstArc;//ָ�򶥵�Vi�ĵ�һ���ڽӵ�ı߽��
//}VNode;
//typedef struct
//{
//	VNode adjList[MAXSIZE];//��������Ϣ
//	int n, e;//ͼ����������
//}ALGraph;
//int LocateVex(ALGraph G, ElemType v)//��ͼG�в��Ҷ���V���ҵ��󷵻ض�������������ţ������ڷ���-1
//{
//	int i;
//	for (i = 0; i < G.n;i++)
//	if (G.adjList[i].data == v)return i;
//	return -1;
//}
//void DisplayAdjList(ALGraph G)//����Ļ����ʾͼG���ڽӱ��ʾ
//{
//	int i;
//	ArcNode *p;
//	printf("ͼ���ڽӱ��ʾ:");
//	for (i = 0; i < G.n; i++)
//	{
//		printf("\n%4c", G.adjList[i].data);
//		p = G.adjList[i].firstArc;
//		while (p != NULL)
//		{
//			printf("-->%d", p->adjVex); p = p->nextArc;
//		}
//	}
//	printf("\n");
//}
////��������ͼ
//void CreateLink(ALGraph *pg)
//{
//	int i, j, k;
//	ElemType v1, v2;
//	ArcNode *s;
//	printf("������ͼ�Ķ�����������:\n");
//	printf("������="); scanf("%d", &pg->n);
//	printf("����="); scanf("%d", &pg->e);
//	printf("������ͼ������Ϣ:\n"); getchar();
//	for (i = 0; i <= pg->n; i++)
//	{
//		scanf("%c", &pg->adjList[i].data);
//		pg->adjList[i].firstArc = NULL;
//	}
//	printf("������ߵ���Ϣ:\n");
//	for (k = 0; k < pg->e; k++)
//	{
//		printf("�������%d���ߵ������ϵ�:", k + 1);
//		scanf("%c%c", &v1, &v2); getchar();
//		i = LocateVex(*pg, v1); j = LocateVex(*pg, v2);
//		if (i >= 0 && j >= 0)
//		{
//			
//			s = (ArcNode*)malloc(sizeof(ArcNode));
//			s->adjVex = j;
//			s->nextArc = pg->adjList[i].firstArc;
//			pg->adjList[i].firstArc = s;
//			s = (ArcNode*)malloc(sizeof(ArcNode));
//			s->adjVex = i;
//			s->nextArc = pg->adjList[j].firstArc;
//			pg->adjList[j].firstArc = s;
//
//		}
//
//	}
//}
//int main()
//{
//	ALGraph G;
//	CreateLink(&G);
//	DisplayAdjList(G);
//	return 0;
//}
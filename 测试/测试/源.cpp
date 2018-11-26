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
		printf("打开文件失败!\n");
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
			printf("一致\n");
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
	strcpy(k.name, "唐亿");
	k.next = NULL;
	struct num *o;
	o = (struct num*)malloc(sizeof(struct num));
	strcpy(o->name, "有陈伟");
	o->next = NULL;
	k.next = o;
	o = &k;
	while (o != NULL)
	{
		printf("名字:%s\n", o->name);
		o = o->next;
	}
	User->next = NULL;
	fp = fopen("1.txt", "a+");
	id user,*q=User,*p=User->next;
	do{
	printf("请输入用户名:");
	fflush(stdin);
	scanf("%s", user.data.name);
	i = compose(user.data.name, secr);
	if (i == 1)
	{
		//printf("用户名重复\n");
		//printf("是否继续？");
		i = MessageBox(0, L"用户名重复", L"错误", MB_OKCANCEL);
		switch (i)
		{
		case IDOK:a = 'y'; break;
		case IDCANCEL:fclose(fp); return 1; break;
		}
	}
	else if (i==-1)
	{
		printf("密码:");
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
		printf("测试%s\n", m.data.name);
		printf("则是%s\n", m.data.secret);
		fclose(fp);
		g++;
	}
	a = 'n';
	do{
		printf("用户名:");
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
			printf("密码:%s\n", p->data.secret);
			printf("密码:");
			fflush(stdin);
			scanf("%s", user.data.secret);
			if (strcmp(user.data.secret, p->data.secret) == 0)
			{
				MessageBox(0, L"用户登录成功", L"正确", MB_OK);
			}
			else{
				i = MessageBox(0, L"密码错误!是否继续?", L"错误", MB_OKCANCEL);
				switch (i)
				{
				case IDOK:a = 'y'; break;
				case IDCANCEL:return 1; break;
				}
			}
		}
		else 
		{
			MessageBox(0, L"无该用户!", L"错误", MB_OK);
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
//	int adjVex;//存放vi 邻接序列
//	struct ArcNode *nextArc;//指向VI下一个邻接点的边界点
//	int weight;//权值
//}ArcNode;
//typedef struct VNode
//{
//	ElemType data;//存储顶点名称
//	ArcNode *firstArc;//指向顶点Vi的第一个邻接点的边界点
//}VNode;
//typedef struct
//{
//	VNode adjList[MAXSIZE];//顶点结点信息
//	int n, e;//图顶点数、边
//}ALGraph;
//int LocateVex(ALGraph G, ElemType v)//在图G中查找顶点V，找到后返回顶点数组的索引号，不存在返回-1
//{
//	int i;
//	for (i = 0; i < G.n;i++)
//	if (G.adjList[i].data == v)return i;
//	return -1;
//}
//void DisplayAdjList(ALGraph G)//在屏幕上显示图G的邻接表表示
//{
//	int i;
//	ArcNode *p;
//	printf("图的邻接表表示:");
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
////建立无向图
//void CreateLink(ALGraph *pg)
//{
//	int i, j, k;
//	ElemType v1, v2;
//	ArcNode *s;
//	printf("请输入图的顶点数及边数:\n");
//	printf("顶点数="); scanf("%d", &pg->n);
//	printf("边数="); scanf("%d", &pg->e);
//	printf("请输入图顶点信息:\n"); getchar();
//	for (i = 0; i <= pg->n; i++)
//	{
//		scanf("%c", &pg->adjList[i].data);
//		pg->adjList[i].firstArc = NULL;
//	}
//	printf("请输入边的信息:\n");
//	for (k = 0; k < pg->e; k++)
//	{
//		printf("请输入第%d条边的两个断点:", k + 1);
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
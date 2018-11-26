#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
typedef char ElemType;
typedef struct
{
	ElemType V[MAXSIZE];//������Ϣ
	int arcs[MAXSIZE][MAXSIZE];//�ٽ������
	int e;//����
	int n;//������
}Graph;
//�߽������Ͷ���
typedef struct ArcNode
{
	int adjVex;//�����vi�ڽӵ����
	struct ArcNode *nextArc;//ָ��vi��һ���ڽӵ�ı߽��
	int weight;//Ȩֵ
}ArcNode;
//ͼ�Ľ������ٽ����
typedef struct VNode
{
	ElemType data;//�洢�������ƻ�ȥ�����Ϣ
	ArcNode *firstArc;
}VNode;
typedef struct
{
	VNode adjList[MAXSIZE];//������Ϣ
	int n, e;//ͼ�Ķ������ͻ���
}ALGraph;
int getpos(ElemType V, Graph aj)
{
	int i = -1;
	for (int j = 0; j < aj.n; j++)
	{
		if (aj.V[j] == V)
		{
			return j;
		}
	}
	return i;
}
void displayAdj(Graph aj)
{
	for (int i = 0; i < aj.n; i++)
	{
		for (int j = 0; j < aj.n; j++)
		{
			printf("%d\t", aj.arcs[i][j]);
		}
		printf("\n");
	}
}
void CreatAdj()
{
	Graph aj;
	ElemType V1, V2;
	int i, j,k;
	printf("�����붥�����ͱ���:");
	scanf("%d%d", &aj.n, &aj.e);
	printf("�����붥����Ϣ��");
	getchar();
	for (i = 0; i < aj.n; i++)
	{
		scanf("%c", &aj.V[i]);
	}
	//��ʼ���ڽӾ���
	for (i = 0; i < aj.n; i++)
	{
		for (j = 0; j < aj.n; j++)
		{
			aj.arcs[i][j] = 0;
		}
	}
	getchar();
	for (i = 0; i < aj.e; i++)
	{
		printf("������%d���ߵ������˵�:", i + 1);
		scanf("%c%c", &V1, &V2);
		getchar();
		j = getpos(V1, aj), k = getpos(V2, aj);
		if (j >= 0 && k >= 0)
		{
			aj.arcs[j][k] = 1;
			aj.arcs[k][j] = 1;
		}
	}
	displayAdj(aj);
}
int locPos(ElemType V,ALGraph aj)
{
	int i = -1, j;
	for (j = 0; j < aj.n; j++)
	{
		if (aj.adjList[j].data == V)
		{
			return j;
		}
	}
	return i;
}
void displayLink(ALGraph aj)
{
	int i;
	ArcNode *p;
	for (i = 0; i < aj.n; i++)
	{
		p = aj.adjList[i].firstArc;
		printf("%c:\t", aj.adjList[i].data);
		while (p != NULL)
		{
			printf("%d->", p->adjVex);
			p = p->nextArc;
		}
		printf("\n");
	}
}
void CreatLink()
{
	ALGraph aj;
	ElemType V1, V2;
	int i, j, k;
	printf("�����붥�����ͱ�����");
	scanf("%d%d", &aj.n,&aj.e);
	printf("�����붥����Ϣ:");
	getchar();
	for (i = 0; i < aj.n; i++)
	{
		scanf("%c", &aj.adjList[i].data);
		aj.adjList[i].firstArc = NULL;
	}
	getchar();
	for (i = 0; i < aj.e; i++){
		printf("�������%d���ߵĶ˵�:", i + 1);
		scanf("%c%c", &V1, &V2);
		getchar();
		j=locPos(V1, aj),k=locPos(V2, aj);
		if (j >= 0 && k >= 0)
		{
			ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjVex = k;
			p->nextArc = aj.adjList[j].firstArc;
			aj.adjList[j].firstArc = p;
			ArcNode*q = (ArcNode*)malloc(sizeof(ArcNode));
			q->adjVex = j;
			q->nextArc = aj.adjList[k].firstArc;
			aj.adjList[k].firstArc = q;
		}
	}
	displayLink(aj);
}
int main()
{
	//CreatAdj();
	CreatLink();
	return 0;
}
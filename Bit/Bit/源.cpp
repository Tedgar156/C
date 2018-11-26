#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
typedef char ElemType;
typedef struct
{
	ElemType V[MAXSIZE];//顶点信息
	int arcs[MAXSIZE][MAXSIZE];//临界矩阵建立
	int e;//边数
	int n;//顶点数
}Graph;
//边界点的类型定义
typedef struct ArcNode
{
	int adjVex;//存放与vi邻接的序号
	struct ArcNode *nextArc;//指向vi下一个邻接点的边界点
	int weight;//权值
}ArcNode;
//图的建立用临界矩阵
typedef struct VNode
{
	ElemType data;//存储顶点名称或去相关信息
	ArcNode *firstArc;
}VNode;
typedef struct
{
	VNode adjList[MAXSIZE];//顶点信息
	int n, e;//图的顶点数和弧数
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
	printf("请输入顶点数和边数:");
	scanf("%d%d", &aj.n, &aj.e);
	printf("请输入顶点信息：");
	getchar();
	for (i = 0; i < aj.n; i++)
	{
		scanf("%c", &aj.V[i]);
	}
	//初始化邻接矩阵
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
		printf("请输入%d条边的两个端点:", i + 1);
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
	printf("请输入顶点数和边数：");
	scanf("%d%d", &aj.n,&aj.e);
	printf("请输入顶点信息:");
	getchar();
	for (i = 0; i < aj.n; i++)
	{
		scanf("%c", &aj.adjList[i].data);
		aj.adjList[i].firstArc = NULL;
	}
	getchar();
	for (i = 0; i < aj.e; i++){
		printf("请输入第%d条边的端点:", i + 1);
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
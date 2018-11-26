#include<stdio.h>
#include<stdlib.h>
#define P 20
typedef char ElemType;
typedef struct ThrNode
{
	ElemType data;
	struct ThrNode *lchild, *rchild;
	int ltag, rtag;
}ThrNode;
ThrNode* CreatTree()
{
	ElemType Ti;
	ThrNode *Bt;
	scanf("%c", &Ti);
	if (Ti == '#') Bt= NULL;
	else
	{
		Bt = (ThrNode*)malloc(sizeof(ThrNode));
		Bt->data = Ti;
		Bt->rtag = 0;
		Bt->ltag = 0;
		Bt->lchild=CreatTree();
		Bt->rchild = CreatTree();
	}
	return Bt;
}
//建立中序线索原因：
//查找到任意一个结点的前驱和后继
//查找前驱时：1、当ltag=1时，lchild即为前驱。2、当ltag=0时，查找到lchild的最右边的即是左孩子的最后一个。while(rtag==0)q=q->rchild;
//查找后继时：1、当rtag=1时，rchild即为后继。2、当rtag=0时，查找到rchild的最左边的即是右孩子的第一个。while(ltag==0)q=q->lchild;
void ThrBiTree(ThrNode *bt, ThrNode *pre)//建立中序线索
{
	if (bt == NULL)return;
	ThrBiTree(bt->rchild, pre);
	if (bt->lchild==NULL)
	{
		bt->ltag = 1;
		bt->lchild = pre;
	}
	if (bt->rtag == 1&&pre!=NULL)
	{
		pre->rchild = bt;
	}
	if (bt->rchild == NULL)
	{
		bt->rtag = 1;
	}
	pre = bt;
	ThrBiTree(bt->lchild, pre);
}
void Display(ThrNode *bt)
{
	if (bt == NULL)return;
	else
	{
		printf("%c\t", bt->data);
		Display(bt->lchild);
		Display(bt->rchild);
	}
	return;
}
int main()
{
	ThrNode *Bt;
	Bt=CreatTree();
	Display(Bt);
}
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
//������������ԭ��
//���ҵ�����һ������ǰ���ͺ��
//����ǰ��ʱ��1����ltag=1ʱ��lchild��Ϊǰ����2����ltag=0ʱ�����ҵ�lchild�����ұߵļ������ӵ����һ����while(rtag==0)q=q->rchild;
//���Һ��ʱ��1����rtag=1ʱ��rchild��Ϊ��̡�2����rtag=0ʱ�����ҵ�rchild������ߵļ����Һ��ӵĵ�һ����while(ltag==0)q=q->lchild;
void ThrBiTree(ThrNode *bt, ThrNode *pre)//������������
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
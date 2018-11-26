#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode;
int InsertList(LNode *L, int i, ElemType e)
{
	int j;
	LNode *p, *q;
	//初始化，指向头结点，并初始化计数器j=0
	p = L; j = 0;
	//循环：将指针指向第i-1个结点
	while (p != NULL&&j<i - 1)
	{
		p = p->next;
		j++;
	}
	//检果i是否正确(1<=i<=n+1)    j>i-1时，i<1
	if (p == NULL || j>i - 1)return 0;//p==NULL时，i>n+1
	//分配空间并插入
	q = (LNode*)malloc(sizeof(LNode));
	if (q == NULL)return 0;
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}
void display(LNode *L)
{
	LNode *p;
	p = L->next;
	while (p != NULL)
	{
		printf("%3d", p->data);
		p = p->next;
	}
	printf("\n");
}
void mergeList(LNode *La, LNode *Lb)
{
	LNode *pa, *pb, *pc;
	pa = La;
	pb = La->next;
	pc = Lb->next;
	while (pc != NULL&&pb != NULL)
	{
		/*if (pb->data < pc->data)
		{
			pa = pa->next;
			pb = pb->next;
			pa->next = pc;
			pc = pc->next;
			pa->next->next = pb;
			pa = pa->next;
		}
		else
		{
			pa->next = pc;
			pc = pc->next;
			pa->next->next = pb;
			pa = pa->next;
			pa = pa->next;
			pb = pb->next;
		}*/
		if (pb->data < pc->data)
		{
			pa->next = pb;
			pb = pb->next;
			pa = pa->next;
		}
		else
		{
			pa->next = pc;
			pc = pc->next;
			pa = pa->next;
		}
	}
	if (pb == NULL)
	{
		pa->next = pc;
	}
	if (pc == NULL)
	{
		pa->next = pb;
	}
}
void deleteElem(LNode *L)
{
	LNode *q, *p, *r;
	p = L->next;
	r = L->next;
	q = p->next;

	/*while (q->next != NULL)
	{
		r = L->next;
		while (r !=q)
		{
			if(r->data == q->data)
			{
				if(q->next!=NULL)
				{
				p->next = q->next;
				free(q);
				q = p->next;
				}
				else
				{
					free(q);
				}
			}
			r = r->next;
		}
		if (q->next != NULL&&r!= q)
		{
			q = q->next;
			p = p->next;
		}
	}*/
	while (q->next != NULL)
	{
		r = L->next;
		while (r->data != q->data&&r->next != q)
		{
			r = r->next;
		}
		if (r->data == q->data)
		{
			if (q->next != NULL)
			{
				p->next = q->next;
				free(q);
				q = p->next;
			}
			else
			{
				free(q);
			}
		}
		if (q->next != NULL&&r->data!=q->data)
		{
			q = q->next;
			p = p->next;
		}
	}
}
int main()
{
	LNode Ha, Hb,Hc;
	Ha.next = NULL;
	Hb.next = NULL;
	Hc.next = NULL;
	InsertList(&Ha, 1, 16);
	InsertList(&Ha, 2, 25);
	InsertList(&Ha, 3, 37);
	InsertList(&Ha, 4, 45);
	InsertList(&Ha, 5, 52);
	InsertList(&Ha, 6, 59);
	InsertList(&Ha, 7, 63);
	InsertList(&Ha, 8, 65);
	//显示所有元素
	display(&Ha);

	InsertList(&Hb, 1, 12);
	InsertList(&Hb, 2, 21);
	InsertList(&Hb, 3, 39);
	InsertList(&Hb, 4, 55);
	InsertList(&Hb, 5, 62);
	display(&Hb);

	mergeList(&Ha, &Hb);

	display(&Ha);

	InsertList(&Hc, 1, 16);
	InsertList(&Hc, 2, 16);
	InsertList(&Hc, 3, 16);
	InsertList(&Hc, 4, 45);
	InsertList(&Hc, 5, 16);
	InsertList(&Hc, 6, 16);
	InsertList(&Hc, 7, 16);
	InsertList(&Hc, 8, 16);
	InsertList(&Hc, 9, 16);
	InsertList(&Hc, 10, 25);
	InsertList(&Hc, 11, 39);
	InsertList(&Hc, 12, 37);
	InsertList(&Hc, 13, 62);
	display(&Hc);
	deleteElem(&Hc);
	display(&Hc);
}
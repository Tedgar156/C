//树
#include<stdio.h>
#include<stdlib.h>
typedef char Elemtype;
typedef struct BiNOde
{
	Elemtype data;
	struct BiNOde *lchild;
	struct BiNOde *rchild;
}BiNode;
void visit(Elemtype e)
{
	printf("%c", e);
}
BiNode* CreatBi(FILE *fp)
{
	Elemtype c;
	BiNode *p;
	if (!feof(fp))c = fgetc(fp);
	else return NULL;
	//c = getchar();
	if(c!='#')
	{
		p = (BiNode*)malloc(sizeof(BiNode));
		if (p == NULL) printf("申请失败");
		p->data = c;
		p->lchild=CreatBi(fp);
		p->rchild=CreatBi(fp);
	}
	else return NULL;
	return p;
}
void PreOrder(BiNode *bt)//先序
{
	if (bt!=NULL)
	{
		visit(bt->data);//读取数据
		PreOrder(bt->lchild);//读取右孩子
		PreOrder(bt->rchild);//读取左孩子
	}
}
int main()
{
	FILE *fp;
	fp = fopen("Data//BiTree.txt", "r");
	BiNode *T;
	printf("先序为:");
	T=CreatBi(fp);
	PreOrder(T);
	printf("\n");
	fclose(fp);
	return 0;
}
/*#include<stdio.h>
#include<stdlib.h>
#define N 10
typedef struct
{
	int score;
	char name[10];
	int E;
}stdata;
typedef struct st
{
	stdata data;
	struct st *next;
}st;
typedef struct st Elemtype;
void add(Elemtype *ST)
{
	FILE *fp;
	Elemtype *p=ST->next, *q=ST;
	char a;
	fp = fopen("s.txt", "w+");
	while (p != NULL)
		{
			p = p->next;
			q = q->next;
		}
	do{
		p = (Elemtype*)malloc(sizeof(Elemtype));
		if (p == NULL)printf("申请失败");
		printf("总成绩:");
		scanf("%d", &p->data.score);
		getchar();
		printf("名中国i");
		scanf("%s", p->data.name);
		printf("E");
		scanf("%d", &p->data.E);
		if (fwrite(&p->data, sizeof(stdata), 1, fp) !=1)
			printf("存储信息失败");
		p->next = NULL;
		q->next = p;
		q = q->next;
		getchar();
		printf("是否继续");
		scanf("%c", &a);
	} while (a == 'y' || a == 'Y');
		fclose(fp);
}
void dis(st *ST)
{
	st *p = ST->next;
	while (p != NULL)
	{
		printf("\n\n%d-%s-%d", p->data.score, p->data.name, p->data.E);
		p = p->next;
	}
}
void load(st*ST)
{
	FILE *fp;
	fp = fopen("s.txt", "r");
	Elemtype *p = ST->next, *q = ST;
		while (p != NULL)//q=链表中最后一个
		{
			p = p->next;
			q = q->next;
		}
	while (!feof(fp))
	{
		
		p = (Elemtype*)malloc(sizeof(Elemtype));
		if (p == NULL){
			printf("申请失败"); return;
		}
		fread(&p->data, sizeof(stdata), 1, fp);
		p->next = NULL;
		q->next = p;
		q = q->next;
	}
	fclose(fp);
}
int main()
{
	FILE *fp;
	Elemtype ST;
	ST.next = NULL;
	if ((fp = fopen("s.txt", "r")) == NULL)
	{
		fp = fopen("s.txt", "w");
		add(&ST);
		fclose(fp);
	}
	else
	{
		load(&ST);
	}
	
	dis(&ST);
}
//栈
/*#include<stdio.h>
#include<stdlib.h>
typedef char Elemtype;
typedef struct Link
{
	Elemtype data;
	struct Link *next;
}Link;
typedef struct 
{
	Link *top;
	Link *bottom;
}LNode;
void InitStack(LNode *T)
{
	T->top = (Link*)malloc(sizeof(Link));

	T->bottom = T->top ;
	T->top->next = NULL;
}
void push(LNode *T,Elemtype e)
{
	Link *p=(Link*)malloc(sizeof(Link));
	if (p == NULL){ printf("申请空间失败"); return;}
	p->data = e;
	p->next = T->top;
	T->top = p;
}
bool Empty(LNode *t)
{
	if (t->bottom == t->top)return true;
	else return false;
}
void pop(LNode *T, Elemtype *e)
{
	Link *p=NULL;	
	//if (T->bottom == T->top){ printf("空栈无数据"); return; }//判断是否为空栈
	//*e = T->top->data;
	//p = T->top;
	//T->top = T->top->next;
	//free(p);
	if (Empty(T))
	{
		printf("空栈无数据");
		return;
	}
	else
	{
		*e = T->top->data;
		p = T->top;
		T->top = T->top->next;
		free(p);
	}
}
int main()
{
	LNode H;
	Elemtype e='A';
	InitStack(&H);
	push(&H,e);
	pop(&H, &e);
	printf("%c\n", e);
	e = 'B';
	push(&H, e);
	pop(&H, &e);
	printf("%c\n", e);
	e = 'C';
	push(&H, e);
	e = 'D';
	push(&H, e);
	pop(&H, &e);
	printf("%c\n", e);
	pop(&H, &e);
	printf("%c\n", e);
	pop(&H, &e);
	printf("%c\n", e);
	return 0;
}*/
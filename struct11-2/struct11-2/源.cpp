//��
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
		if (p == NULL) printf("����ʧ��");
		p->data = c;
		p->lchild=CreatBi(fp);
		p->rchild=CreatBi(fp);
	}
	else return NULL;
	return p;
}
void PreOrder(BiNode *bt)//����
{
	if (bt!=NULL)
	{
		visit(bt->data);//��ȡ����
		PreOrder(bt->lchild);//��ȡ�Һ���
		PreOrder(bt->rchild);//��ȡ����
	}
}
int main()
{
	FILE *fp;
	fp = fopen("Data//BiTree.txt", "r");
	BiNode *T;
	printf("����Ϊ:");
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
		if (p == NULL)printf("����ʧ��");
		printf("�ܳɼ�:");
		scanf("%d", &p->data.score);
		getchar();
		printf("���й�i");
		scanf("%s", p->data.name);
		printf("E");
		scanf("%d", &p->data.E);
		if (fwrite(&p->data, sizeof(stdata), 1, fp) !=1)
			printf("�洢��Ϣʧ��");
		p->next = NULL;
		q->next = p;
		q = q->next;
		getchar();
		printf("�Ƿ����");
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
		while (p != NULL)//q=���������һ��
		{
			p = p->next;
			q = q->next;
		}
	while (!feof(fp))
	{
		
		p = (Elemtype*)malloc(sizeof(Elemtype));
		if (p == NULL){
			printf("����ʧ��"); return;
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
//ջ
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
	if (p == NULL){ printf("����ռ�ʧ��"); return;}
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
	//if (T->bottom == T->top){ printf("��ջ������"); return; }//�ж��Ƿ�Ϊ��ջ
	//*e = T->top->data;
	//p = T->top;
	//T->top = T->top->next;
	//free(p);
	if (Empty(T))
	{
		printf("��ջ������");
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
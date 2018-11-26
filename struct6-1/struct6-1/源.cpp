#include<stdio.h>
/*void display(int x[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%3d", x[i]);
	}
	printf("\n");
}
void change(int x[], int n)
{
	int i = 0, j = n-1;
	while (i<j)
	{
		//i = 0, j = n - 1;
		while (i<j&&x[i] < 0)
		{
			i++;
		}
		while (i<j&&x[j] > 0)
		{
			j--;
		}
		if (i < j)
		{
			int a = x[i];
			x[i] = x[j];
			x[j] = a;
		}
	}
}
int main()
{
	int a[] = { 5, 14, -6, 8, -7, 9, 6, 13, -2, -1, 0, -4 };
	display(a, 12);
	change(a, 12);
	display(a, 12);
	return 0;
}*/
typedef struct LNode
{
	char data;
	struct LNode *next;
}LNode;
void display(LNode *L)
{
	LNode *p = L->next;
	while (p != NULL)
	{
		printf("%3c", p->data);
		p = p->next;
	}
	printf("\n");
}
void reverseLink(LNode *L)
{
	LNode *p, *q;
	p = L->next;
	
	L->next = NULL;
	while (p != NULL)
	{
		q = p->next;
		p->next = L->next;
		L->next = p;	
		p = q;
	}
}
int main()
{
	LNode H;
	LNode na, nb, nc, nd, ne, nf;
	na.data = 'A'; nb.data = 'B'; nc.data = 'C'; nd.data = 'D'; ne.data = 'E'; nf.data = 'F';
	H.next = &na; na.next = &nb; nb.next = &nc; nc.next = &nd; nd.next = &ne; ne.next = &nf; nf.next = NULL;
	display(&H);
	reverseLink(&H);
	display(&H);
}
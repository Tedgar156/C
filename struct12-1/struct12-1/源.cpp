#include<stdio.h>
#include<stdlib.h>
typedef char ElemType;
typedef struct BiNode
{
	ElemType data;
	struct BiNode *lchild;
	struct BiNode *rchild;
}BiNode;
BiNode *T;
void visit(ElemType e)
{
	printf("%3c", e);
}
//����һ��������(�������������У���#��ʾ����)����������)
BiNode *Creat(FILE *fp)
{
	BiNode *p;
	ElemType e;
	//e=getchar();
	if (!feof(fp))e = fgetc(fp);
	else return NULL;
	if (e != '#')
	{
		p = (BiNode*)malloc(sizeof(BiNode));//����ռ�
		if (p == NULL)return NULL;
		p->data = e;
		//��ֵ
		p->lchild = Creat(fp);//������������
		p->rchild = Creat(fp);//������������
	}
	else return NULL;
	return p;

}
//�������
void PreOrder(BiNode *bt)
{
	if (bt != NULL)
	{
		visit(bt->data);//���ʸ����
		PreOrder(bt->lchild);//�������������
		PreOrder(bt->rchild);//�������������
	}
}
//�������
void InOrder(BiNode *bt)
{
	if (bt != NULL)
	{
		InOrder(bt->lchild);//�������������
		visit(bt->data);//���ʸ����		
		InOrder(bt->rchild);//�������������
	}
}
//�������
void PostOrder(BiNode *bt)
{
	if (bt != NULL)
	{
		PostOrder(bt->lchild);//�������������
		PostOrder(bt->rchild);//�������������
		visit(bt->data);//���ʸ����		

	}
}
int length = 0;
int leaf = 0;
void Count(BiNode *bt)
{

	if (bt != NULL)
	{
		length++;//���ʸ����
		if (bt->lchild == NULL&&bt->rchild == NULL)leaf++;
		Count(bt->lchild);//�������������
		Count(bt->rchild);//�������������
	}


}
int DeleteNode(BiNode *bt, ElemType e)
{
	if (bt->data == e)//ɾ����
	{
		return 1;
	}
	else
	{
		if (bt != NULL)
		{
			if (bt->lchild != NULL&&bt->lchild->data == e)
			{
				bt->lchild = NULL;
				return 0;
			}
			else if (bt->rchild != NULL&&bt->rchild->data == e){

				bt->rchild = NULL;
				return 0;
			}
			else{
				DeleteNode(bt->lchild, e);//�������������
				DeleteNode(bt->rchild, e);//�������������
			}

		}
	}

}
BiNode* inisort(BiNode *bt,ElemType e,ElemType c)
{
	BiNode *p;
	if (bt != NULL)
	{
		if (bt->data == e)
		{
			
			p = (BiNode*)malloc(sizeof(BiNode));
			if (p == NULL)return NULL;
			p->data = c;
			p->lchild = NULL;
			p->rchild = NULL;
			if (bt->lchild == NULL)
			{
				bt->lchild = p;
			}
			else if (bt->rchild == NULL)
			{
				bt->rchild = p;
			}
			else
			{
				p->lchild = bt->lchild;
				bt->lchild = p;
			}
			
		}
		else{
			inisort(bt->lchild, e,c);//�������������
			inisort(bt->rchild, e,c);//�������������
		}

	}
}
int CountIf(BiNode *bt)
{
	int ld=0, rd=0;
	if (bt != NULL)
	{
		rd=CountIf(bt->rchild);
		ld = CountIf(bt->lchild);
		if (rd > ld)
		{
			return rd+1;
		}
		else
		{
			return ld+1;
		}
	}
	else
	{
		return 0;
	}
}
//�˵�
void menu()
{
	ElemType e,c;
	int select,i;
	FILE *fp;
	do
	{
		system("cls");//����
		printf("\t***********************************\n");
		printf("\t*1.���ļ��ж���������������       *\n");
		printf("\t*2.�������������                 *\n");
		printf("\t*3.�������������                 *\n");
		printf("\t*4.�������������                 *\n");
		printf("\t*5.������������ܽ������Ҷ����� *\n");
		printf("\t*6.ɾ����������ָ�����           *\n");
		printf("\t*7.�ڶ�����ָ����㴦������     *\n");
		printf("\t*8.��������������               *\n");
		printf("\t*0.�˳�                           *\n");
		printf("\t***********************************\n");
		printf("\t������ٺʹ��룺");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			fp = fopen("Data\\BiTree.txt", "r");
			if (fp == NULL)
			{
				printf("\t�ļ���ʧ��!\b");
				return;
			}
			T = Creat(fp);
			fclose(fp);
			system("pause");
			break;
		case 2:
			printf("\t���������");
			PreOrder(T);
			printf("\n");
			system("pause");
			break;
		case 3:
			printf("\t���������");
			InOrder(T);
			printf("\n");
			system("pause");
			break;
		case 4:
			printf("\t���������");
			PostOrder(T);
			printf("\n");
			system("pause");
			break;
		case 5:
			Count(T);
			printf("\t�������Ľ�����ǣ�%d\n", length);
			printf("\t��������Ҷ������ǣ�%d\n", leaf);
			system("pause");
			break;
		case 6:
			printf("\t������Ҫɾ���Ľ���ֵ��");
			fflush(stdin);
			e = getchar();
			i=DeleteNode(T, e);
			if (i > 0)
			{
				printf("\t���������");
				printf("\n");
			}
			else
			{
				printf("\t���������");
				PreOrder(T);
				printf("\n");
			}
			system("pause");
			break;
		case 7:
			printf("\t������Ҫ����Ľ���ֵ��");
			fflush(stdin);
			e = getchar();
			printf("\t������Ҫ�����ֵ:");
			fflush(stdin);
			c = getchar();
			inisort(T,e,c);
			printf("\t���������");
			PreOrder(T);
			printf("\n");
			system("pause");
			break;
		case 8:
			i=CountIf(T);
			printf("\t������������ǣ�%d\n",i );
			system("pause");
			break;
		case 0:
			//�˳�
			printf("\t�����Ƿ�ȷ��Ҫ�˳�����(Y/N)");
			//�����û������ѡ��ִ���Ƿ�Ҫ�˳��Ĺ���
			exit(0);
			break;
		}
	} while (select<0 || select>4);
}
int main()
{

	//�ļ�ָ��
	while (1)
	{
		menu();
	}

}

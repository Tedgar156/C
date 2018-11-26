#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 5  //�ռ������
typedef struct
{
	int year;
	int month;
	int day;
}Data;
typedef struct
{
	int id; //ͼ����
	char name[20];//ͼ����
	int price;//�۸�
	Data pubData;//��������
}Book;

typedef Book ElemType;
typedef struct
{
	ElemType *elem;//�׵�ַ
	int length;//Ԫ�ظ���
	int listSize;//����
}sqList;
//��ʼ���߱�L,����Ϊsize,�ɹ�����1,ʧ�ܷ���0
int InitiList(sqList *L, int size)
{

	L->elem = (ElemType*)malloc(size*sizeof(ElemType));
	if (L->elem == NULL)return 0;
	L->listSize = size;
	L->length = 0;
	return 1;

}
//���ͼ�飬���ɹ��򷵻�1��ʧ���򷵻�0��
int add(sqList *opbook)
{
	int loc, i;
	ElemType *p;
	printf("\t****************************\n");
	printf("\t*     ����µ�ͼ��         *\n");
	printf("\t****************************\n");
	printf("\t���������ͼ���λ��:");
	scanf("%d", &loc);
	//�жϲ���λ���Ƿ���ȷ
	if (loc<1 || loc>opbook->length + 1)return 0;
	//�жϿռ��Ƿ���
	if (opbook->length >= opbook->listSize)
	{
		p = (ElemType*)realloc(opbook->elem, sizeof(ElemType)*(opbook->listSize + N));
		if (p == NULL)return 0;
		opbook->elem = p;
		opbook->listSize += N;
	}
	//����Ϣ�������������ƶ�
	for (i = opbook->length; i >= loc; i--)
	{
		opbook->elem[i] = opbook->elem[i - 1];
	}
	//���趨��λ�ý��д洢��Ϣ
	printf("\t������ͼ����:");
	scanf("%d", &opbook->elem[loc - 1].id);
	printf("\t������ͼ����:");
	scanf("%s", opbook->elem[loc - 1].name);
	printf("\t������ͼ��۸�:");
	scanf("%d", &opbook->elem[loc - 1].price);
	printf("\t�������������(��/��/��):");
	scanf("%d/%d/%d", &opbook->elem[loc - 1].pubData.year, &opbook->elem[loc - 1].pubData.month, &opbook->elem[loc - 1].pubData.day);
	opbook->length++;
	return 1;
}
//ɾ����Ϣ�ɹ�����1ʧ�ܷ���0
int dele(sqList *book)
{
	int elect,i;
	printf("\t****************************\n");
	printf("\t*      ɾ��ͼ��            *\n");
	printf("\t****************************\n");
	printf("��������Ҫɾ����λ��:");
	scanf("%d", &elect);//ȷ��ɾ����λ���Ƿ���ȷ
	if (elect<1 || elect>book->length)return 0;
	for (i = elect; i < book->length; i++)//��λ�ôӺ���ǰ�ƶ�
	{
		book->elem[i - 1] = book->elem[i];
	}
	book->length--;
	return 1;
}
//��ʾȫ����Ϣ
void display(sqList *book)
{
	int i;
	printf("ͼ����\tͼ����\tͼ��۸�\t��������:��\t��\t��\n");
	for (i = 0; i < book->length; i++)
	{
		printf("%d\t\t%s\t%d\t\t\t%d\t%d\t%d\n", book->elem[i].id, book->elem[i].name,
			book->elem[i].price, book->elem[i].pubData.year, book->elem[i].pubData.month, book->elem[i].pubData.day);
	}
}
//����(����ָ��ͼ����Ϣ)���ҵ��˷���1ʧ�ܷ���0
int LocateList(sqList *book)
{
	char name_1[20];
	int i;
	printf("\t****************************\n");
	printf("\t*      ����ͼ��            *\n");
	printf("\t****************************\n");
	printf("����������:");
	scanf("%s", name_1);
	for (i = 0; i < book->length; i++){
		if (strcmp(name_1, book->elem[i].name) == 0)
		{
			printf("ͼ����\tͼ����\tͼ��۸�\t��������:��\t��\t��\n");
			printf("%d\t\t%s\t%d\t\t\t%d\t%d\t%d\n", book->elem[i].id, book->elem[i].name,
				book->elem[i].price, book->elem[i].pubData.year, book->elem[i].pubData.month, book->elem[i].pubData.day);
			getchar();
			getchar();
			return 1;
		}
	}
	return 0;
}
//�˵�
void menu(sqList *pbook)
{
	//pbook->elem[i].pubData.day

	int select,result;
	char a,choice;
	do
	{
		system("cls");//����
		printf("\t****************************\n");
		printf("\t*1.����µ�ͼ��            *\n");
		printf("\t*2.ɾ��ָ��ͼ��            *\n");
		printf("\t*3.����ָ��ͼ��(����)      *\n");
		printf("\t*4.��ʾ���е�ͼ��          *\n");
		printf("\t*0.�˳�                    *\n");
		printf("\t****************************\n");
		printf("\t������ٺʹ��룺");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			//����һ��Ԫ����ָ��λ��
			result = add(pbook);
			system("cls");
			if (result == 1)
				printf("\t�洢��Ϣ�ɹ�!");
			else
				printf("\t�洢��Ϣʧ��!");
			system("pause");
			break;
		case 2:
			//ɾ��ָ��λ�õ�Ԫ�ط���
			result = dele(pbook);
			system("cls");
			if (result == 1)
				printf("\tɾ����Ϣ�ɹ�!");
			else
				printf("\tɾ����Ϣʧ��!");
			system("pause");
			break;
		case 3:
			//����ָ��Ԫ�ص�λ��
			result = LocateList(pbook);
			system("cls");
			if (result == 1)
				printf("\t������Ϣ�ɹ�!");
			else
				printf("\t������Ϣʧ��!");
			system("pause");
			break;
		case 4:
			//��ʾ���е�Ԫ��
			display(pbook);
			system("pause");
			break;
		case 0:
			//�˳�
			printf("\t�����Ƿ�ȷ��Ҫ�˳�����(Y/N)");
			//�����û������ѡ��ִ���Ƿ�Ҫ�˳��Ĺ���
			scanf("%c", &a);
			scanf("%c", &choice);
			if (choice == 'Y' || choice == 'y'){
				exit(0);
			}
			break;
		}
	} while (select<0 || select>4);
}
int main()
{
	sqList books;
	InitiList(&books, 100);
	while (1)
	{
		menu(&books);
	}

}
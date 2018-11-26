#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#define MAX 100
#define MAX_1 2147483647
struct book//�����û�Ԥ���ķɻ�
{
	char fly[5];//Ԥ�������
	struct book *next;
};
struct iddata
{
	char NO[20];//�û���
	char secret[20];//�û�����
	int booknum;//�����Ѿ�Ԥ���˼���
	int waitnum;//����ȴ���
	struct book bookfly;
	struct book waitfly;
};
typedef struct User
{
	struct iddata IdData;
	struct User *next;
}User;//�û���Ϣ
typedef struct ArcNode//����ͼ
{
	int adjvex;//�洢�������
	char fly[5];//���溽���
	char endplace[10];//�յ�ط�
	int money;//����Ȩ
	struct ArcNode *nextArc;
}ArcNode;
typedef struct VNode
{
	char starplace[10];//ͷ�����Ϣ
	ArcNode* firstnext;
}VNode;
typedef struct ALGraph
{
	int n;//ͷ������
	VNode map[MAX];
}ALGraph;
typedef struct Roud
{
	struct Roud *next;//·������
	char flyno[5];//�ɻ������
	char startplace[10];//������
	char endplace[10];//�յ�
}Roud;
struct usernum//���溽���е��û�
{
	char NO[20];//�����Ѷ��˵�����
	struct usernum *next;
};
struct flydata//������Ϣ
{	
	int waitnum;//�鿴�洢�ȴ��˵ĸ���
	int booknum;//�鿴����Ԥ���˵ĸ���
	char flyno[10];//�����
	char startplace[20];//��ɵص�
	char endplace[20];//����ص�
	int num;//���Գ���������
	int money;//����
	struct usernum BookUserNum;//Ԥ���û�
	struct usernum WaitUserNum;//�Ŷӵȴ��û�
};
typedef struct fly
{
	struct flydata FlyData;
	struct fly *next;
}Fly;//������Ϣ
User *user = (User*)malloc(sizeof(User));//�����û��ͺ����ͷָ��
User *admini = (User*)malloc(sizeof(User));
Fly *fly=(Fly*)malloc(sizeof(Fly));
ALGraph pg;
int num()
{
	system("cls");
	int choice;
	printf("*******************************\n");
	printf("*    1.�鿴����               *\n");
	printf("*    2.��Ʊ                   *\n");
	printf("*    3.��Ʊ                   *\n");
	printf("*    4.�鿴������Ϣ           *\n");
	printf("*    5.��¼                   *\n");
	printf("*    6.ע��                   *\n");
	printf("*    7.���ȫ������           *\n");
	printf("*    8.�˳�                   *\n");
	printf("*******************************\n");
	printf("��ѡ��:");
	scanf("%d",&choice);
	return choice;
}
void Init()//��ͷָ���ʼ��
{
	user->next = NULL;
	admini->next = NULL;
	fly->next = NULL;
	user->IdData.bookfly.next = NULL;
	user->IdData.booknum = 0;
	admini->IdData.bookfly.next = NULL;
	admini->IdData.booknum = 0;
	user->IdData.waitfly.next = NULL;
	user->IdData.waitnum = 0;
	admini->IdData.waitfly.next = NULL;
	admini->IdData.waitnum = 0;
	fly->FlyData.BookUserNum.next = NULL;
	fly->FlyData.booknum = 0;
	fly->FlyData.WaitUserNum.next = NULL;
	fly->FlyData.waitnum = 0;
	pg.n = 0;
}
int loaddata()//�����ļ��Ķ��� �ɹ�����1 ʧ��0 
{
	FILE *fp,*stream;
	User *p;
	char name[20];
	if ((fp = fopen("admini.txt", "r")) != NULL) 
	{
		User *ad = admini;//���ع�������Ϣ
		struct book *b,*uf1;
		while (!feof(fp))
		{
			p = (User*)malloc(sizeof(User));
			if (p == NULL) return 0;
			fread(&p->IdData, sizeof(struct iddata), 1, fp);
			p->IdData.waitfly.next = NULL;
			p->IdData.bookfly.next = NULL;
			p->next = NULL;
			if (strlen(p->IdData.NO)<20){
				ad->next = p;
				ad = p;
			}
			else{ free(p); continue; }
			if (ad->IdData.booknum > 0||ad->IdData.waitnum>0)//����Ԥ���û�����Ϣ
			{
				struct book *h;
				sprintf(name, "%s.txt", ad->IdData.NO);
				if ((stream = fopen(name, "r")) != NULL){
					h = &ad->IdData.bookfly;//����Ԥ����Ϣ
					for (int i = 0; i < ad->IdData.booknum; i++){
						b = (struct book*)malloc(sizeof(struct book));
						fread(&b->fly,sizeof(b->fly),1,stream);
						//fgets(b->fly, sizeof(b->fly), stream);
						//fscanf(stream, "%s", b->fly);
						b->next = NULL;
						h->next = b;
						h = b;
					}
					h = &ad->IdData.waitfly;//���صȶ���Ϣ
					for (int i = 0; i < ad->IdData.waitnum; i++){
						b = (struct book*)malloc(sizeof(struct book));
						fread(&b->fly,sizeof(b->fly),1,stream);
						//fgets(b->fly, 5, stream);
						//fscanf(stream,"%s",b->fly);
						b->next = NULL;
						h->next = b;
						h = b;
					}
				}
				fclose(stream);
			}
		}
		fclose(fp);
	}
	if ((fp = fopen("user.txt", "r")) != NULL){
		User *us = user;
		struct book *b;
		while (!feof(fp))//�����û���Ϣ
		{
			p = (User*)malloc(sizeof(User));
			if (p == NULL)return 0;
			fread(&p->IdData, sizeof(struct iddata), 1, fp);
			p->IdData.bookfly.next = NULL;
			p->IdData.waitfly.next = NULL;
			p->next = NULL;
			if (strlen(p->IdData.NO)<20){
				us->next = p;
				us = p;
			}
			else{
				free(p); continue;
			}
			if (us->IdData.booknum > 0 || us->IdData.waitnum > 0)//����Ԥ���û�����Ϣ
			{
				struct book *h;
				sprintf(name, "%s.txt", us->IdData.NO);
				if ((stream = fopen(name, "r")) != NULL){
					h = &us->IdData.bookfly;//����Ԥ����Ϣ
					for (int i = 0; i < us->IdData.booknum; i++){
						b = (struct book*)malloc(sizeof(struct book));
						fread(&b->fly,sizeof(b->fly),1,stream);
						//fgets(b->fly, sizeof(b->fly), stream);
						//fscanf(stream, "%s", b->fly);
						b->next = NULL;
						h->next = b;
						h = b;
					}
					h = &us->IdData.waitfly;//����Ԥ����Ϣ
					for (int i = 0; i < us->IdData.waitnum; i++){
						b = (struct book*)malloc(sizeof(struct book));
						fread(&b->fly,sizeof(b->fly),1,stream); 
						//fgets(b->fly, sizeof(b->fly), stream);
						//fscanf(stream, "%s", b->fly);
						b->next = NULL;
						h->next = b;
						h = b;
					}
				}
				fclose(stream);
			}
		}
		fclose(fp);
	}
	if ((fp = fopen("fly.txt", "r")) != NULL){
		Fly *fl = fly, *q;
		struct usernum *u;
		while (!feof(fp))//���غ�����Ϣ
		{
			q = (Fly*)malloc(sizeof(Fly));
			if (q == NULL)return 0;
			fread(&q->FlyData, sizeof(struct flydata), 1, fp);
			q->FlyData.BookUserNum.next = NULL;
			q->FlyData.WaitUserNum.next = NULL;
			q->next = NULL;
			if (strlen(q->FlyData.startplace) < 10)
			{
				fl->next = q;
				fl = q;
			}
			else{
				free(q); continue;
			}
			if (q->FlyData.booknum>0 || q->FlyData.waitnum > 0)
			{
				struct usernum *usn;
				sprintf(name, "%s.txt", q->FlyData.flyno);
				if ((stream = fopen(name, "rb")) == NULL) return 0;
				usn = &q->FlyData.BookUserNum;
				for (int i = 0; i < q->FlyData.booknum; i++)
				{
					u = (struct usernum*)malloc(sizeof(struct usernum));
					fread(&u->NO, sizeof(u->NO), 1, stream);
					//fgets(u->NO,7 ,stream);
					//fscanf(stream, "%s", u->NO);
					u->next = NULL;
					if (strlen(u->NO) < 10)
					{
						usn->next = u;
						usn = u;
					}
					else{
						free(u);
					}
				}
				usn = &q->FlyData.WaitUserNum;
				for (int i = 0; i < q->FlyData.waitnum; i++)
				{
					u = (struct usernum*)malloc(sizeof(struct usernum));
					fread(&u->NO, sizeof(u->NO), 1, stream);
					//fgets(u->NO, sizeof(u->NO), stream);
					//fscanf(stream, "%s", u->NO);
					u->next = NULL;
					if (strlen(u->NO) < 10)
					{
						usn->next = u;
						usn = u;
					}
					else{
						free(u);
					}
				}
				fclose(stream);
			}
		}
		fclose(fp);
	}
	return 1;
}
void saveflyuser(Fly *p)
{
	struct usernum *u;
	int i;
	FILE *fp;
	char file[20];
	u=p->FlyData.BookUserNum.next;
	sprintf(file, "%s.txt", p->FlyData.flyno);
	if ((fp = fopen(file, "w")) != NULL){
		for (i = 0; i < p->FlyData.booknum; i++)
		{
			fwrite(&u->NO, sizeof(u->NO), 1, fp);
			u = u->next;
		}
		u = p->FlyData.WaitUserNum.next;
		for (i = 0; i < p->FlyData.waitnum; i++)
		{
			fwrite(&u->NO, sizeof(u->NO), 1, fp);
			u = u->next;
		}
		fclose(fp);
	}
}
void saveuserfly(User *p)
{
	struct book *b;
	FILE *fp;
	char file[20];
	int i;
	b = p->IdData.bookfly.next;
	sprintf(file, "%s.txt", p->IdData.NO);
	if ((fp = fopen(file, "w")) != NULL)
	{
		for (i = 0; i < p->IdData.booknum; i++)
		{
			fwrite(&b->fly, sizeof(b->fly), 1, fp);
			b = b->next;
		}
		b = p->IdData.waitfly.next;
		for (i = 0; i < p->IdData.waitnum; i++)
		{
			fwrite(&b->fly, sizeof(b->fly), 1, fp);
			b = b->next;
		}
		fclose(fp);
	}
}
int savedatauser(char function[],int i)
{
	FILE *fp,*stream;
	User *us;
	char name[20];
	if (i == 1)
	{
		us = user->next;
		if ((fp = fopen("user.txt", function)) == NULL)
		{
			return 0;
		}
	}
	else if (i==2)
	{
		us = admini->next;
		if ((fp = fopen("admini.txt", function)) == NULL)
		{
			return 0;
		}
	}
	while (us != NULL)
	{
		fflush(fp);
		fwrite(&us->IdData, sizeof(struct iddata), 1, fp);
		us = us->next;
	}
	fclose(fp);
	return 1;
}
int savedatafly(char function[])
{
	FILE *fp;
	Fly *fl;
	char name[20];
	fl = fly->next;
	if ((fp = fopen("fly.txt", function)) == NULL)
	{
		printf("���溽����Ϣʱ�����ļ�ʧ��!\n");
		return 0;
	}
	while (fl != NULL)
	{
		fflush(fp);
		fwrite(&fl->FlyData, sizeof(struct flydata), 1, fp);//���º�����Ϣ
		fl = fl->next;
	}
	fclose(fp);
	return 1;
}
int addfly()//��ӷɻ���Ϣ
{
	char a = 'n';
	Fly *fl,*p=fly,*q=fly;
	do{
		p = fly;
		fl = (Fly*)malloc(sizeof(Fly));
		if (fl == NULL)return 0;
		do{
			printf("�����뺽���(�벻Ҫ�ظ�):");//������Ϣ
			fflush(stdin);
			scanf("%s", fl->FlyData.flyno);
			while (p != NULL)
			{
				if (strcmp(fl->FlyData.flyno, p->FlyData.flyno) == 0)//�жϺ�����Ƿ��ظ�
				{
					break;
				}
				p = p->next;
			}
		} while (p != NULL);
		printf("��������ɵص�:");
		fflush(stdin);
		scanf("%s", fl->FlyData.startplace);
		printf("�����뵽��ص�:");
		fflush(stdin);
		scanf("%s", fl->FlyData.endplace);
		printf("�������������:");
		scanf("%d", &fl->FlyData.num);
		printf("�����뵥��:");
		fflush(stdin);
		scanf("%d", &fl->FlyData.money);
		fl->next = NULL;
		fl->FlyData.booknum = 0;
		fl->FlyData.BookUserNum.next = NULL;
		fl->FlyData.WaitUserNum.next = NULL;
		fl->FlyData.waitnum = 0;
		q->next = fl;
		q = fl;
		printf("�Ƿ�����洢������Ϣ(y/n):");
		fflush(stdin);
		a = getchar();
	} while (a == 'y' || a == 'Y');
	return savedatafly("a+");
}
void Creat()//����ͷ�ڵ�
{
	Fly *p =fly->next;
	int k = 0,j=0;
	while (p != NULL)
	{
		k = 0;	j = 0;//kΪ�����㣬jΪ�յ�
		for (int i = 0; i < pg.n; i++)//�жϽڵ��Ƿ��ظ�
		{
			if (strcmp(p->FlyData.startplace, pg.map[i].starplace) == 0)
			{
				k++;
			}
		}
		if (k == 0&&strlen(p->FlyData.startplace)<10)
		{
			strcpy(pg.map[pg.n].starplace, p->FlyData.startplace);
			pg.map[pg.n].firstnext = NULL;pg.n++;
		}
		for (int i = 0; i < pg.n; i++)
		{
			if (strcmp(p->FlyData.endplace, pg.map[i].starplace) == 0)
			{
				j++;
			}
		}
		if (j == 0&&strlen(p->FlyData.endplace)<10)
			{	
				strcpy(pg.map[pg.n].starplace, p->FlyData.endplace);
				pg.map[pg.n].firstnext = NULL;pg.n++; 
			}
		p = p->next;
	}
}
void CreateTi()//�����ڽӱ�
{
	int i = 0,j=0;
	Fly *q = fly->next;
	Creat();//����ͷ�ڵ�
	while (q != NULL)
	{
		for (i = 0; i < pg.n; i++)//�ҵ���Ӧ�����к�
		{
			if (strcmp(pg.map[i].starplace, q->FlyData.startplace) == 0)
			{
				break;
			}
		}
		for (j = 0; j < pg.n; j++)
		{
			if (strcmp(pg.map[j].starplace, q->FlyData.endplace) == 0)
			{
				break;
			}
		}
		ArcNode *p;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		if (p == NULL){ return; }
		if (strlen(q->FlyData.flyno)<10)
		strcpy(p->fly, q->FlyData.flyno);//���溽���
		p->money = q->FlyData.money;//Ȩ�ĸ�ֵ
		p->adjvex = j;//��һ���������
		if (strlen(q->FlyData.endplace)<10)
		strcpy(p->endplace, q->FlyData.endplace);
		p->nextArc = pg.map[i].firstnext;//�����ڶ�Ӧ���������
		pg.map[i].firstnext = p;
		q = q->next;
	}
}
void findfly(Roud *roud)//����·���ҵ�����
{
	Fly *p = fly->next;
	while (p != NULL)
	{
		if ((strcmp(roud->startplace, p->FlyData.startplace) == 0) && (strcmp(roud->endplace, p->FlyData.endplace) == 0))
		{
			strcpy(roud->flyno, p->FlyData.flyno);
		}
		p = p->next;
	}
}
void displayfly(Fly *p, int i)
{
	printf("�ҵ��ú����%s\n", p->FlyData.flyno);
	printf("��ɵص�:%s\n", p->FlyData.startplace);
	printf("����ص�:%s\n", p->FlyData.endplace);
	printf("��Ʊ:%d��\n", p->FlyData.num - p->FlyData.booknum);
	printf("����:%dԪ\n", p->FlyData.money);
	if (i == 2)
	{
		struct usernum *l = p->FlyData.BookUserNum.next;
		flydata *b=&p->FlyData;
		printf("��Ԥ���û�:\n");
		while (l != NULL&&b->booknum != 0)
		{
			printf("%s\n", l->NO);
			l = l->next;
		}
		l = p->FlyData.WaitUserNum.next;
		printf("���ڵȴ����û�\n");
		while (l != NULL&&b->waitnum != 0)
		{
			printf("%s\n", l->NO);
			l = l->next;
		}
	}
}
Fly* findno(char n[])//���ݺ���Ų���
{
	Fly *p = fly->next;
	while (p != NULL)
	{
		if (strcmp(n, p->FlyData.flyno) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}
void DBS(int V0, int path[],int b[])//iΪͷ�ڵ��������
{
	int a[MAX],i,j,k,min;
	ArcNode *p;
	for (i = 0; i < pg.n; i++)//��ʼ������
	{
		a[i] = 0;
		b[i] = MAX_1;
		path[i] = V0;
	}
		p = pg.map[V0].firstnext;
		while (p != NULL)
		{
			i = p->adjvex;
			b[i] = p->money;
			if (b[i] < MAX_1)
				path[i] = V0;
			else 
				path[i] = -1;
			p = p->nextArc;
		}
	a[V0] = 1;
	b[V0] = 0;
	/*
	a[]Ϊ�鿴�Ƿ��߹�
	b[]Ϊ·��
	*/
	for (i = 1; i < pg.n-1; i++)
	{
		min = MAX_1;
		for (k = 0; k < pg.n; k++)
		{
			if (min>b[k] && !a[k])//һ�ζ�û�д���ȥ
			{
				j = k;
				min = b[k];
			}
		}
		a[j] = 1;
		p = pg.map[j].firstnext;
		while (p != NULL)
		{
			if (b[j] + p->money < b[p->adjvex] && !a[p->adjvex])
			{
				b[p->adjvex] = b[j] + p->money;
				path[p->adjvex] = j;
			}
			p = p->nextArc;
		}
	}
}
Roud * FindTi(char start[], char end[],int *s)//�������վ���յ�վ��·�̴�������
{
	VNode *p;
	int i = 0, j, k=-20;
	int path[MAX], lowcost[MAX];
	Roud *q,*roud;
	roud = (Roud*)malloc(sizeof(Roud));
	if (roud == NULL){ return NULL; }
	for (i = 0; i < pg.n; i++)//�ҵ�����ͷ�ڵ�
	{
		p = &pg.map[i];
		if (strcmp(p->starplace, start) == 0)
		{
			j = i;//��ʼ���������
		}
		if (strcmp(p->starplace, end) == 0)
		{
			k = i;//�յ��������
		}
	}
	if (k >= pg.n || k < 0)
	{
		return NULL;
	}
	DBS(j,path,lowcost);
	roud->next = NULL;//��·��ת����roud
	if (lowcost[k] < MAX_1)//��·��
	{
		printf("��Ҫ%dԪ���ܵ���%s\n", lowcost[k], end);
		q = roud;
		strcpy(q->endplace, pg.map[k].starplace);//���յ���ĵ�
		i = path[k];
		while (i != j)
		{
			strcpy(q->startplace, pg.map[i].starplace);//�����㸳ֵ
			q = (Roud*)malloc(sizeof(Roud));
			if (q == NULL)return NULL;
			q->next = NULL;
			strcpy(q->endplace, pg.map[i].starplace);//���յ���ĵ�
			q->next = roud;
			roud = q;
			i = path[i];
		}
		strcpy(q->startplace, pg.map[j].starplace);//�����㸳ֵ
		q = roud;
		while (q != NULL)//��ֵ�����
		{
			findfly(q);
			q = q->next;
		}
	}
	q = roud;
	while (q != NULL)
	{
		Fly *f;
		f = findno(q->flyno);
		if (f != NULL)
		{
			displayfly(f, i);
			(*s)++;
		}
		q = q->next;
	}
	return roud;
}
void lookflyno(int i)
{
	Fly *p;
	int j;
	char n[10],a = 'n';
	do{
		printf("�����뺽���:");
		fflush(stdin);
		scanf("%s", n);
		p=findno(n);
		if (p!=NULL)
		{
			displayfly(p, i);
			return;
		}
		else//δ���ҵ��û�����ĺ���
		{
			j = MessageBox(0, L"δ���ҵ��ú���!�Ƿ��������?", L"����", MB_OKCANCEL);
			switch (j)
			{
			case IDOK:a = 'y'; break;
			case IDCANCEL:return;
				break;
			}
		}
	} while (a == 'y');
}
void lookflytime(int i)
{
	Fly *p,q;
	int j,k=0;
	char a = 'n',b='n',c='n';
	do{
		k = 0;
		a = 'n';
		printf("��������ɵص�:");
		fflush(stdin);
		scanf("%s", q.FlyData.startplace);
		printf("�Ƿ���������յ�վ(y/n)?");
		fflush(stdin);
		b = getchar();
		if (b != 'n'&&b!='N')
		{
			printf("�������յ�վ:");
			fflush(stdin);
			scanf("%s", q.FlyData.endplace);
		}
		p = fly->next;
		while (p != NULL)
		{
			if ((strcmp(q.FlyData.startplace, p->FlyData.startplace) == 0)&&b=='n'&&c=='n')//ֻ������ɵص�
			{
				displayfly(p,i);
				k++;
			}
			p = p->next;
		}
		if (b != 'n'&&c == 'n')//����ת��·��
		{
			FindTi(q.FlyData.startplace, q.FlyData.endplace,&k);
		}
		if (k==0)//δ���ҵ��û�����ĺ���
		{
			j = MessageBox(0, L"δ���ҵ��ú���!�Ƿ��������?", L"����", MB_OKCANCEL);
			switch (j)
			{
			case IDOK:a = 'y'; break;
			case IDCANCEL:return;
			}
		}
	} while (a == 'y');
}
void lookfly(int i)
{
	
	int choice;
	while (1)
	{
		system("cls");
		printf("***********************************\n");
		printf("*     1.������Ų���              *\n");
		printf("*     2.���ص����                *\n");
		printf("*     3.�˳�                      *\n");
		printf("***********************************\n");
		printf("��ѡ��:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:lookflyno(i);
			break;
		case 2:lookflytime(i);
			break;
		case 3:return;
		default:
			break;
		}
		system("pause");
	}
}
User *finduser(char no[],int *i)//�ҵ������ҵ��Ǹ�ָ��δ�ҵ�����NULL
{
	User *p = user,*q=admini;
	while (q != NULL)
	{
		if (strcmp(q->IdData.NO, no) == 0)
		{
			*i = 2;
			return q;
		}
		q = q->next;
	}
	while (p != NULL)
	{
		if (strcmp(p->IdData.NO, no) == 0)
		{
			*i = 1;
			return p;
		}
		p = p->next;
	}
	return NULL;
}
void Register(int *j,char name[])//��¼
{
	User a,*p;
	int i,k=0;
	char m = 'n';
	printf("�������û���:");
	fflush(stdin);
	scanf("%s", a.IdData.NO);
	p = finduser(a.IdData.NO,&k);
	if (p != NULL)
	{
		do{
			m = 'n';
			printf("����������:");
			fflush(stdin);
			scanf("%s", a.IdData.secret);
			if (strcmp(p->IdData.secret, a.IdData.secret) == 0)
			{
				strcpy(name,a.IdData.NO);
				MessageBox(0, L"��¼�ɹ�!", L"�ɹ�", MB_OK);
				if (k == 2)
					*j = 2;
				else if (k == 1)
					*j = 1;
				return;
			}
			else
			{
				i = MessageBox(0, L"��¼ʧ��!�Ƿ������¼?", L"ʧ��", MB_OKCANCEL);
				switch (i)
				{
				case IDOK:m = 'y';
					break;
				case IDCANCEL:return;
					break;
				}
			}
		} while (m == 'y');
	}
	else
	{
		MessageBox(0, L"δ�ҵ����û�!���ȴ������û�", L"����", MB_OK);
		return;
	}
}
void Create()//ֻ��һ������Ա
{
	FILE *fp;
	User *a,*p,*q;
	a = (User*)malloc(sizeof(User));
	int i;
	char s;
	if ((fp = fopen("admini.txt", "r")) == NULL)
	{
		p = admini;q = admini->next;
		while (q!=NULL)
		{
			p = p->next; q = q->next;
		}
		printf("�������û���:");
		fflush(stdin);
		scanf("%s", a->IdData.NO);
		do
		{
			printf("����������(������λ��С��ʮ��λ):");
			fflush(stdin);
			scanf("%s", a->IdData.secret);
		} while (strlen(a->IdData.secret)<6||strlen(a->IdData.secret)>16);
		a->IdData.bookfly.next = NULL;
		a->IdData.booknum = 0;
		a->IdData.waitfly.next = NULL;
		a->IdData.waitnum = 0;
		a->next = NULL;
		p->next = a;
		fp = fopen("admini.txt", "w");
		fwrite(&a->IdData, sizeof(struct iddata), 1, fp);
		fclose(fp);
		MessageBox(0, L"�����ɹ�!", L"�ɹ�", MB_OK);
		return;
	}
	else
	{
		do{
			s = 'n';
			if ((fp = fopen("user.txt", "a")) == NULL)return;
			printf("�������û���:");
			fflush(stdin);
			scanf("%s", a->IdData.NO);
			p = finduser(a->IdData.NO,&i);
			if (p == NULL)
			{
				do{
					printf("����������(������λ��С��ʮ��λ��):");
					fflush(stdin);
					scanf("%s", a->IdData.secret);
				} while (strlen(a->IdData.secret)<6 || strlen(a->IdData.secret)>16);
				p = user; q = user->next;
				while (q != NULL)
				{
					p = p->next;
					q = q->next;
				}
				a->IdData.bookfly.next = NULL;
				a->IdData.booknum = 0;
				a->IdData.waitfly.next = NULL;
				a->IdData.waitnum = 0;
				a->next = NULL;
				p->next = a;
				fwrite(&a->IdData, sizeof(struct iddata), 1, fp);
				fclose(fp);
				MessageBox(0, L"�����ɹ�!", L"�ɹ�", MB_OK);
				return;
			}
			else
			{
				i = MessageBox(0, L"�û����ظ�!�Ƿ��������?", L"����", MB_OKCANCEL);
				switch (i)
				{	
				case IDOK:s = 'y';
					break;
				case IDCANCEL:return;
					break;
				}
			}
		} while (s=='y');
	}
}
void display(int j)
{
	Fly *p = fly->next;
	printf("-------------���к���--------------\n");
	while (p != NULL)
	{
		displayfly(p, j);
		p = p->next;
	}
	VNode *a;//��ͼ��ʾ����
	ArcNode *q;
	int i=0;
	printf("-----------�ڽӱ�--------------\n");
	for (i = 0; i < pg.n; i++)
	{
		a = &pg.map[i];
		printf("���ǵ�%d������:%s\n", i + 1,a->starplace);
		q = a->firstnext;
		while (q != NULL)
		{
			printf("��һ������Ϊ%d,�յ�վ%s,�����:%s,���ۣ�%d\n", q->adjvex,q->endplace, q->fly, q->money);
			q = q->nextArc;
		}
	}
}
void bookticket(int i,char name[])//��Ʊ
{
	if (i == 1 || i == 2)
	{
		char a, b, start[20], end[20], file[20];
		int num,j,k=0,h=i;
		FILE *fp;
		Roud *r;
		Roud *rou;
		User *u;
		Fly *f;
		system("cls");
		printf("**************************************\n");
		printf("*              ��Ʊ                  *\n");
		printf("**************************************\n");
		printf("��������ɵص�:");
		fflush(stdin);
		scanf("%s", start);
		printf("�������յ�վ:");
		fflush(stdin);
		scanf("%s", end);
		r=FindTi(start,end,&k);
		if (k != 0)//��·��
		{
			printf("�Ƿ�Ʊ(y/n)?");
			fflush(stdin);
			a = getchar();
			if (a == 'y' || a == 'Y')
			{
				printf("�����빺Ʊ����:");
				scanf("%d", &num);
				rou = r;
				while (rou != NULL)
				{
					f = findno(rou->flyno);
					if ((f->FlyData.num - f->FlyData.booknum) < num)
					{
						system("cls");
						displayfly(f,0);
						printf("�ú�����Ʊ����!�Ƿ��Ŷӵȴ�(y/n)?");
						fflush(stdin);
						b = getchar();
						if (b != 'y' && b != 'Y')
						{
							return;
						}
					}
					rou = rou->next;
				}
				while (r != NULL)
				{
					f = findno(r->flyno);//pΪ����
					u = finduser(name, &h);//uΪ�û�
					for (j = 0; j < num; j++)
					{
						if (f->FlyData.booknum < f->FlyData.num)//��Ԥ������С������������ӵ��û��ͺ�����
						{
							struct usernum *us, *fu1 = &f->FlyData.BookUserNum, *fu2 = f->FlyData.BookUserNum.next;//������Ԥ�����û�
							struct book *boo, *b1 = &u->IdData.bookfly, *b2 = u->IdData.bookfly.next;//�û���Ԥ���ĺ���
							while (fu2 != NULL)//�ҵ�δ���
							{
								fu1 = fu1->next;//
								fu2 = fu2->next;
							}
							while (b2 != NULL)
							{
								b1 = b1->next;//
								b2 = b2->next;
							}
							us = (struct usernum*)malloc(sizeof(struct usernum));//�û���ӵ�������
							strcpy(us->NO, name);
							us->next = NULL;
							fu1->next = us;
							f->FlyData.booknum++;
							sprintf(file, "%s.txt", f->FlyData.flyno);
							if ((fp = fopen(file, "ab")) == NULL) return;//д���û�
							fflush(fp);
							//fprintf(fp,"%s",us->NO);
							fwrite(&us->NO,sizeof(us->NO),1,fp);
							//fputs(us->NO,fp);
							fclose(fp);
							boo = (struct book*)malloc(sizeof(struct book));//д�뺽�ൽ�û���
							strcpy(boo->fly, f->FlyData.flyno);
							boo->next = NULL;
							b1->next = boo;
							u->IdData.booknum++;
							saveuserfly(u);
						}
						else//��Ԥ���������ڻ���������������Ŷ���
						{
							struct usernum *us, *fu1 = &f->FlyData.WaitUserNum, *fu2 = f->FlyData.WaitUserNum.next;
							struct book *boo, *b1 = &u->IdData.waitfly, *b2 = u->IdData.waitfly.next;
							while (fu2 != NULL)//�ҵ�δ���
							{
								fu1 = fu1->next;//
								fu2 = fu2->next;
							}
							while (b2 != NULL)
							{
								b1 = b1->next;//
								b2 = b2->next;
							}
							us = (struct usernum*)malloc(sizeof(struct usernum));//�û���ӵ��ȴ�������
							strcpy(us->NO, name);
							us->next = NULL;
							fu1->next = us;
							f->FlyData.waitnum++;
							sprintf(file, "%s.txt",f->FlyData.flyno );
							if ((fp=fopen(file, "ab")) == NULL) return;//д��ȴ����û�����
							fflush(fp);
							//fprintf(fp,"%s",us->NO);
							fwrite(&us->NO,sizeof(us->NO),1,fp);
							//fputs(us->NO, fp);
							fclose(fp);
							boo = (struct book*)malloc(sizeof(struct book));//������ӵ��ȴ��û���
							strcpy(boo->fly, f->FlyData.flyno);
							boo->next = NULL;
							b1->next = boo;
							u->IdData.waitnum++;
							saveuserfly(u);
						}
					}
					r = r->next;
				}
				savedatafly("w");
				savedatauser("w",h);
			}
			else
			{
				return;
			}
		 }
		else
		{
				MessageBox(0, L"δ�ҵ��ú���", L"����", MB_OK);
		}
	}
	else 
	{
		MessageBox(0, L"���ȵ�¼", L"����", MB_OK);
		return;
	}
}
void returnticket(int i, char name[])//��Ʊ
{
	if (1 == i || 2 == i)
	{
		int j=i;
		char s,f[10],file[20];
		struct book *b,*bo,*bo1,*bo2;
		struct usernum *u,*us,*usn1,*usn2;
		User *q;
		Fly *p;
		FILE *fp;
		system("cls");
		printf("**************************************\n");
		printf("*              ��Ʊ                  *\n");
		printf("**************************************\n");
		printf("�������ĺ�������:\n");
		q = finduser(name, &j);//qΪ��Ʊ�û�
		b = q->IdData.bookfly.next;//bΪ��Ʊ�û����Ѷ��˺���
		while (b != NULL)//�������Ѷ��ĺ���չʾ����
		{
			p=findno(b->fly);
			displayfly(p, 1);
			printf("------------------\n");
			b = b->next;
		}
		if (q->IdData.booknum < 1)return;//���û�ж�Ʊ�˳�
		printf("�Ƿ���Ʊ(y/n)��");
		fflush(stdin);
		s = getchar();
		if (s == 'y' || s == 'Y')
		{
			do{
				s = 'n';
				j = i;
				printf("��������Ҫ��Ʊ�ĺ����:");
				scanf("%s",f);
				q = finduser(name, &j);//qΪ��Ʊ�û�
				p = findno(f);//�ҵ���Ʊ�ĺ���
				if (p == NULL)//��û����Ʊ�ĺ���
				{
					j=MessageBox(0, L"�������!�Ƿ������Ʊ?", L"����", MB_OKCANCEL);
					switch (j)
					{
					case IDOK:s='y'; break;
					case IDCANCEL:return;
					}
				}
				else{
					u = p->FlyData.BookUserNum.next;//��Ʊ�����ж�Ʊ����
					us = &p->FlyData.BookUserNum;
					b = q->IdData.bookfly.next;//��Ʊ�û������ĺ���
					bo = &q->IdData.bookfly;
					while (u != NULL)
					{
						if (strcmp(u->NO, name) == 0)//�ҵ���Ʊ�������Ʊ��
						{
							break;
						}
						u = u->next;//�ҵ��ö�Ʊ�û��Ľ��
						us = us->next;//����ǰ���
					}
					if (u == NULL)//��δ�ҵ���Ʊ���ں�����
					{
						j = MessageBox(0, L"�������!�Ƿ������Ʊ?", L"����", MB_OKCANCEL);
						switch (j)
						{
						case IDOK:s = 'y'; break;
						case IDCANCEL:return;
						}
					}
					else{
						while (b != NULL)
						{
							if (strcmp(b->fly, p->FlyData.flyno) == 0)//�ҵ���Ʊ�˵���Ʊ����
							{
								break;
							}
							b = b->next;//�ҵ��ú���
							bo = bo->next;//����ǰ���
						}
						if (b == NULL)//��δ�ҵ���Ʊ�˵ĺ���
						{
							j = MessageBox(0, L"�������!�Ƿ������Ʊ?", L"����", MB_OKCANCEL);
							switch (j)
							{
							case IDOK:s = 'y'; break;
							case IDCANCEL:return;
							}
							break;
						}
						else{
							if (p->FlyData.waitnum > 0)//���ú��������˵ȴ�
							{
								usn1 = &p->FlyData.WaitUserNum;//��Ʊ������
								usn2 = p->FlyData.WaitUserNum.next;
								q->IdData.booknum--;//��Ʊ�û��Ķ�Ʊ����һ
								if (b->next != NULL)bo->next = b->next;
								else bo->next = NULL;//*����Ʊ�û��Ѷ��ĺ���ɾȥ*
								free(b);
								q = finduser(usn2->NO, &j);//���Ŷӵ��û��������Ѷ�Ʊ��
								q->IdData.booknum++;
								q->IdData.waitnum--;
								b = &q->IdData.bookfly;//�û��ж�Ʊ��һ
								bo = q->IdData.bookfly.next;
								while (bo != NULL)//�ҵ��Ѷ������α���
								{
									b = b->next;//
									bo = bo->next;
								}
								bo = (struct book*)malloc(sizeof(struct book));//��α������ȴ��������Ϣ
								strcpy(bo->fly, p->FlyData.flyno);
								bo->next = NULL;
								b->next = bo;//*���ȴ��û��ĵȴ�������뵽�Ѷ�������*
								b = &q->IdData.waitfly;
								bo = q->IdData.waitfly.next;
								while (bo != NULL)//�ҵ��ȴ��û��ĵȴ�����
								{
									if (strcmp(bo->fly, p->FlyData.flyno) == 0)
									{
										break;
									}
									b = b->next;
									bo = bo->next;
								}
								if (bo->next != NULL)
									b->next = bo->next;//*�ȴ��û��ȴ�����ɾȥ*
								else b->next = NULL;
								free(bo);
								strcpy(u->NO, usn2->NO);//*����������Ʊ�û��滻Ϊ�ȴ��û�*�ȴ��û��ȴ����࣬�Ѷ����࣬��Ʊ�������Ѷ��û�
								p->FlyData.waitnum--;
								if (usn2->next != NULL)//ɾȥ����Ʊ�����еȴ��û�
									usn1->next = usn2->next;
								else usn1->next = NULL;
								free(usn2);
								q = finduser(u->NO, &j);//�ȴ��û��ĺ���
								saveuserfly(q);//����ȴ��û��ĺ���
								q = finduser(name, &j);
							}
							else
							{
								if (u->next != NULL)//�ж��Ƿ�Ҫɾ���Ľ��Ϊ���һ�����
									us->next = u->next;
								else us->next = NULL;
								free(u);
								if (b->next != NULL)bo->next = b->next;
								else bo->next = NULL;//*����Ʊ�û��Ѷ��ĺ���ɾȥ*
								free(b);
								p->FlyData.booknum--;
								q->IdData.booknum--;
							}
							saveflyuser(p);//�ú����е��û�
							saveuserfly(q);//��Ʊ�û�����
							if (q->IdData.booknum < 1)
							{
								savedatafly("w");//���溽����Ϣ
								savedatauser("w", i);//�����û���Ϣ
								return; 
							}//���û�ж�Ʊ�˳�
							printf("�Ƿ������Ʊ(y/n):");
							fflush(stdin);
							s = getchar();
							savedatafly("w");//���溽����Ϣ
							savedatauser("w", i);//�����û���Ϣ
						}
					}
				}
			} while (s=='y'||s=='Y');
		}
		else
		{
			return;
		}
	}
	else
	{
		MessageBox(0, L"���ȵ�¼", L"����", MB_OK);
		return;
	}
}
void lookcity()
{
	FILE *fp;
	char city_1[20],city_2[20],c;
	printf("              ����          \n");
	printf("                            \n");
	printf("                        �Ϻ�\n");
	printf("                            \n");
	printf(" �ɶ�                       \n");
	printf("                      ����  \n");
	printf("                 ����       \n");
	printf("��������Ҫ���ҳ�����Ϣ�ĳ���:");
	fflush(stdin);
	scanf("%s", city_1);
	sprintf(city_2, "%s.txt", city_1);
	if ((fp = fopen(city_2, "r")) != NULL)
	{
		while (!feof(fp))
		{
			c = fgetc(fp);
			printf("%c", c);
		}
		printf("\n");
	}
	else
	{
		printf("�������!\n");
	}
}
int main()
{
    int i = 0;//����һ���ж��û���ݵı���
	char a;
	char name[20];
	Init();
	loaddata();
	printf("�Ƿ�洢������Ϣ(y/n):");
	fflush(stdin);
	scanf("%c",&a);
	if (a == 'y' || a == 'Y')
		addfly();
	CreateTi();
	while (1)
	{
		switch (num())
		{	
		case 1:lookfly(i);
			break;
		case 2:bookticket(i, name);//��Ʊ
			break;
		case 3:returnticket(i,name);//��Ʊ
			break;
		case 4:lookcity();//�鿴������Ϣ
			break;
		case 5:Register(&i,name);//��¼����Ա2�û�1
			break;
		case 6:Create();//ע��
			break;
		case 7:display(i);
			break;
		case 8:exit(1);
			break;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}
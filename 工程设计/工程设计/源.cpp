#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#define MAX 100
#define MAX_1 2147483647
struct book//保存用户预定的飞机
{
	char fly[5];//预定航班号
	struct book *next;
};
struct iddata
{
	char NO[20];//用户名
	char secret[20];//用户密码
	int booknum;//保存已经预定了几个
	int waitnum;//保存等待中
	struct book bookfly;
	struct book waitfly;
};
typedef struct User
{
	struct iddata IdData;
	struct User *next;
}User;//用户信息
typedef struct ArcNode//建立图
{
	int adjvex;//存储点的序列
	char fly[5];//储存航班号
	char endplace[10];//终点地方
	int money;//设置权
	struct ArcNode *nextArc;
}ArcNode;
typedef struct VNode
{
	char starplace[10];//头结点信息
	ArcNode* firstnext;
}VNode;
typedef struct ALGraph
{
	int n;//头结点个数
	VNode map[MAX];
}ALGraph;
typedef struct Roud
{
	struct Roud *next;//路线链表
	char flyno[5];//飞机航班号
	char startplace[10];//出发点
	char endplace[10];//终点
}Roud;
struct usernum//保存航班中的用户
{
	char NO[20];//储存已定人的名字
	struct usernum *next;
};
struct flydata//航班信息
{	
	int waitnum;//查看存储等待人的个数
	int booknum;//查看储存预订人的个数
	char flyno[10];//航班号
	char startplace[20];//起飞地点
	char endplace[20];//到达地点
	int num;//可以乘坐的人数
	int money;//单价
	struct usernum BookUserNum;//预定用户
	struct usernum WaitUserNum;//排队等待用户
};
typedef struct fly
{
	struct flydata FlyData;
	struct fly *next;
}Fly;//航班信息
User *user = (User*)malloc(sizeof(User));//定义用户和航班的头指针
User *admini = (User*)malloc(sizeof(User));
Fly *fly=(Fly*)malloc(sizeof(Fly));
ALGraph pg;
int num()
{
	system("cls");
	int choice;
	printf("*******************************\n");
	printf("*    1.查看航班               *\n");
	printf("*    2.订票                   *\n");
	printf("*    3.退票                   *\n");
	printf("*    4.查看城市信息           *\n");
	printf("*    5.登录                   *\n");
	printf("*    6.注册                   *\n");
	printf("*    7.浏览全部航班           *\n");
	printf("*    8.退出                   *\n");
	printf("*******************************\n");
	printf("请选择:");
	scanf("%d",&choice);
	return choice;
}
void Init()//将头指针初始化
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
int loaddata()//加载文件的东西 成功返回1 失败0 
{
	FILE *fp,*stream;
	User *p;
	char name[20];
	if ((fp = fopen("admini.txt", "r")) != NULL) 
	{
		User *ad = admini;//加载管理者信息
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
			if (ad->IdData.booknum > 0||ad->IdData.waitnum>0)//加载预订用户的信息
			{
				struct book *h;
				sprintf(name, "%s.txt", ad->IdData.NO);
				if ((stream = fopen(name, "r")) != NULL){
					h = &ad->IdData.bookfly;//加载预订信息
					for (int i = 0; i < ad->IdData.booknum; i++){
						b = (struct book*)malloc(sizeof(struct book));
						fread(&b->fly,sizeof(b->fly),1,stream);
						//fgets(b->fly, sizeof(b->fly), stream);
						//fscanf(stream, "%s", b->fly);
						b->next = NULL;
						h->next = b;
						h = b;
					}
					h = &ad->IdData.waitfly;//加载等订信息
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
		while (!feof(fp))//加载用户信息
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
			if (us->IdData.booknum > 0 || us->IdData.waitnum > 0)//加载预订用户的信息
			{
				struct book *h;
				sprintf(name, "%s.txt", us->IdData.NO);
				if ((stream = fopen(name, "r")) != NULL){
					h = &us->IdData.bookfly;//加载预订信息
					for (int i = 0; i < us->IdData.booknum; i++){
						b = (struct book*)malloc(sizeof(struct book));
						fread(&b->fly,sizeof(b->fly),1,stream);
						//fgets(b->fly, sizeof(b->fly), stream);
						//fscanf(stream, "%s", b->fly);
						b->next = NULL;
						h->next = b;
						h = b;
					}
					h = &us->IdData.waitfly;//加载预订信息
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
		while (!feof(fp))//加载航班信息
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
		printf("保存航机信息时，打开文件失败!\n");
		return 0;
	}
	while (fl != NULL)
	{
		fflush(fp);
		fwrite(&fl->FlyData, sizeof(struct flydata), 1, fp);//更新航班信息
		fl = fl->next;
	}
	fclose(fp);
	return 1;
}
int addfly()//添加飞机信息
{
	char a = 'n';
	Fly *fl,*p=fly,*q=fly;
	do{
		p = fly;
		fl = (Fly*)malloc(sizeof(Fly));
		if (fl == NULL)return 0;
		do{
			printf("请输入航班号(请不要重复):");//航班信息
			fflush(stdin);
			scanf("%s", fl->FlyData.flyno);
			while (p != NULL)
			{
				if (strcmp(fl->FlyData.flyno, p->FlyData.flyno) == 0)//判断航班号是否重复
				{
					break;
				}
				p = p->next;
			}
		} while (p != NULL);
		printf("请输入起飞地点:");
		fflush(stdin);
		scanf("%s", fl->FlyData.startplace);
		printf("请输入到达地点:");
		fflush(stdin);
		scanf("%s", fl->FlyData.endplace);
		printf("请输入乘坐人数:");
		scanf("%d", &fl->FlyData.num);
		printf("请输入单价:");
		fflush(stdin);
		scanf("%d", &fl->FlyData.money);
		fl->next = NULL;
		fl->FlyData.booknum = 0;
		fl->FlyData.BookUserNum.next = NULL;
		fl->FlyData.WaitUserNum.next = NULL;
		fl->FlyData.waitnum = 0;
		q->next = fl;
		q = fl;
		printf("是否继续存储航班信息(y/n):");
		fflush(stdin);
		a = getchar();
	} while (a == 'y' || a == 'Y');
	return savedatafly("a+");
}
void Creat()//建立头节点
{
	Fly *p =fly->next;
	int k = 0,j=0;
	while (p != NULL)
	{
		k = 0;	j = 0;//k为出发点，j为终点
		for (int i = 0; i < pg.n; i++)//判断节点是否重复
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
void CreateTi()//建立邻接表
{
	int i = 0,j=0;
	Fly *q = fly->next;
	Creat();//建立头节点
	while (q != NULL)
	{
		for (i = 0; i < pg.n; i++)//找到对应的序列号
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
		strcpy(p->fly, q->FlyData.flyno);//储存航班号
		p->money = q->FlyData.money;//权的赋值
		p->adjvex = j;//下一个结点序列
		if (strlen(q->FlyData.endplace)<10)
		strcpy(p->endplace, q->FlyData.endplace);
		p->nextArc = pg.map[i].firstnext;//链接在对应的链表后面
		pg.map[i].firstnext = p;
		q = q->next;
	}
}
void findfly(Roud *roud)//根据路线找到航班
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
	printf("找到该航班号%s\n", p->FlyData.flyno);
	printf("起飞地点:%s\n", p->FlyData.startplace);
	printf("到达地点:%s\n", p->FlyData.endplace);
	printf("余票:%d张\n", p->FlyData.num - p->FlyData.booknum);
	printf("单价:%d元\n", p->FlyData.money);
	if (i == 2)
	{
		struct usernum *l = p->FlyData.BookUserNum.next;
		flydata *b=&p->FlyData;
		printf("已预定用户:\n");
		while (l != NULL&&b->booknum != 0)
		{
			printf("%s\n", l->NO);
			l = l->next;
		}
		l = p->FlyData.WaitUserNum.next;
		printf("正在等待的用户\n");
		while (l != NULL&&b->waitnum != 0)
		{
			printf("%s\n", l->NO);
			l = l->next;
		}
	}
}
Fly* findno(char n[])//根据航班号查找
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
void DBS(int V0, int path[],int b[])//i为头节点数组序号
{
	int a[MAX],i,j,k,min;
	ArcNode *p;
	for (i = 0; i < pg.n; i++)//初始化数组
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
	a[]为查看是否走过
	b[]为路程
	*/
	for (i = 1; i < pg.n-1; i++)
	{
		min = MAX_1;
		for (k = 0; k < pg.n; k++)
		{
			if (min>b[k] && !a[k])//一次都没有传进去
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
Roud * FindTi(char start[], char end[],int *s)//传入起点站、终点站、路程传出链表
{
	VNode *p;
	int i = 0, j, k=-20;
	int path[MAX], lowcost[MAX];
	Roud *q,*roud;
	roud = (Roud*)malloc(sizeof(Roud));
	if (roud == NULL){ return NULL; }
	for (i = 0; i < pg.n; i++)//找到起点的头节点
	{
		p = &pg.map[i];
		if (strcmp(p->starplace, start) == 0)
		{
			j = i;//开始的数组序号
		}
		if (strcmp(p->starplace, end) == 0)
		{
			k = i;//终点数组序号
		}
	}
	if (k >= pg.n || k < 0)
	{
		return NULL;
	}
	DBS(j,path,lowcost);
	roud->next = NULL;//将路径转化成roud
	if (lowcost[k] < MAX_1)//有路径
	{
		printf("需要%d元才能到达%s\n", lowcost[k], end);
		q = roud;
		strcpy(q->endplace, pg.map[k].starplace);//最终到达的点
		i = path[k];
		while (i != j)
		{
			strcpy(q->startplace, pg.map[i].starplace);//出发点赋值
			q = (Roud*)malloc(sizeof(Roud));
			if (q == NULL)return NULL;
			q->next = NULL;
			strcpy(q->endplace, pg.map[i].starplace);//最终到达的点
			q->next = roud;
			roud = q;
			i = path[i];
		}
		strcpy(q->startplace, pg.map[j].starplace);//出发点赋值
		q = roud;
		while (q != NULL)//赋值航班号
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
		printf("请输入航班号:");
		fflush(stdin);
		scanf("%s", n);
		p=findno(n);
		if (p!=NULL)
		{
			displayfly(p, i);
			return;
		}
		else//未查找到用户输入的航班
		{
			j = MessageBox(0, L"未查找到该航班!是否继续查找?", L"错误", MB_OKCANCEL);
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
		printf("请输入起飞地点:");
		fflush(stdin);
		scanf("%s", q.FlyData.startplace);
		printf("是否继续输入终点站(y/n)?");
		fflush(stdin);
		b = getchar();
		if (b != 'n'&&b!='N')
		{
			printf("请输入终点站:");
			fflush(stdin);
			scanf("%s", q.FlyData.endplace);
		}
		p = fly->next;
		while (p != NULL)
		{
			if ((strcmp(q.FlyData.startplace, p->FlyData.startplace) == 0)&&b=='n'&&c=='n')//只输入起飞地点
			{
				displayfly(p,i);
				k++;
			}
			p = p->next;
		}
		if (b != 'n'&&c == 'n')//查找转运路线
		{
			FindTi(q.FlyData.startplace, q.FlyData.endplace,&k);
		}
		if (k==0)//未查找到用户输入的航班
		{
			j = MessageBox(0, L"未查找到该航班!是否继续查找?", L"错误", MB_OKCANCEL);
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
		printf("*     1.按航班号查找              *\n");
		printf("*     2.按地点查找                *\n");
		printf("*     3.退出                      *\n");
		printf("***********************************\n");
		printf("请选择:");
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
User *finduser(char no[],int *i)//找到返回找到那个指针未找到返回NULL
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
void Register(int *j,char name[])//登录
{
	User a,*p;
	int i,k=0;
	char m = 'n';
	printf("请输入用户名:");
	fflush(stdin);
	scanf("%s", a.IdData.NO);
	p = finduser(a.IdData.NO,&k);
	if (p != NULL)
	{
		do{
			m = 'n';
			printf("请输入密码:");
			fflush(stdin);
			scanf("%s", a.IdData.secret);
			if (strcmp(p->IdData.secret, a.IdData.secret) == 0)
			{
				strcpy(name,a.IdData.NO);
				MessageBox(0, L"登录成功!", L"成功", MB_OK);
				if (k == 2)
					*j = 2;
				else if (k == 1)
					*j = 1;
				return;
			}
			else
			{
				i = MessageBox(0, L"登录失败!是否继续登录?", L"失败", MB_OKCANCEL);
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
		MessageBox(0, L"未找到该用户!请先创建该用户", L"错误", MB_OK);
		return;
	}
}
void Create()//只有一个管理员
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
		printf("请输入用户名:");
		fflush(stdin);
		scanf("%s", a->IdData.NO);
		do
		{
			printf("请输入密码(大于六位数小于十六位):");
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
		MessageBox(0, L"创建成功!", L"成功", MB_OK);
		return;
	}
	else
	{
		do{
			s = 'n';
			if ((fp = fopen("user.txt", "a")) == NULL)return;
			printf("请输入用户名:");
			fflush(stdin);
			scanf("%s", a->IdData.NO);
			p = finduser(a->IdData.NO,&i);
			if (p == NULL)
			{
				do{
					printf("请输入密码(大于六位数小于十六位数):");
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
				MessageBox(0, L"创建成功!", L"成功", MB_OK);
				return;
			}
			else
			{
				i = MessageBox(0, L"用户名重复!是否继续创建?", L"错误", MB_OKCANCEL);
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
	printf("-------------所有航班--------------\n");
	while (p != NULL)
	{
		displayfly(p, j);
		p = p->next;
	}
	VNode *a;//将图显示出来
	ArcNode *q;
	int i=0;
	printf("-----------邻接表--------------\n");
	for (i = 0; i < pg.n; i++)
	{
		a = &pg.map[i];
		printf("这是第%d个序列:%s\n", i + 1,a->starplace);
		q = a->firstnext;
		while (q != NULL)
		{
			printf("下一个序列为%d,终点站%s,航班号:%s,单价：%d\n", q->adjvex,q->endplace, q->fly, q->money);
			q = q->nextArc;
		}
	}
}
void bookticket(int i,char name[])//订票
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
		printf("*              订票                  *\n");
		printf("**************************************\n");
		printf("请输入起飞地点:");
		fflush(stdin);
		scanf("%s", start);
		printf("请输入终点站:");
		fflush(stdin);
		scanf("%s", end);
		r=FindTi(start,end,&k);
		if (k != 0)//有路线
		{
			printf("是否购票(y/n)?");
			fflush(stdin);
			a = getchar();
			if (a == 'y' || a == 'Y')
			{
				printf("请输入购票数量:");
				scanf("%d", &num);
				rou = r;
				while (rou != NULL)
				{
					f = findno(rou->flyno);
					if ((f->FlyData.num - f->FlyData.booknum) < num)
					{
						system("cls");
						displayfly(f,0);
						printf("该航班余票不足!是否排队等待(y/n)?");
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
					f = findno(r->flyno);//p为航班
					u = finduser(name, &h);//u为用户
					for (j = 0; j < num; j++)
					{
						if (f->FlyData.booknum < f->FlyData.num)//当预订数量小于总数量则添加到用户和航班中
						{
							struct usernum *us, *fu1 = &f->FlyData.BookUserNum, *fu2 = f->FlyData.BookUserNum.next;//航班中预订的用户
							struct book *boo, *b1 = &u->IdData.bookfly, *b2 = u->IdData.bookfly.next;//用户中预订的航班
							while (fu2 != NULL)//找到未结点
							{
								fu1 = fu1->next;//
								fu2 = fu2->next;
							}
							while (b2 != NULL)
							{
								b1 = b1->next;//
								b2 = b2->next;
							}
							us = (struct usernum*)malloc(sizeof(struct usernum));//用户添加到航班中
							strcpy(us->NO, name);
							us->next = NULL;
							fu1->next = us;
							f->FlyData.booknum++;
							sprintf(file, "%s.txt", f->FlyData.flyno);
							if ((fp = fopen(file, "ab")) == NULL) return;//写入用户
							fflush(fp);
							//fprintf(fp,"%s",us->NO);
							fwrite(&us->NO,sizeof(us->NO),1,fp);
							//fputs(us->NO,fp);
							fclose(fp);
							boo = (struct book*)malloc(sizeof(struct book));//写入航班到用户中
							strcpy(boo->fly, f->FlyData.flyno);
							boo->next = NULL;
							b1->next = boo;
							u->IdData.booknum++;
							saveuserfly(u);
						}
						else//当预定数量等于或大于总数量进入排队中
						{
							struct usernum *us, *fu1 = &f->FlyData.WaitUserNum, *fu2 = f->FlyData.WaitUserNum.next;
							struct book *boo, *b1 = &u->IdData.waitfly, *b2 = u->IdData.waitfly.next;
							while (fu2 != NULL)//找到未结点
							{
								fu1 = fu1->next;//
								fu2 = fu2->next;
							}
							while (b2 != NULL)
							{
								b1 = b1->next;//
								b2 = b2->next;
							}
							us = (struct usernum*)malloc(sizeof(struct usernum));//用户添加到等待航班中
							strcpy(us->NO, name);
							us->next = NULL;
							fu1->next = us;
							f->FlyData.waitnum++;
							sprintf(file, "%s.txt",f->FlyData.flyno );
							if ((fp=fopen(file, "ab")) == NULL) return;//写入等待的用户航班
							fflush(fp);
							//fprintf(fp,"%s",us->NO);
							fwrite(&us->NO,sizeof(us->NO),1,fp);
							//fputs(us->NO, fp);
							fclose(fp);
							boo = (struct book*)malloc(sizeof(struct book));//航班添加到等待用户中
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
				MessageBox(0, L"未找到该航班", L"错误", MB_OK);
		}
	}
	else 
	{
		MessageBox(0, L"请先登录", L"错误", MB_OK);
		return;
	}
}
void returnticket(int i, char name[])//退票
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
		printf("*              退票                  *\n");
		printf("**************************************\n");
		printf("您所订的航班如下:\n");
		q = finduser(name, &j);//q为退票用户
		b = q->IdData.bookfly.next;//b为退票用户中已定了航班
		while (b != NULL)//将所有已定的航班展示出来
		{
			p=findno(b->fly);
			displayfly(p, 1);
			printf("------------------\n");
			b = b->next;
		}
		if (q->IdData.booknum < 1)return;//如果没有订票退出
		printf("是否退票(y/n)？");
		fflush(stdin);
		s = getchar();
		if (s == 'y' || s == 'Y')
		{
			do{
				s = 'n';
				j = i;
				printf("请输入需要退票的航班号:");
				scanf("%s",f);
				q = finduser(name, &j);//q为退票用户
				p = findno(f);//找到退票的航班
				if (p == NULL)//若没有退票的航班
				{
					j=MessageBox(0, L"输入错误!是否继续退票?", L"错误", MB_OKCANCEL);
					switch (j)
					{
					case IDOK:s='y'; break;
					case IDCANCEL:return;
					}
				}
				else{
					u = p->FlyData.BookUserNum.next;//退票航班中订票的人
					us = &p->FlyData.BookUserNum;
					b = q->IdData.bookfly.next;//退票用户所订的航班
					bo = &q->IdData.bookfly;
					while (u != NULL)
					{
						if (strcmp(u->NO, name) == 0)//找到退票航班的退票人
						{
							break;
						}
						u = u->next;//找到该订票用户的结点
						us = us->next;//她的前结点
					}
					if (u == NULL)//若未找到退票人在航班中
					{
						j = MessageBox(0, L"输入错误!是否继续退票?", L"错误", MB_OKCANCEL);
						switch (j)
						{
						case IDOK:s = 'y'; break;
						case IDCANCEL:return;
						}
					}
					else{
						while (b != NULL)
						{
							if (strcmp(b->fly, p->FlyData.flyno) == 0)//找到退票人的退票航班
							{
								break;
							}
							b = b->next;//找到该航班
							bo = bo->next;//她的前结点
						}
						if (b == NULL)//若未找到退票人的航班
						{
							j = MessageBox(0, L"输入错误!是否继续退票?", L"错误", MB_OKCANCEL);
							switch (j)
							{
							case IDOK:s = 'y'; break;
							case IDCANCEL:return;
							}
							break;
						}
						else{
							if (p->FlyData.waitnum > 0)//若该航班中有人等待
							{
								usn1 = &p->FlyData.WaitUserNum;//退票航班中
								usn2 = p->FlyData.WaitUserNum.next;
								q->IdData.booknum--;//退票用户的订票数减一
								if (b->next != NULL)bo->next = b->next;
								else bo->next = NULL;//*将退票用户已订的航班删去*
								free(b);
								q = finduser(usn2->NO, &j);//将排队的用户保存在已订票中
								q->IdData.booknum++;
								q->IdData.waitnum--;
								b = &q->IdData.bookfly;//用户中订票加一
								bo = q->IdData.bookfly.next;
								while (bo != NULL)//找到已订航班的伪结点
								{
									b = b->next;//
									bo = bo->next;
								}
								bo = (struct book*)malloc(sizeof(struct book));//在伪结点加入等待航班的信息
								strcpy(bo->fly, p->FlyData.flyno);
								bo->next = NULL;
								b->next = bo;//*将等待用户的等待航班加入到已定航班中*
								b = &q->IdData.waitfly;
								bo = q->IdData.waitfly.next;
								while (bo != NULL)//找到等待用户的等待航班
								{
									if (strcmp(bo->fly, p->FlyData.flyno) == 0)
									{
										break;
									}
									b = b->next;
									bo = bo->next;
								}
								if (bo->next != NULL)
									b->next = bo->next;//*等待用户等待航班删去*
								else b->next = NULL;
								free(bo);
								strcpy(u->NO, usn2->NO);//*将航班中退票用户替换为等待用户*等待用户等待航班，已定航班，退票航班中已定用户
								p->FlyData.waitnum--;
								if (usn2->next != NULL)//删去在退票航班中等待用户
									usn1->next = usn2->next;
								else usn1->next = NULL;
								free(usn2);
								q = finduser(u->NO, &j);//等待用户的航班
								saveuserfly(q);//保存等待用户的航班
								q = finduser(name, &j);
							}
							else
							{
								if (u->next != NULL)//判断是否要删除的结点为最后一个结点
									us->next = u->next;
								else us->next = NULL;
								free(u);
								if (b->next != NULL)bo->next = b->next;
								else bo->next = NULL;//*将退票用户已订的航班删去*
								free(b);
								p->FlyData.booknum--;
								q->IdData.booknum--;
							}
							saveflyuser(p);//该航班中的用户
							saveuserfly(q);//退票用户航班
							if (q->IdData.booknum < 1)
							{
								savedatafly("w");//保存航班信息
								savedatauser("w", i);//保存用户信息
								return; 
							}//如果没有订票退出
							printf("是否继续退票(y/n):");
							fflush(stdin);
							s = getchar();
							savedatafly("w");//保存航班信息
							savedatauser("w", i);//保存用户信息
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
		MessageBox(0, L"请先登录", L"错误", MB_OK);
		return;
	}
}
void lookcity()
{
	FILE *fp;
	char city_1[20],city_2[20],c;
	printf("              北京          \n");
	printf("                            \n");
	printf("                        上海\n");
	printf("                            \n");
	printf(" 成都                       \n");
	printf("                      深圳  \n");
	printf("                 广州       \n");
	printf("请输入需要查找城市信息的城市:");
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
		printf("输入错误!\n");
	}
}
int main()
{
    int i = 0;//定义一个判断用户身份的变量
	char a;
	char name[20];
	Init();
	loaddata();
	printf("是否存储航班信息(y/n):");
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
		case 2:bookticket(i, name);//订票
			break;
		case 3:returnticket(i,name);//退票
			break;
		case 4:lookcity();//查看城市信息
			break;
		case 5:Register(&i,name);//登录管理员2用户1
			break;
		case 6:Create();//注册
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
#include <string.h> 
#include <stdio.h> 
#include <malloc.h>
#include <stdlib.h>
#define Max 20000
#define MAXSIZE 3 

typedef struct ArcCell
{
	int adj;  /* 相邻接的城市之间的路程 */
}ArcCell;   /* 定义边的类型 */
typedef struct VertexType
{
	int number;  /* 城市编号 */
	char sight[100];  /* 城市名称 */
	char description[1000]; /* 城市描述 */
}VertexType;   /* 定义顶点的类型 */
typedef struct
{
	VertexType vex[20]; /* 图中的顶点，城市 */
	ArcCell arcs[20][20]; /* 图中的边，即为城市间的距离 */
	int vexnum, arcnum; /* 顶点数，边数 */
}MGraph;   /* 定义图的类型 */
MGraph G;   /* 把图定义为全局变量 */

typedef struct wat_ros
{
	char name[10];/*姓名*/
	int req_amt;/*订票量*/
	struct wat_ros *next;
}qnode, *qptr;

typedef struct pqueue
{
	qptr front;/*等候替补客户名单域的头指针*/
	qptr rear;/*等候替补客户名单域的属指针*/
}linkqueue;

typedef struct ord_ros
{
	char name[10];/*客户姓名*/
	int ord_amt;/*订票量*/
	int grade;/*舱位等级*/
	struct ord_ros *next;
}linklist;

typedef struct airline
{
	char str_name[10];
	char ter_name[10];/*终点站名 */
	char air_num[10];/*航班号*/
	char plane_num[10];/*飞机号*/
	char day[7];/*飞行周日（星期几）*/
	int tkt_amt;/*乘员定额*/
	int tkt_sur;/*余票量*/
	int money;
	linklist *order;/*乘员名单域，指向乘员名单链表的头指针*/
	linkqueue wait;/*等候替补的客户名单域，分别指向排队等候名单队头队尾的指针*/
	struct airline *next;//可直达的城市
}lineinfo;

struct airline *start;

void display(struct airline *info)
/*打印每条航线的基本信息*/
{
	printf("%8s\t%8s\t%3s\t%s\t%4s\t\t%3d\t%10d\t%10d\n", info->str_name, info->ter_name, info->air_num, info->plane_num, info->day, info->tkt_amt, info->tkt_sur, info->money);
}

void list()/*打印全部航线信息*/
{
	struct airline *info;
	int i = 0;
	info = start;
	printf("起点站名\t终点站名\t航班号\t飞机号\t飞行周日\t乘员定额\t余票量\t      票价\n");
	while (i<MAXSIZE) {
		display(info);
		info++;
		i++;
	}
	printf("\n\n");
}

struct airline *find()
	/*根据系统提出的航班号查询并以指针形式返回*/
{
	struct airline *info;
	char number[10];
	int i = 0;
	info = start;
	printf("请输入航班号:");
	scanf("%s", number);
	while (i<MAXSIZE) {
		if (!strcmp(number, info->air_num))
			return info;
		info++;
		i++;
	}
	printf("对不起，该航线末找到!\n");
	return NULL;
}

struct airline *fix_start(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("请输入要修改的目的起点站：");
		scanf("%s", a);
		strcpy(p->ter_name, a);
	}
	else
		printf("已有乘客，无法修改！");
	return p;
}
struct airline *fix_terminal(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("请输入要修改的目的终点站：");
		scanf("%s", a);
		strcpy(p->ter_name, a);
	}
	else
		printf("已有乘客，无法修改！");
	return p;
}
struct airline *fix_time(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("请输入要修改起飞时间（飞行周日（星期几））：");
		scanf("%s", a);
		strcpy(p->day, a);
	}
	else
		printf("已有乘客，无法修改！");
	return p;
}
struct airline *fix_plane_num(struct airline *p)
{
	char  a[10];
	if (p->order == NULL)
	{
		printf("请输入要修改的飞机号：");
		scanf("%s", a);
		strcpy(p->day, a);
	}
	else
		printf("已有乘客，无法修改！");
	return p;
}
struct airline *tkt_amt(struct airline *p)
{
	int a;
	if (p->order == NULL)
	{
		printf("请输入要修改的额定成员数量：");
		scanf("%d", &a);
		p->tkt_amt = a;
	}
	else
		printf("已有乘客，无法修改！");
	return p;
}
struct airline *money(struct airline *p)
{
	int a;
	if (p->order == NULL)
	{
		printf("请输入要修改的票价为：");
		scanf("%d", &a);
		p->tkt_amt = a;
	}
	else
		printf("已有乘客，无法修改！");
	return p;
}


struct airline *fix()
{
	int choose;
	struct airline * p;
	p = find();
	while (1)
	{//显示菜单
		system("cls");//清屏
		printf("请选择要修改的信息：\n");
		printf("*************************************\n");
		printf("[1] 修改起点站\n");
		printf("[2] 修改终点站\n");
		printf("[3] 修改起飞时间\n");
		printf("[4] 修改飞机型号\n");
		printf("[5] 修改票价\n");
		printf("[6] 修改乘员定额\n");
		printf("[0] 退出程序\n");
		printf("请输入您的选择（0 - 9）：\n");
		printf("**************************************)\n");
		scanf("%d", &choose);
		if (choose == 0)
		{
			break;//用于结束距离它最近的循环
		}
		switch (choose)
		{
		case 1:
			p = fix_start(p);
			break;
		case 2:
			p = fix_terminal(p);
			break;
		case 3:
			p = fix_time(p);
			break;
		case 4:
			p = fix_plane_num(p);
			break;
		case 5:
			p = money(p);
			break;
		case 6:
			p = tkt_amt(p);
			break;
		default:
			printf("输入有误 请从新输入");
		}
	}
	return p;
}
void Search()
/*根据客户提出的终点站名输出航线信息*/
{
	struct airline *info, *find();
	char name[10], name1[10];
	int i = 0;
	info = start;
	printf("请输入起点站名:");
	scanf("%s", name);
	printf("请输入终点站名:");
	scanf("%s", name1);
	while (i<MAXSIZE)
	{
		if (!strcmp(name, info->str_name))
		{
			if (!strcmp(name1, info->ter_name))
				break;
		}
		info++;
		i++;
	}
	if (i >= MAXSIZE)
		printf("对不起，无该航线!\n");
	else {
		printf("起点站名\t终点站名\t航班号\t飞机号\t飞行周日\t乘员定额\t余票量\t      票价\n");
		display(info);
	}
}
void prtlink()
/*打印订票乘员名单域的客户名单信息*/
{
	linklist *p;
	struct airline *info;
	info = find();
	p = info->order;
	if (p != NULL) {
		printf("客户姓名   订票数额   舱位等级\n");
		while (p) {
			printf("%s\t\t%d\t%d\n", p->name, p->ord_amt, p->grade);
			p = p->next;
		}
	}
	else
		printf("该航线没有客户信息!!\n");
}
linklist *insertlink(linklist *head, int amount, char name[], int grade)
/*增加订票乘员名单域的客户信息*/
{
	linklist *p1, *new;
	p1 = head;
	new = (linklist *)malloc(sizeof(linklist));
	if (!new) { printf("\nOut of memory!!\n"); return NULL; }
	strcpy(new->name, name);
	new->ord_amt = amount;
	new->grade = grade;
	new->next = NULL;
	if (head == NULL)/*若原无订票客户信息*/
	{
		head = new; new->next = NULL;
	}
	else
		head = new;
	new->next = p1;
	return head;
}

linkqueue appendqueue(linkqueue q, char name[], int amount)
/*增加排队等候的客户名单域*/
{
	qptr new;
	new = (qptr)malloc(sizeof(qnode));
	strcpy(new->name, name);
	new->req_amt = amount;
	new->next = NULL;
	if (q.front == NULL)/*若原排队等候客户名单域为空*/
		q.front = new;
	else
		q.rear->next = new;
	q.rear = new;
	return q;
}

void order()
/*办理订票业务*/
{
	struct airline *info;
	int amount, grade;
	char name[10];
	info = start;
	if (!(info = find())) return;/*根据客户提供的航班号进行查询，如为空，退出该模块*/
	printf("请输入你订票所需要的数量:");
	scanf("%d", &amount);
	if (amount>info->tkt_amt)/*若客户订票额超过乘员定票总额，退出*/
	{
		printf("\n对不起，您输入的票的数量已经超过乘员定额!");
		return;
	}
	if (amount <= info->tkt_sur)/*若客户订票额末超过余票量，订票成功并等记信息*/
	{
		int i;
		printf("请输入您的姓名（订票客户）:");
		scanf("%s", name);
		printf("请输入%s票的舱位等级:", name);
		scanf("%d", &grade);
		info->order = insertlink(info->order, amount, name, grade);/*在订票乘员名单域中添加客户信息*/
		for (i = 0; i<amount; i++)/*依次输出该订票客户的座位号*/
			printf("%s的座位号是:%d\n", name, info->tkt_amt - info->tkt_sur + i + 1);
		info->tkt_sur -= amount;/*该航线的余票量应减掉该客户的订票量*/
		printf("\n祝您乘坐愉快！\n");
	}
	else       /*若满员或余票额少于订票额，询问客户是否需要进行排队等候*/
	{
		char r;
		printf("\n已经没有更多的票，您需要排队等候吗?(Y/N)");
		r = getch();
		printf("%c", r);
		if (r == 'Y' || r == 'y')
		{
			printf("\n请输入您的姓名（排队订票客户）:");
			scanf("%s", name);
			info->wait = appendqueue(info->wait, name, amount);/*在排队等候乘员名单域中添加客户信息*/
			printf("\n注册成功!\n");
		}
		else printf("\n欢迎您下次再次订购！\n");
	}
}
void return_tkt()
/*退票模块*/
{
	struct airline *info;
	qnode *t, *back, *f, *r;
	int grade;
	linklist *p1, *p2, *head;
	char cusname[10];
	if (!(info = find())) return;/*调用查询函数，根据客户提供的航线进行搜索*/
	head = info->order;
	p1 = head;
	printf("请输入你的姓名（退票客户）:");
	scanf("%s", cusname);
	while (p1 != NULL) {/*根据客户提供的姓名到订票客户名单域进行查询*/
		if (!strcmp(cusname, p1->name)) break;
		p2 = p1; p1 = p1->next;
	}
	if (p1 == NULL) { printf("对不起，你没有订过票!\n"); return; }/*若未找到，退出本模块*/
	else {/*若信息查询成功，删除订票客户名单域中的信息*/
		if (p1 == head) head = p1->next;
		else p2->next = p1->next;
		info->tkt_sur += p1->ord_amt;
		grade = p1->grade;
		printf("%s成功退票！\n", p1->name);
		free(p1);
	}
	info->order = head;/*重新将航线名单域指向订票单链表的头指针 */
	f = (info->wait).front;/*f指向排队等候名单队列的头结点*/
	r = (info->wait).rear;/*r指向排队等候名单队列的尾结点*/
	t = f;/*t为当前满点条件的排队候补名单域*/
	while (t)
	{
		if (info->tkt_sur >= info->wait.front->req_amt) {/*若满足条件者为头结点*/
			int i;
			info->wait.front = t->next;
			printf("%s订票成功！\n", t->name);
			for (i = 0; i<t->req_amt; i++)/*输出座位号*/
				printf("%s的座位号是:%d\n", t->name, (info->tkt_sur) - i);
			info->tkt_sur -= t->req_amt;
			info->order = insertlink(info->order, t->req_amt, t->name, grade);/*插入到订票客户名单链表中*/
			free(t);
			break;
		}
		back = t; t = t->next;
		if ((info->tkt_sur) >= (t->req_amt) && t != NULL)/*若满足条件者不为头结点*/
		{
			int i;
			back->next = t->next;
			printf("%s订票成功！\n", t->name);
			for (i = 0; i<t->req_amt; i++)/*输出座位号*/
				printf("<%s>'s seat number is:%d\n", t->name, (info->tkt_sur) - i);
			info->tkt_sur -= t->req_amt;
			info->order = insertlink(info->order, t->req_amt, t->name, grade);/*插入到订票客户名单链表中*/
			free(t); break;
		}
		if (f == r) break;
	}
}

char nameofairplane[100];
int NUM = 10;
int P[20][20];  /*  */
int p[20];/*全局数组，用来存放路径上的各顶点*/
int visited[20];/*全局数组，用来记录各顶点被访问的情况*/
int a = 0;/*全局变量，用来记录每对顶点之间的所有路径的条数*/
long int D[20];  /* 辅助变量存储最短路径长度 */
int   x[20] = { 0 };
void CreateUDN(int v, int a); /* 造图函数 */
void narrate();   /*说明函数*/
void ShortestPath(int num); /*最短路径函数*/
void output(int sight1, int sight2); /*输出函数*/
char Menu();   /* 主菜单 */
void search();   /* 查询景点信息 */
char SearchMenu();  /* 查询子菜单 */
void HaMiTonian(int);   /* 图的遍历 */
void Searchpath1(MGraph g);/*查询两个景点间的所有路径*/
void disppath(MGraph g, int i, int j);
void path(MGraph g, int i, int j, int k);/*确定路径上第k+1个顶点的序号*/
void NextValue(int);
void display(); /* 显示遍历结果 */
int Addnewsight(int n); /*添加新的景点和路径*/
int Deletesight(int n); /*删除景点和路径*/
void Changesight(); /*修改景点和路径*/
char Changemenu();  /*修改路径或顶点的选择菜单*/
char Sightmenu();  /*选择需该景点的菜单*/
void narrate1();


void main() /* 主函数 */
{
	int v0, v1;
	int ck;
	CreateUDN(NUM, 11);
	int i = 0;
	struct airline * p;
	FILE *fp = NULL;
	struct airline air[MAXSIZE];
	char msg[1024] = { 0 };
	fp = fopen("初始航线.txt", "r");
	if (fp == NULL)
	{
		printf("读取失败");
	}
	else
	{
		while (fgets(msg, 1024, fp) != NULL)
		{
			air[i].order = NULL;
			air[i].wait.front = NULL;
			air[i].wait.rear = NULL;
			sscanf_s(msg, "%s %s %s %s %s %d %d %d", &air[i].str_name, 20, &air[i].ter_name, 20, &air[i].air_num, 20, &air[i].plane_num, 20, &air[i].day, 20, &air[i].tkt_amt, &air[i].tkt_sur, &air[i].money);
			i++;
		}
	}
	if (i == MAXSIZE)
		printf("读取成功\n");
	system("pause");
	start = &air[0];					 /*  clrscr();*/
	do
	{
		ck = Menu();
		switch (ck)
		{
		case 1:
			search();
			break;
		case 2:
			system("cls");
			narrate1();
			printf("\n\n\t\t\t请选择起点城市（0～%d）：", NUM - 1);
			scanf("%d", &v0);
			printf("\t\t\t请选择终点城市（0～%d）：", NUM - 1);
			scanf("%d", &v1);
			ShortestPath(v0);  /* 计算两个城市之间的最短路径 */
			output(v0, v1);     /* 输出结果 */
			printf("\n\n\t\t\t\t请按任意键继续...\n");
			getchar();
			getchar();
			break;
		case 3:
			system("cls");
			narrate1();
			x[0] = 1;
			Searchpath1(G);
			printf("\n\n\t\t\t\t请按任意键继续...\n");
			getchar();
			getchar();
			break;
		case 4:
			system("cls");
			narrate1();
			NUM = Addnewsight(NUM);
			system("cls");
			narrate();
			break;
		case 5:
			NUM = Deletesight(NUM);
			break;
		case 6:
			Changesight();
			break;
		case 7:
			order();
			system("pause");
			break;
		case 8:
			return_tkt();
			system("pause");
			break;
		case 9:
			list();
			system("pause");
			break;
		case 10:
			prtlink();
			system("pause");
			break;
		case 11:
			fix();
			system("pause");
			break;
		case 12:
			Search();
			system("pause");
			break;
		case 13:
			narrate();
			system("pause");
			break;
		};
	} while (ck != 14);
}
char Menu()  /* 主菜单 */
{
	int c;
	int flag;
	do {
		flag = 1;
		system("cls");
		printf("\n--------------------weclome airplan manenagment-------------------\n");
		printf("\n                           菜单选择                             \n\n");
		printf("       1、查询城市信息               2、查询两城市间最短路径        \n");
		printf("       3、查询两城市间所有路线       4、输入航线图                  \n");
		printf("       5、删除已有城市和路径         6、修改已有城市和路径          \n");
		printf("       7.办理订票业务                8.办理退票业务                 \n");
		printf("       9.查看所有航班信息            10.浏览已订票客户信息          \n");
		printf("       11.修改航班信息               12 查询航班信息                \n");
		printf("       13 查看所有城市信息           14退出		     			   \n");
		printf("--------------------------------------------------------------------\n");
		printf("\n 请输入你的选择：");
		scanf("%d", &c);
		if (c == 1 || c == 2 || c == 3 || c == 4 || c == 5 || c == 6 || c == 7 || c == 8 || c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 14)
			flag = 0;
	} while (flag);
	return c;
}
char SearchMenu()  /* 查询子菜单 */
{
	char c;
	int flag;
	do {
		flag = 1;
		system("cls");
		narrate1();
		printf("\n\t\t\t				                \n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t        1、按照城市编号查询       \n");
		printf("\t\t\t        2、按照城市名称查询       \n");
		printf("\t\t\t        e、返回                   \n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t									\n");
		printf("\t\t\t\t请输入您的选择：");
		scanf("%c", &c);
		if (c == '1' || c == '2' || c == 'e')
			flag = 0;
	} while (flag);
	return c;
}

void search()  /* 查询城市信息 */
{
	int num;
	int i;
	char c;
	char name[20];
	do
	{
		system("cls");
		c = SearchMenu();
		switch (c)
		{
		case '1':
			system("cls");
			narrate();
			printf("\n\n\t\t请输入您要查找的城市编号：");
			scanf("%d", &num);
			for (i = 0; i<NUM; i++)
			{
				if (num == G.vex[i].number)
				{
					printf("\n\n\t\t\t您要查找城市信息如下:");
					printf("\n\n\t\t\t%-25s\n\n", G.vex[i].description);
					printf("\n\t\t\t按任意键返回...");
					getchar();
					getchar();
					break;
				}
			}
			if (i == NUM)
			{
				printf("\n\n\t\t\t没有找到！");
				printf("\n\n\t\t\t按任意键返回...");
				getchar();
				getchar();
			}
			break;
		case '2':
			system("cls");
			narrate();
			printf("\n\n\t\t请输入您要查找的城市名称：");
			scanf("%s", name);
			for (i = 0; i<NUM; i++)
			{
				if (!strcmp(name, G.vex[i].sight))
				{
					printf("\n\n\t\t\t您要查找城市信息如下:");
					printf("\n\n\t\t\t%-25s\n\n", G.vex[i].description);
					printf("\n\t\t\t按任意键返回...");
					getchar();
					getchar();
					break;
				}
			}
			if (i == NUM)
			{
				printf("\n\n\t\t\t没有找到！");
				printf("\n\n\t\t\t按任意键返回...");
				getchar();
				getchar();
			}
			break;
		}
	} while (c != 'e');
}
void CreateUDN(int v, int a) /* 造图函数 */
{
	int i, j;
	strcpy(nameofairplane, "中国民用");
	G.vexnum = v;  /* 初始化结构中的城市数和边数 */
	G.arcnum = a;
	for (i = 0; i<20; ++i) G.vex[i].number = i; /* 初始化每一个城市的编号 */
	/* 初始化每一个城市名及其城市描述 */
	strcpy(G.vex[0].sight, "北京");
	strcpy(G.vex[0].description, "北京是首批国家历史文化名城和世界上拥有世界文化遗产数最多的城市，三千多年的历史孕育了故宫、天坛、八达岭长城、颐和园等众多名胜古迹");
	strcpy(G.vex[1].sight, "上海");
	strcpy(G.vex[1].description, "上海，简称“沪”或“申”，是中华人民共和国直辖市，国家中心城市，超大城市，是中国第一大城市，中国的经济、交通、科技、工业、金融、贸易、会展和航运中心，首批沿海开放城市");
	strcpy(G.vex[2].sight, "广州");
	strcpy(G.vex[2].description, "广州是广东省省会、国家中心城市、超大城市、南部战区司令部驻地。是国务院定位的国际大都市、国际商贸中心、国际综合交通枢纽、国家综合性门户城市、国家历史文化名城");
	strcpy(G.vex[3].sight, "深圳");
	strcpy(G.vex[3].description, "深圳，简称“深”，别称鹏城，中国四大一线城市之一[1]  ，广东省省辖市、计划单列市、副省级市、国家区域中心城市、超大城市");
	strcpy(G.vex[4].sight, "香港");
	strcpy(G.vex[4].description, "香港（粤拼：hoeng1 gong2；英文：Hong Kong；普通话拼音：xiāng gǎng；缩写：HK），简称“港”，全称为中华人民共和国香港特别行政区（HKSAR）");
	strcpy(G.vex[5].sight, "成都");
	strcpy(G.vex[5].description, "成都，简称蓉，四川省省会、副省级市，中国西南地区的科技、商贸、金融中心和交通枢纽[1]  ，国家重要的高新技术产业基地、商贸物流中心和综合交通枢纽、西部地区重要的中心城市");
	strcpy(G.vex[6].sight, "重庆");
	strcpy(G.vex[6].description, "重庆，简称巴或渝，位于中国西南部，是中华人民共和国直辖市、国家中心城市[1]  、超大城市、国际大都市，长江上游地区经济、金融、商贸物流、科技创新和航运中心");
	strcpy(G.vex[7].sight, "杭州");
	strcpy(G.vex[7].description, "杭州，简称“杭”，浙江省省会、副省级市，位于中国东南沿海、浙江省北部、钱塘江下游、京杭大运河南端，是浙江省的政治、经济、文化、教育、交通和金融中心，长江三角洲城市群中心城市之一、长三角宁杭生态经济带节点城市");
	strcpy(G.vex[8].sight, "武汉");
	strcpy(G.vex[8].description, "武汉，简称“汉”，别称“江城”，是湖北省省会、中部六省唯一的副省级市和特大城市，中国中部地区中心城市，全国重要的工业基地、科教基地和综合交通枢纽");
	strcpy(G.vex[9].sight, "天津");
	strcpy(G.vex[9].description, "天津，简称津，中华人民共和国直辖市、国家中心城市、超大城市、[1-2]  环渤海地区经济中心、首批沿海开放城市，全国先进制造研发基地、北方国际航运核心区、金融创新运营示范区、改革开放先行区");
	/* 这里把所有的边假定为20000，含义是这两个城市之间是不可到达 */
	for (i = 0; i<20; ++i)
	for (j = 0; j<20; ++j)
		G.arcs[i][j].adj = Max;
	/*
	下边是可直接到达的城市间的距离，由于两城市点间距离是互相的，
	所以要对图中对称的边同时赋值。
	*/
	G.arcs[0][1].adj = G.arcs[1][0].adj = 500;
	G.arcs[1][3].adj = G.arcs[3][1].adj = 70;
	G.arcs[0][6].adj = G.arcs[3][0].adj = 250;
	G.arcs[1][4].adj = G.arcs[4][1].adj = 80;
	G.arcs[2][4].adj = G.arcs[4][2].adj = 100;
	G.arcs[3][5].adj = G.arcs[5][3].adj = 90;
	G.arcs[5][2].adj = G.arcs[2][5].adj = 100;
	G.arcs[4][6].adj = G.arcs[6][4].adj = 75;
	G.arcs[4][7].adj = G.arcs[7][4].adj = 300;
	G.arcs[2][7].adj = G.arcs[7][2].adj = 400;
	G.arcs[7][8].adj = G.arcs[8][7].adj = 40;
}
void narrate() /* 说明函数 */
{
	int i, k = 0;
	printf("\n\t***************欢迎使用%s航空程序**************\n", nameofairplane);
	printf("\t______________________________\n");
	printf("\t\t城市名称与简介\t\t\t\n");
	printf("\t______________________________\n");
	for (i = 0; i<NUM; i++)
	{
		printf("\n%-10d%-25s\n\n%-80s\n", i, G.vex[i].sight, G.vex[i].description);

		/* 输出城市列表 */
		k = k + 1;
	}
	printf("\t________________________________|_________________________________\n");
}
void narrate1() /* 说明函数 */
{
	int i, k = 0;
	printf("\n\t***************欢迎使用%s航空程序**************\n", nameofairplane);
	printf("\t______________________________\n");
	printf("\t\t城市名称\t\t\t\n");
	printf("\t______________________________\n");
	for (i = 0; i<NUM; i++)
	{
		printf("\n%-10d%-25s\n\n", i, G.vex[i].sight);

		/* 输出城市列表 */
		k = k + 1;
	}
	printf("\t________________________________|_________________________________\n");
}
void ShortestPath(int num) /* 迪杰斯特拉算法最短路径函数 num为入口点的编号 */
{
	int v, w, i, t;  /* i、w和v为计数变量 */
	int final[20]; /*  */
	int min;
	for (v = 0; v<NUM; v++)
	{
		final[v] = 0;  /* 假设从顶点num到顶点v没有最短路径 */
		D[v] = G.arcs[num][v].adj;/* 将与之相关的权值放入D中存放
								  */
		for (w = 0; w<NUM; w++) /* 设置为空路径 */
			P[v][w] = 0;
		if (D[v]<20000)  /* 存在路径 */
		{
			P[v][num] = 1; /* 存在标志置为一 */
			P[v][v] = 1; /* 自身到自身 */
		}
	}
	D[num] = 0;
	final[num] = 1;      /* 初始化num顶点属于S集合 */
	/* 开始主循环，每一次求得num到某个顶点的最短路径，并将其加入到S集合 */
	for (i = 0; i<NUM; ++i)     /* 其余G.vexnum-1个顶点 */
	{
		min = Max;     /* 当前所知离顶点num的最近距离 */
		for (w = 0; w<NUM; ++w)
		if (!final[w])    /* w顶点在v-s中 */
		if (D[w]<min)   /* w顶点离num顶点更近 */
		{
			v = w;
			min = D[w];
		}
		final[v] = 1;   /* 离num顶点更近的v加入到s集合 */
		for (w = 0; w<NUM; ++w)  /* 更新当前最短路径极其距离 */
		if (!final[w] && ((min + G.arcs[v][w].adj)<D[w]))/* 不在s集合，并且比以前所找到的路径都短就更新当前路径 */
		{
			D[w] = min + G.arcs[v][w].adj;
			for (t = 0; t<NUM; t++)
				P[w][t] = P[v][t];
			P[w][w] = 1;
		}
	}
}
void output(int sight1, int sight2)    /* 输出函数 */
{
	int a, b, c, d, q = 0;
	a = sight2;    /* 将城市二赋值给a */
	if (a != sight1)    /* 如果城市二不和城市一输入重合，则进行... */
	{
		printf("\n\t从%s到%s的最短路径是", G.vex[sight1].sight, G.vex[sight2].sight);/* 输出提示信息 */
		printf("\t(最短距离为 %dkm.)\n\n\t", D[a]);  /* 输出sight1到sight2的最短路径长度，存放在D[]数组中 */
		printf("\t%s", G.vex[sight1].sight);   /* 输出城市一的名称 */
		d = sight1;      /* 将城市一的编号赋值给d */
		for (c = 0; c<NUM; ++c)
		{
		gate:;        /* 标号，可以作为goto语句跳转的位置 */
			P[a][sight1] = 0;
			for (b = 0; b<NUM; b++)
			{
				if (G.arcs[d][b].adj<20000 && P[a][b])  /* 如果城市一和它的一个临界点之间存在路径且最短路径 */
				{
					printf("-->%s", G.vex[b].sight);  /* 输出此节点的名称 */
					q = q + 1;     /* 计数变量加一，满8控制输出时的换行 */
					P[a][b] = 0;
					d = b;     /* 将b作为出发点进行下一次循环输出，如此反复 */
					if (q % 8 == 0) printf("\n");
					goto gate;
				}
			}
		}
	}
}
void Searchpath1(MGraph g)/*查询两个城市间的所有路径*/
{
	int l = 0;
	int k = 0;
	int i, j;
	printf("选择出发景点：");
	scanf("%d", &i);
	printf("选择目地景点：");
	scanf("%d", &j);
	for (; k<g.vexnum; k++)/*g.vexnumber表示网中的顶点个数*/
	if (i == g.vex[k].number) i = k;/*在网中找到其编号与输入的出发城市的编号相同的顶点*/
	for (; l<g.vexnum; l++)
	if (j == g.vex[l].number) j = l;/*在网中找到其编号与输入的目地城市的编号相同的顶点*/
	printf("\n从%s到%s的所有游览路径有:\n\n", g.vex[i].sight, g.vex[j].sight);/*输出出发城市和目地城市的名称*/

	disppath(g, i, j);/*调用disppath函数,用来输出两个城市间的所有路径*/
}
void disppath(MGraph g, int i, int j)
{
	int k;
	p[0] = i;
	for (k = 0; k<g.vexnum; k++)
		visited[i] = 0;/*初始化各顶点的访问标志位，即都为未访问过的*/
	a = 0;/*初始化路径的条数*/
	path(g, i, j, 0);/*通过调用path函数，找到从vi到vj的所有路径并输出*/
}
void path(MGraph g, int i, int j, int k)
/*确定路径上第k+1个顶点的序号*/
{
	int s;
	if (p[k] == j)/*找到一条路径*/
	{
		a++;/*路径的条数值加1*/
		printf("第%d条:\t", a);
		for (s = 0; s <= k - 1; s++)/*输出一条路径*/
		{
			printf("%s", g.vex[p[s]].sight);
			printf("->");
		}
		//cout<<g.vex[p[s]].sight;
		printf("%s\n", g.vex[p[s]].sight);
	}
	s = 0;
	while (s<g.vexnum)
	{
		if (s != i)/*保证找到的是简单路径*/
		{
			if (g.arcs[p[k]][s].adj != Max&&visited[s] == 0)
				/*当vk与vs之间有边存在且vs未被访问过*/
			{
				visited[s] = 1;/*置访问标志位为1,即已访问的*/
				p[k + 1] = s;/*将顶点s加入到p数组中*/
				path(g, i, j, k + 1);/*递归调用之*/
				visited[s] = 0;/*重置访问标志位为0，即未访问的，以便该顶点能被重新使用*/
			}
		}
		s++;
	}
}
int Addnewsight(int n)
{
	int i;
	char sight[100], description[1000];
	int length;
	printf("请输入新城市的名称：\n");
	scanf("%s", &sight);
	printf("请输入新城市的相关信息：\n");
	scanf("%s", &description);
	strcpy(G.vex[n].sight, sight);
	strcpy(G.vex[n].description, description);
	G.vex[n].number = n;
	for (i = 0; i<n; i++)
	{
		system("cls");
		narrate();
		printf("请输入此城市到第%d个城市的距离（单位：m）（同一城市或不可到达用20000表示）：\n", i);
		scanf("%d", &length);
		if (length != 20000)
			G.arcnum++;
		G.arcs[n][i].adj = G.arcs[i][n].adj = length;
	}
	n++;
	G.vexnum++;
	return n;
}
int Deletesight(int n)
{
	int i;
	int j;
	char c;
	int num;
	char name[20];
	system("cls");
	c = SearchMenu();
	switch (c)
	{
	case '1':
		system("cls");
		narrate();
		printf("\n\n\t\t请输入您要删除城市的编号：");
		scanf("%d", &num);
		for (i = 0; i<NUM; i++)
		{
			if (num == G.vex[i].number)
			{
				for (j = 0; j<NUM; j++)
				{
					if (G.arcs[i][j].adj != 20000)
						G.arcnum--;
					G.arcs[i][j].adj = G.arcs[j][i].adj = 20000;
				}

			}
		}
		for (; num<NUM; num++)
		{
			strcpy(G.vex[num].sight, G.vex[num + 1].sight);
			strcpy(G.vex[num].description, G.vex[num + 1].description);
		}
		n--;
		printf("\n\t\t\t按任意键返回...");
		getchar();
		getchar();
		break;
		if (i == NUM)
		{
			printf("\n\n\t\t\t没有找到！");
			printf("\n\n\t\t\t按任意键返回...");
			getchar();
			getchar();
		}
		break;
	case '2':
		system("cls");
		narrate();
		printf("\n\n\t\t请输入您要删除城市的名称：");
		scanf("%s", name);
		for (i = 0; i<NUM; i++)
		{
			if (!strcmp(name, G.vex[i].sight))
			{
				num = i;
				for (j = 0; j<NUM; j++)
				{
					if (G.arcs[i][j].adj != 20000)
						G.arcnum--;
					G.arcs[i][j].adj = G.arcs[j][i].adj = 20000;
				}
			}
		}
		for (; num<NUM; num++)
		{
			strcpy(G.vex[num].sight, G.vex[num + 1].sight);
			strcpy(G.vex[num].description, G.vex[num + 1].description);
		}
		n--;
		printf("\n\t\t\t按任意键返回...");
		getchar();
		getchar();
		break;
		if (i == NUM)
		{
			printf("\n\n\t\t\t没有找到！");
			printf("\n\n\t\t\t按任意键返回...");
			getchar();
			getchar();
		}
		break;
	}
	return n;
}
char Changemenu()
{
	char c;
	int flag;
	do {
		flag = 1;
		system("cls");
		narrate();
		printf("\n\t\t\t								\n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t        1、修改城市信息           \n");
		printf("\t\t\t        2、修改航线信息           \n");
		printf("\t\t\t         e、返回                  \n");
		printf("\t\t\t	                                \n");
		printf("\t\t\t									\n");
		printf("\t\t\t\t请输入您的选择：");
		scanf("%c", &c);
		if (c == '1' || c == '2' || c == 'e')
			flag = 0;
	} while (flag);
	return c;
}
char Sightmenu()
{
	char c;
	int flag;
	do {
		flag = 1;
		system("cls");
		narrate();
		printf("\n\t\t\t								\n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t        1、修改城市名称           \n");
		printf("\t\t\t        2、修改城市描述           \n");
		printf("\t\t\t        e、返回                   \n");
		printf("\t\t\t                                  \n");
		printf("\t\t\t									\n");
		printf("\t\t\t\t请输入您的选择：");
		scanf("%c", &c);
		if (c == '1' || c == '2' || c == 'e')
			flag = 0;
	} while (flag);
	return c;
}
void Changesight()
{
	int a, b, length;
	char sight[100];
	char description[1000];
	char p;
	char q;
	int i;
	int num;
	p = Changemenu();
	switch (p)
	{
	case'1':
		system("cls");
		narrate();
		printf("\n\n\t\t请输入您要修改的城市编号：");
		scanf("%d", &num);
		for (i = 0; i < NUM; i++)
		{
			if (G.vex[i].number == num)
			{
				q = Sightmenu();
				if (q == '1')
				{
					printf("请输入修改后的城市名称：\n");
					scanf("%s", &sight);
					strcpy(G.vex[num].sight, sight);
					printf("\t\t\t\t修改成功！\n");
				}
				else if (q == '2')
				{
					printf("请输入修改后的城市信息：\n");
					scanf("%s", &description);
					strcpy(G.vex[num].description, description);
					printf("\t\t\t\t修改成功！\n");
				}
				else if (q == 'e')
					p = Changemenu();
			}
		}
		printf("\n\t\t按任意键返回...");
		getchar();
		getchar();
		break;
		if (i == NUM)
		{
			printf("\n\n\t\t\t\t没有找到！");
			printf("\n\n\t\t\t按任意键返回...");
			getchar();
			getchar();
		}
		break;
	case '2':
		printf("\t\t请输入道路一侧的城市序号：");
		scanf("%d", &a);
		printf("\t\t请输入道路另一侧的城市序号：");
		scanf("%d", &b);
		printf("\t\t请输入修改后的道路长度：");
		scanf("%d", &length);
		G.arcs[a][b].adj = G.arcs[b][a].adj = length;
		printf("\t\t\t\t修改成功！\n");
		printf("\t\t");
		getchar();
		system("PAUSE");
		break;
	}
}


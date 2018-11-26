#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>//malloc函数
#include <string.h>
#define O 50
#define Max 6000
#define c 10 
#define J 40
int sum = 0/*  城市个数*/, sum1 = 0/* 边数*/, sum2 = 0, sum3 = 0, sum4 = 0;//管理员数
const int N = 25;                           //航班数    //乘客数
int squre[N][N];
typedef struct relationship
{
	char origin[20];
	char terminal[20];
	int wight;
}R;
typedef struct manager
{
	char name[20];
	char password[20];
	struct manager*next;
}MN;
typedef struct cities
{
	char name[10];
	char information[2000];
}C;
typedef struct MAP
{
	C data[N];
	int n;
}M;
typedef struct city
{
	char cityname[15];
}CI;
typedef struct onecitymoney
{
	int Amoney;
	int Bmoney;
}OM;
typedef struct Flight
{
	char name[15];
	char plane[15];
	char time[15];
	int A;
	int B;
	int sum;
	CI city[c];
	int ticeketA;
	int ticeketB;
	OM dollar[c];
}FL;
typedef struct passenger
{
	char Fname[10];
	char name[10];
	char ID[20];
	int pay;
	char clas[10];
	int number;
}P;
typedef struct placename
{
	char name[20];
}PN;
FL H[J];
int login()
{
	int i = 0, sign = 0;
	FILE*fp;
	char name[10];
	MN*p;
	char password[20];
	char C;
	p = (MN*)malloc(sizeof(MN));
	printf("***********管理员登录************\n");
	printf("请输入用户名;");
	scanf("%s", name);
	printf("请输入密码:");
	scanf("%s", password);
	fp = fopen("manage.txt", "rb");
	sign = sum4;
	while (i < sign - 1)
	{
		fread(p, sizeof(MN), 1, fp);
		if (!strcmp(name, p->name))
		{

			getchar();
			if (!strcmp(p->password, password))
				return 1;
			else
			{
				printf("密码错误！请重新输入\n");
				free(p);
				system("pause");
				return 0;
			}
		}
		i++;
	}
	if (i == sign - 1)
	{
		printf("没有该用户！");
		free(p);
		system("pause");
		return 0;
	}
}
void registe()
{
	printf("***************管理员注册***************\n\n");
	FILE*fp;
	char a[20]; int i = 0;
	MN*p, *q;
	char C;
	p = (MN*)malloc(sizeof(MN));
	if (p == NULL) return;
	printf("请输入真实姓名：");
	scanf("%s", p->name);
	printf("请输入密码：");
	getchar();
	scanf("%s", p->password);
	printf("请再次输入密码:");
	scanf("%s", a);
	if (!strcmp(p->password, a))
	{
		printf("注册成功！\n");
		fp = fopen("manage.txt", "ab+");
		if (fp == NULL) printf("打开文件失败;");
		fwrite(p, sizeof(MN), 1, fp);//将这块空间写进文件里去
		rewind(fp);
		while (!feof(fp))
		{
			fread(p, sizeof(MN), 1, fp);
			sum4++;
		}//更新sum4的值
		getchar();
		fclose(fp);
	}
	else
	{
		printf("密码不一致!请重新输入\n");
		system("pause");
		getchar();//吃字符
		system("cls");
		printf("是否退出Y or N\n");
		scanf("%c", &C);
		if (C == 'Y')
		{
			free(p);
			return;
		}
		else
			registe();//重新调用函数
	}
}
void timesarch()
{
	int i = 0, j = 0, k, k2, add;
	char time[15];
	printf("*******时间查询******\n\n");
	printf("请输入时间(如 11:00--16:00)：\n");
	scanf("%s", time);
	while (i < sum2 - 1)
	{
		if (!strcmp(H[i].time, time))
		{
			printf("\n航班号：%s \n飞机型号：%s\n", H[i].name, H[i].plane);
			printf("剩余特等舱票数：%d\n", H[i].ticeketA);
			printf("剩余经济舱票数：%d\n", H[i].ticeketB);
			printf("时间：%s \n", H[i].time);
			printf("总经济舱票价：%d\n", H[i].B);
			printf("总特等舱票价：%d\n", H[i].A);
			printf("   ");
			while (j < H[i].sum)
			{
				if (j == H[i].sum - 1)
				{
					printf("%s\n", H[i].city[j].cityname);
				}
				else
				{
					printf("%s------>", H[i].city[j].cityname);
				}
				j++;
			}
			k = 0;
			printf("经济舱：");
			while (k < H[i].sum - 1)
			{
				add = 0;
				for (k2 = 0; k2 <= k; k2++)
				{
					add += H[i].dollar[k2].Bmoney;
				}
				printf("%-12d", add);
				k++;
			}
			printf("\n");
			printf("特等舱：");
			k = 0;
			while (k < H[i].sum - 1)
			{
				add = 0;
				for (k2 = 0; k2 <= k; k2++)
				{
					add += H[i].dollar[k2].Amoney;
				}
				printf("%-12d", add);
				k++;
			}
			break;
		}

		i++;
	}
	if (i == sum2 - 1) printf("该时间没有航班！");
}
void Fnumbersarch()
{
	int i = 0, j = 0, k, k2, add;
	char Fl[10];
	printf("*******航班查询******\n\n");
	printf("请输入航班：");
	scanf("%s", Fl);
	while (i < sum2 - 1)
	{
		if (!strcmp(H[i].name, Fl))
		{
			printf("\n航班号：%s \n飞机型号：%s\n", H[i].name, H[i].plane);
			printf("剩余特等舱票数：%d\n", H[i].ticeketA);
			printf("剩余经济舱票数：%d\n", H[i].ticeketB);
			printf("时间：%s \n", H[i].time);
			printf("总经济舱票价：%d\n", H[i].B);
			printf("总特等舱票价：%d\n", H[i].A);
			printf("   ");
			while (j < H[i].sum)
			{
				if (j == H[i].sum - 1)
				{
					printf("%s\n", H[i].city[j].cityname);
				}
				else
				{
					printf("%s------>", H[i].city[j].cityname);
				}
				j++;
			}
			k = 0;
			printf("经济舱：");
			while (k < H[i].sum - 1)
			{

				while (k < H[i].sum - 1)
				{
					add = 0;
					for (k2 = 0; k2 <= k; k2++)
					{
						add += H[i].dollar[k2].Bmoney;
					}
					printf("%-12d", add);
					k++;
				}
			}
			printf("\n");
			printf("特等舱：");
			k = 0;
			while (k < H[i].sum - 1)
			{
				while (k < H[i].sum - 1)
				{
					add = 0;
					for (k2 = 0; k2 <= k; k2++)
					{
						add += H[i].dollar[k2].Amoney;
					}
					printf("%-12d", add);
					k++;
				}
			}

			break;
		}
		i++;
	}
	if (i == sum2 - 1) printf("没有该航班！");
}
int q_travelrouteinformation()//最优路径
{

	int i, j, v, w, v0 = 0, min, next, j1, sin = 0, i1, sing = 0, v1;
	int path[N];
	int dist[N], s[N];
	char a[15], b[10], k, start[15];
	FILE*fp;
	C G[N];
	R n[O];
	PN name[20];
	if ((sum - 1) == 0 || (sum - 1) > N || sum1 - 1 == 0)
	{
		return 0;
	}

	else
	{
		fp = fopen("information.txt", "rb");
		fread(G, sizeof(C), sum - 1, fp);
		fclose(fp);

		fp = fopen("relationship_length.txt", "rb");
		fread(n, sizeof(R), sum1 - 1, fp);
		fclose(fp);
	}

	for (i = 0; i < sum - 1; i++)
	{
		s[i] = 0;
		dist[i] = squre[v0][i];
		if (dist[i] < Max) path[i] = v0;
		else path[i] = -1;
	}
	dist[v0] = 0; s[v0] = 1;
	for (i = 1; i < N; i++)
	{
		min = Max;
		for (w = 0; w < N; w++)
		{

			if (!s[w] && dist[w] < min)
			{
				v = w; min = dist[w];
			}

		}

		s[v] = 1;
		for (j = 0; j < N; j++)
		{
			if (!s[j] && (min + squre[v][j] < dist[j]))
			{
				dist[j] = min + squre[v][j];
				path[j] = v;
			}
		}
	}
	printf("请输入起点：");
	scanf("%s", start);
	printf("请输入终点站：");
	fflush(stdin);
	scanf("%s", a);
	getchar();
	for (i = 0; i < sum - 1; i++) if (!strcmp(a, G[i].name)) break;
	for (v1 = 0; v1 < sum - 1; v1++) if (!strcmp(start, G[v1].name)) break;
	if (i == sum - 1)
	{
		printf("没有相关城市！ \n");
		return 0;
	}
	else
	{
		if (dist[i] <= min && i != v0)
		{
			j1 = 0;
			printf("%s<---", G[i].name);
			strcpy(name[sin].name, G[i].name);
			sin++;
			next = path[i];
			while (next != v0)
			{
				printf("%s<---", G[next].name);
				strcpy(name[sin].name, G[next].name);
				sin++;
				next = path[next];
			}
			strcpy(name[sin].name, G[next].name);
			printf("%s  \n", G[v1].name);
			printf("最优惠价格只需%d元\n ", dist[i]);
			sin++;
			i1 = 0;
			while (i1 < sum2 - 1)
			{
				j = 0;
				sing = 0;
				while (j<H[i1].sum)
				{
					w = 0;
					while (w < sin)
					{
						if (!strcmp(H[i1].city[j].cityname, name[w].name))
						{
							sing++;
							break;
						}
						w++;
					}
					j++;
				}
				if (j == H[i1].sum&&sing == sin) break;
				i1++;
			}
			printf("您的航班为%s\n", H[i1].name);
			return 1;
		}
		else
		{
			if (i != v0) printf("V%d<---V%d:no path\n", i, v0);
			return 0;
		}
	}
	return 0;
}
int  place()
{
	int i = 0, j = 0, k = 0, sign = 0, k1, sign1, sign2, sign3, k2, add, add1;
	int j1, j2;
	char staraddress[10];
	char terminal[10];
	char startplace[15];
	printf("********获得航班号*******\n\n");
	printf("请输入起点：");
	scanf("%s", startplace);
	fflush(stdin);
	printf("请输入终点：");
	scanf("%s", terminal);
	while (i < sum2 - 1)
	{
		j = 0;
		sign2 = 0;
		while (j<H[i].sum)
		{

			if (!strcmp(H[i].city[j].cityname, startplace))
			{
				sign1 = 0; sign2++;
			}
			if (!strcmp(terminal, H[i].city[j].cityname))
			{
				sign1 = 1;
				sign2++;
			}
			if (sign1 == 1 && sign2 == 2)
			{
				sign = 1;
				sign3 = 1;
				printf("\n航班号：%s \n飞机型号：%s\n", H[i].name, H[i].plane);
				printf("剩余特等舱票数：%d\n", H[i].ticeketA);
				printf("剩余经济舱票数：%d\n", H[i].ticeketB);
				printf("时间：%s \n", H[i].time);
				printf("总经济舱票价：%d\n", H[i].B);
				printf("总特等舱票价：%d\n", H[i].A);
				k = 0;
				printf("   ");
				while (k< H[i].sum)
				{
					if (k == H[i].sum - 1)
					{
						printf("%s\n", H[i].city[k].cityname);
					}
					else
					{
						printf("%s------>", H[i].city[k].cityname);
					}
					k++;
				}
				k1 = 0;
				printf("经济舱：");
				while (k1 < H[i].sum - 1)
				{
					add = 0;
					for (k2 = 0; k2 <= k1; k2++)
					{
						add += H[i].dollar[k2].Bmoney;
					}
					printf("%-12d", add);
					k1++;
				}
				printf("\n");
				printf("特等舱：");
				k1 = 0;
				while (k1 < H[i].sum - 1)
				{
					add = 0;
					for (k2 = 0; k2 <= k1; k2++)
					{
						add += H[i].dollar[k2].Amoney;
					}
					printf("%-12d", add);
					k1++;
				}
				for (j1 = 0; j1< H[i].sum; j1++) if (!strcmp(terminal, H[i].city[j1].cityname))break;
				for (j2 = 0; j2< H[i].sum; j2++) if (!strcmp(startplace, H[i].city[j2].cityname))break;
				add = 0;
				add1 = 0;
				for (k1 = j2; k1 <j1 - j2; k1++)
				{
					add += H[i].dollar[k1].Bmoney;
					add1 += H[i].dollar[k1].Amoney;
				}
				printf("\n\n您应付：\n");
				printf("经济舱：%d元\n特等舱：%d元\n", add, add1);
				printf("\n\n");
				break;
			}
			j++;
		}
		i++;
	}
	if (sign3 != 1)
	{
		printf("没有查找到相关航线!!\n");
		return 0;
	}
	else return 1;
}
void q_flightinformation()
{
	int a;
	while (1)
	{
		system("cls");
		printf("\t**********************\n");
		printf("\t*1.查询您的航班      *\n");
		printf("\t*2.按时间查询航班    *\n");
		printf("\t*3.按航班号查询航班  *\n");
		printf("\t*4.返回              *\n");
		printf("\t**********************\n");
		printf("请输入操作代码：");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			place();
			system("pause");
			break;
		case 2:
			timesarch();
			system("pause");
			break;
		case 3:
			Fnumbersarch();
			system("pause");
			break;
		case 4:
			return;
			system("pause");
			break;
		}
	}
}
void  waitbook()
{
	P*p;
	int j1, j2, i, j;
	char a;
	FILE *fp;
	p = (P*)malloc(sizeof(P));
	j2 = 0;
	printf("您需要后补多少张票\n");
	scanf("%d", &j1);
	p->number = j1;
	while (j2 < j1)
	{
		i = 0;
		printf("请输入航班号：\n");
		scanf("%s", p->Fname);
		getchar();
		while (i < sum2 - 1)
		{
			if (!strcmp(p->Fname, H[i].name))
			{
				printf("\n航班号：%s \n飞机型号：%s\n", H[i].name, H[i].plane);
				printf("时间：%s \n", H[i].time);
				printf("特等舱余票：%d张\n", H[i].ticeketA);
				printf("经济舱余票：%d张\n", H[i].ticeketB);
				printf("经济舱票价：%d元\n", H[i].B);
				printf("特等舱票价：%d元\n", H[i].A);
				printf("路径：\n");
				j = 0;
				while (j < H[i].sum)
				{
					if (j == H[i].sum - 1)
					{
						printf("%s\n", H[i].city[j].cityname);
					}
					else
					{
						printf("%s-->", H[i].city[j].cityname);
					}
					j++;
				}
				break;
			}
			i++;
		}
		printf("请输入名字：\n");
		scanf("%s", p->name);
		getchar();
		printf("请输入身份证号码：\n");
		scanf("%s", p->ID);
		getchar();
		printf("经济舱 or 特等舱:\n");
		scanf("%s", p->clas);
		printf("实付钱:\n");
		scanf("%d", &p->pay);
		printf("是否存档  Y or N：");
		getchar();
		scanf("%c", &a);
		getchar();
		if (a == 'Y')
		{
			fp = fopen("B_allpassenger.txt", "ab+");
			fwrite(p, sizeof(P), 1, fp);
			fclose(fp);
			printf("存档成功！");

			getchar();
		}
		j2++;
	}
	free(p);
}
void M_book()
{
	FILE*fp;
	int i, j, k, o, s3, j1, j2, sum5, select;
	char a;
	char placee[10], flight[10], clas[10];
	P*p, *p1;
	FL*q, *q1;
	p = (P*)malloc(sizeof(P));
	q = (FL*)malloc(sizeof(FL));
	q1 = (FL*)malloc(sizeof(FL));
	p1 = (P*)malloc(sizeof(P));
	if (p == NULL) return;
	while (1)
	{
		i = 0;
		j = 0;
		k = 0;
		o = 0;
		s3 = 0;
		system("cls");
		printf("1.最优惠航班推荐\n2.普通航班查询\n");
		scanf("%d", &select);
		if (select == 1)
		{
			if (!q_travelrouteinformation())//最优路劲无路线
			{
				printf("无法订票！");
				return;
			}
		}
		else if (select == 2)
		{
			if (!place())
			{
				printf("无法订票！");
				return;
			}
		}
		printf("***********欢迎使用订票服务**********\n");
		printf("在订票之前您须知航班号，获得航班号请看上面信息或者在主菜单中选择(4.)查询\n");
		printf("是否继续： Y or N\n ");
		getchar();
		scanf("%c", &a);
		if (a == 'Y')
		{
			printf("请输入航班号\n");
			fflush(stdin);
			scanf("%s", p->Fname);
			getchar();

			while (i < sum2 - 1)
			{
				if (!strcmp(p->Fname, H[i].name))
				{
					if (H[i].ticeketA == 0 && H[i].ticeketB == 0)
					{
						printf("经济舱的票和特等舱的票买完了^_^");
						printf("如果您想排队等候请按1\n退出请按2:\n");
						scanf("%d", &select);
						if (select == 1)
						{
							waitbook();
							printf("排队候补成功！");
							return;
						}
						else return;
					}
					if (H[i].ticeketA == 0 && H[i].ticeketB != 0)
					{
						printf("特等舱的票卖完了^_^ 只能购买经济舱，经济舱余票：%d\n", H[i].ticeketB);
						printf("如果您想乘特等舱请按1排队等候\n如果您要继续购票请按2继续购票");
						scanf("%d", &select);
						if (select == 1)
						{
							waitbook();
							printf("排队候补成功！");
							return;
						}
						else;
					}
					if (H[i].ticeketB == 0 && H[i].ticeketA != 0)
					{
						printf("经济舱的票卖完了^_^ 只能购买特等舱，特等舱余票：%d张\n", H[i].ticeketA);
						printf("如果您想乘经济舱请按1排队等候：\n如果您要继续购票请按2继续购票：\n");
						scanf("%d", &select);
						if (select == 1)
						{
							waitbook();
							printf("排队候补成功！");
							return;
						}
						else;
					}
					printf("请确认您的航班信息\n");
					printf("\n航班号：%s \n飞机型号：%s\n", H[i].name, H[i].plane);
					printf("时间：%s \n", H[i].time);
					printf("特等舱余票：%d张\n", H[i].ticeketA);
					printf("经济舱余票：%d张\n", H[i].ticeketB);
					printf("经济舱票价：%d元\n", H[i].B);
					printf("特等舱票价：%d元\n", H[i].A);
					printf("路径：\n");
					while (j < H[i].sum)
					{
						if (j == H[i].sum - 1)
						{
							printf("%s\n", H[i].city[j].cityname);
						}
						else
						{
							printf("%s-->", H[i].city[j].cityname);
						}
						j++;
					}
					break;
				}
				i++;
			}
			printf("是否继续？ Y or N\n");
			fflush(stdin);
			scanf("%c", &a);
			if (a == 'Y')
			{
				j2 = 0;
				printf("您需要订多少张票\n");
				scanf("%d", &j1);
				while (j1 > H[i].ticeketA &&j1 > H[i].ticeketB)
				{
					printf("订票数大于余票数\n");
					printf("特等舱余票：%d张   经济舱余票：%d张\n", H[i].ticeketA, H[i].ticeketB);
					printf("重新输入订票数量按1\n排队候补请按2\n");
					scanf("%d", &select);
					if (select == 2)
					{
						waitbook();
						printf("排队候补成功！");
						return;
					}
					else
					{
						printf("您需要订多少张票:\n");
						scanf("%d", &j1);
					}
				}
				while (j2 < j1)
				{
					p->number = 1;
					printf("请输入名字：\n");
					scanf("%s", p->name);
					getchar();
					printf("请输入身份证号码：\n");
					scanf("%s", p->ID);
					getchar();
					printf("经济舱 or 特等舱:\n");
					scanf("%s", p->clas);
					printf("实付钱:\n");
					scanf("%d", &p->pay);
					printf("是否存档  Y or N：");
					getchar();
					scanf("%c", &a);
					if (a == 'Y')
					{
						fp = fopen("allpassenger.txt", "ab+");
						if (fp == NULL) return;
						fwrite(p, sizeof(P), 1, fp);
						fclose(fp);
						fp = fopen("allpassenger.txt", "rb");
						while (!feof(fp))
						{
							fread(p, sizeof(P), 1, fp);
							s3++;
						}
						sum3 = s3;

						fp = fopen("flight_information.txt", "rb+");
						while (o < sum2 - 1)
						{
							fread(q, sizeof(FL), 1, fp);
							i = 0;
							while (i < sum2 - 1)
							{
								if (!strcmp(H[i].name, p->Fname))
								{
									break;
								}
								i++;
							}

							if (!strcmp(q->name, p->Fname))
							{
								if (!strcmp(p->clas, "经济舱"))
								{
									q1->ticeketB = H[i].ticeketB - p->number;
									q1->ticeketA = H[i].ticeketA;
									getchar();
								}
								else if (!strcmp(p->clas, "特等舱"))
								{
									q1->ticeketA = H[i].ticeketA - p->number;
									q1->ticeketB = H[i].ticeketB;
								}
								q1->A = H[i].A;
								q1->B = H[i].B;
								k = 0;
								while (k < H[i].sum)
								{
									strcpy(q1->city[k].cityname, H[i].city[k].cityname);
									k++;
								}
								strcpy(q1->name, p->Fname);
								strcpy(q1->plane, H[i].plane);
								q1->sum = H[i].sum;
								strcpy(q1->time, H[i].time);
								k = 0;
								while (k<H[i].sum - 1)
								{
									q1->dollar[k].Amoney = H[i].dollar[k].Amoney;
									q1->dollar[k].Bmoney = H[i].dollar[k].Bmoney;
									k++;
								}
								fseek(fp, -sizeof(FL), SEEK_CUR);
								fwrite(q1, sizeof(FL), 1, fp);
								rewind(fp);
								fread(H, sizeof(FL), sum2 - 1, fp);
								fclose(fp);
								break;
							}
							o++;
						}
						fclose(fp);

						fp = fopen("allpassenger.txt", "rb");
						sum5 = 0;
						while (!feof(fp))
						{
							fread(p1, sizeof(P), 1, fp);
							if (!strcmp(p1->Fname, p->Fname)) sum5++;
						}
						if (sum5 - 1>10 && sum5 - 1 == 10)
							printf("您的座位号：%s0%d\n", p->Fname, sum5 - 1);
						else
							printf("您的座位号：%s00%d", p->Fname, sum5 - 1);
						printf("存档成功！\n");
					}
					else;
					j2++;
				}
			}
		}
		else return;
		getchar();
		printf("是否继续订票：\n");
		scanf("%c", &a);
		if (a == 'Y');
		else
		{
			free(p);
			free(q);
			free(q1);
			break;
		}
	}
}
void M_backticket()
{
	char ID[20];
	char name[10];

	FILE*fp, *fp1, *fp2, *fp3;
	P*p, *q;
	char a;
	int i, o;
	p = (P*)malloc(sizeof(P));
	q = (P*)malloc(sizeof(P));
	fp = fopen("allpassenger.txt", "rb+");
	printf("*********欢迎使用退票服务*********\n");
	printf("请输入您的身份证号码：\n");
	scanf("%s", ID);
	while (!feof(fp))
	{
		fread(p, sizeof(P), 1, fp);
		if (!strcmp(ID, p->ID)) break;
	}
	if (feof(fp))
	{
		printf("没有该乘客！\n");
		return;
	}
	printf("请确认您的信息");
	printf("名字：%s\n", p->name);
	printf("身份证号码：%s\n", p->ID);
	printf("航班号：%s\n", p->Fname);
	printf("舱位等级：%s\n", p->clas);
	printf("票数：%d\n", p->number);
	printf("支付：%d\n", p->pay);
	printf("您确定要退票吗？Y or N\n");
	getchar();
	scanf("%c", &a);
	if (a == 'Y')
	{
		i = 0;
		for (i = 0; i < sum2 - 1; i++)if (!strcmp(H[i].name, p->Fname))	break;
		if (!strcmp(p->clas, "经济舱"))
		{
			printf("11\n");
			if (H[i].ticeketB == 0)
			{
				fp1 = fopen("B_allpassenger.txt", "rb+");
				while (!feof(fp1))
				{
					fread(q, sizeof(P), 1, fp1);
					if (!strcmp(q->Fname, p->Fname))
					{
						fp2 = fopen("allpassenger.txt", "ab+");
						fwrite(q, sizeof(P), 1, fp2);
						fclose(fp2);
						*q->clas = '0';
						*q->Fname = '0';
						*q->ID = '0';
						*q->name = '0';
						q->number = 0;
						q->pay = 0;
						fseek(fp1, -sizeof(P), SEEK_CUR);
						fwrite(q, sizeof(P), 1, fp1);
						fclose(fp1);
						break;
					}
				}
				if (feof(fp1))
				{
					H[i].ticeketB++;
					printf("%d\n", H[i].ticeketB);
					fp3 = fopen("flight_information.txt", "wb");
					fclose(fp3);
					fp3 = fopen("flight_information.txt", "ab+");
					fwrite(H, sizeof(FL), sum2 - 1, fp3);
					fclose(fp3);
				}
			}
			else
			{
				H[i].ticeketB++;
				printf("%d\n", H[i].ticeketB);
				fp3 = fopen("flight_information.txt", "wb");
				fclose(fp3);
				fp3 = fopen("flight_information.txt", "ab+");
				fwrite(H, sizeof(FL), sum2 - 1, fp3);
				fclose(fp3);
			}
		}
		if (!strcmp(p->clas, "特等舱"))
		{
			printf("11\n");
			if (H[i].ticeketA == 0)
			{
				fp1 = fopen("B_allpassenger.txt", "rb");
				while (!feof(fp1))
				{
					fread(q, sizeof(P), 1, fp1);
					if (!strcmp(q->Fname, p->Fname))
					{
						fp2 = fopen("allpassenger.txt", "ab+");
						fwrite(q, sizeof(P), 1, fp2);
						fclose(fp2);
						*q->clas = '0';
						*q->Fname = '0';
						*q->ID = '0';
						*q->name = '0';
						q->number = 0;
						q->pay = 0;
						fseek(fp1, -sizeof(P), SEEK_CUR);
						fwrite(q, sizeof(P), 1, fp1);
						break;
					}
				}
				if (feof(fp1))
				{
					H[i].ticeketA++;
					printf("%d\n", H[i].ticeketA);
					fp3 = fopen("flight_information.txt", "wb");
					fclose(fp3);
					fp3 = fopen("flight_information.txt", "ab+");
					fwrite(H, sizeof(FL), sum2 - 1, fp3);
					fclose(fp3);


				}
			}
			else
			{
				H[i].ticeketA++;
				printf("%d\n", H[i].ticeketA);
				fp3 = fopen("flight_information.txt", "wb");
				fclose(fp3);
				fp3 = fopen("flight_information.txt", "ab+");
				fwrite(H, sizeof(FL), sum2 - 1, fp3);
				fclose(fp3);
			}
		}
		*p->clas = '0';
		*p->Fname = '0';
		*p->ID = '0';
		*p->name = '0';
		p->number = 0;
		p->pay = 0;
		fseek(fp, -sizeof(P), SEEK_CUR);
		fwrite(p, sizeof(P), 1, fp);
		fclose(fp);
	}
	else return;
}
void PAsarch(char a[], int i)
{
	FILE*fp;
	P*p;
	p = (P*)malloc(sizeof(P));
	fp = fopen("allpassenger.txt", "rb");
	if (i == 0)
	{
		printf("*********订票客户身份证查询*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->ID)) break;
		}
	}
	else if (i == 1)
	{
		printf("*********订票客户名字查询*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->name)) break;
		}
	}
	if (feof(fp))
	{
		printf("没有该乘客！\n");
		return;
	}
	printf("名字：%s\n", p->name);
	printf("身份证号码：%s\n", p->ID);
	printf("航班号：%s\n", p->Fname);
	printf("舱位等级：%s\n", p->clas);
	printf("票数：%d\n", p->number);
	printf("支付：%d\n", p->pay);
}
void PBsarch(char a[], int i)
{
	FILE*fp;
	P*p;
	p = (P*)malloc(sizeof(P));
	fp = fopen("B_allpassenger.txt", "rb");
	if (i == 0)
	{
		printf("*********排队客户身份证查询*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->ID)) break;
		}
	}
	else if (i == 1)
	{
		printf("*********排队客户名字查询*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->name)) break;
		}
	}
	if (feof(fp))
	{
		printf("没有该乘客！\n");
		return;
	}
	printf("名字：%s\n", p->name);
	printf("身份证号码：%s\n", p->ID);
	printf("航班号：%s\n", p->Fname);
	printf("舱位等级：%s\n", p->clas);
	printf("票数：%d\n", p->number);
	printf("支付：%d\n", p->pay);
}
void Psarch()
{
	int a;
	char Person[20];

	while (1)
	{
		system("cls");
		printf("\t*********************************\n");
		printf("\t* 1.订票客户的身份证号码查询    *\n");
		printf("\t* 2.订票客户的名字查询          *\n");
		printf("\t* 3.排队客户的身份证号码查询    *\n");
		printf("\t* 4.排队客户的名字查询          *\n");
		printf("\t* 5.返回                        *\n");
		printf("\t*********************************\n");
		printf("请输入操作代码：");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			printf("请输入您的身份证号码：\n");
			scanf("%s", Person);
			PAsarch(Person, 0);
			system("pause");
			break;
		case 2:
			printf("请输入您的名字：\n");
			scanf("%s", Person);
			PAsarch(Person, 1);
			system("pause");
			break;
		case 3:
			printf("请输入您的身份证号码：\n");
			scanf("%s", Person);
			PBsarch(Person, 0);
			system("pause");
			break;
		case 4:
			printf("请输入您的名字：\n");
			scanf("%s", Person);
			PBsarch(Person, 1);
			system("pause");
			break;
		case 5:
			return;
			system("pause");
			break;
		}
	}
}
void M_cities_information()
{
	FILE*fp;
	C city;
	char name[20];
	fp = fopen("information.txt", "rb");
	printf("请输入城市名称\n");
	scanf("%s", name);
	while (!feof(fp))
	{
		fread(&city, sizeof(C), 1, fp);
		if (!strcmp(name, city.name))break;
	}
	printf("城市简介：\n");
	printf("%s\n", city.information);
	if (feof(fp))
	{
		printf("没有该城市！");
		getchar();
		return;
	}
}
void M_query()
{

	int a;
	while (1)
	{
		system("cls");
		printf("\t*********************************\n");
		printf("\t* 1.订票客户和排队客户详细资料  *\n");
		printf("\t* 2.了解航班信息                *\n");
		printf("\t* 3.最优惠航班推荐              *\n");
		printf("\t* 4.查询城市信息                *\n");
		printf("\t* 5.返回                        *\n");
		printf("\t*********************************\n");
		printf("请输入操作代码：");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			Psarch();//1.订票客户详细资料
			system("pause");
			break;
		case 2:
			q_flightinformation();//1.所有航班信息
			system("pause");
			break;
		case 3:
			q_travelrouteinformation();//1.旅行线路   
			system("pause");
			break;
		case 4:
			M_cities_information();
			system("pause");
			break;
		case 5:
			return;
			system("pause");
			break;
		}
	}

}
int  M_edit()
{
	int a;
	char password[15];
	while (1)
	{
		system("cls");
		printf("\t*****************\n");
		printf("\t* 1.注册        *\n");
		printf("\t* 2.登录        *\n");
		printf("\t* 3.返回        *\n");
		printf("\t*****************\n");
		printf("请输入操作代码：");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			printf("请输入注册指令:");
			scanf("%s", password);
			if (!strcmp(password, "123456"))
				registe();
			else
			{
				printf("指令错误！\n");
				system("pause");
				return 0;
			}
			system("pause");
			break;
		case 2:


			return login();
			break;

		case 3:
			return 0;
			system("pause");
			break;
		}
	}
}
void creatsqure()
{

	int j = 0, i, k;
	FILE*fp;
	C*p;
	R*q;
	C a[N];
	R n[O];
	p = (C*)malloc(sizeof(C));
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			squre[i][j] = 0;
	}
	fp = fopen("information.txt", "rb");
	if (fp == NULL) return;
	while (!feof(fp))
	{
		fread(p, sizeof(C), 1, fp);
		sum++;
	}
	fclose(fp);
	fp = fopen("information.txt", "rb");
	fread(a, sizeof(C), sum - 1, fp);
	fclose(fp);
	j = 0;
	fp = fopen("relationship_length.txt", "rb");
	q = (R*)malloc(sizeof(R));
	while (!feof(fp))
	{
		fread(q, sizeof(R), 1, fp);
		sum1++;
	}
	fclose(fp);

	fp = fopen("relationship_length.txt", "rb");
	fread(n, sizeof(R), sum1 - 1, fp);
	fclose(fp);
	i = 0;
	for (i = 0; i < sum1 - 1; i++)
	{
		for (j = 0; j < sum - 1; j++)
		{
			if (!strcmp(n[i].origin, a[j].name))
				break;
		}

		for (k = 0; k < sum - 1; k++)
		{
			if (!strcmp(n[i].terminal, a[k].name)) break;
		}
		squre[j][k] = n[i].wight;
	}
	for (j = 0; j < N; j++)
	{

		for (i = 0; i < N; i++)
		{
			if (squre[j][i] == 0) squre[j][i] = Max;
		}
	}
	free(p);
	free(q);
}
void M_creatmap(M*map)
{
	C a[N];
	int i = 0, j = 0, s, s1, wight;
	int  b;
	FILE*fp;
	C*p;
	R*q, *q1;
	char k;
	p = (C*)malloc(sizeof(C));
	printf("添加城市个数:");
	if (sum - 1 > N)
	{
		printf("城市数目达到上限！无法添加");
		getchar();
		return;
	}
	if (sum1 - 1 > O)
	{
		printf("城市关系达到上限！无法添加");
		getchar();
		return;
	}
	scanf("%d", &map->n);
	while (i < map->n)
	{
		printf("请输入城市名称：");
		scanf("%s", map->data[i].name);
		printf("请输入城市信息：");
		scanf("%s", map->data[i].information);
		i++;
	}
	fp = fopen("information.txt", "ab+");
	if (fp == NULL)
	{
		printf("打开文件失败！");
		return;
	}
	fwrite(map->data, sizeof(C), i, fp);
	fclose(fp);
	printf("是否继续：（1.是    2.否）");
	scanf("%d", &b);
	if (b == 1)
	{
		printf("*******请添加城市之间的关系********\n");
		q = (R*)malloc(sizeof(R)); if (q == NULL) return;
		while (1)
		{
			s = 0;
			s1 = 0;
			printf("起始地:");
			fflush(stdin);
			scanf("%s", q->origin);
			getchar();
			printf("是否继续？Y or N");
			scanf("%c", &k);
			if (k == 'N')
				return;
			getchar();
			printf("终点：");
			scanf("%s", q->terminal);
			getchar();
			printf("是否继续？ Y or N");
			scanf("%c", &k);
			if (k == 'N')
				return;
			printf("权值：");
			scanf("%d", &q->wight);
			getchar();
			fp = fopen("relationship_length.txt", "ab+");
			if (fp == NULL)
			{
				printf("打开文件失败！");
				return;
			}
			fwrite(q, sizeof(R), 1, fp);
			fclose(fp);
			printf("是否存档？ Y or N");
			scanf("%c", &k);
			if (k == 'N') break;
			else(k == 'Y');
			{
				fp = fopen("relationship_length.txt", "rb");
				if (fp == NULL)
				{
					printf("打开文件失败！");
					return;
				}
				q1 = (R*)malloc(sizeof(R));
				while (!feof(fp))
				{
					fread(q1, sizeof(R), 1, fp);
					s1++;
				}
				sum1 = s1;
				fclose(fp);

				fp = fopen("information.txt", "rb");
				if (fp == NULL)
				{
					printf("打开文件失败！");
					return;
				}
				while (!feof(fp))
				{
					fread(map->data, sizeof(C), 1, fp);
					s++;
				}
				sum = s;
				fclose(fp);
				fp = fopen("information.txt", "rb");
				fread(a, sizeof(C), sum - 1, fp);
				for (j = 0; j < s - 1; j++) if (!strcmp(q->origin, a[j].name)) break;
				for (i = 0; i < s - 1; i++) if (!strcmp(q->terminal, a[i].name)) break;
				getchar();
				squre[j][i] = q->wight;
			}
			printf("是否继续添加？Y or N\n");
			scanf("%c", &k);
			if (k == 'N')
			{
				free(p);
				free(q);
				free(q1);
				break;
			}
		}
	}
	else if (b == 2) return;
}
void edit_flight()
{
	FL*p, q;
	char k;
	FILE*fp;
	int s2, s3;

	while (1)
	{
		int i = 0;
		s2 = 0;
		p = (FL*)malloc(sizeof(FL));//
		printf("请输入这条航线城市个数:");
		scanf("%d", &p->sum);
		getchar();
		printf("请输入航班名称：");
		scanf("%s", p->name);
		getchar();
		printf("请输入航班时间：");
		scanf("%s", p->time);
		getchar();
		printf("请输入经济舱票数：");
		scanf("%d", &p->ticeketB);
		printf("请输入特等舱票数：");
		scanf("%d", &p->ticeketA);
		printf("请输入特等舱总票价:");
		scanf("%d", &p->A);
		printf("请输入经济舱票总价:");
		scanf("%d", &p->B);
		getchar();
		printf("请输入飞机型号:");
		scanf("%s", p->plane);
		getchar();
		while (i < p->sum)
		{
			printf("请输入城市名称：");
			scanf("%s", p->city[i].cityname);
			getchar();
			i++;
		}
		i = 0;
		while (i < p->sum - 1)
		{
			printf("请输入%s到%s的经济舱票价：", p->city[i].cityname, p->city[i + 1].cityname);
			scanf("%d", &p->dollar[i].Bmoney);
			printf("请输入%s到%s的特等舱票价：", p->city[i].cityname, p->city[i + 1].cityname);
			scanf("%d", &p->dollar[i].Amoney);
			i++;
		}
		getchar();
		printf("是否存档：Y or N\n");
		scanf("%c", &k);
		if (k == 'Y')
		{
			fp = fopen("flight_information.txt", "ab+");
			fwrite(p, sizeof(FL), 1, fp);
			fclose(fp);
			fp = fopen("flight_information.txt", "rb");
			while (!feof(fp))
			{
				fread(&q, sizeof(FL), 1, fp);
				s2++;
			}
			sum2 = s2;
			fclose(fp);
			fp = fopen("flight_information.txt", "rb");
			fread(H, sizeof(FL), sum2 - 1, fp);
			fclose(fp);
		}
		getchar();
		printf("是否继续添加? Y or N\n");
		scanf("%c", &k);
		if (k == 'N')
		{
			free(p);
			break;
		}
	}
}
void modification()
{
	int a;
	char flight[10];
	char time[15];
	int A, B, i;
	FILE*fp;
	FL p, q;
	int k;
	while (1)
	{
		system("cls");
		printf("\t******************\n");
		printf("\t* 1.修改航班号   *\n");
		printf("\t* 2.修改航班时间 *\n");
		printf("\t* 3.修改票数     *\n");
		printf("\t* 4.返回         *\n");
		printf("\t******************\n");
		printf("请输入操作代码：");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			printf("请输入修改的经济舱票数：");
			scanf("%d", &B);
			printf("请输入航班号：\n");
			scanf("%s", flight);
			printf("请输入修改的特等舱舱票数：");
			scanf("%d", &A);
			fp = fopen("flight_information.txt", "rb+");
			if (fp == NULL) return;
			while (!feof(fp))
			{
				fread(&p, sizeof(FL), 1, fp);

				if (!strcmp(p.name, flight))
				{
					printf("000");
					break;
				}

			}

			q.ticeketA = A;
			q.ticeketB = B;
			strcpy(q.name, p.name);
			strcpy(q.plane, p.plane);
			q.A = p.A;
			q.B = p.B;
			k = 0;
			while (k < p.sum)
			{
				strcpy(q.city[k].cityname, p.city[k].cityname);
				k++;
			}
			q.sum = p.sum;
			strcpy(q.time, p.time);
			k = 0;
			while (k<p.sum - 1)
			{
				q.dollar[k].Amoney = p.dollar[k].Amoney;
				q.dollar[k].Bmoney = p.dollar[k].Bmoney;
				k++;
			}
			fseek(fp, -sizeof(FL), SEEK_CUR);
			fwrite(&q, sizeof(FL), 1, fp);
			rewind(fp);
			fread(H, sizeof(FL), sum2 - 1, fp);
			fclose(fp);
			system("pause");
			break;
		case 4:
			return;
			break;
		}
	}
}
void operation(M*p)
{
	int a;
	FILE*fp;
	char k;
	while (1)
	{
		system("cls");
		printf("\t*****************\n");
		printf("\t* 1.创建地图    *\n");
		printf("\t* 2.创建航线    *\n");
		printf("\t* 3.格式化地图  *\n");
		printf("\t* 4.格式化航线  *\n");
		printf("\t* 5.修改航线    *\n");
		printf("\t* 6.返回        *\n");
		printf("\t*****************\n");
		printf("请输入操作代码：");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			M_creatmap(p);
			system("pause");
			break;
		case 2:
			edit_flight();
			system("pause");
			break;
		case 3:
			printf("您确定要格式化吗？Y or N");
			scanf("%c", &k);
			if (k == 'Y')fp = fopen("information.txt", "wb");
			else return;
			system("pause");
			break;
		case 4:
			printf("您确定要格式化吗？Y or N");
			getchar();
			scanf("%c", &k);
			if (k == 'Y')fp = fopen("flight_information.txt", "wb");

			else return;
			system("pause");
			break;
		case 5:
			modification();
			system("pause");
			break;
		case 6:
			return;
			system("pause");
			break;
		}
	}
}
void Menu(M *p)
{
	int i;
	system("cls");
	int a;
	printf("\t********************\n");
	printf("\t* 1.订票业务       *\n");
	printf("\t* 2.退票业务       *\n");
	printf("\t* 3.排队候补       *\n");
	printf("\t* 4.查询           *\n");
	printf("\t* 5.管理员操作     *\n");
	printf("\t* 0.退出           *\n");
	printf("\t********************\n");
	printf("请输入操作代码：");
	scanf("%d", &a);
	switch (a)
	{
	case 1:

		M_book();//book
		system("pause");
		break;
	case 2://退票
		M_backticket();
		system("pause");
		break;
	case 3:
		waitbook();
		break;
	case 4://查询
		M_query();
		system("pause");
		break;
	case 5://编辑航班信息  
		i = M_edit();
		if (i == 1) operation(p);
		else return;
		system("pause");
		break;
	case 0:
		exit(0);
		break;
	}
}
void open2()
{
	FILE *fp;
	FL*p;
	p = (FL*)malloc(sizeof(FL));
	if (p == NULL) return;
	fp = fopen("flight_information.txt", "rb");
	if (fp == NULL)
	{
		printf("打开文件失败！");
		return;
	}
	while (!feof(fp))
	{                                                      //初始化sum2  
		fread(p, sizeof(FL), 1, fp);
		sum2++;
	}
	fclose(fp);
	fp = fopen("flight_information.txt", "rb");
	fread(H, sizeof(FL), sum2 - 1, fp);
	fclose(fp);
	free(p);
}
void open3()
{
	FILE *fp;
	P*p;
	p = (P*)malloc(sizeof(P));
	if (p == NULL) return;
	fp = fopen("allpassenger.txt", "rb");
	if (fp == NULL)
	{
		printf("打开文件失败！");
		return;
	}
	while (!feof(fp))
	{
		fread(p, sizeof(P), 1, fp);
		sum3++;
	}
	fclose(fp);
	free(p);
}
void open4()
{
	FILE*fp;
	MN*p;
	p = (MN*)malloc(sizeof(MN));
	fp = fopen("manage.txt", "rb");
	while (!feof(fp))
	{
		fread(p, sizeof(MN), 1, fp);
		sum4++;
	}

	fclose(fp);
}
int main()
{
	int i, j;
	creatsqure();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++) printf("%5d", squre[i][j]);
		printf("\n");
	}

	M map; printf("%d", sum1); getchar();

	open2();
	open3();
	open4();

	while (1)
	{
		Menu(&map);
	}
}
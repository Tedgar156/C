#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>//malloc����
#include <string.h>
#define O 50
#define Max 6000
#define c 10 
#define J 40
int sum = 0/*  ���и���*/, sum1 = 0/* ����*/, sum2 = 0, sum3 = 0, sum4 = 0;//����Ա��
const int N = 25;                           //������    //�˿���
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
	printf("***********����Ա��¼************\n");
	printf("�������û���;");
	scanf("%s", name);
	printf("����������:");
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
				printf("�����������������\n");
				free(p);
				system("pause");
				return 0;
			}
		}
		i++;
	}
	if (i == sign - 1)
	{
		printf("û�и��û���");
		free(p);
		system("pause");
		return 0;
	}
}
void registe()
{
	printf("***************����Աע��***************\n\n");
	FILE*fp;
	char a[20]; int i = 0;
	MN*p, *q;
	char C;
	p = (MN*)malloc(sizeof(MN));
	if (p == NULL) return;
	printf("��������ʵ������");
	scanf("%s", p->name);
	printf("���������룺");
	getchar();
	scanf("%s", p->password);
	printf("���ٴ���������:");
	scanf("%s", a);
	if (!strcmp(p->password, a))
	{
		printf("ע��ɹ���\n");
		fp = fopen("manage.txt", "ab+");
		if (fp == NULL) printf("���ļ�ʧ��;");
		fwrite(p, sizeof(MN), 1, fp);//�����ռ�д���ļ���ȥ
		rewind(fp);
		while (!feof(fp))
		{
			fread(p, sizeof(MN), 1, fp);
			sum4++;
		}//����sum4��ֵ
		getchar();
		fclose(fp);
	}
	else
	{
		printf("���벻һ��!����������\n");
		system("pause");
		getchar();//���ַ�
		system("cls");
		printf("�Ƿ��˳�Y or N\n");
		scanf("%c", &C);
		if (C == 'Y')
		{
			free(p);
			return;
		}
		else
			registe();//���µ��ú���
	}
}
void timesarch()
{
	int i = 0, j = 0, k, k2, add;
	char time[15];
	printf("*******ʱ���ѯ******\n\n");
	printf("������ʱ��(�� 11:00--16:00)��\n");
	scanf("%s", time);
	while (i < sum2 - 1)
	{
		if (!strcmp(H[i].time, time))
		{
			printf("\n����ţ�%s \n�ɻ��ͺţ�%s\n", H[i].name, H[i].plane);
			printf("ʣ���صȲ�Ʊ����%d\n", H[i].ticeketA);
			printf("ʣ�ྭ�ò�Ʊ����%d\n", H[i].ticeketB);
			printf("ʱ�䣺%s \n", H[i].time);
			printf("�ܾ��ò�Ʊ�ۣ�%d\n", H[i].B);
			printf("���صȲ�Ʊ�ۣ�%d\n", H[i].A);
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
			printf("���òգ�");
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
			printf("�صȲգ�");
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
	if (i == sum2 - 1) printf("��ʱ��û�к��࣡");
}
void Fnumbersarch()
{
	int i = 0, j = 0, k, k2, add;
	char Fl[10];
	printf("*******�����ѯ******\n\n");
	printf("�����뺽�ࣺ");
	scanf("%s", Fl);
	while (i < sum2 - 1)
	{
		if (!strcmp(H[i].name, Fl))
		{
			printf("\n����ţ�%s \n�ɻ��ͺţ�%s\n", H[i].name, H[i].plane);
			printf("ʣ���صȲ�Ʊ����%d\n", H[i].ticeketA);
			printf("ʣ�ྭ�ò�Ʊ����%d\n", H[i].ticeketB);
			printf("ʱ�䣺%s \n", H[i].time);
			printf("�ܾ��ò�Ʊ�ۣ�%d\n", H[i].B);
			printf("���صȲ�Ʊ�ۣ�%d\n", H[i].A);
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
			printf("���òգ�");
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
			printf("�صȲգ�");
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
	if (i == sum2 - 1) printf("û�иú��࣡");
}
int q_travelrouteinformation()//����·��
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
	printf("��������㣺");
	scanf("%s", start);
	printf("�������յ�վ��");
	fflush(stdin);
	scanf("%s", a);
	getchar();
	for (i = 0; i < sum - 1; i++) if (!strcmp(a, G[i].name)) break;
	for (v1 = 0; v1 < sum - 1; v1++) if (!strcmp(start, G[v1].name)) break;
	if (i == sum - 1)
	{
		printf("û����س��У� \n");
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
			printf("���Żݼ۸�ֻ��%dԪ\n ", dist[i]);
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
			printf("���ĺ���Ϊ%s\n", H[i1].name);
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
	printf("********��ú����*******\n\n");
	printf("��������㣺");
	scanf("%s", startplace);
	fflush(stdin);
	printf("�������յ㣺");
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
				printf("\n����ţ�%s \n�ɻ��ͺţ�%s\n", H[i].name, H[i].plane);
				printf("ʣ���صȲ�Ʊ����%d\n", H[i].ticeketA);
				printf("ʣ�ྭ�ò�Ʊ����%d\n", H[i].ticeketB);
				printf("ʱ�䣺%s \n", H[i].time);
				printf("�ܾ��ò�Ʊ�ۣ�%d\n", H[i].B);
				printf("���صȲ�Ʊ�ۣ�%d\n", H[i].A);
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
				printf("���òգ�");
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
				printf("�صȲգ�");
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
				printf("\n\n��Ӧ����\n");
				printf("���òգ�%dԪ\n�صȲգ�%dԪ\n", add, add1);
				printf("\n\n");
				break;
			}
			j++;
		}
		i++;
	}
	if (sign3 != 1)
	{
		printf("û�в��ҵ���غ���!!\n");
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
		printf("\t*1.��ѯ���ĺ���      *\n");
		printf("\t*2.��ʱ���ѯ����    *\n");
		printf("\t*3.������Ų�ѯ����  *\n");
		printf("\t*4.����              *\n");
		printf("\t**********************\n");
		printf("������������룺");
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
	printf("����Ҫ�󲹶�����Ʊ\n");
	scanf("%d", &j1);
	p->number = j1;
	while (j2 < j1)
	{
		i = 0;
		printf("�����뺽��ţ�\n");
		scanf("%s", p->Fname);
		getchar();
		while (i < sum2 - 1)
		{
			if (!strcmp(p->Fname, H[i].name))
			{
				printf("\n����ţ�%s \n�ɻ��ͺţ�%s\n", H[i].name, H[i].plane);
				printf("ʱ�䣺%s \n", H[i].time);
				printf("�صȲ���Ʊ��%d��\n", H[i].ticeketA);
				printf("���ò���Ʊ��%d��\n", H[i].ticeketB);
				printf("���ò�Ʊ�ۣ�%dԪ\n", H[i].B);
				printf("�صȲ�Ʊ�ۣ�%dԪ\n", H[i].A);
				printf("·����\n");
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
		printf("���������֣�\n");
		scanf("%s", p->name);
		getchar();
		printf("���������֤���룺\n");
		scanf("%s", p->ID);
		getchar();
		printf("���ò� or �صȲ�:\n");
		scanf("%s", p->clas);
		printf("ʵ��Ǯ:\n");
		scanf("%d", &p->pay);
		printf("�Ƿ�浵  Y or N��");
		getchar();
		scanf("%c", &a);
		getchar();
		if (a == 'Y')
		{
			fp = fopen("B_allpassenger.txt", "ab+");
			fwrite(p, sizeof(P), 1, fp);
			fclose(fp);
			printf("�浵�ɹ���");

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
		printf("1.���Żݺ����Ƽ�\n2.��ͨ�����ѯ\n");
		scanf("%d", &select);
		if (select == 1)
		{
			if (!q_travelrouteinformation())//����·����·��
			{
				printf("�޷���Ʊ��");
				return;
			}
		}
		else if (select == 2)
		{
			if (!place())
			{
				printf("�޷���Ʊ��");
				return;
			}
		}
		printf("***********��ӭʹ�ö�Ʊ����**********\n");
		printf("�ڶ�Ʊ֮ǰ����֪����ţ���ú�����뿴������Ϣ���������˵���ѡ��(4.)��ѯ\n");
		printf("�Ƿ������ Y or N\n ");
		getchar();
		scanf("%c", &a);
		if (a == 'Y')
		{
			printf("�����뺽���\n");
			fflush(stdin);
			scanf("%s", p->Fname);
			getchar();

			while (i < sum2 - 1)
			{
				if (!strcmp(p->Fname, H[i].name))
				{
					if (H[i].ticeketA == 0 && H[i].ticeketB == 0)
					{
						printf("���òյ�Ʊ���صȲյ�Ʊ������^_^");
						printf("��������ŶӵȺ��밴1\n�˳��밴2:\n");
						scanf("%d", &select);
						if (select == 1)
						{
							waitbook();
							printf("�ŶӺ򲹳ɹ���");
							return;
						}
						else return;
					}
					if (H[i].ticeketA == 0 && H[i].ticeketB != 0)
					{
						printf("�صȲյ�Ʊ������^_^ ֻ�ܹ��򾭼òգ����ò���Ʊ��%d\n", H[i].ticeketB);
						printf("���������صȲ��밴1�ŶӵȺ�\n�����Ҫ������Ʊ�밴2������Ʊ");
						scanf("%d", &select);
						if (select == 1)
						{
							waitbook();
							printf("�ŶӺ򲹳ɹ���");
							return;
						}
						else;
					}
					if (H[i].ticeketB == 0 && H[i].ticeketA != 0)
					{
						printf("���òյ�Ʊ������^_^ ֻ�ܹ����صȲգ��صȲ���Ʊ��%d��\n", H[i].ticeketA);
						printf("�������˾��ò��밴1�ŶӵȺ�\n�����Ҫ������Ʊ�밴2������Ʊ��\n");
						scanf("%d", &select);
						if (select == 1)
						{
							waitbook();
							printf("�ŶӺ򲹳ɹ���");
							return;
						}
						else;
					}
					printf("��ȷ�����ĺ�����Ϣ\n");
					printf("\n����ţ�%s \n�ɻ��ͺţ�%s\n", H[i].name, H[i].plane);
					printf("ʱ�䣺%s \n", H[i].time);
					printf("�صȲ���Ʊ��%d��\n", H[i].ticeketA);
					printf("���ò���Ʊ��%d��\n", H[i].ticeketB);
					printf("���ò�Ʊ�ۣ�%dԪ\n", H[i].B);
					printf("�صȲ�Ʊ�ۣ�%dԪ\n", H[i].A);
					printf("·����\n");
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
			printf("�Ƿ������ Y or N\n");
			fflush(stdin);
			scanf("%c", &a);
			if (a == 'Y')
			{
				j2 = 0;
				printf("����Ҫ��������Ʊ\n");
				scanf("%d", &j1);
				while (j1 > H[i].ticeketA &&j1 > H[i].ticeketB)
				{
					printf("��Ʊ��������Ʊ��\n");
					printf("�صȲ���Ʊ��%d��   ���ò���Ʊ��%d��\n", H[i].ticeketA, H[i].ticeketB);
					printf("�������붩Ʊ������1\n�ŶӺ��밴2\n");
					scanf("%d", &select);
					if (select == 2)
					{
						waitbook();
						printf("�ŶӺ򲹳ɹ���");
						return;
					}
					else
					{
						printf("����Ҫ��������Ʊ:\n");
						scanf("%d", &j1);
					}
				}
				while (j2 < j1)
				{
					p->number = 1;
					printf("���������֣�\n");
					scanf("%s", p->name);
					getchar();
					printf("���������֤���룺\n");
					scanf("%s", p->ID);
					getchar();
					printf("���ò� or �صȲ�:\n");
					scanf("%s", p->clas);
					printf("ʵ��Ǯ:\n");
					scanf("%d", &p->pay);
					printf("�Ƿ�浵  Y or N��");
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
								if (!strcmp(p->clas, "���ò�"))
								{
									q1->ticeketB = H[i].ticeketB - p->number;
									q1->ticeketA = H[i].ticeketA;
									getchar();
								}
								else if (!strcmp(p->clas, "�صȲ�"))
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
							printf("������λ�ţ�%s0%d\n", p->Fname, sum5 - 1);
						else
							printf("������λ�ţ�%s00%d", p->Fname, sum5 - 1);
						printf("�浵�ɹ���\n");
					}
					else;
					j2++;
				}
			}
		}
		else return;
		getchar();
		printf("�Ƿ������Ʊ��\n");
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
	printf("*********��ӭʹ����Ʊ����*********\n");
	printf("�������������֤���룺\n");
	scanf("%s", ID);
	while (!feof(fp))
	{
		fread(p, sizeof(P), 1, fp);
		if (!strcmp(ID, p->ID)) break;
	}
	if (feof(fp))
	{
		printf("û�иó˿ͣ�\n");
		return;
	}
	printf("��ȷ��������Ϣ");
	printf("���֣�%s\n", p->name);
	printf("���֤���룺%s\n", p->ID);
	printf("����ţ�%s\n", p->Fname);
	printf("��λ�ȼ���%s\n", p->clas);
	printf("Ʊ����%d\n", p->number);
	printf("֧����%d\n", p->pay);
	printf("��ȷ��Ҫ��Ʊ��Y or N\n");
	getchar();
	scanf("%c", &a);
	if (a == 'Y')
	{
		i = 0;
		for (i = 0; i < sum2 - 1; i++)if (!strcmp(H[i].name, p->Fname))	break;
		if (!strcmp(p->clas, "���ò�"))
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
		if (!strcmp(p->clas, "�صȲ�"))
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
		printf("*********��Ʊ�ͻ����֤��ѯ*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->ID)) break;
		}
	}
	else if (i == 1)
	{
		printf("*********��Ʊ�ͻ����ֲ�ѯ*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->name)) break;
		}
	}
	if (feof(fp))
	{
		printf("û�иó˿ͣ�\n");
		return;
	}
	printf("���֣�%s\n", p->name);
	printf("���֤���룺%s\n", p->ID);
	printf("����ţ�%s\n", p->Fname);
	printf("��λ�ȼ���%s\n", p->clas);
	printf("Ʊ����%d\n", p->number);
	printf("֧����%d\n", p->pay);
}
void PBsarch(char a[], int i)
{
	FILE*fp;
	P*p;
	p = (P*)malloc(sizeof(P));
	fp = fopen("B_allpassenger.txt", "rb");
	if (i == 0)
	{
		printf("*********�Ŷӿͻ����֤��ѯ*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->ID)) break;
		}
	}
	else if (i == 1)
	{
		printf("*********�Ŷӿͻ����ֲ�ѯ*********\n");
		while (!feof(fp))
		{
			fread(p, sizeof(P), 1, fp);
			if (!strcmp(a, p->name)) break;
		}
	}
	if (feof(fp))
	{
		printf("û�иó˿ͣ�\n");
		return;
	}
	printf("���֣�%s\n", p->name);
	printf("���֤���룺%s\n", p->ID);
	printf("����ţ�%s\n", p->Fname);
	printf("��λ�ȼ���%s\n", p->clas);
	printf("Ʊ����%d\n", p->number);
	printf("֧����%d\n", p->pay);
}
void Psarch()
{
	int a;
	char Person[20];

	while (1)
	{
		system("cls");
		printf("\t*********************************\n");
		printf("\t* 1.��Ʊ�ͻ������֤�����ѯ    *\n");
		printf("\t* 2.��Ʊ�ͻ������ֲ�ѯ          *\n");
		printf("\t* 3.�Ŷӿͻ������֤�����ѯ    *\n");
		printf("\t* 4.�Ŷӿͻ������ֲ�ѯ          *\n");
		printf("\t* 5.����                        *\n");
		printf("\t*********************************\n");
		printf("������������룺");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			printf("�������������֤���룺\n");
			scanf("%s", Person);
			PAsarch(Person, 0);
			system("pause");
			break;
		case 2:
			printf("�������������֣�\n");
			scanf("%s", Person);
			PAsarch(Person, 1);
			system("pause");
			break;
		case 3:
			printf("�������������֤���룺\n");
			scanf("%s", Person);
			PBsarch(Person, 0);
			system("pause");
			break;
		case 4:
			printf("�������������֣�\n");
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
	printf("�������������\n");
	scanf("%s", name);
	while (!feof(fp))
	{
		fread(&city, sizeof(C), 1, fp);
		if (!strcmp(name, city.name))break;
	}
	printf("���м�飺\n");
	printf("%s\n", city.information);
	if (feof(fp))
	{
		printf("û�иó��У�");
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
		printf("\t* 1.��Ʊ�ͻ����Ŷӿͻ���ϸ����  *\n");
		printf("\t* 2.�˽⺽����Ϣ                *\n");
		printf("\t* 3.���Żݺ����Ƽ�              *\n");
		printf("\t* 4.��ѯ������Ϣ                *\n");
		printf("\t* 5.����                        *\n");
		printf("\t*********************************\n");
		printf("������������룺");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			Psarch();//1.��Ʊ�ͻ���ϸ����
			system("pause");
			break;
		case 2:
			q_flightinformation();//1.���к�����Ϣ
			system("pause");
			break;
		case 3:
			q_travelrouteinformation();//1.������·   
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
		printf("\t* 1.ע��        *\n");
		printf("\t* 2.��¼        *\n");
		printf("\t* 3.����        *\n");
		printf("\t*****************\n");
		printf("������������룺");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			printf("������ע��ָ��:");
			scanf("%s", password);
			if (!strcmp(password, "123456"))
				registe();
			else
			{
				printf("ָ�����\n");
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
	printf("��ӳ��и���:");
	if (sum - 1 > N)
	{
		printf("������Ŀ�ﵽ���ޣ��޷����");
		getchar();
		return;
	}
	if (sum1 - 1 > O)
	{
		printf("���й�ϵ�ﵽ���ޣ��޷����");
		getchar();
		return;
	}
	scanf("%d", &map->n);
	while (i < map->n)
	{
		printf("������������ƣ�");
		scanf("%s", map->data[i].name);
		printf("�����������Ϣ��");
		scanf("%s", map->data[i].information);
		i++;
	}
	fp = fopen("information.txt", "ab+");
	if (fp == NULL)
	{
		printf("���ļ�ʧ�ܣ�");
		return;
	}
	fwrite(map->data, sizeof(C), i, fp);
	fclose(fp);
	printf("�Ƿ��������1.��    2.��");
	scanf("%d", &b);
	if (b == 1)
	{
		printf("*******����ӳ���֮��Ĺ�ϵ********\n");
		q = (R*)malloc(sizeof(R)); if (q == NULL) return;
		while (1)
		{
			s = 0;
			s1 = 0;
			printf("��ʼ��:");
			fflush(stdin);
			scanf("%s", q->origin);
			getchar();
			printf("�Ƿ������Y or N");
			scanf("%c", &k);
			if (k == 'N')
				return;
			getchar();
			printf("�յ㣺");
			scanf("%s", q->terminal);
			getchar();
			printf("�Ƿ������ Y or N");
			scanf("%c", &k);
			if (k == 'N')
				return;
			printf("Ȩֵ��");
			scanf("%d", &q->wight);
			getchar();
			fp = fopen("relationship_length.txt", "ab+");
			if (fp == NULL)
			{
				printf("���ļ�ʧ�ܣ�");
				return;
			}
			fwrite(q, sizeof(R), 1, fp);
			fclose(fp);
			printf("�Ƿ�浵�� Y or N");
			scanf("%c", &k);
			if (k == 'N') break;
			else(k == 'Y');
			{
				fp = fopen("relationship_length.txt", "rb");
				if (fp == NULL)
				{
					printf("���ļ�ʧ�ܣ�");
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
					printf("���ļ�ʧ�ܣ�");
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
			printf("�Ƿ������ӣ�Y or N\n");
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
		printf("�������������߳��и���:");
		scanf("%d", &p->sum);
		getchar();
		printf("�����뺽�����ƣ�");
		scanf("%s", p->name);
		getchar();
		printf("�����뺽��ʱ�䣺");
		scanf("%s", p->time);
		getchar();
		printf("�����뾭�ò�Ʊ����");
		scanf("%d", &p->ticeketB);
		printf("�������صȲ�Ʊ����");
		scanf("%d", &p->ticeketA);
		printf("�������صȲ���Ʊ��:");
		scanf("%d", &p->A);
		printf("�����뾭�ò�Ʊ�ܼ�:");
		scanf("%d", &p->B);
		getchar();
		printf("������ɻ��ͺ�:");
		scanf("%s", p->plane);
		getchar();
		while (i < p->sum)
		{
			printf("������������ƣ�");
			scanf("%s", p->city[i].cityname);
			getchar();
			i++;
		}
		i = 0;
		while (i < p->sum - 1)
		{
			printf("������%s��%s�ľ��ò�Ʊ�ۣ�", p->city[i].cityname, p->city[i + 1].cityname);
			scanf("%d", &p->dollar[i].Bmoney);
			printf("������%s��%s���صȲ�Ʊ�ۣ�", p->city[i].cityname, p->city[i + 1].cityname);
			scanf("%d", &p->dollar[i].Amoney);
			i++;
		}
		getchar();
		printf("�Ƿ�浵��Y or N\n");
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
		printf("�Ƿ�������? Y or N\n");
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
		printf("\t* 1.�޸ĺ����   *\n");
		printf("\t* 2.�޸ĺ���ʱ�� *\n");
		printf("\t* 3.�޸�Ʊ��     *\n");
		printf("\t* 4.����         *\n");
		printf("\t******************\n");
		printf("������������룺");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			printf("�������޸ĵľ��ò�Ʊ����");
			scanf("%d", &B);
			printf("�����뺽��ţ�\n");
			scanf("%s", flight);
			printf("�������޸ĵ��صȲղ�Ʊ����");
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
		printf("\t* 1.������ͼ    *\n");
		printf("\t* 2.��������    *\n");
		printf("\t* 3.��ʽ����ͼ  *\n");
		printf("\t* 4.��ʽ������  *\n");
		printf("\t* 5.�޸ĺ���    *\n");
		printf("\t* 6.����        *\n");
		printf("\t*****************\n");
		printf("������������룺");
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
			printf("��ȷ��Ҫ��ʽ����Y or N");
			scanf("%c", &k);
			if (k == 'Y')fp = fopen("information.txt", "wb");
			else return;
			system("pause");
			break;
		case 4:
			printf("��ȷ��Ҫ��ʽ����Y or N");
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
	printf("\t* 1.��Ʊҵ��       *\n");
	printf("\t* 2.��Ʊҵ��       *\n");
	printf("\t* 3.�ŶӺ�       *\n");
	printf("\t* 4.��ѯ           *\n");
	printf("\t* 5.����Ա����     *\n");
	printf("\t* 0.�˳�           *\n");
	printf("\t********************\n");
	printf("������������룺");
	scanf("%d", &a);
	switch (a)
	{
	case 1:

		M_book();//book
		system("pause");
		break;
	case 2://��Ʊ
		M_backticket();
		system("pause");
		break;
	case 3:
		waitbook();
		break;
	case 4://��ѯ
		M_query();
		system("pause");
		break;
	case 5://�༭������Ϣ  
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
		printf("���ļ�ʧ�ܣ�");
		return;
	}
	while (!feof(fp))
	{                                                      //��ʼ��sum2  
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
		printf("���ļ�ʧ�ܣ�");
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
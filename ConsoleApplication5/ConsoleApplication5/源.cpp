/*#include<stdio.h>
#include<stdlib.h>
#include<io.h>
typedef struct structdat
{
	int no;
	char name[20];
}dat;
typedef struct st
{
	dat data;
	struct st *next;
}ST;
void loaddata(ST *st)
{
	FILE *fp;
	dat *q;
	ST *p=st->next;
	ST *m;
	//if ((fp = fopen("studenf.FILE", "a+")) == NULL)
	//{
	//	fprintf(stderr, "Can not open output file\n");
	//	printf("加载失败");
	//	return;
	//}	

	//if (fwrite(&p->data, sizeof(struct structdat), 1, fp) != 1)
	//{
	//	printf("有误");
	//	return;
	//}
	if ((fp = fopen("student.FILE", "w+")) == NULL)
		printf("打开失败");
	fseek(fp, 0, SEEK_SET);
	fread(&q, 1, sizeof(dat), fp);
	//printf("%d\t%s\n", q->no, q->name);
	m = (ST*)malloc(sizeof(ST));
	m->data = *q;
	p->next = m;	
	m->next = NULL;
	fclose(fp);
	printf("保存成功");
	return;
}
int welcome()
{
	int choise;
	printf("╔═══════════════╗\n");
	printf("║          学生管理系统        ║\n");
	printf("╠═══════════════╣\n");
	printf("║      1:添加信息              ║\n");
	printf("║      2:查看信息              ║\n");
	printf("║      3:存储信息              ║\n");
	printf("╚═══════════════╝\n");
	printf("请输入您的选择:");
	scanf("%d", &choise);
	return choise;
}
dat add()
{
	dat e;
	printf("no:");
	scanf("%d", &e.no);
	printf("name");
	scanf("%s", e.name);
	return e;
}
void addinformation(ST *st)
{
	FILE *fp;
	ST *p=st, *q=st->next;
	dat e = add();
	char a;
	while (p != NULL)
	{
		p = p->next;
	}
		q = (ST*)malloc(sizeof(ST));
		q->data = e;
		p->next = q;
		q->next = NULL; 
		if ((fp = fopen("studen.bak", "wb")) == NULL)
		{
			printf("\t\t失败，无法创建");
			return;
		}
		if (fwrite(&e, sizeof(dat), 1, fp) != 1)
		{
			getchar();
			printf("\t\t写入错误\n"); return;
		}
		fclose(fp);
		getchar();
		printf("请输入是否继续:");
		scanf("%c", &a);
		if (a == 'y' || a == 'Y')
		{
			addinformation(st);
		}
		else return;
}
void display(ST *st)
{
	ST *p = st->next;
	while (p != NULL)
	{
		printf("%d\t%s\n", p->data.no, p->data.name);
		p = p->next;
	}
}
void save(ST *st)
{
	getchar();
	FILE *fp;
	ST *p;
	if ((fp = fopen("studen.bak", "wb")) == NULL)
	{
		printf("\t\t失败，无法创建");
		return;
	}
	p = st->next;
	while (p != NULL)
	{
		if (fwrite(&p->data, sizeof(dat), 1, fp) != 1)
		{
			getchar();
			printf("\t\t写入错误\n"); return;
		}
		p = p->next;
	}
	printf("\t\t文件保存成功\n"); fclose(fp);
}
int main()
{
	ST studen;
	studen.next = NULL;
	loaddata(&studen);
	while (1)
	{
		system("cls");
		switch (welcome())
		{
		case 1:addinformation(&studen);//存信息
			system("pause");
			break;
		case 2:display(&studen);
			system("pause");
			//查看信息
			break;
		case 3:save(&studen);//存入信息
			system("pause");
			break;
		default:
			break;
		}
	}
	return 0;
}*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#define N 29
#define M 41
#define ROAD 0
#define WALL 1
#define UP 5
#define LEFT 2
#define DOWN 3
#define RIGHT 4
typedef struct 
{
	int x;
	int y;
}cur;
typedef struct
{
	cur pos;
	int p;
}postype;
typedef struct link
{
	struct link *next;
	postype data;
}link;
typedef struct linkstack
{
	link *top;
	link *bottom;
}linkstack;
int map[N + 2][M + 2];
void Creatmap(int p,int q)
{
	int k, h;
	int dir[4][2] = { 0, 1, 0, -1, -1, 0, 1, 0 };
	for (int i = 0; i < 4; i++)
	{
		k = rand() % 4;
		h = dir[k][0];
		dir[k][0] = dir[i][0];
		dir[i][0] = h;
		h = dir[k][1];
		dir[k][1] = dir[i][1];
		dir[i][1] = h;
	}
	map[p][q] = ROAD;
	for (int i = 0; i < 4; i++)
	{
		if (map[p + 2 * dir[i][0]][q + 2 * dir[i][1]] == WALL)
		{
			map[p + dir[i][0]][q + dir[i][1]] = ROAD;
			Creatmap(p + 2*dir[i][0],q + 2*dir[i][1]);
		}
	}
}
void Paint(int i,int j)
{
		switch (map[i][j])
		{
		case WALL:printf("回"); break;
		case ROAD:printf("  "); break;
		case UP:printf("↑"); break;
		case LEFT:printf("→"); break;
		case DOWN:printf("↓"); break;
		case RIGHT:printf("←"); break;
		case 6:printf("艹"); break;
		}
}
void creat()
{
	for (int i = 0; i < N + 2; i++)
	{
		for (int j = 0; j < M + 2; j++)
		{
			if (i == 0 || i == N + 1 || j == 0 || j == M + 1)
			{
				map[i][j] = ROAD;
			}
			else
			{
				map[i][j] = WALL;
			}
		}
	}
	Creatmap(2 * (rand() % (N / 2)), 2 * (rand() % (M / 2)));
	for (int i = 0; i < N + 2; i++)
	{
		for (int j = 0; j < M + 2; j++)
		{
			Paint(i, j);
		}
		printf("\n");
	}
}
void InitStack(linkstack *T)
{
	T->bottom = T->top = NULL;
}
void push(linkstack *H,postype e)//压栈
{
	link *q;
	q = (link*)malloc(sizeof(link)); //申请一个空间
	if (q == NULL) { printf("申请空间失败"); return; }
	q->data = e;//将信息存入
	q->next = H->top;//在头指针的上面插入
	H->top = q;//插入的位置为头指针
}
bool stackempty(linkstack *H)//判断是否为空栈，是返回1，否则返回0.
{
	if (H->top == H->bottom)return true;
	else return false;
}
void pop(linkstack *H, postype *e)
{
	link *p;
	if (stackempty(H)){ printf("空栈"); return; }//判断栈是否为空
	*e = H->top->data;//取出栈的data
	p = H->top;
	H->top = H->top->next;//取出栈
	free(p);
}
cur nextpass(cur pose, int i)
{
	cur pos;
	pos = pose;
	switch (i)
	{
	case LEFT:pos.y += 1;
		break;
	case DOWN:pos.x += 1;
		break;
	case RIGHT:pos.y -= 1;
		break;
	case UP:pos.x -= 1;
		break;
	}
	return pos;
}
int pass(cur pose)//在map[][]中当前位置是否可通，可通返回1，否返回0
{
	if (map[pose.x][pose.y]==ROAD) return 1;
	else return 0;
}
void markmap(cur pose,int x)
{
	map[pose.x][pose.y] = x;
}
void Dirct(cur start,cur end)
{
	linkstack T;
	InitStack(&T);
	cur curpose=start;
	postype e;
	do
	{
		if (pass(curpose))
		{
			
			e.p = LEFT;
			e.pos = curpose;
			push(&T, e);
			markmap(curpose, LEFT);
			if (curpose.x == end.x&&curpose.y == end.y)
			{
				return;
			}
			curpose = nextpass(curpose, LEFT);
		}
		else
		{
			if (!stackempty(&T))
			{
				pop(&T, &e);
				while (e.p == UP&&!stackempty(&T))
				{
					markmap(e.pos,6);
					pop(&T, &e);
				}
				if (e.p < UP)
				{
					e.p++;
					push(&T, e);
					markmap(e.pos, e.p);
					curpose = nextpass(e.pos, e.p);
				}
			}
		}
	} while (1);
		
}
void revolu()
{
	cur poses,posee;
	poses.x = 2;
	poses.y = 2;
	posee.x = N -1;
	posee.y = M -1;
	Dirct(poses,posee);
	for (int i = 0; i < N + 2; i++)
	{
		for (int j = 0; j < M + 2; j++)
		{
			Paint(i, j);
		}
		printf("\n");
	}
	printf("\n");
}
int main()
{
	srand((unsigned)time(NULL));
	creat();
	revolu();
	return 0;
}
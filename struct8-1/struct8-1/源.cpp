#include<stdio.h>
#include<stdlib.h>
int matching(char exp[])//����ƥ��
{
	int i = 0;
	int top=0;
	int state = 1;
	char str[80];
	while (exp[i] != '\0'&&state == 1)
	{
		switch (exp[i])
		{
		case '(':
		case '{':
		case '[':
			str[top++] = exp[i];
			i++; break;
		case ')':
			if (top>0&&str[top-1]=='(')
		{
				top--;//��ջ
			i++;
		}
			else state = 0; break;
		case ']':
			if (top>0 && str[top - 1] == '[')
			{
				top--;//��ջ
				i++;
			}
			else state = 0; break;
		case '}':
			if (top>0 && str[top - 1] == '{')
			{
				top--;//��ջ
				i++;
			}
			else state = 0; break;
		default:i++;
		}
		
	}
	if (top == 0)
		return 1;
	else
		return 0;
	/*state = -1;
	for (int j = 0; exp[j] != '\0'; j++)
	{
		if (exp[j] == '(' || exp[j] == '{' || exp[j] == '[')
		{
			str[++state] = exp[j];
		}
		else
		{
			if (exp[j] - str[state]<4)
			{
				state--;
			}
			else break;
		}
	}
	if (state == -1)
	{
		return 1;
	}
	else
		return 0;*/
}
int main()
{
	char str[80];
	int i;
	printf("�������ַ�");
	gets(str);
	i = matching(str);
	if (i== 1)
		printf("�ɹ�\n");
	else
		printf("ʧ��\n");
	return 0;
}
/*void sert(int num, int n)//����ת��
{
	int str[20];
	int i = -1;
	while (num > 0)
	{
		str[++i] = num%n;
		num /= n;
	}
	printf("ת��Ϊ:");
	while (i > -1)
	{
		if (str[i]>9)
		printf("%c",str[i--]-10+'A');
		else
		{
			printf("%d", str[i--]);
		}
	}
	printf("\n");
}
int main()
{
	A:
	int i,j;
	printf("��������:");
	scanf("%d", &i);
	do{
		printf("���������(2/8/16):");
		scanf("%d", &j);
	} while (j != 2 && j != 8 && j != 16);
	sert(i, j);
	goto A;
	return 0;
}*/
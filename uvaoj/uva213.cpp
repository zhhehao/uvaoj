#include <stdio.h>
#include <math.h>
#define MAXN 500

char sh[8][MAXN];
void decode(int len);

int main()
{
	char c;
	while (1)
	{
		c = getchar();
		while (c == '\n')
			c = getchar();
		if (c == EOF)
			break;
		int lenh = 0;
		while (1)
		{
			for (int i = 1; i < 8; i++)
			{
				int n = pow(2, i) - 1;
				for (int j = 0; j < n; j++)
				{
					sh[i][j] = c;
					if ((c = getchar()) == '\n')
						goto tabledone;
				}
				sh[i][n] = '\0';
			}			
		}
		tabledone:

		int lenk;
		while (1)
		{
			lenk = 0;
			for (int i = 2; i >= 0; i--)
			{
				c = getchar();
				while (c != '0' && c != '1')
					c=getchar();
				if  (c == '1')
					lenk += pow(2, i);
			}
			if (lenk == 0)
				break;
			decode(lenk);
//			printf("%d\n", lenk);
		}
		printf("\n");
	}
	return 0;
}

void decode(int len)
{
	while(1)
	{
		int n = 0;
		char c;
		for (int i = len - 1; i >= 0; i--)
		{
			c = getchar();
			while (c != '0' && c != '1')
				c = getchar();
			if (c == '1')
				n += pow(2, i);
		}
		if (n == pow(2, len) - 1)
			break;
		printf("%c", sh[len][n]);
	}
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXN 11

char s1[MAXN][MAXN];
int s2[MAXN][MAXN];

int main()
{
	int r, c, kase, rev;
	char ch;

	kase = 1;
	while (1)
	{
		rev = scanf("%d", &r);
		if (r == 0) break;
		rev = scanf("%d", &c);
		memset(s2, 0, sizeof(s2));
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c;)
			{
				ch = getchar();
				if ((isalpha(ch)) || (ch == '*'))
					s1[i][j++] = ch;
			}
	
		int num = 1;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (((i-1<0)||(j-1<0)||(s1[i-1][j]=='*')||(s1[i][j-1]=='*')) && (s1[i][j]!='*'))
					s2[i][j] = num++;


		if (kase > 1) printf("\n");
		printf("puzzle #%d:\nAcross\n", kase++);
		
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (isalpha(s1[i][j]))
				{
					if ((j-1<0)||(s1[i][j-1]=='*'))
						printf("%3d.", s2[i][j]);
					printf("%c", s1[i][j]);
					if ((j+1==c)||(s1[i][j+1]=='*'))
						printf("\n");
				}
			}
		}


		printf("Down\n");
		int k = 0;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if ((isalpha(s1[i][j]) && (s2[i][j] != 0)))
				{
					printf("%3d.%c", s2[i][j], s1[i][j]); 
					s2[i][j] = 0;
					k = i;
					while ((k+1<r) && (s1[k+1][j] != '*'))
					{
						printf("%c", s1[k+1][j]); 
						s2[k+1][j] = 0; 
						k++;
					}
					printf("\n");					
				}
			}
		}
	}
	return 0;
}

#include <stdio.h>
#include <ctype.h>

char s[5][5];

int main()
{
	int i, j, kase, bi, bj, br;
	char c;

	kase = 1;
	c = 'a';
	while (1)
	{
		bi = bj = 9;
		br = 0;
		for (i = 0; i < 5; i++)
		{
			j = 0;
			while (j < 5)
			{	
				c = getchar();
				if (c == 'Z') goto end;
				if (isalpha(c))
				{
					s[i][j++] = c;
					continue;
				}
				if (c == ' ')
				{
					bi = i;
					bj = j;
					s[i][j++] = c;
					continue;
				}
				if ((c =='\n') && (j == 4))
				{
					bi = i;
					bj = j;
					s[i][j++] = ' ';
					continue;
				}
			}
		}
		
		while ((c=getchar()) != '0')
		{	
			switch (c)
			{
				case 'A':
					if (bi-1 < 0) {br = 1; break;}
					c = s[bi][bj];
					s[bi][bj] = s[bi-1][bj];
					s[bi-1][bj] = c;
					bi--;
					break;
				case 'B':
					if (bi+1 > 4) {br = 1; break;}
					c = s[bi][bj];
					s[bi][bj] = s[bi+1][bj];
					s[bi+1][bj] = c;
					bi++;
					break;
				case 'L':
					if (bj-1 < 0) {br = 1; break;}
					c = s[bi][bj];
					s[bi][bj] = s[bi][bj-1];
					s[bi][bj-1] = c;
					bj--;
					break;
				case 'R':
					if (bj+1 > 4) {br = 1; break;}
					c = s[bi][bj];
					s[bi][bj] = s[bi][bj+1];
					s[bi][bj+1] = c;
					bj++;
					break;
			}
		}

		if (kase > 1) printf("\n");
		printf("Puzzle #%d:\n", kase++);
		if (br)
			printf("This puzzle has no final configuration.\n");
		else 
		{
			for (i = 0; i < 5; i++)
			{
				for (j = 0; j < 4; j++)
					printf("%c ", s[i][j]);
				printf("%c\n", s[i][4]);
			}
		}
	}
	end:
	return 0;
}

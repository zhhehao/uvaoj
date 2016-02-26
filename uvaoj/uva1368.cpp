#include <stdio.h>
#include <string.h>
#define MAXN 1005

int st[4][MAXN];
char sl[MAXN];

int main()
{
	int rev, t, m, n;

	rev = scanf("%d", &t);
	while (t--)
	{
		rev = scanf("%d%d", &m, &n);
		memset(st, 0, sizeof(st));
		for (int i = 0; i < m; i++)
		{
			rev = scanf("%s", sl);
			for (int j = 0; j < n; j++)
				switch(sl[j])
				{
					case 'A':
						st[0][j]++;
						break;
					case 'C':
						st[1][j]++;
						break;
					case 'G':
						st[2][j]++;
						break;
					case 'T':
						st[3][j]++;
						break;
				}
		}

		int ce = 0;
		for (int i = 0; i < n; i++)
		{
			int max = 0;
			for (int j = 1; j < 4; j++)
				if (st[max][i] < st[j][i])
					max = j;
			switch (max)
			{
				case 0:
					sl[i] = 'A';
					break;
				case 1:
					sl[i] = 'C';
					break;
				case 2:
					sl[i] = 'G';
					break;
				case 3:
					sl[i] = 'T';
					break;
			}
			ce += (m - st[max][i]);
		}

		printf("%s\n", sl);
		printf("%d\n", ce);


	}
	return 0;
}

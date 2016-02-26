#include <stdio.h>
#include <string.h>
#define MAXN 500000

char s[MAXN], t[MAXN];

int main()
{
	int sl, tl, mark;

	while (scanf("%s%s", s, t) != EOF)
	{
		sl = strlen(s);
		tl = strlen(t);
		mark = 0;

		for (int i = 0, j = 0; i < sl; i++)
		{
			if (j == tl) break;
			while (j < tl)
			{
				if (s[i] == t[j])
				{
					mark = i + 1;
					j++;
					break;
				}
				if (j < tl)
					j++;			
				else 
					goto output;
			}
		}
	output:	
		if (mark == sl)
			printf("Yes\n");
		else
			printf("No\n");

	}
	return 0;
}


#include <stdio.h>
#include <string.h>
#define MAXN 85

char s[MAXN];

int main()
{
	int n, rev, k, len, i;
	char *p1, *p2, *p0;
	
	rev = scanf("%d", &n);
	while (n--)
	{
		memset(s, '\0', sizeof(s));
		while (!(rev=scanf("%s",s)))
			;
		k = len = strlen(s);
		p0 = s;
		for (i = 1; i < len; i++)
		{
			if ((s[0] == s[i]) && ((len%i) == 0))
			{	
				p1 = s;
				p2 = s + i;
				while (*p1 == *p2)
				{
					if ((p2-p0) == (len-1))
					{
						k = i;
						goto pr;
					}	
					p1++;
					p2++;
				}
			}
		}
		pr:
		printf("%d\n", k);
		if (n) printf("\n");
	}
	return 0;
}

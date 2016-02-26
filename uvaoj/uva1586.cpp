#include <stdio.h>
#include <ctype.h>
#define MAXN 85

char s[MAXN];

int main()
{
	int n, rev, i;
	double mm, sum;
	
	rev = scanf("%d", &n);
	while (n--)
	{
		sum = mm = 0.0;
		rev = scanf("%s", s);
		for (i = 0; s[i] != '\0'; i++)
		{	
			if (s[i] == 'C') mm += 12.01;
			if (s[i] == 'H') mm += 1.008;
			if (s[i] == 'O') mm += 16.00;
			if (s[i] == 'N') mm += 14.01;
			if (!isdigit(s[i+1]))
			{
				sum += mm;
				mm = 0.0;
			}
			if (isdigit(s[i+1]))
			{
				if (isdigit(s[i+2]))
				{
					sum += (mm * ((s[i+1]-'0') * 10 + (s[i+2]-'0')));
					mm = 0.0;
					i += 2;
				}
				else
				{
					sum += (mm * (s[i+1]-'0'));
					mm = 0.0;
					i++;
				}
			}
		}
		printf("%.3f\n", sum);
	}
	return 0;
}

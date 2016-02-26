#include <stdio.h>
#include <string.h>

#define MAXN 3000

int s[MAXN];
int sd[MAXN];

int main()
{
	int rev, a, b, d, cs, ce, cl, a0, kase;
	
	kase = 1;
	while ((rev=scanf("%d%d", &a, &b)) != EOF)
	{
		memset(s, 0, sizeof(s));
		memset(sd, 0, sizeof(sd));
		a0 = a;
		d = a / b;
		if (d > 0) a = a % b;
		if (a == 0) {cs = ce = 0; cl = 1;goto output;}
		for (int i = 0; i < MAXN;)
		{
			here:
			a *= 10;	
			sd[i] = a;			
			for (int j = 0; j < i; j++)
				if (sd[j] == sd[i])
					{cs = j; ce = (i-1); cl = (i-j);goto output;}	
			while (a < b)
				{ s[i] = 0;	i++; goto here;}
			s[i++] = a / b;
			a = a % b;
			if (a == 0) {cs = ce = i;cl = 1; goto output;}
		}
		
		output:
//		if (kase > 1) printf("\n");
		printf("%d/%d = %d.", a0, b, d);
			for (int i = 0; i < cs; i++)
				printf("%d", s[i]);
			printf("(");
			if (ce < 50)
				for (int i = cs; i < ce + 1; i++)
					printf("%d", s[i]);
			else
			{
				for (int i = cs; i < 50; i++)
					printf("%d", s[i]);
				printf("...");
			}
			printf(")\n");
		printf("   %d = number of digits in repeating cycle\n", cl);
		kase ++;
		printf("\n");
	}
	return 0;
}

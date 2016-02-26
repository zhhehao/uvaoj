#include <stdio.h>
#include <string.h>
#define MAXN 23

int s[MAXN];
int left, n, k, m;
int *p0, *p1, *p2;

void que(void);

int main()
{
	int rev;
	while ((rev=scanf("%d%d%d", &n, &k, &m) == 3))
	{
		if(n == 0) break;
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= n; i++)
			s[i] = i;
		p0 = s;
		p1 = s + 1;
		p2 = s + n;
		left = n;
		k--;
		m--;
		while (left)
			que();
		printf("\n");
	}
	return 0;
}

void que(void)
{
	int qk, qm;
	qk = k;
	qm = m;
	
	while (qk)
	{
		if (p1 == p0 + n)
			p1 = s + 1;
		else
			p1++;
		if (*p1 == 0)
			continue;
		else
			qk--;
	}
	
	while (qm)
	{
		if (p2 == p0 + 1)
			p2 = s + n;
		else 
			p2--;
		if (*p2 == 0)
			continue;
		else 
			qm--;
	}

	if (p1 == p2)
	{
		printf("%3d", *p1);
		*p1 = 0;
		left--;
	}
	if (p1 != p2)
	{
		printf("%3d%3d", *p1, *p2);
		*p1 = *p2 = 0;
		left -= 2;
	}
	if (left)
	{
		printf(",");		
		while (*p1 == 0)
		{
			if (p1 == p0 + n)
				p1 = s + 1;
			else
				p1++;
		}
		while (*p2 == 0)
		{
			if (p2 == p0 + 1)
				p2 = s + n;
			else 
				p2--;
		}
	}
}

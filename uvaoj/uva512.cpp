#include <stdio.h>
#include <string.h>
#include <ctype.h>

int c[1000][1000];
char d[1000][2];
int gone, x, y;

void dr(int n);
void dc(int n);
void ir(int n);
void ic(int n);
void ex(int n);
char rechar(void);

int main()
{
	int rev, rn, cn;
	int kase = 1;
	while ((rev=scanf("%d%d", &rn, &cn) == 2) && rn && cn)
	{
		int n;
		rev = scanf("%d", &n);
		memset(c, 0, sizeof(c));
		memset(d, '\0', sizeof(d));
		for (int i = 1; i <= n; i++)
		{
			d[i][0] = rechar();
			d[i][1] = rechar();
			if (d[i][0] == 'E')
			{
				rev = scanf("%d%d%d%d", &c[i][1], &c[i][2], &c[i][3], &c[i][4]);				
				continue;
			}
			int len;
			rev = scanf("%d", &c[i][0]);
			len = c[i][0];
//			printf("len %d\n", len);
			for (int j = 1; j <= len; j++)
				rev = scanf("%d", &c[i][j]);
		}
		int onum;
		rev = scanf("%d", &onum);
	//	printf("onum %d\n", onum);
		if (kase > 1) 
			printf("\n");
		printf("Spreadsheet #%d\n", kase++);
		for (int i = 0; i < onum; i++)
		{
			gone = 0;
			rev = scanf("%d%d", &x, &y);
//			printf("x %d y %d\n", x, y);
			int x0, y0;
			x0 = x;
			y0 = y;
			for (int j = 1; j <= n; j++)
			{
				if (d[j][0] == 'D' && d[j][1] == 'R')
					{
						dr(j);
						if (gone == 1)
							break;
					}
				if (d[j][0] == 'D' && d[j][1] == 'C')
					{
						dc(j);
						if (gone == 1)
							break;
					}
				if (d[j][0] == 'I' && d[j][1] == 'C')
					ic(j);
				if (d[j][0] == 'I' && d[j][1] == 'R')
					ir(j);
				if (d[j][0] == 'E')
					ex(j);
//				printf("%d: %d %d\n", j, x, y);
			}
			if (gone == 1)
				printf("Cell data in (%d,%d) GONE\n", x0, y0);
			else
				printf("Cell data in (%d,%d) moved to (%d,%d)\n", x0, y0, x, y);
		}
		
	}
	return 0;
}

void dr(int n)
{
	int k;
//	printf("%c %c\n", c[n][4], c[n][5]);
	k = c[n][0];
//	printf("k %d\n", k);
	int m = 0;
	for (int i = 1; i <= k; i++)
	{
		int p = c[n][i];
//		printf("p %d\n", p);
		if (p == x)	
			{gone = 1; break;}
		if (p > x)
			continue;
		if (p < x)
			m--;
	}
	x += m;
//	printf("x %d\n", x);
//	printf("goner %d %d %d\n", gone, x, y);
}

void dc(int n)
{
	int k;
	k = c[n][0];
	int m = 0;
	for (int i = 1; i <= k; i++)
	{
		int p = c[n][i];
		if (p == y)
			{gone = 1; break;}
		if (p > y)
			continue;
		if (p < y);
			m--;
	}
	y += m;
//	printf("y %d\n", y);
//	printf("gonec %d %d %d\n", gone, x, y);
}

void ic(int n)
{
	int k;
	k = c[n][0];
	int m = 0;
	for (int i = 1; i <= k; i++)
	{
		int p = c[n][i];
		if (p <= y)
			m++;
	}
	y += m;
//	printf("y %d\n", y);
}

void ir(int n)
{
	int k;
	k = c[n][0];
	int m = 0;
	for (int i = 1; i <= k; i++)
	{
		int p = c[n][i];
		if (p <= x)
			m++;
	}
	x += m;
//	printf("x %d\n", x);
}

void ex(int n)
{
	int p1, p2, p3, p4;
//	printf("before exchange %d %d\n", x, y);
	p1 = c[n][1];
	p2 = c[n][2];
	p3 = c[n][3];
	p4 = c[n][4];
//	printf("%d %d %d %d\n", p1, p2, p3, p4);
	if (p1==x && p2==y)
//		printf("Yes\n");
		{x = p3; y = p4;}
	else if (p3==x && p4==y)
		{x = p1; y = p2;}
//	printf("after exchange %d %d\n", x, y);
}

char rechar(void)
{
	char c;
	for (;;)
		if (isalnum(c=getchar()))
			break;
	return c;
}

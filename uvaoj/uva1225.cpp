#include <stdio.h>
#include <string.h>

int main()
{
	int a[10], n, m, rev, y;

	rev = scanf("%d", &n);
	while (n--)
	{
		memset(a, 0, sizeof(a));
		rev = scanf("%d", &m);
		for (int i = 1; i <= m; i++)
		{
			y = i;
			while (y > 0)
			{
				a[y%10]++;
				y /= 10;;
			}
		}
		for (int j = 0; j < 9; j++)
			printf("%d ", a[j]);
		printf("%d\n", a[9]);
	}
	return 0;
}

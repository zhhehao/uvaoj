#include <stdio.h>
#define MAXN 85

char a[MAXN];

int main()
{
	int n, plus, sum;
	int rev;

	rev = scanf("%d", &n);
	while (n--)
	{
		plus = 1;
		sum = 0;
		rev = scanf("%s", a);
		for (int i = 0; a[i] != '\0'; i++)
		{
			if (a[i] == 'O')
				sum += (plus++);
			if (a[i] == 'X')
				plus = 1;
		}
		printf("%d\n", sum);
	}
	return 0;
}

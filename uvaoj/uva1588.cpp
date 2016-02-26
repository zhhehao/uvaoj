#include <stdio.h>
#include <string.h>
#define MAXN 220

int s1[MAXN], s2[MAXN];

int main()
{
	while (1)
	{
		memset(s1, 0, sizeof(s1));
		memset(s2, 0, sizeof(s2));
		char c;
		if ((c=getchar()) == EOF)
			break;
		else
			s1[0] = c - '0';
		int k1 = 1;
		while ((c=getchar()) != '\n')
			s1[k1++] = c - '0';
		int k2 = 0;
		while ((c=getchar()) != '\n')
			s2[k2++] = c - '0';
		
		int result1 = 0;
			for (int i = 0, j = 0, k = 0; i <= k1; i++)
			{
				k = i;
				while ((j < k2) && (s1[k]+s2[j] <= 3))
				{
					k++;
					j++;
				}
				if (j == k2)
				{
					if (j+i > k1)
						result1 = j + i;
					else
						result1 = k1;
					break;
				}
				j = 0;
			}
		int result2 = 0;
			for (int i = 0, j = 0, k = 0; i <= k2; i++)
			{
				k = i;
				while ((j < k1) && (s2[k]+s1[j] <= 3))
				{
					k++;
					j++;
				}
				if (j == k1)
				{
					if (j+i > k2)
						result2 = j + i;
					else 
						result2 = k2;
					break;
				}
				j = 0;
			}
		if (result1 < result2)
			printf("%d\n", result1);
		else 
			printf("%d\n", result2);

//		for (int i = 0; s1[i] != 0; i++)
//			printf("%d", s1[i]);
//		printf("\n");
//		for (int i = 0; s2[i] != 0; i++)
//			printf("%d", s2[i]);
//		printf("\n");
	}

	return 0;
}

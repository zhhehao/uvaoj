#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 102

char s1[MAXN], s2[MAXN];
int t1[26], t2[26];
char const st[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
void stat(char *p1, int *p2, int n);
int cmp(const void *a, const void *b);

int main()
{
	int rev;
	while ((rev=scanf("%s", s1)) != EOF)
	{
		memset(t1, 0, sizeof(t1));
		memset(t2, 0, sizeof(t2));
		rev = scanf("%s", s2);
		int len1 = strlen(s1);
		int len2 = strlen(s2);
		
		stat(s1, t1, len1);
		stat(s2, t2, len2);
		
		int result = 1;
		for (int i = 1; i < 26; i++)
			if (t1[i] != t2[i])
				{result = 0; break;}

		if (result)
			printf("YES\n");
		else 
			printf("NO\n");

//		printf("%s\n%s\n", s1, s2);
	}
	return 0;
}

void stat(char *p1, int*p2, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 26; j++)
			if (*(p1+i) == st[j])
				{(*(p2+j))++; break;}
	qsort(p2, 26, sizeof(*p2), cmp);
}

int cmp(const void *a, const void *b)
{
	return (*(int *)b - *(int *)a);
}

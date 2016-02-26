#include <stdio.h>
#include <string.h>
#define MAXN 1000

char s1[MAXN], s2[MAXN];
int t1[MAXN];

int judge(char *a, char *b);

int main()
{
	int kase, rev, len;
	while (1)
	{
		rev = scanf("%d", &kase);
		if (kase == -1) break;
		rev = scanf("%s%s", s1, s2);
		memset(t1, 0, sizeof(t1));
		len = strlen(s2);
		for (int i = 1; i < len; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (s2[i] == s2[j])
				{
					for (int k = i; k <= len; k++)
						s2[k] = s2[k+1];	
					len--;
					i--;
				}
			}
		}
//		printf("%s\n", s2);

		switch(judge(s1, s2))
		{
			case 1:
				printf("Round %d\nYou win.\n", kase);
				break;
			case -1:
				printf("Round %d\nYou lose.\n", kase);
				break;
			case 0:
				printf("Round %d\nYou chickened out.\n", kase);
				break;
		}		
	}

	return 0;
}

int judge(char *a, char *b)
{
	int result;	
	int count, right, chick;
	
	count = 0;
	chick = 0;
	for (int i = 0; *(b+i) != '\0'; i++)
	{
		right = 0;
		for (int j = 0; *(a+j) != '\0'; j++)
		{
			if ( *(b+i) == *(a+j))
			{
				right = 1;
				if (t1[j] == 0)
					t1[j] = 1;
				else
					right = 0;
			}
		}
		if (right == 0) count++;
		if (count == 7) {result = -1; goto end;}
		int win = 1;
		for (int k = 0; *(a+k) != '\0'; k++)
			if (t1[k] == 0) {win = 0; break;}
		if (win) {result = 1; goto end;}
	}
	
	for (int j = 0; *(a+j) != '\0'; j++)
		if (t1[j] == 0)
			{chick = 1; break;}
	result = chick ? 0 : 1;

	end:
	return result;
}

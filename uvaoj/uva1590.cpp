#include <stdio.h>
#include <string.h>

#define MAXN 1005

char s[40];
int ip[MAXN][32];
int mask[32];
int byte[4];
void tobin(int n, int m, int i);
int count;

int main(void)
{
	int rev, m;
	while ((rev=scanf("%d", &m)) != EOF){
		memset(s, '\0', sizeof(s));
		memset(ip, 0, sizeof(ip));
		memset(byte, 0, sizeof(byte));
		memset(mask, 0, sizeof(mask));
		int m0 = m;
		while (m--){
			rev = scanf("%s", s);
			rev = sscanf(s, "%d.%d.%d.%d", &byte[0], &byte[1], &byte[2], &byte[3]);
//			printf("%d %d %d %d\n", byte[0], byte[1], byte[2], byte[3]);
			for (int i = 0; i < 4; i++)
				tobin(byte[i], m, i);			
//			for (int i = 0; i < 32; i++)
//				printf("%d", ip[m][i]);
//			printf("\n");
		}
		int len = 32;
		for (int i = 0; i < 32; i++){
			int m1 = m0;
			while(m1--){
//				printf("%d %d\n", ip[m1][i], ip[0][i]);
				if (ip[m1][i] != ip[0][i]){len = i; goto end;}
			}	
		}
		end:
//		printf("len is %d\n", len);
		for (int i = 0; i < 32; i++){
			(i < len) ? mask[i] = 1 : mask[i] = 0;
			ip[0][i] &= mask[i];
		}
//		for (int i = 0; i < 32; i++)
//			printf("%d", ip[0][i]);
//		printf("\n");
		int n1, n2, n3, n4, n5, n6, n7, n8;
		n1 = n2 = n3 = n4 = n5 = n6 = n7 = n8 = 0;
		for (int i = 0, j = 7; i < 8; i++, j--)
			{n1 += ip[0][i]<<j; n5 += mask[i]<<j;}
		for (int i = 8, j = 7; i < 16; i++, j--)
			{n2 += ip[0][i]<<j; n6 += mask[i]<<j;}
		for (int i = 16, j = 7; i < 24; i++, j--)
			{n3 += ip[0][i]<<j; n7 += mask[i]<<j;}
		for (int i = 24, j = 7; i < 32; i++, j--)
			{n4 += ip[0][i]<<j; n8 += mask[i]<<j;}
		printf("%d.%d.%d.%d\n%d.%d.%d.%d\n",
		n1, n2, n3, n4, n5, n6, n7, n8);
	}
	return 0;
}

void tobin(int n, int m, int i)
{
	int j;
	switch (i)
	{
		case 0:
			j = 7;
			break;
		case 1:
			j = 15;
			break;
		case 2: 
			j = 23;
			break;
		case 3:
			j = 31;
			break;
	}
	while (n)
	{
		ip[m][j--] = n % 2;
		n /= 2;
	}
}

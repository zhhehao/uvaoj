#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>
//#include <time.h>
using namespace std;

char d1[50], d2[50][10], c1[200][15], c2[200][100], morse[100], dic[100][100];

int main(void)
{
	int rev, n;
	n = 0;
	memset(d1, '\0', sizeof(d1));
	memset(d2, '\0', sizeof(d2));
	memset(c1, '\0', sizeof(c1));
	memset(c2, '\0', sizeof(c2));
	while (1){
		rev = scanf("%s", &d1[n]);
		if (d1[n] == '*')
			break;
		rev = scanf("%s", d2[n++]);
	}
//	for (int i = 0; i < n; i++)
//		printf("%c %s\n", d1[i], d2[i]);
	n = 0;
	while (1){
		rev = scanf("%s", c1[n]);
		if (c1[n][0] == '*')
			break;
		int len = strlen(c1[n]);
//		printf("%s\nlen is %d\n",c1[n++], len);
		for (int i = 0; i < len; i++)
			for (int j = 0; d1[j] != '\0'; j++)
				if (c1[n][i] == d1[j])
					strcat(c2[n], d2[j]);
		n++;
	}
//	printf("n = %d\n", n);
//	for (int i = 0; i < n; i++)
//		printf("%s %s\n",c2[i], c1[i]);
	while (1){		
		memset(morse, '\0', sizeof(morse));
		memset(dic, '\0' , sizeof(dic));
		rev = scanf("%s", morse);
		if (morse[0] == '*')
			break;
		n = 0;
		for (int i = 0; c2[i][0] != '\0'; i++){
			if (((rev=strcmp(morse, c2[i]))==0) && (strlen(morse) == strlen(c2[i]))){
				strcpy(dic[n++],c1[i]);
			}
		}
		if (n == 1){
			printf("%s\n", dic[0]);
		}else if (n > 1){
			sort(dic[0], dic[0]+n-1);
			printf("%s!\n", dic[0]);
		}else if (n == 0){
			int mlen = strlen(morse);
			int clen = 1;
			while (1){
				for (int i = 0; c2[i][0] != '\0'; i++){
					if (((rev=strncmp(c2[i], morse, mlen))==0)&&(strlen(c2[i])-clen==mlen)){
						printf("%s?\n", c1[i]); goto here;
					}
					if (((rev=strncmp(morse, c2[i], mlen-clen)==0)&&(strlen(c2[i])+clen==mlen))){
						printf("%s?\n", c1[i]); goto here;
					}
				}
				clen++;
			}
			here:
			int m = 0;
		}
	}	
//	printf("Time used = %.2f\n", (double)clock() / CLOCKS_PER_SEC);
	return 0;
}


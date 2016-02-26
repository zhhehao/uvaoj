#include <stdio.h>
#include <string.h>

int ds[10][7000];
char p[5], si[7000];

int main(void)
{
	int rev, d, s, b;
	for (int kase = 1;; kase++){
		rev = scanf("%d", &d);
		if (d == 0) break;
		memset(p, '\0', sizeof(p));
		rev = scanf("%d%d%s", &s, &b, p);
		int vasum = (p[0] == 'E') ? 0 : 1;
		memset(ds, '\0', sizeof(ds));
		memset(si, '\0', sizeof(si));
		for (int i = 0; i < d; i++){
			rev = scanf("%s", si);
			for (int j = 0; si[j] != '\0'; j++)
				if (si[j] == 'x') {
//					int fo = 1;
///					int x = i;
//					int y = j % (s * d);
//					for (int k = 0; k < s; k++)
//						if (y==s*x+k)
//							fo = 0;
//					if (fo){
						ds[i][j] = 2;	
						ds[d][j] = 1;
//					}else
//						ds[i][j] = 0;
					}
				else
					ds[i][j] = si[j] - '0';
		}
		int len = s * b;
//		for (int i = 0; i <= d; i++){
//			for (int j = 0; j < len; j++)
//				printf("%d", ds[i][j]);
//			printf("\n");
//		}
		int xc, xp, sum, invalid = 0;
		for (int j = 0; j < len; j++){
			invalid = 0;
			sum = 0;
			xc = 0;
			xp = 0;
			for (int i = 0; i < d; i++){
				if (ds[d][j] == 1){
					if (ds[i][j] == 2) {
//						int eo = 1;
//						int x = i;
//						int y = j % (s * d);
//						for (int k = 0; k < s; k++)
//							if (y==s*x+k)
//								eo = 0;
//						if (eo){
							xc++;
							xp = i;
//						}
					}
				}else
					sum ^= ds[i][j];		
			}
			if (xc > 1){invalid = 1; goto iout;}
//			printf("sum is %d\n", sum);
			if ((ds[d][j] != 1) && (sum != vasum)){invalid = 1; goto iout;}
			if (xc == 1){
				sum = 0;
				for (int k = 0; k < d; k++)
					if (ds[k][j] != 2)
						sum ^= ds[k][j];
				ds[xp][j] = (sum == vasum) ? 0 : 1;		
			}
		}
//		for (int i = 0; i <= d; i++){
//			for (int j = 0; j < len; j++)
//				printf("%d", ds[i][j]);
//			printf("\n");
//		}
		printf("Disk set %d is valid, contents are: ", kase);
		int jump, outcount, outsum;
		jump = outsum = 0;
		outcount = 3;
		for (int k = 0; k < len; k += s){
			jump %= d;
			for (int i = 0; i < d; i++){
				for (int j = 0; j < s; j++){
					if (i == jump) break;
					if (outcount < 0) {
						outcount = 3;
						printf("%X", outsum);
						outsum = 0;
					}
//					printf("%d ", ds[i][j+k]);
					outsum += (ds[i][j+k]<<(outcount--));
				}
			}
			jump++;	
		}
//		if (outsum != 0)
			printf("%X", outsum);
		printf("\n");
		
	iout:
		if (invalid)
			printf("Disk set %d is invalid.\n", kase);
	}
	return 0;
}

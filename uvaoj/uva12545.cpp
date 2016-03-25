#include <cstdio>

const int maxn = 100 + 5;
char s[maxn], t[maxn];

int main() {
	int T, kase = 0; scanf("%d", &T);
	while (T--) {
		scanf("%s%s", s, t);
		int c1, c2, c3, c4;
		c1 = c2 = c3 = c4 = 0;
		for (int i = 0; s[i] != '\0'; i++) {
			if (s[i] == t[i]) continue;
			if (s[i] == '1' && t[i] == '0') c1++;
			else if (s[i] == '0' && t[i] == '1') c2++;
			else {
				if (t[i] == '1')
					c3++;
				else
					c4++;
			}
		}

		printf("Case %d: ", ++kase);
		if (c1 > c2+c3) {
			printf("-1\n");
		}
		else if (c1 <= c2){
			printf("%d\n", c2+c3+c4);
		}
		else {
			printf("%d\n", c1+c3+c4);
		}
	}
	return 0;
}

#include <cstdio>

int main() {
	int n, kase = 0;
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	while (scanf("%d", &n) != EOF) {
		if (kase++ > 0) printf("\n");
		printf("2 %d %d\n", n, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i <= 25)
					printf("%c", 'A'+i);
				else
					printf("%c", 'a'+i-26);
			}
			printf("\n");
		}
		printf("\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j <= 25)
					printf("%c", 'A'+j);
				else
					printf("%c", 'a'+j-26);
			}
			printf("\n");
		}
	}
	return 0;
}

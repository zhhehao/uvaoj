#include <cstdio>
#include <cmath>

int main() {
	int t;
	while (scanf("%d", &t) == 1 && t != -1) {
		int d, n, pos;
		while (t--) {
			scanf("%d%d", &d, &n) == 2;
			pos = 1;
			for (int i = 2; i <= d; i++) {
				if (n % 2 == 1) {
					pos = 2 * pos;
					n = (n + 1) / 2;
				}
				else {
					pos = 2 * pos + 1;
					n = n / 2;
				}
			}

			printf("%d\n", pos);
		}
	}
	return 0;
}

#include <cstdio>

int build() {
	int w1, d1, w2, d2;
	scanf("%d%d%d%d", &w1, &d1, &w2, &d2) == 1;
	if (w1 == 0)
		w1 = build();
	if (w2 == 0)
		w2 = build();
	if (w1 == -1 || w2 == -1)
		return -1;
	if (w1*d1 == w2*d2)
		return w1+w2;
	else
		return -1;
}

int main() {
	int t, kase = 1;
	scanf("%d", &t) == 1;
	while (t--) {
	if (kase++ > 1)
		printf("\n");
		if (build() == -1)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}

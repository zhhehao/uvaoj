#include <cstdio>
#include <cstring>
const int maxn = 500;
int lch[maxn], rch[maxn];
int min, max;

void build(int value, int pos, int dr) {
	int v;
	scanf("%d", &v) == 1;
	pos += dr;
	if (pos < min)
		min = pos;
	if (pos > max)
		max = pos;
	if (v != -1)
		build(v, pos, -1);
	scanf("%d", &v) == 1;
	if (v != -1)
		build(v, pos, 1);
	if (pos <= 0) 
		lch[pos * -1] += value;
	else
		rch[pos] += value;
}

int main() {
	int v, kase = 1;
	while(scanf("%d", &v) == 1 && v != -1) {
		memset(lch, 0, sizeof(lch));
		memset(rch, 0, sizeof(rch));
		min = max = 0;
		build(v, 0, 0);
		printf("Case %d:\n", kase++);
		for (int i = min * -1; i >= 0; i--) {
			if (i != min * -1)
				printf(" ");
			printf("%d", lch[i]);
		}
		for (int i = 1; i <= max; i++)
			printf(" %d", rch[i]);
		printf("\n\n");
	}
	return 0;
}

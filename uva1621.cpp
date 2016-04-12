#include <cstdio>

const int maxn = 15000 + 10;
int A, B, C, ans[maxn], cnt, pos;

void solve() {
	ans[0] = 0; cnt = 1; pos = 0;

	if (C % 3 == 0) {
		int ci = C / 3;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos += 3);
		ans[cnt++] = (pos += 1); A--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos -= 3);
		ans[cnt++] = (pos += 1); A--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos += 3);
	}
	else if (C % 3 == 1) {
		int ci = C / 3;
		for (int i = 0; i <= ci; i++) ans[cnt++] = (pos += 3);
		ans[cnt++] = (pos -= 2); B--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos -= 3);
		ans[cnt++] = (pos += 1); A--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos += 3);
		ans[cnt++] = (pos += 2); B--;
	}
	else {
		int ci = C / 3;
		for (int i = 0; i <= ci; i++) ans[cnt++] = (pos += 3);
		ans[cnt++] = (pos -= 1); A--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos -= 3);
		ans[cnt++] = (pos -= 1); A--;
		for (int i = 0; i <= ci; i++) ans[cnt++] = (pos += 3);
	}

	while (A > 1) {ans[cnt++] = (pos += 1); A--;}

	if (B % 2 == 0) {
		int bi = B / 2;
		for (int i = 0; i < bi; i++) ans[cnt++] = (pos += 2);
		ans[cnt++] = (pos += 1);
		for (int i = 0; i < bi; i++) ans[cnt++] = (pos -= 2);
	}
	else {
		int bi = B / 2 ;
		for (int i = 0; i <= bi; i++) ans[cnt++] = (pos += 2);
		ans[cnt++] = (pos -= 1);
		for (int i = 0; i < bi; i++) ans[cnt++] = (pos -= 2);
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &A, &B, &C);
		int end = A + B + C;
		solve();
		for (int i = 0; i <= end; i++) {
			if (i != 0) printf(" ");
			printf("%d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}

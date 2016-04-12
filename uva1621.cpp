#include <cstdio>

const int maxn = 15000 + 10;
int A, B, C, ans[maxn], cnt, pos;

void solve_3() {
	if (C % 3 == 0) {
		int ci = C / 3;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos += 3);
		ans[cnt++] = (pos += 1); A--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos -= 3);
		ans[cnt++] = (pos += 1); A--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos += 3);
		C = 0;
	}
	else if (C % 3 == 2) {
		int ci = (C-2) / 3;
		for (int i = 0; i <= ci; i++) ans[cnt++] = (pos += 3);
		ans[cnt++] = (pos -= 1); A--;
		for (int i = 0; i < ci; i++) ans[cnt++] = (pos -= 3);
		ans[cnt++] = (pos -= 1); A--;
		for (int i = 0; i <= ci; i++) ans[cnt++] = (pos += 3);
		C = 0;
	}
}

void solve_2() {
	while (A > 2) {ans[cnt++] = pos++; A--;}

	if (C) {
		if (B == 1) {
			while (A > 1) {ans[cnt++] = pos++; A--;}
			ans[cnt++] = (pos += 3);
			ans[cnt++] = (pos -= 2);
			ans[cnt++] = (pos += 1);
			return;
		}
		else {
			ans[cnt++] = (pos += 3);
			if (B)
				ans[cnt++] = (pos -= 2);
			if (A)
				ans[cnt++] = (pos += 1);
			A--; B--;
			if (B >= 1) {
				ans[cnt++] = (pos += 2);
				B--;
			}
		}
	}

	while (A > 1) {ans[cnt++] = pos++; A--;}

	if (B % 2 == 0) {
		int bi = B / 2;
		for (int i = 0; i < bi; i++) ans[cnt++] = (pos += 2);
		if (A)
			ans[cnt++] = (pos += 1);
		for (int i = 0; i < bi; i++) ans[cnt++] = (pos -= 2);
	}
	else {
		if (B == 1) {
			ans[cnt++] = (pos += 2);
			if (A)
				ans[cnt++] = (pos -= 1);
		}
		else {
			int bi = B / 2 + 1;
			for (int i = 0; i < bi; i++) ans[cnt++] = (pos += 2);
			if (A)
				ans[cnt++] = (pos -= 1);
			for (int i = 0; i < bi - 1; i++) ans[cnt++] = (pos -= 2);
		}
	}
}


int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &A, &B, &C);
		int end = A + B + C;
		ans[0] = 0; cnt = 1, pos = 0;
		if (C % 3 == 1) {
			C--;
			solve_3();
			C++;
			solve_2();
		}
		else {
			solve_3();
			solve_2();
		}

		for (int i = 0; i <= end; i++) {
			if (i != 0) printf(" ");
			printf("%d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}

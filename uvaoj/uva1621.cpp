#include <cstdio>

int A, B, C, pos;

void solve() {
	pos = 0;
	printf("0");

	if (C % 3 == 0) {
		int ci = C / 3;
		for (int i = 0; i < ci; i++) {pos += 3; printf(" %d", pos);}
		pos += 1; printf(" %d", pos);
		for (int i = 0; i < ci; i++) {pos -= 3; printf(" %d", pos);}
		pos += 1; printf(" %d", pos);
		for (int i = 0; i < ci; i++) {pos += 3; printf(" %d", pos);}
		A -= 2;
	}
	else if (C % 3 == 1) {
		int ci = (C-1) / 3;
		for (int i = 0; i <= ci; i++) {pos += 3; printf(" %d", pos);}
		pos -= 2; printf(" %d", pos);
		for (int i = 0; i < ci; i++) {pos -= 3; printf(" %d", pos);}
		pos += 1; printf(" %d", pos);
		for (int i = 0; i < ci; i++) {pos += 3; printf(" %d", pos);}
		pos += 2; printf(" %d", pos);
		A--; B -= 2;
	}
	else if (C % 3 == 2) {
		int ci = (C-2) / 3;
		for (int i = 0; i <= ci; i++) {pos += 3; printf(" %d", pos);}
		pos -= 1; printf(" %d", pos);
		for (int i = 0; i < ci; i++) {pos -= 3; printf(" %d", pos);}
		pos -= 1; printf(" %d", pos);
		for (int i = 0; i <= ci; i++) {pos += 3; printf(" %d", pos);}
		A -= 2;
	}

	while (A > 1) {pos += 1; printf(" %d", pos); A--;}

	if (B % 2 == 0) {
		int bi = B / 2;
		for (int i = 0; i < bi; i++) {pos += 2; printf(" %d", pos);}
		pos += 1; printf(" %d", pos);
		for (int i = 0; i < bi; i++) {pos -= 2; printf(" %d", pos);}
	}
	else {
		int bi = (B-1) / 2 ;
		for (int i = 0; i <= bi; i++) {pos += 2; printf(" %d", pos);}
		pos -= 1; printf(" %d", pos);
		for (int i = 0; i < bi; i++) {pos -= 2; printf(" %d", pos);}
	}
	printf("\n");
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &A, &B, &C);
		solve();
	}
	return 0;
}

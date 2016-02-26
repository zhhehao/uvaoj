#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 64 + 5;

char board[maxn][maxn];
vector<int> path, ans;

int allchk(int x, int y, int n) {
	bool allw, allb; allw = true; allb = true;
	for (int i = x; i < x+n; i++) 
		for (int j = y; j < y+n; j++) {
			if (board[i][j] == '0')	allb = false;
			if (board[i][j] == '1') allw = false;
			if (!allb && !allw) break;
		}
	if (allw) return 0;
	else if (allb) return 1;
	else return 2;
}

void gennum() {
	int len = path.size() - 2; int sum = 0;
	for (int i = path.size() - 1; i > 0; i--) {
		sum += path[i] * pow(5, len--);
	}
	ans.push_back(sum);
}

void build(int x, int y, int l, int p) {
	path.push_back(p); int checked = allchk(x, y, l);
	if (checked == 1) {gennum(); path.pop_back(); return;}
	if (checked == 0) {path.pop_back(); return;}
	build(x, y, l/2, 1);
	build(x, y+l/2, l/2, 2);
	build(x+l/2, y, l/2, 3);
	build(x+l/2, y+l/2, l/2, 4);
	path.pop_back();
}

void outnum(int n) {
	memset(board, '\0', sizeof(board));
	for (int i = 0; i < n; i++) scanf("%s", board[i]) == 1;
	if (allchk(0, 0, n) == 0) {
		printf("Total number of black nodes = 0\n"); return;
	}
	if (allchk(0, 0, n) == 1) {
		printf("0\nTotal number of black nodes = 1\n"); return;
	}
	path.clear(); ans.clear();
	build(0, 0, n, 0);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) {
		if (i%12 != 0) printf(" ");
		if (i >= 12 && i%12 == 0) printf("\n");
		printf("%d", ans[i]);
	}
	printf("\nTotal number of black nodes = %d\n", ans.size());
}

void pr(int c, int n) {
	char ch;
	if (c == 0) ch = '.';
	else if (c == 1) ch = '*';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%c", ch);
		printf("\n");
	}
}

void draw(int num, int len) {
	vector<int> v; v.clear();
	do {
		v.push_back(num%5);
		num /= 5;
	} while (num > 0);
	int x, y; x = y = 0;
	for (int i = 0; i < v.size(); i++) {
		len /= 2;
		switch (v[i]) {
			case 2:
				y += len; break;
			case 3:
				x += len; break;
			case 4:
				x += len; y += len; break;
		}	
	}
	for (int i = x; i < x+len; i++)
		for (int j = y; j < y+len; j++)
			board[i][j] = '*';
}

void outpic(int n) {
	memset(board, '.', sizeof(board));	
	n = n * -1; int num; bool allw = true; bool allb = false;
	while (scanf("%d", &num) == 1 && num != -1) {
		allw = false;
		if (num == 0) allb = true;
		draw(num, n);
	}
	if (allb) {pr(1, n); return;}
	if (allw) {pr(0, n); return;}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
}

int main() {
	int n, image = 1;
	while (scanf("%d", &n) == 1 && n != 0) {
		if (image > 1) printf("\n");
		printf("Image %d\n", image++);
		if (n > 0) outnum(n);
		else outpic(n);
	}
	return 0;
}

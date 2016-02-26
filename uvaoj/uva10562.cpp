#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int maxn = 200 + 5;
char tree[maxn][maxn];

void ptree(int x, int y) {
	printf("%c(", tree[x][y]);
	if (tree[x+1][y] == '|') {
		int ys, ye; ys = ye = y; int tx = x+2;
		while (tree[tx][ys-1] == '-') ys--;
		while (tree[tx][ye+1] == '-') ye++;
		tx++;
		for(int i = ys; i <= ye; i++)
			if (tree[tx][i] > 32 && tree[tx][i] != '-' && tree[tx][i] != '#'
				&& tree[tx][i] != '|')
				ptree(tx, i);
	}
	printf(")");
}

int main() {
	int t; scanf("%d", &t) == 1;string line;
	getline(cin, line);
	while (t--) {
		memset(tree, '\0', sizeof(tree));
		int cnt = 0;
		while (getline(cin, line) && line[0] != '#') {
			for (int i = 0; i < line.size(); i++)
				tree[cnt][i] = line[i];
			cnt++;
		}
		printf("(");
		for (int i = 0; i < maxn; i++)
			if (tree[0][i] >= '!' ) {
				ptree(0, i);
				break;
			}
		printf(")\n");

		
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 10; j++)
//				cout << tree[i][j];
//			cout << endl;
//		}
	}
	return 0;
}

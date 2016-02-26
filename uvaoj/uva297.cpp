#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
int buf[32][32];

void draw(int r, int c, int len) {
	len /= 2;
	int r1, c1, r2, c2, r3, c3, r4, c4;
	r1 = r; c1 = c + len;
	r2 = r; c2 = c;
	r3 = r + len; c3 = c;
	r4 = r + len; c4 = c + len;
	int cnt = 0, t = 4;
	char ch;
	while (t--) {
		scanf("%c", &ch) == 1; cnt++;
		if (ch == 'p') {
			if (cnt == 1)
				draw(r1, c1, len);
			else if (cnt == 2)
				draw(r2, c2, len);
			else if (cnt == 3)
				draw(r3, c3, len);
			else
				draw(r4, c4, len);
		}
		else if (ch == 'f') {
			int row, col;
			if (cnt == 1) {row = r1; col = c1;}
			else if (cnt == 2) {row = r2; col = c2;}
			else if (cnt == 3) {row = r3; col = c3;}
			else {row = r4; col = c4;}
			for (int i = row; i < row+len; i++)
				for (int j = col; j < col+len; j++)
					buf[i][j] = 1;
//			for (int i = 0; i < 32; i++) {
//				for (int j = 0; j < 32; j++)
//					printf("%d ", buf[i][j]);
//				printf("\n");
//			}
//			printf("\n");
		}
	}
}

int main() {
	int t;
	scanf("%d", &t) == 1;
	while (t--) {
		string str;
		memset(buf, 0, sizeof(buf));
		int ans = 0;
		bool isblack = false;
		char ch1, ch2;
		getline(cin, str);
		scanf("%c", &ch1) == 1;
		if (ch1 == 'f')
			isblack = true;
		else if (ch1 == 'p')
			draw(0, 0, 32);
		getline(cin, str);
		scanf("%c", &ch2) == 1;
		if (ch2 == 'f')
			isblack = true;
		else if (ch2 == 'p')
			draw(0, 0, 32);

		if (isblack)
			printf("There are 1024 black pixels.\n");
		else if (ch1 == 'w' && ch2 == 'w')
			printf("There are 0 black pixels.\n");
		else {
			for (int i = 0; i < 32; i++)
				for (int j = 0; j < 32; j++)
					if (buf[i][j] == 1)
						ans++;
			printf("There are %d black pixels.\n", ans);
		}
	}
	return 0;
}

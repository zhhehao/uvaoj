#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 200 + 5;
int buf[maxn][maxn];
char s[maxn];
int m, n, blank;

void color(int x, int y, int v) {
	if (x < 0 || y < 0 || x >= m || y >= 4*n) return;
	if (buf[x][y] != 0) return;
	buf[x][y] = v;
	color(x-1, y, v);
	color(x+1, y, v);
	color(x, y-1, v);
	color(x, y+1, v);
}

void sblank(int x, int y, int v) {
	if (x < 0 || y < 0 || x >= m || y >= 4*n) return;
	if (buf[x][y] == 2 || buf[x][y] == v) return;
	if (buf[x][y] == 0) {
		color(x, y, v);
		blank++;
	}
	buf[x][y] = v;
	sblank(x-1, y, v);
//	sblank(x-1, y-1, v);
//	sblank(x-1, y+1, v);
	sblank(x, y-1, v);
	sblank(x, y+1, v);
	sblank(x+1, y, v);
//	sblank(x+1, y+1, v);
//	sblank(x+1, y-1, v);
}

int main() {
	int kase = 1;
	while(scanf("%d%d", &m, &n) == 2 && m != 0) {
		memset(buf, 0, sizeof(buf));
		memset(s, '\0', sizeof(s));
		for (int i = 0; i < m; i++) { // 输入图形 1色
			scanf("%s", s) == 1;	
			for (int j = 0; j < n; j++) {
				int value;
				if (isalpha(s[j]))
					value = s[j] - 'a' + 10;
				else
					value = s[j] - '0';
				switch (value) {
					case 0: {break;}
					case 1: {buf[i][4*j+3]=1;break;}
					case 2: {buf[i][4*j+2]=1;break;}
					case 3:	{buf[i][4*j+2]=1;buf[i][4*j+3]=1;break;}
					case 4:	{buf[i][4*j+1]=1;break;}
					case 5: {buf[i][4*j+1]=1;buf[i][4*j+3]=1;break;}
					case 6: {buf[i][4*j+1]=1;buf[i][4*j+2]=1;break;}
					case 7: {buf[i][4*j+1]=1;buf[i][4*j+2]=1;buf[i][4*j+3]=1;break;}
					case 8: {buf[i][4*j]=1;break;}
					case 9: {buf[i][4*j]=1;buf[i][4*j+3]=1;break;}
					case 10: {buf[i][4*j]=1;buf[i][4*j+2]=1;break;}
					case 11: {buf[i][4*j]=1;buf[i][4*j+2]=1;buf[i][4*j+3]=1;break;}
					case 12: {buf[i][4*j]=1;buf[i][4*j+1]=1;break;}
					case 13: {buf[i][4*j]=1;buf[i][4*j+1]=1;buf[i][4*j+3]=1;break;}
					case 14: {buf[i][4*j]=1;buf[i][4*j+1]=1;buf[i][4*j+2]=1;break;}
					case 15: {buf[i][4*j]=1;buf[i][4*j+1]=1;
							  buf[i][4*j+2]=1;buf[i][4*j+3]=1;break;}
				}	
			}
		}
//		for (int i = 0; i < m; i++) {
//			for (int j = 0; j < 4*n; j++)
//				printf("%d", buf[i][j]);
//			printf("\n");
//		}

		// 背景上色 2色
		for (int i = 0; i < 4*n; i++)
			if (buf[0][i] == 0) color(0, i, 2);
		for (int i = 0; i < 4*n; i++)
			if (buf[m-1][i] == 0) color(m-1, i, 2);
		for (int i = 0; i < m; i++)
			if (buf[i][0] == 0) color(i, 0, 2);
		for (int i = 0; i < m; i++)
			if (buf[i][4*n-1] == 0) color(i, 4*n-1, 2);
		// 查找图形，并数空白处 
//		for (int i = 0; i < m; i++) {
//			for (int j = 0; j < 4*n; j++)
//				printf("%d", buf[i][j]);
//			printf("\n");
//		}
		vector<char> ans;
		ans.clear();
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < 4*n; j++) {
				if (buf[i][j] == 1)	{
					blank = 0;
					sblank(i, j, 5);
					switch (blank+1) {
						case 1: ans.push_back('W');break;
						case 2: ans.push_back('A');break;
						case 3: ans.push_back('K');break;
						case 4: ans.push_back('J');break;
						case 5: ans.push_back('S');break;
						case 6: ans.push_back('D');break;
					}
				}
			}
		}
		sort(ans.begin(), ans.end());
//		printf("%d\n", blank);
		printf("Case %d: ", kase++);
		for (int i = 0; i < ans.size(); i++)
			printf("%c", ans[i]);
		printf("\n");
	}
	return 0;
}


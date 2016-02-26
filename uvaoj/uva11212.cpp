#include <cstdio>
#include <cstring>
const int maxn = 10 + 1;
int book[maxn], obj[maxn], n, maxd;

int h() {
	int cnt = 0;
	for (int i = 0; i < n-1; i++)
		if (book[i]+1 != book[i+1]) cnt++;
	if (book[n-1] != n) cnt++;
	return cnt;
}

int dfs(int d) {
	if (d*3 + h() > maxd*3) return -1;
	else {
		int cmp[maxn], tmp[maxn];
		memcpy(tmp, book, sizeof(book));
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++) {
				int cnt = 0;
				for (int k = 0; k < n; k++)
					if (k < i || k > j) cmp[cnt++] = book[k];
				for (int k = 0; k <= cnt; k++) {
					int cnt2 = 0;
					for (int p = 0; p < k; p++) book[cnt2++] = cmp[p];
					for (int p = i; p <=j; p++) book[cnt2++] = tmp[p];
					for (int p = k; p < cnt; p++) book[cnt2++] = cmp[p];
//					printf("d is %d\n", d);
//					for (int i = 0; i < n; i++) printf("%d %d\n", book[i], obj[i]);
					if (memcmp(book, obj, sizeof(obj)) == 0) return d;
					int ans = dfs(d+1);
					if (ans > 0) return ans;
					memcpy(book, tmp, sizeof(book));
				}
			}
	}
	return -1;
}

int main() {
	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		memset(book, 0, sizeof(book));
		int num, cnt = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &num) == 1;
			book[i] = num - 1; // 为了使数组值和下标一致
			if (book[i] == i) cnt++;
		}
		memset(obj, 0, sizeof(obj));
		for (int i = 0; i < n; i++) obj[i] = i;
//		for (int i = 0; i < n; i++) printf("%d ", obj[i]); printf("\n");
		if (cnt == n) {
			printf("Case %d: %d\n", ++kase, 0);
			continue;
		}
		// 迭代加深搜索
		int ans;
		for (maxd = 2; maxd <= 7 ; maxd++) {
//			printf("maxd is %d\n", maxd);
			ans = dfs(1);
			if (ans > 0) break;
		}
		printf("Case %d: %d\n", ++kase, ans);
	}
	return 0; 
}

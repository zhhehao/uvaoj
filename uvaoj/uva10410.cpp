#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
vector<vector<int> > ans;
vector<int> bfs, dfs;

void init(int n) {
	int num;
	for (int i = 0; i < n; i++) {
		scanf("%d", &num);
		bfs.push_back(num);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &num);	
		dfs.push_back(num);
	}
}

void solve() {
	while (bfs.size() > 1) {
		int node = bfs.back();
		int pos1, pos2; pos1 = bfs.size() - 2;
		for (int i = 0; i < dfs.size(); i++) {
			if (dfs[i] == node){
				pos2 = i - 1; 
				while (dfs[pos2] == bfs[pos1]) {
					if (pos2 == 0) break;
					pos2--; pos1--;
				}
				ans[dfs[pos2]-1].push_back(node);
				bfs.pop_back();
				dfs.erase(dfs.begin()+i);
				break;
			}			
		}
	}
}

int main() {
	int n; 
	while (scanf("%d", &n) != EOF) {
		ans.clear(); dfs.clear(); bfs.clear();
		for (int i = 0; i < n; i++) ans.push_back(vector<int>());
		init(n);
		solve();
		for (int i = 0; i < n; i++) {
			printf("%d:", i+1);
			sort(ans[i].begin(), ans[i].end());
			for (int j = 0; j < ans[i].size(); j++)
				printf(" %d", ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 256 + 20;

int left[maxn], right[maxn], value[maxn];
bool have_value[maxn];

const int root = 1;
int cnt;
void newtree() {
	left[root] = 0;
	right[root] = 0;
	have_value[root] = false;
	cnt = root;
}

int newnote() {
	int u = ++cnt;
	left[u] = 0;
	right[u] = 0;
	have_value[u] = false;
	return u;
}

bool failed;

void addnote(int v, char* s) {
	int n = strlen(s);
	int u = root;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'L') {
			if (left[u] == 0) left[u] = newnote();
			u = left[u];
		}
		else if (s[i] == 'R') {
			if (right[u] == 0) right[u] = newnote();
			u = right[u];
		}
	}
	if (have_value[u]) failed = true;
	value[u] = v;
	have_value[u] = true;
}

char s[maxn];
bool readin() {
	failed = false;
	newtree();
	for (;;) {
		if (scanf("%s", s) != 1) return false;
		if (!strcmp(s, "()")) break;
		int v;
		sscanf(s+1, "%d", &v);
		addnote(v, strchr(s, ',')+1);
	}
	return true;
}

bool bfs(vector<int>& ans) {
	ans.clear();
	queue<int> q;
	q.push(root);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (!have_value[u]) return false;
		if (left[u] != 0) q.push(left[u]);
		if (right[u] != 0) q.push(right[u]);
		ans.push_back(value[u]);
	}
	return true;
}

int main() {
	while (readin()) {
		if (failed) {printf("not complete\n"); continue;}
		vector<int> ans;
		if (!bfs(ans)) printf("not complete\n");
		else {
			for (int i = 0; i < ans.size(); i++) {
				if (i != 0) printf(" ");
				printf("%d", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}

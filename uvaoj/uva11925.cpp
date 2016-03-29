#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int n;
vector<int> ans, s;

int main() {
	while (scanf("%d", &n) == 1 && n) {
		ans.clear(); s.clear();
		int num;
		for (int i = 0; i < n; i++) {
			scanf("%d", &num);
			s.push_back(num);
		}
		for (;;) {
			if (s[0] == 1) {
				int ok = 1;
				for (int i = 0; i < n; i++)
					if (s[i] != i+1) {
						ok = 0; break;
					}
				if (ok) break;
			}
			if ((s[0] < s[1]) || (s[0] == n && s[1] == 1)) {
				ans.push_back(2);
				s.insert(s.begin(), s[n-1]);
				s.pop_back();
			}
			else {
				ans.push_back(1);
				swap(s[0], s[1]);
			}
		}
		for (int i = ans.size()-1; i >= 0; i--)
			printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}

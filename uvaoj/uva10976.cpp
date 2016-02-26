#include <cstdio>
#include <vector>
using namespace std;
vector<int> ans;

int main() {
	int k;
	while (scanf("%d", &k) != EOF) {
		int x, y; ans.clear();
		for (int y = k+1; y <= 2*k; y++)
			if (k*y % (y-k) == 0) 
				ans.push_back(y);
		printf("%d\n", ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf("1/%d = 1/%d + 1/%d\n", k, k*ans[i]/(ans[i]-k), ans[i]);
	}
	return 0;
}

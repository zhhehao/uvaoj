#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 10000 + 5;
int c[maxn], n;

struct Step{
	int s, e;
};

vector<Step> step;

int findR(int L, int R) {
	for (int i = L; i <= R; i++)
		if (c[i] == R) return i;
}

void oper(int pos, int R) {
	if (pos == R) return;
	if ((R-pos+1)%2 == 0) {
		Step st; st.s = pos; st.e = R;
		step.push_back(st);
		int width = (R-pos+1)/2;
		for (int i = 0; i < width; i++)
			swap(c[pos+i], c[pos+width+i]);
		pos += width;
		oper(pos, R);
	}
	else {
		Step st; st.s = pos; st.e = R-1;
		step.push_back(st);
		int width = (R-pos)/2;
		for (int i = 0; i < width; i++)
			swap(c[pos+i], c[pos+width+i]);
		pos += width;
		oper(pos, R);
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
		int L = 1, R = n;
		while (c[L] == L) L++;
		while (c[R] == R) R--;
		step.clear();

		while (L < R) {
			int pos = findR(L, R);
			oper(pos, R);
			while (c[L] == L) L++;
			while (c[R] == R) R--;
		}

		printf("%d\n", step.size());
		if (step.size()) {
			for (int i = 0; i < step.size(); i++)
				printf("%d %d\n", step[i].s, step[i].e);
		}
	}
	return 0;
}

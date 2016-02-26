#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
const int maxn = 10000 + 5;
int ltree[maxn], rtree[maxn], value[maxn], sum[maxn], io[maxn], po[maxn];

const int root = 1;
int cnt;
void newtree() {
	ltree[root]=0; rtree[root]=0; sum[root]=0; cnt=root;
}
int newnode() {
	int u = ++cnt;
	ltree[u]=0; rtree[u]=0; sum[u]=0; return u;
}

void createtree(int rnode, int rpos, int ll, int rr, int polen) {
	int u = rnode;
	
	if (rpos - ll == 1) {
		if (ltree[u] == 0) ltree[u] = newnode();
		value[ltree[u]] = io[ll];
		sum[ltree[u]] += value[ltree[u]] + sum[u];
	}
	if (rr - rpos == 1) {
		if (rtree[u] == 0) rtree[u] = newnode();
		value[rtree[u]] = io[rr];
		sum[rtree[u]] += value[rtree[u]] + sum[u];
	}
	if (rpos - ll > 1) {
		int maxvalue = 0;
		int maxpos;
		for (int i = ll; i <= rpos - 1; i++) { 
			for (int j = polen - 1; j >= 0; j--) {
				if (io[i] == po[j]) {
					if (j > maxvalue) {
						maxvalue = j;
						maxpos = i;
					}
					break;
				}
			}
		}
		if (ltree[u] == 0) ltree[u] = newnode();
		value[ltree[u]]= io[maxpos];
		sum[ltree[u]] += value[ltree[u]] + sum[u];
		createtree(ltree[u], maxpos, ll, rpos-1, polen);
	}
	if (rr - rpos > 1) {
		int maxvalue = 0;
		int maxpos = 0;
		for (int i = rpos + 1; i <= rr; i++) { 
			for (int j = polen - 1; j >= 0; j--) {
				if (io[i] == po[j]) {
					if (j > maxvalue) {
						maxvalue = j;
						maxpos = i;
					}
					break;
				}
			}
		}
		if (rtree[u] == 0) rtree[u] = newnode();
		value[rtree[u]]= io[maxpos];
		sum[rtree[u]] += value[rtree[u]] + sum[u];
		createtree(rtree[u], maxpos, rpos+1, rr, polen);
	}
}

struct Answer {
	int value, sum;
	bool operator < (const Answer& b) const {
		if (sum == b.sum)
			return value < b.value;
		else
			return sum < b.sum;
	}
};

/*bool cmp(Answer& a, Answer& b) {
	if (a.sum == b.sum)
		return a.value < b.value;
	else
		return a.sum < b.sum;
}*/

int main() {
	string str1, str2;
	while (getline(cin, str1), getline(cin, str2)) {
		int iolen = 0, polen = 0;
		stringstream ss1(str1); while (ss1 >> io[iolen]) iolen++;
		stringstream ss2(str2); while (ss2 >> po[polen]) polen++;
		newtree();
		int rpos;
		for (int i = 0; i < iolen; i++)
			if (io[i] == po[polen-1]) {
				rpos = i; break;
			}
		value[root] = io[rpos];
		sum[root] = value[root];
		createtree(root, rpos, 0, polen-1, polen);
		vector<Answer> ans;
		Answer answer;
		for (int i = 1; i <= iolen; i++) {
			if (ltree[i] == 0 && rtree[i] == 0) {
				answer.value = value[i];
				answer.sum = sum[i];
				ans.push_back(answer);
			}
		}
		sort(ans.begin(), ans.end());
		cout << ans[0].value << endl;

/*		for (int i = 0; i <= iolen; i++) {
			cout << ltree[i] << "  ";
		}
		cout << endl;
		for (int i = 0; i <= iolen; i++) {
			cout << value[i] << "  ";
		}
		cout << endl;

		for (int i = 0; i <= iolen; i++) {
			cout << rtree[i] << "  ";
		}
		cout << endl;
		for (int i = 0; i <= iolen; i++) {
			cout << sum[i] << "  ";
		}
		cout << endl << endl;*/
	}
	return 0;
}

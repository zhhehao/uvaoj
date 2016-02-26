#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;

struct Point {
	int x, y;
};

const int FT = 500000;
const int MAXN = 1000 + 5;
set<int> s[MAXN];

int ftest(set<int>& snum) {
	vector<int> v;
	for (set<int>::iterator it = snum.begin(); it != snum.end(); ++it)
		v.push_back(*it);
	if (v.size()%2 == 0) {
		bool tok = true;
		int end = v.size()/2 - 1;
		int mid = v[0] + v[v.size()-1];
		for (int i = 1, j = v.size()-2; i <= end; i++, j--) {
			if (mid != v[i]+v[j]) {
				tok = false;
				break;
			}
		}
		if (tok)
			return mid;
		else
			return FT;
	}else {
		bool tok = true;
		int mid = v[0] + v[v.size()-1];
		if (mid != (v[v.size()/2])*2)
			return FT;
		for (int i = 0, j = v.size()-1; i < v.size()/2; i++, j--) {
			if (mid != v[i]+v[j]) {
				tok = false;
				break;
			}
		}
		if (tok)
			return mid;
		else
			return FT;
	}
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		Point p;
		map<int, int> m;
		for (int i = 0; i < MAXN; i++)
			s[i].clear();
		while (n--) {
			cin >> p.x >> p.y;
			if (m.count(p.y)) {
				if (!s[m[p.y]].count(p.x))
					s[m[p.y]].insert(p.x);
			}else {
				int size = m.size();
				s[size].insert(p.x);
				m[p.y] = size;
			}
		}
		if (m.size() == 1) {
			int result;
			result = ftest(s[0]);
			if (result != FT)
				cout << "YES\n";
			else
				cout << "NO\n";
			goto end;
		}
		int sym;
		sym = FT;
		for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
			int snum;
			snum = ftest(s[it->second]);
			if (snum == FT) {
				cout << "NO\n";
				goto end;
			}
			if (sym == FT)
				sym = snum;
			else {
				if (sym != snum) {
					cout << "NO\n";
					goto end;
				}
			}
		}

		cout << "YES\n";
		end:
		m.clear();
	}
	return 0;
}

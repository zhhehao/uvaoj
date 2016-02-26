#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

void ducci(vector<int>& v) {
	int v0 = v[0];
	for (int i = 0; i < v.size()-1; i++) {
		v[i] = fabs(v[i]-v[i+1]);
	}
	v[v.size()-1] = fabs(v[v.size()-1] - v0);
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		vector<int> v;
		set<vector<int> > s;
		int m;
		cin >> m;
		int num;
		while (m--) {
			cin >> num;
			v.push_back(num);
		}
		s.insert(v);
		for (;;) {
			bool zero = true;
			ducci(v);
			for (int i = 0; i < v.size(); i++) {
				if (v[i] != 0) {
					zero = false;
					break;
				}
			}
			if (zero) {
				cout << "ZERO\n";
				break;
			}
			if (s.count(v)) {
				cout << "LOOP\n";
				break;
			} else {
				s.insert(v);
			}
		}	
		v.resize(0);
		s.clear();
	}
	return 0;
}

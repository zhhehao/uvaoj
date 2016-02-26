#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	int n;
	vector<string> s;
	while (cin >> n) {
		s.clear();
		string st;
		int maxl = 0;
		for (int i = 0; i < n; i++) {
			cin >> st;
			maxl = (maxl < st.length()) ? st.length() : maxl;
			s.push_back(st);
		}
		sort(s.begin(), s.end());
		int colu = (60 - maxl) / (maxl + 2) + 1;
		int row = (n % colu == 0) ? n / colu : n / colu + 1;
		if (s.size()%row == 0)
			colu = s.size() / row;
		else
			colu = s.size() / row + 1;
		int end = s.size() % row;
		if (end == 0)
			end = row;
		for (int i = 0; i < 60; i++)
			cout << "-";
		cout << endl;
		for (int i = 0; i < row; i++) {
			int num = 1;
			for (int j = 0; j < colu-1; j++) {
				if (num++ > 1) cout << "  ";
				cout << left << setw(maxl) << s[i+j*row];
			}
			if (end-- > 0) {
				if (num++ > 1) cout << "  ";
				cout << left << setw(maxl) << s[i+(colu-1)*row];
			}
			cout << endl;
		}

	}
	return 0;
}

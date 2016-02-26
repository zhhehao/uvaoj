#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Matrix {
	int row, col;
};

bool mcm(Matrix& ma, Matrix& mb, Matrix& mc, int& ans) {
	if (ma.col != mb.row)
		return false;
	ans += ma.row * ma.col * mb.col;
	mc.row = ma.row;
	mc.col = mb.col;
	return true;
}

int main() {
	int n; 
	cin >> n;
	Matrix a[26];
	char name;
	for (int i = 0; i < n; i++) {
		Matrix m;
		cin >> name >> m.row >> m.col;
		a[name-'A'] = m;
	}
	string str;
	getline(cin, str);
	while (getline(cin, str)) {
		if (str.size() == 1) {
			cout << "0\n";
			continue;
		}
		int ans = 0;
		stack<Matrix> s;
		while (!s.empty()) s.pop();
		for (int i = 0; i < str.size(); i++) {
			if (str[i] >= 'A' && str[i] <= 'Z')
				s.push(a[str[i]-'A']);
			else if (str[i] == ')') {
				if (s.size() >= 2) {
					Matrix mb = s.top();
					s.pop();
					Matrix ma = s.top();
					s.pop();
					Matrix mc;
					if (!mcm(ma, mb, mc, ans)) {
						cout << "error\n";
						goto end;
					}
					s.push(mc);
				}
			}
		}
		cout << ans << endl;
		end:
		continue;
	}
	return 0;
}

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

vector<string> v;
vector<string> ans;
map<string, int> m;

string repr(const string& s) {
	string ans = s;
	for (int i = 0; i < ans.length(); i++)
		ans[i] = tolower(ans[i]);
	sort(ans.begin(), ans.end());
	return ans;
}

int main() {
	string s;
	while (cin >> s) {
		if (s[0] == '#') break;
		v.push_back(s);
		string r = repr(s);
		if (!m.count(r)) m[r] = 0;
		m[r]++;
	}
	for (int i = 0; i < v.size(); i++)
		if (m[repr(v[i])] == 1)
			ans.push_back(v[i]);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << "\n";

	return 0;
}

#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int main() {
	string str;
	set<string> dict;
	vector<string> v;
	while (cin >> str) {
		if (!dict.count(str)) {
			dict.insert(str);
			if (str.length() > 1) {
				v.push_back(str);
			}
		}
	}
	set<string> sout;
	for (int i = 0; i < v.size(); i++) {
		string str1, str2;
		for (int j = 1; j < v[i].length(); j++) {
			str1 = v[i].substr(0, j);
//			cout << str1 << endl;
			if (dict.count(str1)) {
				str2 = v[i].substr(j);
				if (dict.count(str2)) {
					if (!sout.count(v[i])) {
						cout << v[i] << endl;
						sout.insert(v[i]);
					}
				}
			}
		}
	}

	dict.clear();
	sout.clear();
	v.resize(0);
	return 0;
}

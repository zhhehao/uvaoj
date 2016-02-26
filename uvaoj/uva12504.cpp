#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cctype>
#include <iterator>
using namespace std;

void initstr(string& s);
void initdict(string& s, map<string, string>& m, vector<string>& v);

int main() {
	int t; 
	cin >> t; // 读入case数目
	string str;
	getline(cin, str); // 读掉一个换行符
	while (t--) {
		// 读入两个字典
		string oldstr, newstr;
		getline(cin, oldstr);
		getline(cin, newstr);
		initstr(oldstr);
		initstr(newstr);
		// 把key和value存储起来
		map<string, string> mold;
		map<string, string> mnew;
		vector<string> vold;
		vector<string> vnew;
		initdict(oldstr, mold, vold);
		initdict(newstr, mnew, vnew);

		sort(vold.begin(), vold.end());
		sort(vnew.begin(), vnew.end());
	
		vector<string> vis;
		vector<string> vplus;
		vector<string> vminus;
		vector<string> vchange;
		
		set_intersection(vold.begin(), vold.end(), vnew.begin(), vnew.end(), inserter(vis, vis.begin()));
		set_difference(vnew.begin(), vnew.end(), vis.begin(), vis.end(), inserter(vplus, vplus.begin()));
		set_difference(vold.begin(), vold.end(), vis.begin(), vis.end(), inserter(vminus, vminus.begin()));

		for (int i = 0; i < vis.size(); i++) {
			if (mold[vis[i]] != mnew[vis[i]])
				vchange.push_back(vis[i]);
		}


		bool nochange = true;
		if (!vplus.empty()) {
			nochange = false;
			cout << "+";
			for (int i = 0; i < vplus.size(); i++) {
				cout << vplus[i];
				if (i < vplus.size()-1)
					cout << ",";
			}
			cout << endl;
		}
		if (!vminus.empty()) {
			nochange = false;
			cout << "-";
			for (int i = 0; i < vminus.size(); i++) {
				cout << vminus[i];
				if (i < vminus.size()-1)
					cout << ",";
			}
			cout << endl;
		}
		if (!vchange.empty()) {
			nochange = false;
			cout << "*";
			for (int i = 0; i < vchange.size(); i++) {
				cout << vchange[i];
				if (i < vchange.size()-1)
					cout << ",";
			}
			cout << endl;
		}
		if (nochange)
			cout << "No changes\n";
		cout << endl;

		mold.clear();
		mnew.clear();
		vold.resize(0);
		vnew.resize(0);
		vis.resize(0);
		vplus.resize(0);
		vminus.resize(0);
		vchange.resize(0);
	}
	return 0;
}

void initstr(string& s) { // 替换非字母和数字字符为空格
	for (int i = 0; i < s.size(); i++)
		if (!isalnum(s[i]))
			s[i] = ' ';
}

// 把key和value放入map，把key放入vector
void initdict(string& s, map<string, string>& m, vector<string>& v) {
	stringstream ss(s);
	string key, value;
	while (ss >> key >> value) {
		m[key] = value;
		v.push_back(key);
	}
}

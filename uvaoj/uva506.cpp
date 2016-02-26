#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 100000;
vector<string> v;
map<string, int> m;
vector<int> dep[maxn];
vector<int> bedep[maxn];
vector<int> inlist;
int status[maxn];

void Depend(string& line) {
	cout << line << endl; stringstream ss(line); string str; ss >> str; ss >> str; 
	int id1, id2;
	if (!m.count(str)) {v.push_back(str); id1 = m[str] = v.size() - 1;}
	else id1 = m[str];
	while (ss >> str) {
		if (!m.count(str)) {v.push_back(str); id2 = m[str] = v.size() - 1;}
		else id2 = m[str];
		dep[id1].push_back(id2); bedep[id2].push_back(id1);
	}
}

void Install(int id) {
	for (int i = 0; i < dep[id].size(); i++) {
		if (status[dep[id][i]] == 0)
			Install(dep[id][i]);
	}
	status[id] = -1;
	inlist.push_back(id);
	cout << "   Installing " << v[id] << endl;
}

void Remove(int id) {
	bool isneed = false;
	for (int i = 0; i < bedep[id].size(); i++) {
		if (status[bedep[id][i]] != 0) {
			isneed = true; break;
		}
	}
	if (!isneed) {
		for (int i = 0; i < inlist.size(); i++) 
			if (inlist[i] == id) {
				inlist.erase(inlist.begin()+i);
				break;
			}
		status[id] = 0;
		cout << "   Removing "  << v[id] << endl;
		for (int i = 0; i < dep[id].size(); i++) {
			if (status[dep[id][i]] == -1)
				Remove(dep[id][i]);
		}
	}
}

void List(string& str) {
	cout << str << endl;
	for (int i = 0; i < inlist.size(); i++) {
		cout << "   " << v[inlist[i]] << endl;
	}
}

int main() {
	string str;
	memset(status, 0, sizeof(status));
	for(;;) {
		getline(cin, str);
		if (str[0] == 'E') {cout << str << endl; break;}
		else if (str[0] == 'D') Depend(str);
		else if (str[0] == 'I') {
			stringstream ss(str); string com; ss >> com; ss >> com;
			cout << str << endl;
			if (!m.count(com)) {
				v.push_back(com); int nid = m[com] = v.size() - 1;
				status[nid] = 1; inlist.push_back(nid);
				cout << "   Installing " << com << endl; continue;
			}
			int id = m[com];
			if (status[id] != 0) {
				cout << "   " << com << " is already installed.\n"; continue;
			}
			Install(id); status[id] = 1;
		}
		else if (str[0] == 'R') {
			stringstream ss(str); string com; ss >> com; ss >> com; 
			cout << str << endl;
			if (!m.count(com)) {cout << "   " << com << " is not installed.\n"; continue;}
			int id = m[com];
			if (status[id] == 0) {cout << "   " << com << " is not installed.\n"; continue;}
			bool isneed = false;
			for (int i = 0; i < bedep[id].size(); i++)
				if (status[bedep[id][i]] != 0) isneed = true;
			if (isneed) {cout << "   " << com << " is still needed.\n"; continue;}
			Remove(id);
		}
		else if (str[0] == 'L') List(str);
	}
	return 0;
}

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;

const int maxr = 10000 + 10;
const int maxc = 10 + 2;

int db[maxr][maxc];

int tran(const string& str, map<string, int>& ma, vector<string>& v);

int main() {
	int n, m;
	string str;
	while (getline(cin, str)) {
		memset(db, 0, sizeof(db));
		map<string, int> mp;
		vector<string> v;
		stringstream ss(str);
		ss >> n >> m;
		for (int i = 0; i < n; i++) {
			getline(cin, str);
			stringstream ss(str);
			for (int j = 0; j < m; j++) {
				getline(ss, str, ',');
				db[i][j] = tran(str, mp, v);				
			}
		}
		bool pnf = true;
		int r1, r2, c1, c2;
		for (c1 = 0; c1 < m-1; c1++) {
			for (c2 = c1+1; c2 < m; c2++) {
				vector<int> vm;
				vm.push_back(db[0][c1]);
				vm.push_back(db[0][c2]);
				map<vector<int>, int> mc;
				mc[vm] = 0;
				for (int r = 1; r < n; r++) {
					vm.clear();
					vm.push_back(db[r][c1]);
					vm.push_back(db[r][c2]);
					if (mc.count(vm)){
						r1 = mc[vm] + 1;
						r2 = r + 1;
						c1++;
						c2++;
						pnf = false;
						goto end;
					}
					mc[vm] = r;					
				}
			}
		}
		end:
		if (pnf) 
			cout << "YES" << endl;
		else 
			cout << "NO\n" << r1 << " " << r2 << "\n" << c1 << " " << c2 << endl;
	}	
	return 0;
}

int tran(const string& str, map<string, int>& mp, vector<string>& v) {
	if (mp.count(str)) 
		return mp[str];
	v.push_back(str);
	return mp[str] = v.size() - 1;
}

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAXN = 1000 + 10;

vector<string> v[MAXN];
int width[200];

int main() {
	int n = 0;
	string str;
	memset(width, 0, sizeof(width));
	while (getline(cin, str)) { 
		istringstream ss(str);
		string word;
		int m = 0;
		while (ss >> word) {
			if (word.length() > width[m])
				width[m] = word.length();
			v[n].push_back(word);
			m++;
		}
		n++;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < v[i].size()-1; j++) {
			cout << left << setw(width[j]+1) << v[i][j];
		}
		cout << left << v[i][v[i].size()-1];
		cout << endl;
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 30;
vector <int> pile[MAXN];
int n;
int posi[MAXN][2];

void back(int a);

bool issp(int a, int b) {
	return	(posi[a][0] == posi[b][0]);
}

void mon(int a, int b, string s) {
	back(a);
	if (s == "onto")
		back(b);
	pile[posi[a][0]].pop_back();
	posi[a][0] = posi[b][0];
	posi[a][1] = pile[posi[b][0]].size();
	pile[posi[a][0]].push_back(a);	
}

void pon(int a, int b, string s) {
	if (s == "onto")
		back(b);
	int col = posi[a][0];
	int begin = posi[a][1];
	int end = pile[col].size();
	for (int i = begin; i < end; i++) {
		int	value = pile[col][i];
		pile[posi[b][0]].push_back(value);
		posi[value][0] = posi[b][0];
		posi[value][1] = pile[posi[b][0]].size() - 1;
	}
	for (int i = begin; i < end; i++) {
		pile[col].pop_back();
	}
}

void back(int a) {
	int x = posi[a][0];
	int y;
	int high = pile[x].size();
	for (int i = 0; i < high; i++)
		if (pile[x][i] == a) {y = i; break;}
	for (int i = high - 1; i > y; i--) {
		int value = pile[x][i];
		pile[value].push_back(value);
		posi[value][0] = value;
		posi[value][1] = 0;
		pile[x].pop_back();
	}	
}

int main() {
	int a, b;
	string s1, s2;
	memset(posi, 0, sizeof(posi));
	cin >> n;
	for (int i = 0; i < n; i++) {pile[i].push_back(i); posi[i][0] = i;}
	while (cin >> s1) {
		if (s1 == "quit") break;
		cin >> a >> s2 >> b;
		if (a == b) continue;
		if (issp(a, b)) continue;
		if (s1 == "move")
			mon(a, b, s2);
		else
			pon(a, b, s2);
	}
	for (int i = 0; i < n; i++) {
		printf("%d:", i);
		int len = pile[i].size();
		for (int j = 0; j < len; j++)
			printf(" %d", pile[i][j]);	
		printf("\n");
	}
	return 0;
}

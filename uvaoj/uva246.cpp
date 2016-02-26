#include <cstdio>
#include <cstring>
#include <deque>
#include <vector>
#include <set>
using namespace std;
int pos[7], deal;
vector<deque<int> > pile;
set<vector<deque<int> > > vis;

bool check1(int pos) {
//	if (pile[pos].size() < 3) return false;
	int c1, c2, c3;
	c1 = pile[pos].front(); pile[pos].pop_front();
	c2 = pile[pos].front();
	c3 = pile[pos].back();
	int sum = c1 + c2 + c3;
	if (sum == 10 || sum == 20 || sum == 30) {
		pile[7].push_back(c1);
		pile[7].push_back(c2);
		pile[7].push_back(c3);
		pile[pos].pop_front();
		pile[pos].pop_back();
		return true;
	}
	else {
		pile[pos].push_front(c1);
		return false;
	}
}

bool check2(int pos) {
//	if (pile[pos].size() < 3) return false;
	int c1, c2, c3;
	c1 = pile[pos].front();
	c3 = pile[pos].back(); pile[pos].pop_back();
	c2 = pile[pos].back();
	int sum = c1 + c2 + c3;
	if (sum == 10 || sum == 20 || sum == 30) {
		pile[7].push_back(c1);
		pile[7].push_back(c2);
		pile[7].push_back(c3);
		pile[pos].pop_front();
		pile[pos].pop_back();
		return true;
	}
	else {
		pile[pos].push_back(c3);
		return false;
	}
}

bool check3(int pos) {
//	if (pile[pos].size() < 3) return false;
	int c1, c2, c3;
	c3 = pile[pos].back(); pile[pos].pop_back();
	c2 = pile[pos].back(); pile[pos].pop_back();
	c1 = pile[pos].back();
	int sum = c1 + c2 + c3;
	if (sum == 10 || sum == 20 || sum == 30) {
		pile[7].push_back(c1);
		pile[7].push_back(c2);
		pile[7].push_back(c3);
		pile[pos].pop_back();
		return true;
	}
	else {
		pile[pos].push_back(c2);
		pile[pos].push_back(c3);
		return false;
	}
}

int play() {
	for (int i = 0; i < 7; i++) {
		pile[i].push_back(pile[7].front()); pile[7].pop_front();
	}
	deal = 7; int p = 0;
	for (;;) {
		deal++; bool again = true;
		pile[p].push_back(pile[7].front()); pile[7].pop_front();
		while (again) {
			if (pile[p].size() < 3) break;
			if (check1(p)) continue;
			if (check2(p)) continue;
			if (check3(p)) continue;
			again = false;
		}
		if (pile[p].size() == 0) pos[p] = 0;
		p = (p+1) % 7;
		if (pile[7].size() == 52) return 1;
		if (pile[7].size() == 0) return -1;
		if (!vis.count(pile)) vis.insert(pile);
		else
			return 0;
		while(pos[p] == 0) p = (p+1) % 7;
	}
}

int main() {
	int num;
	while (scanf("%d", &num) == 1 && num != 0) {
		memset(pos, 1, sizeof(pos)); pile.clear(); vis.clear();
		for (int i = 0; i < 8; i++) pile.push_back(deque<int>());
		pile[7].push_back(num);
		for (int i = 1; i < 52; i++) {
			scanf("%d", &num) == 1;
			pile[7].push_back(num);
		}
		int ans = play();
		if (ans == 1) printf("Win : %d\n", deal);
		else if (ans == 0) printf("Draw: %d\n", deal);
		else if (ans == -1) printf("Loss: %d\n", deal);
	}
	return 0;
}

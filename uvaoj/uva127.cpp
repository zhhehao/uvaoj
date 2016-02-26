#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
const int maxn = 78 + 5;
char buf1[maxn], buf2[maxn];
struct Card {
	char v, s;
};
stack<Card> pile[52];
vector<int> vp;

void match() {
	Card card1, card2;
	for (int i = 1; i < vp.size(); i++) {
		card1.v = pile[vp[i]].top().v;
		card1.s = pile[vp[i]].top().s;
		if (i - 3 >= 0) {
			card2.v = pile[vp[i-3]].top().v;
			card2.s = pile[vp[i-3]].top().s;
			if (card1.s == card2.s || card1.v == card2.v) {
				pile[vp[i-3]].push(card1);
				pile[vp[i]].pop();
				if (pile[vp[i]].size() == 0) vp.erase(vp.begin()+i);
				i = 0; continue;
			}
		}
		if (i - 1 >= 0) {
			card2.v = pile[vp[i-1]].top().v;
			card2.s = pile[vp[i-1]].top().s;
			if (card1.s == card2.s || card1.v == card2.v) {
				pile[vp[i-1]].push(card1);
				pile[vp[i]].pop();
				if (pile[vp[i]].size() == 0) vp.erase(vp.begin()+i);
				i = 0; continue;
			}
		}
	}
}

int main() {
	for (;;) {
		fgets(buf1, 100, stdin); 
		if (buf1[0] == '#') break;
		fgets(buf2, 100, stdin);
		vp.clear();
		for (int i = 0; i < 52; i++) {
			while (!pile[i].empty()) pile[i].pop();
			vp.push_back(i);
		}
		Card card;
		for (int i = 0; i < 26; i++) {
			card.v = buf1[3*i];
			card.s = buf1[3*i+1];
			pile[i].push(card);
		}
		for (int i = 0; i < 26; i++) {
			card.v = buf2[3*i];
			card.s = buf2[3*i+1];
			pile[i+26].push(card);
		}
		match();
		if (vp.size() == 1) {printf("1 pile remaining: 52\n");continue;}
		else {
			printf("%d piles remaining:", vp.size());
			for (int i = 0; i < vp.size(); i++)
				printf(" %d", pile[vp[i]].size());
			printf("\n");
		}
	}
	return 0;
}

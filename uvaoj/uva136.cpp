#include <cstdio>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef long long LL;
set<LL> s;
priority_queue <LL, vector<LL>, greater<LL> > pq;

int main() {
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(5);
	pq.push(2);
	pq.push(3);
	pq.push(5);

	for (int i = 2;; i++) {	
		LL x = pq.top();
		pq.pop();
		if (i == 1500) {
			printf("The 1500'th ugly number is %lld.\n", x);
			break;
		}	
		LL x2, x3, x5;
		x2 = 2*x;
		x3 = 3*x;
		x5 = 5*x;
		if (!s.count(x2)) {s.insert(x2); pq.push(x2);}
		if (!s.count(x3)) {s.insert(x3); pq.push(x3);}
		if (!s.count(x5)) {s.insert(x5); pq.push(x5);}
	}
	return 0;
}

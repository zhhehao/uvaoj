#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

struct Es {
	int a, b;
	bool operator < (const Es& B) const {
		if (a < B.a)
			return true;
		else
			return false;
	}
};

int main() {
	int n;
	while ((cin >> n) && (n != 0)) {
		int a, b; 
		if (n % 2 != 0) { // n is odd, couldn't match.
			while (n--)
				cin >> a >> b;
			cout << "NO\n";
			continue;
		}
		Es est;
		set<Es> s;
		while (n--) {
			cin >> est.a >> est.b;
			if (est.a > est.b) swap(est.a, est.b);
			if (s.count(est))
				s.erase(s.find(est));
			else 
				s.insert(est);
		}
		if (s.size() == 0)
			cout << "YES\n";
		else
			cout << "NO\n";
		s.clear();
	}
	return 0;
}
